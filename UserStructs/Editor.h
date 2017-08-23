/*
Classe derivata astratta Editor
*/
#ifndef EDITOR_H
#define EDITOR_H

#include "../DataStructs/MultimediaItem.h"
#include "User.h"

class Editor: public User{
	public:
		Editor(const std::string&, const std::string&, std::list<MultimediaItem*>*&);
		Editor(const std::string&, const std::string&);
		virtual void add(MultimediaItem*) const = 0;
		virtual void remove(MultimediaItem*) const = 0;
		virtual void replace(MultimediaItem*, MultimediaItem*) const = 0;
		virtual bool hasPermission(MultimediaItem*) const = 0;
};

#endif
