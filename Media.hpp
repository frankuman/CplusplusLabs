#ifndef MEDIA
#define MEDIA
#pragma once
#include <string>
//KLAR?
class Media {

public:
    std::string title;
    Media(); 
    //Initierar objektet med basvärden
    Media(const std::string& title);
    virtual ~Media();
    virtual const std::string& getTitle() const;
    virtual std::string prettyPrint() const = 0;
    virtual bool operator ==(const Media& other) const;
    virtual bool operator !=(const Media& other) const;
};
#endif
/*
    TODO:
    1. Add include guard
    2. Define the class 'Media'
    3. Declare necessary members
    4. Define member functions in Media.cpp
*/