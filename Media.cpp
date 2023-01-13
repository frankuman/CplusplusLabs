#include "Media.hpp"

Media::Media() 
//konstruktor
	:title("?")
{
}

Media::Media(const std::string& title) 
//standard copykonstruktor
	:title(title)
{
}

Media::~Media() 
//destruktor
{
}

const std::string& Media::getTitle() const
{
	return title;
}

std::string Media::prettyPrint() const
{
	return "Title: " + title;
}

bool Media::operator==(const Media& other) const
{
	return this->title == other.title;
}

bool Media::operator!=(const Media& other) const
{
	return !(this->title == other.title);
}
