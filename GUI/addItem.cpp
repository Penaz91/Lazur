#include "addItem.h"

addItem::addItem(const User* lUser, QWidget* parent): QWidget(parent), loggedUser(lUser){
	save = new QPushButton("Salva Modifiche", this);
	labelList= new std::list<QLabel*>();
	fieldList = new std::map<std::string, QLineEdit*>();
	layout = new QGridLayout(this);
	connect(save, SIGNAL(clicked()), this, SLOT(saveEdits()));
}

void addItem::setFileType(addItem::FileType ft){
	type = ft;
	buildFields();
}

void addItem::cleanFields() const{
	auto it = labelList->begin();
	for (; it!=labelList->end(); it++){
		layout->removeWidget(*it);
		delete *it;
	}
	auto it2 = fieldList->begin();
	for (; it2!=fieldList->end(); it2++){
		layout->removeWidget(std::get<1>(*it2));
		delete std::get<1>(*it2);
	}
	labelList->clear();
	fieldList->clear();
	QLayoutItem* child;
	while((child = layout->takeAt(0))!=0){
		delete child;
	}
}

void addItem::buildFields(){
	cleanFields();
	labelList->push_back(new QLabel("Nome", this));
	labelList->push_back(new QLabel("Link", this));
	labelList->push_back(new QLabel("Descrizione", this));
	QLineEdit* currField = new QLineEdit(this);
	fieldList->insert({"Nome", currField});
	currField = new QLineEdit(this);
	fieldList->insert({"Link", currField});
	currField = new QLineEdit(this);
	fieldList->insert({"Descrizione",currField});
	if (type==FileType::SOFTWARE){
		labelList->push_back(new QLabel("Developer", this));
		QLineEdit* currField = new QLineEdit(this);
		fieldList->insert({"Developer", currField});
		labelList->push_back(new QLabel("OS", this));
		currField = new QLineEdit(this);
		fieldList->insert({"OS", currField});
	}
	if (type==FileType::VIDEO){
		labelList->push_back(new QLabel("Autore", this));
		QLineEdit* currField = new QLineEdit(this);
		fieldList->insert({"Autore", currField});

	}
	auto it3 = labelList->begin();
	int i = 0;
	for (; it3!=labelList->end(); it3++, i++){
		std::string str = ((*it3)->text()).toStdString();
		QLineEdit* ql = (*fieldList)[str];
		layout->addWidget(*it3, i, 0);
		layout->addWidget(ql, i, 1, 1, 2);
	}
	layout->addWidget(save, i, 0, 1, -1);
	setLayout(layout);
}

std::string addItem::getFromField(const std::string& name) const{
	return ((std::get<1>(*(fieldList->find(name))))->text()).toStdString();
}

void addItem::saveEdits(){
	try{
		const Editor* pntr = dynamic_cast<const Editor*>(loggedUser);
		//std::cout<<"Puntatore ad Editor creato"<<std::endl;
		MultimediaItem* newItem = 0;
		//std::cout<<"Puntatore ad Oggetto creato"<<std::endl;
		if (type==FileType::VIDEO){
			newItem = new Video(getFromField("Nome"), getFromField("Link"), getFromField("Descrizione"), getFromField("Autore"), 0);
		}
		if (type==FileType::SOFTWARE){
			newItem = new Software(getFromField("Nome"), getFromField("Link"), getFromField("Descrizione"), getFromField("Developer"), getFromField("OS"), 0);
		}
		if (newItem){
			//std::cout<<"Creato oggetto"<<std::endl;
			pntr->add(newItem);
			//std::cout<<"Oggetto Inserito"<<std::endl;
		}else{
			throw("Puntatore ad oggetto vuoto! Nessun oggetto è stato inserito");
		}
	}catch (const char*& exc){
		QMessageBox* msg = new QMessageBox(QMessageBox::Warning, "OUCH!!!", QString::fromStdString(exc), QMessageBox::Ok, this);
		msg->show();
	}
	emit switchWindow(0);
}
