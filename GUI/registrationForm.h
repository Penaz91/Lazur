/* Widget per la registrazione di un nuovo utente */

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include "../UserStructs/User.h"
#include "../Utilities/UserUtilities.h"
#include "../Utilities/XMLUtilities.h"

#ifndef REGFORM_H
#define REGFORM_H

class registrationForm: public QWidget{
	Q_OBJECT
	public:
		registrationForm(std::list<User*>*, std::list<MultimediaItem*>*, QWidget* = 0);
	public slots:
		void sendRegistration();
	signals:
		void exitRegistration();
	private slots:
		void checkPasswords();
	private:
		QLineEdit* userName;
		QLineEdit* password1;
		QLineEdit* password2;
		QPushButton* registrationBtn;
		QPushButton* cancelBtn;
		QLabel* status;
		QVBoxLayout* layout;
		std::list<User*>* users;
		std::list<MultimediaItem*>* items;
};

#endif
