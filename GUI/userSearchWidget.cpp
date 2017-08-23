/* Implementazione widget di ricerca utenti*/

#include "userSearchWidget.h"

userSearchWidget::userSearchWidget(const User* user, std::list<User*>* uList, QWidget* parent): QWidget(parent), loggedUser(user), userList(uList){
	searchField = new QLineEdit(this);
	searchField->setPlaceholderText("Inserisci il nome utente da cercare");
	searchBtn = new QPushButton("Cerca...", this);
	editBtn = new QPushButton("Modifica", this);
	deleteBtn = new QPushButton("Elimina", this);
	results = new QListWidget(this);
	layout = new QGridLayout(this);
	sublayout = new QVBoxLayout();
	resList = std::vector<User*>();
	connect(searchBtn, SIGNAL(clicked()), this, SLOT(search()));
	connect(editBtn, SIGNAL(clicked()), this, SLOT(edit()));
	connect(deleteBtn, SIGNAL(clicked()), this, SLOT(remove()));
	connect(searchField, SIGNAL(returnPressed()), searchBtn, SIGNAL(clicked()));
	layout->addWidget(searchField, 0, 0, Qt::AlignTop);
	layout->addWidget(searchBtn, 0, 1, Qt::AlignTop);
	sublayout->addWidget(editBtn, 0, Qt::AlignTop);
	sublayout->addWidget(deleteBtn, 1, Qt::AlignTop);
	layout->addWidget(results, 1, 0, -1, 1);
	layout->addLayout(sublayout, 1, 1, 1, -1);
}

void userSearchWidget::search(){
	results->clear();
	resList.clear();
	//std::cout << "Compilazione Lista" << std::endl;
	std::list<User*>::const_iterator itUser = userList->begin();
	//std::cout << "Iteratore creato" << std::endl;
	for (; itUser != userList->end(); itUser++){
		//if ((*itUser)->getUser() == (searchField->text()).toStdString()){
		if (((*itUser)->getUser()).find((searchField->text()).toStdString()) != std::string::npos){
			resList.push_back(*itUser);
		}
	}
	//std::cout << "Reslist Piena?" << (!resList.empty()) << std::endl;
	//std::cout << "Stampa Lista" << std::endl;
	std::vector<User*>::const_iterator it = resList.begin();
	for (; it != resList.end(); it++){
		QString nome = QString::fromStdString((*it)->getUser());
		results->addItem(nome);
	}
}

void userSearchWidget::edit(){
	if (!resList.empty() && results->currentRow() != -1){
		emit populateEditWindow(resList[results->currentRow()]);
		emit changeWindow(2);
	}
}

void userSearchWidget::remove(){
	if (!resList.empty() && results->currentRow() != -1){
		userList->remove(resList[results->currentRow()]);
	}
	resList.clear();
	results->clear();
}
