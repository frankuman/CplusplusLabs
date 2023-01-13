#include <iostream>
#include "assembler.hpp"
#include <string>
#include <vector>
#include <sstream>

using namespace std;
//Oliver Bölin
int main()
{	
	
	
	string tmp_word;
	//Detta behöver förmodligen inte göras. Gjorde det när jag hade problem med jämnförelse-operatorer
	string run = "run";
	string exit = "exit";
	string MOV1 = "MOV";
	string ADD1 = "ADD";
	string SUB1 = "SUB";
	string CMP1 = "CMP";
	string JEQ1 = "JEQ";
	string JGT1 = "JGT";
	string JLT1 = "JLT";

	bool running = true;

	//Programmets while-loop
	while (running && cin.good()){ 
		string input;
		vector<string> list;

		cout << "> ";
		getline(cin, input);
		
		istringstream ss(input);
		while (ss >> tmp_word) { //gör listan 
			list.push_back(tmp_word);
		}
		

		
		if (list.at(0) == run && list.size() > 1 && list.size() <= REGISTER_SIZE + 2) {
			
			int registers[REGISTER_SIZE] = { 0 };

			for (int i = 2; i <= list.size() - 1; i++) { ////Gör om listan från -string- till -int-, känns som det finns ett bättre sätt
				int num;
				string current_word = list.at(i);
				stringstream ss;
				ss << current_word;
				ss >> num;
				registers[i - 2] = num;
			}

			vector<std::vector<std::string>> commandList;
			if (BuildCommandList(commandList, list.at(1)) == false) { //Ifall våran funktion blir false, visa error
				cout << "Error: Could not open file " << list.at(1) << ". Try again." << endl;
			}
			else {
				
				while (PeekNextCommandIndex(registers) < commandList.size()) { //Här nedan är det näst intill kopierat från pythonprogrammet
	
					vector command = commandList[GetAndStepCommandIndex(registers)];
				
					if (command.at(0) == MOV1) {
						MOV(command, registers);
					}
					else if (command.at(0) == ADD1) {
						ADD(command, registers);
					}
					else if (command.at(0) == SUB1) {
						SUB(command, registers);
					}
					else if (command.at(0) == CMP1) {
						CMP(command, registers);
					}
					else if (command.at(0) == JEQ1) {
						JEQ(command, registers);
					}
					else if (command.at(0) == JGT1) {
						JGT(command, registers);
					}
					else if (command.at(0) == JLT1) {
						JLT(command, registers);
					}
				}

				
				for (int i = 0; i < REGISTER_SIZE; i++) {
					cout << registers[i] << " ";

				}
				cout << endl;
			}
		}
		else if (list.at(0) == exit) {
			cout << "Goodbye!" << endl;
			running = false;
		}
		else {
			cout << "Error: Invalid command or number of arguments. Try again." << endl;
			cout << "---------------------------------------------------" << endl;
			cout << "Available commands:\n" << endl;
			cout << "> run program.asm (R0) (R1) ... (R7)" << endl;
			cout << "\tExecutes a program where 'program.asm' is the name" << endl;
			cout << "\tof the assembly file and (R0), (R1), ... (R7) is" << endl;
			cout << "\tthe optional initial values for the registers R0," << endl;
			cout << "\tR1, ... R7." << endl;
			cout << "> exit" << endl;
			cout << "\tCloses the application."<< endl;
			cout << "---------------------------------------------------" << endl;
		}
	}
		
	system("pause");
	return 0;
}