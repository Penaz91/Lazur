#include "../UserStructs/User.h"
#include "../UserStructs/Developer.h"
#include "../UserStructs/Admin.h"
#include "../DataStructs/MultimediaItem.h"
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <typeinfo>

#ifndef ADDUSER_H
#define ADDUSER_H
class addUser: public QWidget{
	Q_OBJECT
	private:
		QLabel* uNamelbl;
		QLineEdit* uName;
		QLabel* pwlbl;
		QLineEdit* pw;
		QLabel* typelbl;
		QComboBox* type;
		QPushButton* confirm;
		QPushButton* abort;
		User* userPtr;
		const User* loggedUser;
		QGridLayout* layout;
		QVBoxLayout* sublayout;
	public:
		addUser(const User*, QWidget*);
	public slots:
		void saveAndReturn();
		void abortAndReturn();
	signals:
		void returnToSearch();
		void switchWindow(int);
};
#endif
