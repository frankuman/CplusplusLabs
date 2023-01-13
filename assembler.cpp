#include "assembler.hpp"
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

const int FLAG_EQUAL_TO = 1;
const int FLAG_GREATER_THAN = 2;
const int FLAG_LESS_THAN = 3;


int GetRegIndex(string reg) { //Denna funktion ska ta in t.ex #5 och ge tillbaka 5. 
	//Jag g�r detta genom att g�ra en substring fr�n position 1 till slutet, sen g�r jag om stringen till en int
	int number = 0;
	string new_source = reg.substr(1, reg.length() - 1);
	stringstream ss;
	ss << new_source;
	ss >> number;
	return(number);
}
int GetConstant(string const_source) { //Denna funktion ska ta in t.ex R5 och ge tillbaka 5
	//G�rs p� samma s�tt som GetRegIndex
	int number;
	string new_source = const_source.substr(1,const_source.length() - 1);
	stringstream ss;
	ss << new_source;
	ss >> number;
	return(number);
}
char IsReg(string term) { //Return true om parametern p� index 0 == 'R', annars false
	if (term[0] == 'R') {
		return(true);
	}
	else {
		return(false);
	}
}
int ExtractValue(string source, int* registers) { //Egentligen bara kopierad fr�n python. MEn den �ndrar registers lite
	if (IsReg(source)) {
		return(registers[GetRegIndex(source)]);
	}
	return(GetConstant(source));
}
bool BuildCommandList(std::vector<std::vector<std::string>>& commandList, std::string filepath) { //Viktigaste funktionen som g�r v�ran kommandolista
	commandList.clear();
	vector<string> lineParts;
	vector<string> labelNames;
	vector<string> labelRows;
	ifstream ifs;
	ifs.open(filepath);
	if (ifs.is_open()) {               //�ppnar asm filen (eller vilken fil som helst)
		string line;
		int i = 0;
		while (getline(ifs, line)) {  //Pythonprogrammet g�r en ny lista av textfilen genom att g�ra om newlines till space och sen splitta. Detta ska fungera p� samma s�tt. 

			
			if (line.length() != 0) { //Detta  nedan beh�vdes lite omskrivningar innan de blir korrekt.
				char y = ':';		  //Vi vill hitta alla ':' i texten som h�mtas fr�n filen
				string buffer;		  //och sedan ta bort dem
				stringstream ss(line);
				while (ss >> buffer) {
					lineParts.push_back(buffer); //Vi l�gger in alla textrader i vektorn lineParts s� den ser ut kanske s�h�r [CMD, R0, R1]
				}
				if (lineParts[0][lineParts[0].size() - 1] == y){ 
					lineParts[0] = lineParts[0].substr(0,lineParts[0].size() - 1);
					labelNames.push_back(lineParts[0]);
					string item;
					stringstream ss;
					int intitem = commandList.size();
					ss << intitem;
					ss >> item;

					labelRows.push_back(item);
					lineParts.clear(); //Vi rensar vektorn s� vi kan s�tta in nya v�rden s� den kan kolla p� [0][0] igen
				}
				else {
					commandList.push_back(lineParts);
					lineParts.clear();
				}
			}
		
		}

		ifs.close();
	}
	else {
		return(false);
	}
	string MOV1 = "MOV"; //Som sagt i main.cpp, detta �r f�rmodligen on�digt
	string ADD1 = "ADD";
	string SUB1 = "SUB";
	string CMP1 = "CMP";
	string JEQ1 = "JEQ";
	string JGT1 = "JGT";
	string JLT1 = "JLT";

	for (int i = 0; i < commandList.size(); i++) { //H�r letar vi efter viktiga commands. Vi b�rjar med att iterera genom listan
		if (commandList[i][0] == JEQ1 || commandList[i][0] == JGT1 || commandList[i][0] == JLT1) { //commandList[i][0] �r samma sak som command[0]. Det blir en liknande iteration
			int index = -1;
			for (int p = 0; p < labelNames.size(); p++) { //Vi itererar genom vektorn i vektorn
				if (labelNames[p] == commandList[i][1]) { 
					index = p;
				}
			}
			if (index == -1) {
				commandList[i][1] = labelRows[labelRows.size()-1];
			}
			else {
				commandList[i][1] = labelRows[index];
			}
		}
	}
	return(true);
}//Restan nedan �r n�stan kopierat fr�n pythonprogrammet, det �r inte s� mycket �ndrat
int PeekNextCommandIndex(int* registers) {
	return(registers[REGISTER_SIZE - 1]);
	}
int GetAndStepCommandIndex(int* registers) {
	int index = registers[REGISTER_SIZE - 1];
	registers[REGISTER_SIZE - 1] += 1;
	return(index);
}
void MOV(std::vector<std::string>& command, int* registers){
	int destIndex = GetRegIndex(command[1]);
	int value = ExtractValue(command[2], registers);
	registers[destIndex] = value;
	
}
void ADD(std::vector<std::string>& command, int* registers) {
	int destIndex = GetRegIndex(command[1]);
	int term1 = ExtractValue(command[2], registers);
	int term2 = ExtractValue(command[3], registers);
	registers[destIndex] = term1 + term2;
}
void SUB(std::vector<std::string>& command, int* registers) {
	int destIndex = GetRegIndex(command[1]);
	int term1 = ExtractValue(command[2], registers);
	int term2 = ExtractValue(command[3], registers);
	registers[destIndex] = term1 - term2;
}
void CMP(std::vector<std::string>& command, int* registers) {
	int value1 = ExtractValue(command[1], registers);
	int value2 = ExtractValue(command[2], registers);

	if (value1 == value2) {
		registers[REGISTER_SIZE - 2] = FLAG_EQUAL_TO;
	}
	else if (value1 > value2) {
		registers[REGISTER_SIZE - 2] = FLAG_GREATER_THAN;
	}
	else {
		registers[REGISTER_SIZE - 2] = FLAG_LESS_THAN;
	}
}
void JEQ(std::vector<std::string>& command, int* registers) {

	if (registers[REGISTER_SIZE - 2] == FLAG_EQUAL_TO) {
		int command1;
		stringstream ss;
		ss << command[1];
		ss >> command1;
		registers[REGISTER_SIZE - 1] = command1;
	}
}
void JGT(std::vector<std::string>& command, int* registers) {
	if (registers[REGISTER_SIZE - 2] == FLAG_GREATER_THAN) {
		int command1;
		stringstream ss;
		ss << command.at(1);
		ss >> command1;
		registers[REGISTER_SIZE - 1] = command1;
	}

}
void JLT(std::vector<std::string>& command, int* registers) {
	if (registers[REGISTER_SIZE - 2] == FLAG_LESS_THAN) {
		int command1;
		stringstream ss;
		ss << command[1];
		ss >> command1;
		registers[REGISTER_SIZE - 1] = command1;
	}
}