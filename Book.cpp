#include "Book.hpp"
// KLAR
Book::Book()
	:Media(), author("?"), isbn("?"), pages(0), edition(0)
{
}

Book::Book(const std::string& title, const std::string& author, const std::string& isbn, int pages, int edition)
	:Media(title), author(author), isbn(isbn), pages(pages), edition(edition)
{
}

Book::Book(const Book& other)
	:Media(other.title), author(other.author), isbn(other.isbn), pages(other.pages), edition(other.edition)
{
}

Book::~Book()
{
	
}

Book& Book::operator=(const Book& other) //copykonstruktor
{
	if (this != &other) {
		author = other.author;
		title = other.title;
		isbn = other.isbn;
		pages = other.pages;
		edition = other.edition;
	}
	return *this;
}


const std::string& Book::getAuthor() const
{
	return this->author;
}

const std::string& Book::getIsbn() const
{
	return this->isbn;
}

int Book::getPages() const
{
	return this->pages;
}

int Book::getEdition() const
{
	return this->edition;
}

bool Book::operator==(const Book& other) const
{
	return (this->title == other.title && this->author == other.author && this->isbn == other.isbn && this->pages == other.pages && this->edition == other.edition);
}

bool Book::operator!=(const Book& other) const
{
	return (this->title != other.title || this->author != other.author || this->isbn != other.isbn || this->pages != other.pages || this->edition != other.edition);
}

std::string Book::prettyPrint() const
{
	return Media::prettyPrint() + "\nAuthor(s): " + this->author + "\nISBN: " + this->isbn + "\nPages: " + std::to_string(this->pages) + "\nEdition: " + std::to_string(this->edition);
}

bool Book::operator==(const Media& other) const //Detta funkade bäst och på alla scenarion.
{
	return (this->prettyPrint() == other.prettyPrint());
}

bool Book::operator!=(const Media& other) const
{
	return !(this->prettyPrint() == other.prettyPrint());
}
