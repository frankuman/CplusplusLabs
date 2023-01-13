#include "Ps2Game.hpp"

// KLAR?

Ps2Game::Ps2Game()
	:Media(), studio("?"), year(0)
{
}

Ps2Game::Ps2Game(const std::string& title, const std::string& studio, int year)
	:Media(title), studio(studio), year(year)
{
}

Ps2Game::Ps2Game(const Ps2Game& other)
	:Ps2Game(other.title, other.studio, other.year)
{
}

Ps2Game::~Ps2Game()
{

}

Ps2Game& Ps2Game::operator=(const Ps2Game& other)
{
	if (this != &other) { //enligt destruktorn
		//"Rensa" listan :)
		studio = other.studio;
		title = other.title;
		year = other.year;
	}
	return *this;
}

const std::string& Ps2Game::getStudio() const
{
	return this->studio;
}

int Ps2Game::getYear() const
{
	return this->year;
}

bool Ps2Game::operator==(const Ps2Game& other) const
{
	return (this->title == other.title && this->studio == other.studio && this->year == other.year);
}	

bool Ps2Game::operator!=(const Ps2Game& other) const
{
	return !(this->title == other.title && this->studio == other.studio && this->year == other.year);
}

std::string Ps2Game::prettyPrint() const
{
	return Media::prettyPrint() + "\nStudio: " + this->studio + "\nYear: " + std::to_string(this->year);
}

bool Ps2Game::operator==(const Media& other) const
{
	return (this->prettyPrint() == other.prettyPrint());
}

bool Ps2Game::operator!=(const Media& other) const
{
	return !(this->prettyPrint() == other.prettyPrint());
}
