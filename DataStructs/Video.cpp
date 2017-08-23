/*
 * Implementazione Video
 */
#include "Video.h"
#include "MultimediaItem.h"

std::map<std::string, bool (*)(const Video&, const std::string&)> Video::searchMap = {{"autore", &has_author}};

bool Video::has_author(const Video& vid, const std::string& authname){
	//return vid.author == authname;
	return (vid.author.find(authname) != std::string::npos);
}

Video::Video(const std::string& name, const std::string& lnk, const std::string& desc, const std::string& auth, int hits): MultimediaItem(name, lnk, desc, hits), author(auth){}

const std::map<std::string, std::string> Video::readInfo() const{
	std::map<std::string, std::string> out = MultimediaItem::readInfo();
	out.insert({"author", author});
	return out;
}

void Video::get(){
	//Stub
	MultimediaItem::get();
	throw("Lo streaming di contenuti video non è ancora implementato!");
}

MultimediaItem* Video::search(const std::string& field, const std::string& value){
	if (searchMap.count(field)){
		if ( (*searchMap[field])(*this, value) ){
			return this;
		}
	}else{
		return MultimediaItem::search(field, value);
	}
	return 0;

}

bool Video::operator==(const Video& other){
	return MultimediaItem::operator==(other) && author == other.author;
}

std::string Video::getAuthor() const{
	return author;
}
