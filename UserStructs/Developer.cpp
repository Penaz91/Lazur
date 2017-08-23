/* Implementazione di Developer*/
#include "Developer.h"
#include <iostream>

class Software;

Developer::Developer(const std::string& name, const std::string& pass, std::list<MultimediaItem*>*& itemList): Editor(name, pass, itemList){}

Developer::Developer(const std::string& name, const std::string& pass): Editor(name, pass){}

void Developer::add(MultimediaItem* item) const{
	if (hasPermission(item)){
		//ItemUtilities::addItem(items, item);
		items->push_back(item);
	}else{
		throw("Non puoi creare software per conto di qualcun'altro, contatta l'amministratore");
	}
}

void Developer::remove(MultimediaItem* item) const{
	if (hasPermission(item)){
		//ItemUtilities::removeItem(items, item);
		items->remove(item);
		delete item;
	}
}

void Developer::replace(MultimediaItem* one, MultimediaItem* other) const{
	if (!hasPermission(other)){
		throw("Non puoi assegnare un tuo software a qualcun'altro, contatta l'amministratore");
	}
	if (hasPermission(one)){
		//ItemUtilities::replaceItem(items, one, other);
		std::replace(items->begin(), items->end(), one, other);
		delete one;
	}
}

std::string Developer::getType() const{
	return "Developer";
}

bool Developer::hasPermission(MultimediaItem* item) const{
	auto x = dynamic_cast<Software*>(item);
	if (x){
		return userName == x->getDeveloper();
	}
	return false;
}
