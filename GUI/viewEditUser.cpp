#include "viewEditUser.h"
#include <QString>

viewEditUser::viewEditUser(const User* lUser, QWidget* parent): QWidget(parent), loggedUser(lUser){
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
	setLayout(layout);
	connect(abort, SIGNAL(clicked()), this, SLOT(abortAndReturn()));
	connect(confirm, SIGNAL(clicked()), this, SLOT(saveAndReturn()));
}

void viewEditUser::setUser(User* toEdit){
	userPtr = toEdit;
	uName->setText(QString::fromStdString(toEdit->getUser()));
	pw->setText(QString::fromStdString(toEdit->getPass()));
	type->setCurrentIndex(type->findText("User"));
	if (dynamic_cast<Developer*>(toEdit)){
		//std::cout << "Seleziono Dev" << std::endl;
		type->setCurrentIndex(type->findText("Developer"));
	}
	if (dynamic_cast<Admin*>(toEdit)){
		//std::cout << "Seleziono Admin"<< std::endl;
		type->setCurrentIndex(type->findText("Admin"));
	}
}

void viewEditUser::saveAndReturn(){
	User* replacer = nullptr;
	if (type->currentText()=="Admin"){
		replacer = new Admin((uName->text()).toStdString(), (pw->text()).toStdString());
	}
	if (type->currentText()=="Developer"){
		replacer = new Developer((uName->text()).toStdString(), (pw->text()).toStdString());
	}
	if (type->currentText()=="User"){
		replacer = new User((uName->text()).toStdString(), (pw->text()).toStdString());
	}
	if (replacer){
		// Non serve fare controllo, se sono arrivato su questa finestra DEVO essere admin per forza
		const Admin* adm = dynamic_cast<const Admin*>(loggedUser);
		adm->replaceUser(userPtr, replacer);
	}
	emit switchWindow(1);
}

void viewEditUser::abortAndReturn(){
	emit switchWindow(1);
}
