/* Sidebar Finestra principale */

#ifndef SIDEBAR_H
#define SIDEBAR_H

#include<QWidget>
#include<QPushButton>
#include<QVBoxLayout>
#include<list>
#include<QMenu>
#include<QAction>
#include "addItem.h"
#include "../UserStructs/User.h"
#include "../UserStructs/Editor.h"
#include "../UserStructs/Admin.h"

class sidebarWidget: public QWidget{
	Q_OBJECT
	public:
		sidebarWidget(const User*, QWidget*);
	private:
		std::list<QPushButton*>* btnList;
		const User* loggedUser;
		QVBoxLayout* layout;
		QMenu* addMenu;
	signals:
		void switchWindow(int);
		void setFileType(addItem::FileType);
	public slots:
		void searchItem();
		void searchUser();
		void addUser();
	private slots:
		void newSoftware();
		void newVideo();
};

#endif
