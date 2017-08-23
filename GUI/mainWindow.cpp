#include "mainWindow.h"
#include "../Utilities/XMLUtilities.h"
#include <iostream>

mainWindow::mainWindow(std::list<User*>*& userList, std::list<MultimediaItem*>*& itemList, QWidget* parent): QMainWindow(parent), users(userList), items(itemList){
	connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(cleanupAndSave()));
	setWindowTitle("LAZUR - Content Search and Delivery Engine");
	goToLogin();
	setFixedSize(600,350);
}

void mainWindow::goToRegistration(){
	reg = new registrationForm(users, items);
	connect(reg, SIGNAL(exitRegistration()), this, SLOT(goToLogin()));
	setCentralWidget(reg);
}

void mainWindow::goToLogin(){
	if (users){
		std::list<User*>::const_iterator it = users->begin();
		//Housekeeping
		for (; it != users->end(); it++){
			delete *it;
		}
		delete users;
	}
	users = XMLUtilities::loadUserList(items);
	login = new loginWidget(users);
	//std::cout << "Puntatore"<<users<<std::endl;
	connect(login, SIGNAL(openRegistrationWindow()), this, SLOT(goToRegistration()));
	connect(login, SIGNAL(loginExecuted(const User*)), this, SLOT(doLogin(const User*)));
	//connect(login, SIGNAL(loginFailed(const QString&)), this, SLOT(doFailedLogin()));
	setCentralWidget(login);
}

void mainWindow::doLogin(const User* loggedUser){
	//std::cout << "Login Riuscita" << std::endl;
	mainWidget* mainWid = new mainWidget(loggedUser, users, items, this);
	connect(mainWid, SIGNAL(userLogout()), this, SLOT(goToLogin()));
	setCentralWidget(mainWid);
}

//void mainWindow::doFailedLogin() const{
	//std::cout << "Login Fallita" << std::endl;
//}

void mainWindow::cleanupAndSave() const{
	//std::cout << "Salvataggio Utenti" << std::endl;
	XMLUtilities::saveUserList(users);
	XMLUtilities::saveItemsList(items);
}
