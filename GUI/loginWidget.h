/* Widget per la Login*/

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include <QPixmap>
#include <algorithm>
#include "../UserStructs/User.h"
#include "../Utilities/UserUtilities.h"

#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

class loginWidget: public QWidget{
	Q_OBJECT
	public:
		loginWidget(std::list<User*>*, QWidget* = 0);
		//std::pair<std::string, std::string> getValues() const;
	public slots:
		void checkUser() const;
	signals:
		void openRegistrationWindow();
		void loginExecuted(const User*) const;
		void loginFailed(const QString&) const;
	private:
		QLabel* logo;
		QLineEdit* userName;
		QLineEdit* password;
		QPushButton* loginBtn;
		QPushButton* registerBtn;
		QVBoxLayout* layout;
		std::list<User*>* users;
		QLabel* status;
};

#endif
