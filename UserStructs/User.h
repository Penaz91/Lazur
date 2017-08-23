/*
Classe Base della gerarchia Utenti - concreta
*/
#ifndef USER_H
#define USER_H

#include<iostream>
#include<vector>
#include<list>
#include"../DataStructs/MultimediaItem.h"

class User{
  protected:
	std::string userName;
	std::string passHash;  //Se ho tempo farò l'hash della password
	std::list<MultimediaItem*>* items;
  public:
	std::string getUser() const;
	std::string getPass() const;
	/* Per quanto insensato possa sembrare, questa funzione mi risparmia una sequenza
	 * potenzialmente illimitata di if(dynamic_cast...)/if(typeid()) nella serializzazione,
	 * penso valga la pena di creare una stringa temporanea anonima come tradeoff*/
	virtual std::string getType() const;
	//--------------------------------------------------
	User(const std::string&, const std::string&, std::list<MultimediaItem*>*&);
	User(const std::string&, const std::string&);
	//void setList(std::list<MultimediaItem*>*&);
	std::vector<MultimediaItem*> search(const std::string&, const std::string&) const;
	virtual bool operator==(const User&) const;
	virtual ~User()=default;
};

#endif
