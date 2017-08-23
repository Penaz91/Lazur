/* Implementazione widget principale */

#include "mainWidget.h"

mainWidget::mainWidget(const User* user, std::list<User*>* uList, std::list<MultimediaItem*>* items, QWidget* parent): QWidget(parent), loggedUser(user), userList(uList), itemList(items){
	layout = new QGridLayout(this);
	luw = new loggedUserWidget(user, this);
	sbw = new sidebarWidget(user, this);
	hsep=new QFrame(this);
	hsep->setFrameShape(QFrame::HLine);
	vsep=new QFrame(this);
	vsep->setFrameShape(QFrame::VLine);
	layout->addWidget(luw, 0, 0, 1, -1);
	layout->addWidget(hsep, 1, 0, 1, -1);
	layout->addWidget(sbw, 2, 0);
	//------
	itemSearchWidget* itemSearch = new itemSearchWidget(user, this);
	userSearchWidget* userSearch = new userSearchWidget(user, userList, this);
	viewEditUser* userEdit = new viewEditUser(loggedUser, this);
	addUser* addUsr = new addUser(loggedUser, this);
	viewEditItem* itemEdit = new viewEditItem(loggedUser, nullptr, this);
	addItem* itemAdd = new addItem(loggedUser, this);
	mainWdg = new QStackedWidget(this);
	mainWdg->insertWidget(0, itemSearch);
	mainWdg->insertWidget(1, userSearch);
	mainWdg->insertWidget(2, userEdit);
	mainWdg->insertWidget(3, addUsr);
	mainWdg->insertWidget(4, itemEdit);
	mainWdg->insertWidget(5, itemAdd);
	layout->addWidget(vsep, 2, 1, 1, -1);
	layout->addWidget(mainWdg, 2, 2);
	//------
	setLayout(layout);
	connect(luw, SIGNAL(userLogout()), this, SIGNAL(userLogout()));
	connect(sbw, SIGNAL(switchWindow(int)), mainWdg, SLOT(setCurrentIndex(int)));
	connect(userSearch, SIGNAL(populateEditWindow(User*)), userEdit, SLOT(setUser(User*)));
	connect(userSearch, SIGNAL(changeWindow(int)), mainWdg, SLOT(setCurrentIndex(int)));
	connect(userEdit, SIGNAL(switchWindow(int)), mainWdg, SLOT(setCurrentIndex(int)));
	connect(addUsr, SIGNAL(switchWindow(int)), mainWdg, SLOT(setCurrentIndex(int)));
	connect(itemSearch, SIGNAL(populateItemEditWindow(MultimediaItem*)), itemEdit, SLOT(setItem(MultimediaItem*)));
	connect(itemSearch, SIGNAL(switchWindow(int)), mainWdg, SLOT(setCurrentIndex(int)));
	connect(itemEdit, SIGNAL(switchWindow(int)), mainWdg, SLOT(setCurrentIndex(int)));
	connect(itemAdd, SIGNAL(switchWindow(int)), mainWdg, SLOT(setCurrentIndex(int)));
	connect(sbw, SIGNAL(setFileType(addItem::FileType)), itemAdd, SLOT(setFileType(addItem::FileType)));
}
