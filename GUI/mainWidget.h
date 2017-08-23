/* Widget principale */

#ifndef MAINWDG_H
#define MAINWDG_H

#include <QWidget>
#include <QGridLayout>
#include "loggedUserWidget.h"
#include "sidebarWidget.h"
#include "itemSearchWidget.h"
#include "userSearchWidget.h"
#include "viewEditItem.h"
#include "addItem.h"
#include "viewEditUser.h"
#include "addUser.h"
#include <QStackedWidget>
#include <list>
#include <QFrame>
#include "../UserStructs/User.h"
#include "../DataStructs/MultimediaItem.h"

class mainWidget: public QWidget{
	Q_OBJECT
	public:
		mainWidget(const User*, std::list<User*>*, std::list<MultimediaItem*>*, QWidget*);
	private:
		const User* loggedUser;
		QGridLayout* layout;
		loggedUserWidget* luw;
		QStackedWidget* mainWdg;
		sidebarWidget* sbw;
		std::list<User*>* userList;
		std::list<MultimediaItem*>* itemList;
		QFrame* hsep;
		QFrame* vsep;
	signals:
		void userLogout();
};

#endif
