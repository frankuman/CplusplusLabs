#ifndef BOOK
#define BOOK
#include "Media.hpp"
#include <string>
#include <iostream>
class Book : public Media {
private:
    std::string author;
    std::string isbn;
    int pages;
    int edition;
public:
    Book();
    Book(const std::string& title, const std::string& author, const std::string& isbn, int pages, int edition);
    Book(const Book& other);
    virtual ~Book();
    Book& operator=(const Book& other);
    const std::string& getAuthor() const;
    const std::string& getIsbn() const;
    int getPages() const;
    int getEdition() const;
    bool operator==(const Book& other) const;
    bool operator!=(const Book& other) const;
    virtual std::string prettyPrint() const;
    virtual bool operator==(const Media& other) const;
    virtual bool operator!=(const Media& other) const;



};
#endif
/*
    TODO:
    1. Add include guard
    2. Define the class 'Book'
    3. Declare necessary members
    4. Define member functions in Book.cpp
*/