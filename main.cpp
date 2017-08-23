//#include "GUI/loginWidget.h"
//#include "GUI/registrationForm.h"
#include "GUI/mainWindow.h"
#include <QApplication>
#include "Utilities/XMLUtilities.h"

int main(int argc, char* argv[]){
	QApplication app(argc, argv);
	std::list<MultimediaItem*>* items = XMLUtilities::loadItemsList();
	//std::list<User*>* users = XMLUtilities::loadUserList(items);
	std::list<User*>* users = 0;
	mainWindow* mainW = new mainWindow(users, items);
	mainW->show();
	return QApplication::exec();
}
