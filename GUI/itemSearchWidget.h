/* Widget di ricerca oggetti */

#ifndef ITEMSEARCHWDG_H
#define ITEMSEARCHWDG_H

#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QListWidget>
#include <QMessageBox>
#include <list>
#include <vector>
#include "../UserStructs/User.h"
#include "../UserStructs/Editor.h"
#include "../DataStructs/MultimediaItem.h"

class itemSearchWidget: public QWidget{
	Q_OBJECT
	public:
		itemSearchWidget(const User*, QWidget*);
	private:
		const User* loggedUser;
		QLineEdit* searchField;
		QComboBox* fieldToSearch;
		QPushButton* searchBtn;
		std::list<QPushButton*>* lowerButtons;
		std::vector<MultimediaItem*> resultList;
		QListWidget* results;
		QGridLayout* layout;
		QHBoxLayout* sublayout;
	signals:
		void populateItemEditWindow(MultimediaItem*);
		void switchWindow(int);
	public slots:
		void search();
		void view();
		void deleteItem();
};

#endif
