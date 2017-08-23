#include "loginWidget.h"
#include "registrationForm.h"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QRect>

loginWidget::loginWidget(std::list<User*>* userList, QWidget* parent): QWidget(parent){
	logo = new QLabel(this);
	const QPixmap* logoimg = new QPixmap("Resources/logo.png");
	logo->setPixmap(*logoimg);
	logo->setMinimumSize(100,100);
	userName = new QLineEdit(this);
	password = new QLineEdit(this);
	loginBtn = new QPushButton("Login", this);
	loginBtn->setDefault(true);
	users = userList;
	registerBtn = new QPushButton("Registrati", this);
	layout = new QVBoxLayout(this);
	userName->setPlaceholderText("Username");
	password->setPlaceholderText("Password");
	password->setEchoMode(QLineEdit::Password);
	status = new QLabel("Premi \"Login\" per accedere. Non hai un account? Premi \"Registrati\" per crearne uno.", this);
	//Penso sia una cosa carina fare la login con Invio
	connect(userName, SIGNAL(returnPressed()), password, SLOT(setFocus()));
	connect(password, SIGNAL(returnPressed()), loginBtn, SIGNAL(clicked()));
	layout->addStretch();
	layout->addWidget(logo);
	layout->addWidget(userName);
	layout->addWidget(password);
	layout->addWidget(loginBtn);
	layout->addWidget(registerBtn);
	layout->addWidget(status);
	layout->addStretch();
	layout->setAlignment(logo, Qt::AlignCenter);
	setLayout(layout);
	connect(loginBtn, SIGNAL(clicked()), this, SLOT(checkUser()));
	connect(registerBtn, SIGNAL(clicked()), this, SIGNAL(openRegistrationWindow()));
	connect(this, SIGNAL(loginFailed(const QString&)), password, SLOT(clear()));
	connect(this, SIGNAL(loginFailed(const QString&)), status, SLOT(setText(const QString&)));
	//std::cout<< "UserList Vuota? " << (userList==0) << std::endl;
}

/*std::pair<std::string, std::string> loginWidget::getValues() const{
	// Costruzione di Pair alla C++11
	return {(userName->text()).toStdString(), (password->text()).toStdString()};
}*/

void loginWidget::checkUser() const{
	//std::cout<<"Inizio Login"<<std::endl;
	User* found = UserUtilities::findUser(users, (userName->text()).toStdString());
	//std::cout<<"Utente ricercato"<<std::endl;
	if (found){
		//bool valid=UserUtilities::checkPassword(found, (password->text()).toStdString());
		bool valid = (found->getPass() == (password->text()).toStdString());
		if (valid){
			emit loginExecuted(found);
		}else{
			emit loginFailed("Password non valida");
		}
	}else{
		emit loginFailed("Utente non trovato");
	}
}
