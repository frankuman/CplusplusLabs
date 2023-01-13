#pragma once
#include <Media.hpp>
#include <string>
//klar?

class Ps2Game : public Media {
private:
    std::string studio;
    int year;

public:
    Ps2Game();
    Ps2Game(const std::string& title, const std::string& studio, int year);
    Ps2Game(const Ps2Game& other);
    virtual ~Ps2Game();
    Ps2Game& operator=(const Ps2Game& other);
    const std::string& getStudio() const;
    int getYear() const;
    bool operator==(const Ps2Game& other) const;
    bool operator!=(const Ps2Game& other) const;
    virtual std::string prettyPrint() const;
    virtual bool operator==(const Media& other) const;
    virtual bool operator!=(const Media& other) const;
};
/*
    TODO:
    1. Add include guard
    2. Define the class 'Ps2Game'
    3. Declare necessary members
    4. Define member functions in Ps2Game.cpp
*/