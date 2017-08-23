#include "viewEditItem.h"

viewEditItem::viewEditItem(const User* lUser, MultimediaItem* item, QWidget* parent): QWidget(parent), toView(item), loggedUser(lUser){
	edit = new QPushButton("Modifica", this);
	get = new QPushButton("Scarica/Vedi", this);
	save = new QPushButton("Salva Modifiche", this);
	labelList= new std::list<QLabel*>();
	fieldList = new std::map<std::string, QLineEdit*>();
	layout = new QGridLayout(this);
	connect(get, SIGNAL(clicked()), this, SLOT(getItem()));
	connect(edit, SIGNAL(clicked()), this, SLOT(enableFields()));
	connect(save, SIGNAL(clicked()), this, SLOT(saveEdits()));
}

void viewEditItem::cleanFields(){
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

void viewEditItem::buildFields(){
	cleanFields();
	labelList->push_back(new QLabel("Nome", this));
	labelList->push_back(new QLabel("Link", this));
	labelList->push_back(new QLabel("Descrizione", this));
	labelList->push_back(new QLabel("Hits", this));
	QLineEdit* currField = new QLineEdit(this);
	currField->setText(QString::fromStdString(toView->getNome()));
	currField->setEnabled(false);
	fieldList->insert({"Nome", currField});
	currField = new QLineEdit(this);
	currField->setText(QString::fromStdString(toView->getLink()));
	currField->setEnabled(false);
	fieldList->insert({"Link", currField});
	currField = new QLineEdit(this);
	currField->setText(QString::fromStdString(toView->getDesc()));
	currField->setEnabled(false);
	fieldList->insert({"Descrizione",currField});
	currField = new QLineEdit(this);
	currField->setText(QString::fromStdString(toView->getHits()));
	currField->setEnabled(false);
	fieldList->insert({"Hits", currField});
	Software* x = dynamic_cast<Software*>(toView);
	if (x){
		labelList->push_back(new QLabel("Developer", this));
		QLineEdit* currField = new QLineEdit(this);
		currField->setText(QString::fromStdString(x->getDeveloper()));
		currField->setEnabled(false);
		fieldList->insert({"Developer", currField});
		labelList->push_back(new QLabel("OS", this));
		currField = new QLineEdit(this);
		currField->setText(QString::fromStdString(x->getOS()));
		currField->setEnabled(false);
		fieldList->insert({"OS", currField});
	}
	Video* y = dynamic_cast<Video*>(toView);
	if (y){
		labelList->push_back(new QLabel("Autore", this));
		QLineEdit* currField = new QLineEdit(this);
		currField->setText(QString::fromStdString(y->getAuthor()));
		currField->setEnabled(false);
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
	auto edptr = dynamic_cast<const Editor*>(loggedUser);
	if (!edptr || !edptr->hasPermission(toView)){
		//Disattivazione pulsanti
		edit->setEnabled(false);
		save->setEnabled(false);
	}
	layout->addWidget(get, i, 0);
	layout->addWidget(edit, i, 1);
	layout->addWidget(save, i, 2);
	setLayout(layout);

}

void viewEditItem::setItem(MultimediaItem* item){
	toView = item;
	buildFields();
}

void viewEditItem::getItem(){
	try{
		toView->get();
	}catch (const char*& e){
		QMessageBox* msg=new QMessageBox(QMessageBox::Information, "Ouch!", QString::fromStdString(e), QMessageBox::Ok, this);
	msg->show();
	}
}

void viewEditItem::enableFields(){
	auto it = fieldList->begin();
	for (; it!=fieldList->end(); it++){
		(std::get<1>(*it))->setEnabled(true);
	}
}

std::string viewEditItem::getFromField(const std::string& name) const{
	return ((std::get<1>(*(fieldList->find(name))))->text()).toStdString();
}

void viewEditItem::saveEdits(){
	try{
		MultimediaItem* replacer = 0;
		const Editor* pntr = dynamic_cast<const Editor*>(loggedUser);
		if (dynamic_cast<Video*>(toView)){
			replacer = new Video(getFromField("Nome"), getFromField("Link"), getFromField("Descrizione"), getFromField("Autore"), std::stoi(getFromField("Hits")));
		}
		if (dynamic_cast<Software*>(toView)){
			replacer = new Software(getFromField("Nome"), getFromField("Link"), getFromField("Descrizione"), getFromField("Developer"), getFromField("OS"), std::stoi(getFromField("Hits")));
		}
		if (replacer){
			pntr->replace(toView, replacer);
		}else{
			throw("Il puntatore all'oggetto da sostituire è vuoto! L'oggetto non è stato sostituito");
		}
	}catch (const char*& exc){
		QMessageBox* msg = new QMessageBox(QMessageBox::Warning, "OUCH!!!", QString::fromStdString(exc), QMessageBox::Ok, this);
		msg->show();
	}
	emit switchWindow(0);
}
