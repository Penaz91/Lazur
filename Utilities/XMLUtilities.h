#include "../UserStructs/User.h"
#include "../UserStructs/Admin.h"
#include "../UserStructs/Developer.h"
#include "../DataStructs/Software.h"
#include "../DataStructs/Video.h"
#include "../DataStructs/MultimediaItem.h"
#include <list>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#ifndef XMLUTILITIES_H
#define XMLUTILITIES_H

namespace XMLUtilities{
	User* gatherUser(QXmlStreamReader&, std::list<User*>*&, std::list<MultimediaItem*>*);
	std::list<User*>* loadUserList(std::list<MultimediaItem*>*);
	void saveUserList(const std::list<User*>*);
	std::list<MultimediaItem*>* loadItemsList();
	void saveItemsList(const std::list<MultimediaItem*>*);
	MultimediaItem* gatherItem(QXmlStreamReader&);
}
#endif
