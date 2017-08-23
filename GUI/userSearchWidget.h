/* Widget di ricerca utenti*/

#ifndef USERSEARCHWDG_H
#define USERSEARCHWDG_H

#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <vector>
#include <list>
#include "../UserStructs/User.h"

class userSearchWidget: public QWidget{
	Q_OBJECT
	public:
		userSearchWidget(const User*, std::list<User*>*, QWidget*);
	private:
		const User* loggedUser;
		QLineEdit* searchField;
		QPushButton* searchBtn;
		QPushButton* editBtn;
		QPushButton* deleteBtn;
		std::vector<User*> resList;
		std::list<User*>* userList;
		QListWidget* results;
		QGridLayout* layout;
		QVBoxLayout* sublayout;
	public slots:
		void search();
		void edit();
		void remove();
	signals:
		void populateEditWindow(User*);
		void changeWindow(int);
};

#endif
