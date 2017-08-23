#include <iostream>
#include "Software.h"

class unordered_set;

std::map<std::string, bool (*)(const Software&, const std::string&)> Software::searchMap = {{"developer", &has_dev}, {"OS", &has_os}};

bool Software::has_dev(const Software& i, const std::string& value){
	//return i.developer == value;
	return (i.developer.find(value)!=std::string::npos);
}

bool Software::has_os(const Software& i, const std::string& value){
	//return i.OS==value;
	return (i.OS.find(value)!=std::string::npos);
}

//Software::Software(){}

Software::Software(const std::string& n, const std::string& l, const std::string& d, const std::string& dev, const std::string& so, int hits): MultimediaItem(n, l, d, hits), developer(dev), OS(so){}

MultimediaItem* Software::search(const std::string& field, const std::string& value){
	// FIXME: Inizio codice duplicato
	if (searchMap.count(field)){
		if ( (*searchMap[field])(*this, value) ){
			return this;
		}
	// Fine codice duplicato
	}else{
		return MultimediaItem::search(field, value);
	}
	return 0;
}

const std::map<std::string, std::string> Software::readInfo() const{
	std::map<std::string, std::string> toReturn = MultimediaItem::readInfo();
	toReturn.insert({"developer", developer});
	toReturn.insert({"OS", OS});
	return toReturn;

}

void Software::get(){
	MultimediaItem::get();
	throw("Il download di contenuti non è ancora stato implementato!");
}

bool Software::operator==(const Software& other){
	return MultimediaItem::operator==(other) && developer == other.developer && OS == other.OS;
}

std::string Software::getDeveloper() const{
	return developer;
}

std::string Software::getOS() const{
	return OS;
}
