/*
Header Classe concreta Software
*/
#ifndef SOFTWARE_H
#define SOFTWARE_H

#include"MultimediaItem.h"
#include<iostream>

class Software: public MultimediaItem{
  private:
    std::string developer;
    std::string OS;
    static bool has_dev(const Software&, const std::string&);
    static bool has_os(const Software&, const std::string&);
    static std::map<std::string, bool (*)(const Software&, const std::string&)> searchMap;
  public:
    std::string getDeveloper() const;
    std::string getOS() const;
    // Di Default il costruttore ha il set di Sistemi operativi a vuoto (C++11)
    Software(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, int);
    virtual const std::map<std::string, std::string> readInfo() const;
    virtual void get() override;
    MultimediaItem* search(const std::string&, const std::string&);
    virtual bool operator==(const Software&);
    virtual ~Software()=default;
};

#endif
