#include "XMLUtilities.h"
#include <QApplication>
#include <QString>
#include <QFile>

User* XMLUtilities::gatherUser(QXmlStreamReader& x, std::list<User*>*& userList, std::list<MultimediaItem*>* items){
	x.readNext();
	std::string nome, pass, tipo, nomenodo;
	while(nomenodo!="User"){
		nomenodo = x.name().toString().toStdString();
		if (x.isStartElement()){
			if (nomenodo == "Name"){
				nome = x.readElementText().toStdString();
			}
			if (nomenodo == "Password"){
				pass = x.readElementText().toStdString();
			}
			if (nomenodo == "Type"){
				tipo = x.readElementText().toStdString();
			}
		}
		x.readNext();
	}
	if (tipo == "User"){
		return new User(nome, pass, items);
	}
	if (tipo == "Admin"){
		return new Admin(nome, pass, items, userList);
	}
	if (tipo == "Developer"){
		return new Developer(nome, pass, items);
	}
	return 0;
}

std::list<User*>* XMLUtilities::loadUserList(std::list<MultimediaItem*>* items){
	std::list<User*>* toreturn = new std::list<User*>();
	QFile* file = new QFile("Users.xml");
	file->open(QIODevice::ReadOnly);
	QXmlStreamReader xml(file);
	while (!xml.atEnd()){
		xml.readNext();
		if (xml.isStartElement()){
			if (xml.name() == "User"){
				toreturn->push_back(gatherUser(xml, toreturn, items));
			}
		}
	}
	if (xml.hasError()){
		std::cout << "Errore nella lettura del file XML Utenti:" << xml.errorString().toStdString();
	}
	file->close();
	return toreturn;
}

void XMLUtilities::saveUserList(const std::list<User*>* userList){
	QFile* fil = new QFile("Users.xml");
	fil->open(QIODevice::WriteOnly);
	QXmlStreamWriter* xml = new QXmlStreamWriter(fil);
	xml->setAutoFormatting(true);
	xml->writeStartDocument();
	xml->writeStartElement("Users");
	std::list<User*>::const_iterator it = userList->begin();
	for (; it != userList->end(); it++){
		//QString user(((*it)->getUser()).c_str());
		//QString pass(((*it)->getPass()).c_str());
		//QString type(((*it)->getType()).c_str());
		xml->writeStartElement("User");
		xml->writeTextElement("Name", QString::fromStdString((*it)->getUser()));
		xml->writeTextElement("Password", QString::fromStdString((*it)->getPass()));
		xml->writeTextElement("Type", QString::fromStdString((*it)->getType()));
		xml->writeEndElement();
	}
	xml->writeEndElement();
	xml->writeEndDocument();
	fil->close();
}

void XMLUtilities::saveItemsList(const std::list<MultimediaItem*>* itemList){
	QFile* fil = new QFile("Items.xml");
	fil->open(QIODevice::WriteOnly);
	QXmlStreamWriter* xml = new QXmlStreamWriter(fil);
	xml->setAutoFormatting(true);
	xml->writeStartDocument();
	xml->writeStartElement("items");
	std::list<MultimediaItem*>::const_iterator it = itemList->begin();
	for (; it != itemList->end(); it++){
		//QString nome(((*it)->getNome()).c_str());
		//QString link(((*it)->getLink()).c_str());
		//QString descrizione(((*it)->getDesc()).c_str());
		//QString hits(((*it)->getHits()).c_str());
		xml->writeStartElement("item");
		Software* x = dynamic_cast<Software*>(*it);
		Video* y = dynamic_cast<Video*>(*it);
		xml->writeAttribute("type", (x ? "Software" : (y ? "Video" : "MultimediaItem")));
		xml->writeTextElement("name", QString::fromStdString((*it)->getNome()));
		xml->writeTextElement("link", QString::fromStdString((*it)->getLink()));
		xml->writeTextElement("description", QString::fromStdString((*it)->getDesc()));
		xml->writeTextElement("hits", QString::fromStdString((*it)->getHits()));
		if (x){
			//QString dev((x->getDeveloper()).c_str());
			//QString OS((x->getOS()).c_str());
			xml->writeTextElement("developer", QString::fromStdString(x->getDeveloper()));
			xml->writeTextElement("OS", QString::fromStdString(x->getOS()));
		}
		if (y){
			//QString auth((y->getAuthor()).c_str());
			xml->writeTextElement("author", QString::fromStdString(y->getAuthor()));
		}
		xml->writeEndElement();
	}
	xml->writeEndElement();
	xml->writeEndDocument();
	fil->close();
}

std::list<MultimediaItem*>* XMLUtilities::loadItemsList(){
	std::list<MultimediaItem*>* toreturn = new std::list<MultimediaItem*>();
	QFile* fil = new QFile("Items.xml");
	fil->open(QIODevice::ReadOnly);
	QXmlStreamReader xml(fil);
	while(!xml.atEnd()){
		xml.readNext();
		if (xml.isStartElement()){
			if (xml.name() == "item"){
				toreturn->push_back(gatherItem(xml));
			}
		}
	}
	if (xml.hasError()){
		std::cout << "Errore nella lettura del file XML Dati:" << xml.errorString().toStdString();
	}
	fil->close();
	return toreturn;
}

MultimediaItem* XMLUtilities::gatherItem(QXmlStreamReader& xml){
	std::string type = "";
	QXmlStreamAttributes atts = xml.attributes();
	if (atts.hasAttribute("type")){
		type = atts.value("type").toString().toStdString();
	}else{
		return 0;
	}
	std::string nomeNodo, nome, link, desc, dev, auth, os;
	int hits = 0;
	xml.readNext();
	while(nomeNodo != "item"){
		nomeNodo = xml.name().toString().toStdString();
		if (xml.isStartElement()){
			if (nomeNodo == "name"){
				nome = xml.readElementText().toStdString();
			}
			if (nomeNodo == "link"){
				link = xml.readElementText().toStdString();
			}
			if (nomeNodo == "description"){
				desc = xml.readElementText().toStdString();
			}
			if (nomeNodo == "hits"){
				hits = xml.readElementText().toInt();
			}
			//--------------------
			if (type == "Software"){
				if (nomeNodo == "developer"){
					dev = xml.readElementText().toStdString();
				}
				if (nomeNodo == "OS"){
					os = xml.readElementText().toStdString();
				}
			}
			if (type == "Video"){
				if (nomeNodo == "author"){
					auth = xml.readElementText().toStdString();
				}
			}
		}
		xml.readNext();
	}
	if (type == "Software"){
		return new Software(nome, link, desc, dev, os, hits);
	}
	if (type == "Video"){
		return new Video(nome, link, desc, auth, hits);
	}
	return 0;

}
