/*
Header Classe Derivata Videogame
*/
#ifndef VIDEOGAME_H
#define VIDEOGAME_H

#include<iostream>
#include"Video.h"
#include<unordered_set>

class Videogame: public Software{
  private:
    std::string publisher;
    std::string genre;
    underdered_set<std::string> tags;
  public:
    /*
    std::string getPublisher() const;
    std::string getGenre() const;
    unordered_set<std::string> getTags() const;
    */
    Videogame();
    Videogame(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const unordered_set&<std::string>)
    virtual std::string readInfo() const;
    //get() ereditato da software
};
#endif
