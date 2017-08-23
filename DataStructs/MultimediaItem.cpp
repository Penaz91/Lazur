/*
Implementazione di MultimediaItem
*/

#include "MultimediaItem.h"

// Questa inizializzazione mi è consentita da C++11: Le {} esterne inizializzano una std::map, quelle interne una std::pair
std::map<std::string, bool (*)(const MultimediaItem&, const std::string&)> MultimediaItem::searchMap = {{"nome", &has_name}};

MultimediaItem::MultimediaItem(){}

std::string MultimediaItem::getNome() const{
	return nome;
}

std::string MultimediaItem::getLink() const{
	return link;
}

std::string MultimediaItem::getDesc() const{
	return descrizione;
}

std::string MultimediaItem::getHits() const{
	return std::to_string(nHits);
}

MultimediaItem::MultimediaItem(const std::string& n, const std::string& l, const std::string& d, int hits): nome(n), link(l), descrizione(d), nHits(hits){}

void MultimediaItem::get(){
	nHits++;
}

bool MultimediaItem::has_name(const MultimediaItem& i, const std::string& othername){
	//return i.nome == othername;
	return (i.nome.find(othername)!=std::string::npos);
}

MultimediaItem* MultimediaItem::search(const std::string& field, const std::string& value){
	if (searchMap.count(field)){
		// Secondo C++Reference posso usare count per i test di esistenza
		if ( (*searchMap[field])(*this, value) ){
			return this;
		}
	}
	return 0;
}

const std::map<std::string, std::string> MultimediaItem::readInfo() const{
	// Uso il metodo std::to_string di C++11 Per la conversione int -> string + Inizializzazione di mappa tramite graffe (Sempre da C++11)
	return {
		{"nome", nome},
		{"link", link},
		{"descrizione", descrizione},
		{"hits", std::to_string(nHits)}
	};
}

bool MultimediaItem::operator==(const MultimediaItem& other){
	return nome == other.nome && link == other.link && descrizione == other.descrizione && nHits == other.nHits;
}

MultimediaItem::~MultimediaItem()=default;
