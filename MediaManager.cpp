#include "MediaManager.hpp"

// TODO

MediaManager::MediaManager(size_t size)
	:size(size), nrOfMedias(0), nrOfBooks(0), nrOfPs2Games(0), arr(NULL)
{
	//this->nrOfMedias = size;
	//Book* aBookPtr = nullptr;
	//Ps2Game* aPs2Ptr = nullptr;
	this->arr = new Media * [this->size]{ nullptr };
}

MediaManager::MediaManager(const MediaManager& other) //deepcopy
	:size(other.size), nrOfMedias(other.nrOfMedias), nrOfBooks(other.nrOfBooks), nrOfPs2Games(other.nrOfPs2Games), arr(arr)
{
	//this->arr = new Media * [other.size]{nullptr};
	//for (int i = 0; i < other.size; i++) {
	//	this->arr[i](other.arr[i]);
	//}
	this->arr = new Media * [other.size]{ nullptr };
	Book* aBookPtr = nullptr;
	for (int i = 0; i < other.nrOfBooks + other.nrOfPs2Games; i++) {
		aBookPtr = dynamic_cast<Book*>(other.arr[i]);
		if (aBookPtr != nullptr) {
			this->arr[i] = new Book(*aBookPtr);
		}

	}

	Ps2Game* aPs2Ptr = nullptr;
	for (int i = 0; i < other.nrOfPs2Games + other.nrOfBooks; i++) {
		aPs2Ptr = dynamic_cast<Ps2Game*>(other.arr[i]);
		if (aPs2Ptr != nullptr) {
			this->arr[i] = new Ps2Game(*aPs2Ptr);
		}
	}
}

MediaManager::~MediaManager()
{
	
	//for (int i = 0; i < size; i++) {
	//	if (arr[i] != nullptr){
	//		delete arr[i];
	//		arr[i] = nullptr;
	//	}
	//}
	//size = NULL;
	//nrOfBooks = NULL;
	//nrOfPs2Games = NULL;
	//nrOfMedias = NULL;
	//delete[] arr;

	if (this->arr[0] != nullptr) {
		for (int i = 0; i < this->size; i++) {
			if (this->arr[i] != nullptr) {
				delete this->arr[i];
				this->arr[i] = nullptr;
			}
		}
		delete[]this->arr;
	}

}

void MediaManager::addMedia(Media* media) //Använder dynamiccast (som allt annat typ) för att kolla vilka objekt som ska var
{
	Book* aBookPtr = nullptr;
	aBookPtr = dynamic_cast<Book*>(media);
	if (aBookPtr != nullptr) {
		this->addBook(*aBookPtr);
	}

	Ps2Game* aPs2Ptr = nullptr;
	aPs2Ptr = dynamic_cast<Ps2Game*>(media);
	if (aPs2Ptr != nullptr) {
		this->addPs2Game(*aPs2Ptr);
	}
	
}

void MediaManager::addBook(const Book& book) //Skapar en kopia av ett givet bokobjekt och sparar en pekare till kopian i den interna media-arrayen
{

	this->nrOfBooks++;
	this->arr[this->nrOfMedias++] = new Book(book);
	
}

void MediaManager::addPs2Game(const Ps2Game& game)
{
	this->nrOfPs2Games++;
	this->arr[this->nrOfMedias++] = new Ps2Game(game);
	
}

