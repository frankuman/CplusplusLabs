#ifndef MediaManager_hpp
#define MediaManager_hpp
#include "Ps2Game.hpp"
#include "Book.hpp"
#include "Media.hpp"
#include <string>
#include <iostream>
using namespace std;
//?
class MediaManager{
private:
	Media* *arr;
	Book* book_in_array;
	Ps2Game* game_in_array;
	size_t size;
	int nrOfBooks;
	int nrOfPs2Games;
	int nrOfMedias;

public:
	MediaManager(size_t size);
	MediaManager(const MediaManager& other);
	~MediaManager();
	void addMedia(Media* media);
	void addBook(const Book& book);
	void addPs2Game(const Ps2Game& game);
	std::string printMedia() const;
	void getBooks(Book*& out_array, int& out_bookCount) const;
	void getPs2Games(Ps2Game*& out_array, int& out_gameCount) const;
	Media** getMedias() const;
	bool operator==(const MediaManager& other) const;
	bool operator!=(const MediaManager& other) const;

};
#endif
/*
    TODO:
    1. Add include guard
    2. Define the class 'MediaManager'
    3. Declare necessary members
    4. Define member functions in MediaManager.cpp
*/