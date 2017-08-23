/* Finestra principale */
#include <QMainWindow>
#include <QApplication>
#include <QWidget>
#include "loginWidget.h"
#include "registrationForm.h"
#include "mainWidget.h"
#include "../UserStructs/User.h"
#include "../DataStructs/MultimediaItem.h"

class mainWindow: public QMainWindow{
	Q_OBJECT
	public:
		mainWindow(std::list<User*>*&,std::list<MultimediaItem*>*&, QWidget* = 0);
	private:
		loginWidget* login;
		registrationForm* reg;
		std::list<User*>* users;
		std::list<MultimediaItem*>* items;
	public slots:
		void goToRegistration();
		void goToLogin();
		void doLogin(const User*);
		//void doFailedLogin() const;
		void cleanupAndSave() const;
};
