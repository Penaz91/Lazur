/* Implementazione User
 */
#include "User.h"
#include <iostream>

User::User(const std::string& name, const std::string& pass, std::list<MultimediaItem*>*& itemList): userName(name), passHash(pass), items(itemList){}

User::User(const std::string& name, const std::string& pass): userName(name), passHash(pass), items(0){}

//void User::setList(std::list<MultimediaItem*>*& item){
	//items=item;
//}

std::vector<MultimediaItem*> User::search(const std::string& dove, const std::string& cosa) const{
	std::list<MultimediaItem*>::const_iterator it = items->begin();
	std::vector<MultimediaItem*> results;
	for (; it != items->end(); it++){
		MultimediaItem* item = (*it)->search(dove, cosa);
		if (item)
			results.push_back(item);
	}
	return results;
}

//User::~User(){}

std::string User::getUser() const{
	return userName;
}

std::string User::getPass() const{
	return passHash;
}

std::string User::getType() const{
	return "User";
}

bool User::operator==(const User& other) const{
	return userName == other.userName && passHash == other.passHash;

}
