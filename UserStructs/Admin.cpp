/*
 * Implementazione Admin
 */

#include "Admin.h"
#include "../DataStructs/MultimediaItem.h"

class Editor;

void Admin::add(MultimediaItem* item) const{
	//ItemUtilities::addItem(items, item);
	items->push_back(item);
}

void Admin::remove(MultimediaItem* item) const{
	//ItemUtilities::removeItem(items, item);
	items->remove(item);
	delete item;
}

void Admin::replace(MultimediaItem* one, MultimediaItem* other) const{
	//ItemUtilities::replaceItem(items, one, other);
	std::replace(items->begin(), items->end(), one, other);
	delete one;
}

void Admin::addUser(User* user) const{
	//UserUtilities::pushUser(userList, user);
	userList->push_back(user);
	XMLUtilities::saveUserList(userList);
}

void Admin::removeUser(User* user){
	//UserUtilities::popUser(userList, user);
	userList->remove(user);
	delete user;
	XMLUtilities::saveUserList(userList);
}

void Admin::replaceUser(User* one, User* other) const{
	//userList->remove(one);
	//userList->push_back(other);
	std::replace(userList->begin(), userList->end(), one, other);
	delete one;
	XMLUtilities::saveUserList(userList);
}

Admin::Admin(const std::string& name, const std::string& pass, std::list<MultimediaItem*>*& itemList, std::list<User*>*& users): Editor(name, pass, itemList), userList(users){}

Admin::Admin(const std::string& name, const std::string& pass, std::list<User*>*& users): Editor(name, pass), userList(users){}

Admin::Admin(const std::string& name, const std::string& pass): Editor(name, pass){}

std::string Admin::getType() const{
	return "Admin";
}

bool Admin::hasPermission(MultimediaItem*) const{
	return true;
}
