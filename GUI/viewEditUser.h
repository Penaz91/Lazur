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

#ifndef VEUSER_H
#define VEUSER_H
class viewEditUser: public QWidget{
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
		viewEditUser(const User*, QWidget*);
	public slots:
		void saveAndReturn();
		void abortAndReturn();
		void setUser(User*);
	signals:
		//void returnToSearch();
		void switchWindow(int);
};
#endif
