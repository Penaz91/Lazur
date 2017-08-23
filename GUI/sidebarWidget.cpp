/* Implementazione sidebar */

#include "sidebarWidget.h"

sidebarWidget::sidebarWidget(const User* user, QWidget* parent): QWidget(parent), loggedUser(user){
	btnList = new std::list<QPushButton*>();
	QPushButton* currbtn = new QPushButton("Ricerca Oggetti", this);
	connect(currbtn, SIGNAL(clicked()), this, SLOT(searchItem()));
	btnList->push_back(currbtn);
	addMenu = new QMenu(this);
	// FIXME: Leggera ripetizione di codice
	if (dynamic_cast<const Editor*>(user)){
		currbtn = new QPushButton("Aggiungi Oggetto", this);
		currbtn->setMenu(addMenu);
		btnList->push_back(currbtn);
	}
	if (dynamic_cast<const Admin*>(user)){
		currbtn = new QPushButton("Ricerca Utenti", this);
		connect(currbtn, SIGNAL(clicked()), this, SLOT(searchUser()));
		btnList->push_back(currbtn);
		currbtn = new QPushButton("Aggiungi Utente", this);
		connect(currbtn, SIGNAL(clicked()), this, SLOT(addUser()));
		btnList->push_back(currbtn);

	}
	//--------------------------------------------------
	layout = new QVBoxLayout(this);
	std::list<QPushButton*>::const_iterator it = btnList->begin();
	for (; it != btnList->end(); it++){
		layout->addWidget((*it));
	}
	layout->addStretch();
	setLayout(layout);
	QAction* SoftItem = new QAction("Software", this);
	connect(SoftItem, SIGNAL(triggered()), this, SLOT(newSoftware()));
	addMenu->addAction(SoftItem);
	if (dynamic_cast<const Admin*>(user)){
		QAction* VidItem= new QAction("Video", this);
		connect(VidItem, SIGNAL(triggered()), this, SLOT(newVideo()));
		addMenu->addAction(VidItem);
	}
}


void sidebarWidget::newSoftware(){
	emit switchWindow(5);
	emit setFileType(addItem::FileType::SOFTWARE);
}

void sidebarWidget::newVideo(){
	emit switchWindow(5);
	emit setFileType(addItem::FileType::VIDEO);
}

void sidebarWidget::searchItem(){
	emit switchWindow(0);
}

void sidebarWidget::searchUser(){
	emit switchWindow(1);
}

void sidebarWidget::addUser(){
	emit switchWindow(3);
}
