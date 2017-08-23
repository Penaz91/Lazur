#include "addUser.h"
#include <QString>

addUser::addUser(const User* lUser, QWidget* parent): QWidget(parent), loggedUser(lUser){
	uName = new QLineEdit(this);
	uNamelbl = new QLabel("UserName:", this);
	pw = new QLineEdit(this);
	pwlbl = new QLabel("Password", this);
	type = new QComboBox(this);
	typelbl = new QLabel("Tipo Utente", this);
	confirm = new QPushButton("Conferma");
	abort = new QPushButton("Annulla");
	layout = new QGridLayout(this);
	sublayout = new QVBoxLayout();
	type->addItem("User");
	type->addItem("Developer");
	type->addItem("Admin");
	layout->addWidget(uNamelbl, 0, 0);
	layout->addWidget(uName, 0, 1);
	layout->addWidget(pwlbl, 1, 0);
	layout->addWidget(pw, 1, 1);
	layout->addWidget(typelbl, 2, 0);
	layout->addWidget(type, 2, 1);
	sublayout->addWidget(confirm);
	sublayout->addWidget(abort);
	layout->addLayout(sublayout, 3, 0, 1, -1);
	connect(abort, SIGNAL(clicked()), this, SLOT(abortAndReturn()));
	connect(confirm, SIGNAL(clicked()), this, SLOT(saveAndReturn()));
}

void addUser::saveAndReturn(){
	User* newUsr = nullptr;
	if (type->currentText()=="Admin"){
		newUsr = new Admin((uName->text()).toStdString(), (pw->text()).toStdString());
	}
	if (type->currentText()=="Developer"){
		newUsr = new Developer((uName->text()).toStdString(), (pw->text()).toStdString());
	}
	if (type->currentText()=="User"){
		newUsr = new User((uName->text()).toStdString(), (pw->text()).toStdString());
	}
	if (newUsr){
		// Non serve fare controllo, se sono arrivato su questa finestra DEVO essere admin per forza
		const Admin* adm = dynamic_cast<const Admin*>(loggedUser);
		adm->addUser(newUsr);
	}
	emit switchWindow(1);
}

void addUser::abortAndReturn(){
	emit switchWindow(1);
}
