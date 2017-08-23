/*
Classe derivata da Editor per rappresentare un developer
*/

#ifndef DEVELOPER_H
#define DEVELOPER_H

#include<iostream>
#include<algorithm>
#include "Editor.h"
#include "../DataStructs/Software.h"
class Developer: public Editor{
	public:
		Developer(const std::string&, const std::string&, std::list<MultimediaItem*>*&);
		Developer(const std::string&, const std::string&);
		/* Uso la keyword di C++11 "Override" per assicurarmi che sto facendo override di metodi*/
		virtual void add(MultimediaItem*) const override;
		virtual void remove(MultimediaItem*) const override;
		virtual void replace(MultimediaItem*, MultimediaItem*) const override;
		std::string getType() const override;
		bool hasPermission(MultimediaItem*) const override;
		//Distruttore Virtuale ereditato da User, non avendo campi che necessitano di particolare attenzione
};

#endif