std::string MediaManager::printMedia() const //Gör en fin print
{
	string formatedString = "------MediaManager------\n";
	formatedString = formatedString + "\n" + "Capacity: " + to_string(this->size) + "\n" + "Books: " + to_string(this->nrOfBooks) + "\n" + "Ps2Games: " + to_string(this->nrOfPs2Games) + "\n";
	formatedString = formatedString + "\n" + "------Books------" + "\n" + "\n";

	Book* aBookPtr = nullptr;
	for (int i = 0; i < this->nrOfBooks + this->nrOfPs2Games; i++) {
		aBookPtr = dynamic_cast<Book *>(this->arr[i]);
		if (aBookPtr != nullptr) {
			
			formatedString = formatedString + aBookPtr->prettyPrint() + "\n" + "\n";
		}
	
	}
	formatedString = formatedString + "------Ps2Games------" + "\n" + "\n";
	Ps2Game* aPs2Ptr = nullptr;
	for (int i = 0; i < this->nrOfPs2Games + this->nrOfBooks; i++) {
		aPs2Ptr = dynamic_cast<Ps2Game *>(this->arr[i]);
		if (aPs2Ptr != nullptr) {
			formatedString = formatedString + aPs2Ptr->prettyPrint() + "\n" + "\n";
		}
	}
	
	Media* aMediaPtr = nullptr;
	for (int i = 0; i < this->nrOfMedias; i++) {
		aMediaPtr = dynamic_cast<Media*> (this->arr[i]);
		if (aMediaPtr != nullptr) {
			formatedString = formatedString + aMediaPtr->prettyPrint() + "\n" + "\n";
		}
	}
	return formatedString;
}

void MediaManager::getBooks(Book*& out_array, int& out_bookCount) const //Gör vår fina array för böcker
{
	
	if (this->nrOfBooks != 0){
		Book* book_in_array = new Book[this->nrOfBooks];
		Book* aBookPtr = nullptr;
		for (int i = 0; i < this->nrOfBooks; i++) {
			aBookPtr = dynamic_cast<Book*>(this->arr[i]);
			if (aBookPtr != nullptr) {
				book_in_array[i] = *aBookPtr;
			}

		}
		
		
		out_array = book_in_array;
		out_bookCount = this->nrOfBooks;
		
	}
	else {
		out_bookCount = 0;
	}
}
void MediaManager::getPs2Games(Ps2Game*& out_array, int& out_gameCount) const //Gör våran fina array för spel
{
	
	if (this->nrOfPs2Games != 0) {
		Ps2Game* games_in_array = new Ps2Game[this->nrOfPs2Games];
		Ps2Game* aPs2Ptr = nullptr;
		for (int i = 0; i < this->nrOfPs2Games; i++) {
			aPs2Ptr = dynamic_cast<Ps2Game*>(this->arr[i]);
			if (aPs2Ptr != nullptr) {
				games_in_array[i] = *aPs2Ptr;
			}

		}
		
		out_array = games_in_array;
		out_gameCount = this->nrOfPs2Games;
	
	}
	else {
		out_gameCount = 0;
	}
	//Ps2Game* in_array = new Ps2Game[this->nrOfPs2Games];
	//Ps2Game* aPs2Ptr = nullptr;
	//for (int i = 0; i < this->nrOfBooks + this->nrOfPs2Games; i++) {
	//	aPs2Ptr = dynamic_cast<Ps2Game*>(this->arr[i]);
	//	if (aPs2Ptr != nullptr) {
	//		in_array[i] = *aPs2Ptr;
	//	}

	//}
	//out_array = in_array;
	//out_gameCount = this->nrOfPs2Games;

}

Media** MediaManager::getMedias() const
{
	Media** arr_pointer;
	arr_pointer = this->arr;
	return arr_pointer;
}

bool MediaManager::operator==(const MediaManager& other) const
{

	for (int i = 0; i < this->nrOfMedias; i++) {
		if (this->arr[i]->operator!=(*other.arr[i])) {
			return false;
		}
		else if (this->arr[i]->title != other.arr[i]->title) {
			return false;
		}
	}
	
	return true;

}
bool MediaManager::operator!=(const MediaManager& other) const //Jag vet faktiskt inte hur jag fick denna att funka annorlunda mot ==operatorn
{
	for (int i = 0; i < this->nrOfMedias; i++) {
		if (this->arr[i] != other.arr[i]) {
			return true;
		}
		if (this->arr[i]->getTitle() != other.arr[i]->getTitle()) {
			return true;
		}
	}
	return false;
}
