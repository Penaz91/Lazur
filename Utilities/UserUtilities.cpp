/* Implementazione UserUtilities */

#include "UserUtilities.h"

class User;

User* UserUtilities::findUser(std::list<User*>* list, const std::string& name){
	//std::cout<<"List passato vuoto? "<<(list==0)<<std::endl;
	std::list<User*>::const_iterator it = list->begin();
	//std::cout << "Iteratore Costruito" << std::endl;
	for (; it != list->end(); it++){
		if ((*it)->getUser() == name){
			return (*it);
		}
	}
	return 0;
}
