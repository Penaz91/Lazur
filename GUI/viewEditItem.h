#include <QWidget>
#include <list>
#include <map>
#include <utility>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QMessageBox>
#include "../DataStructs/MultimediaItem.h"
#include "../DataStructs/Software.h"
#include "../DataStructs/Video.h"
#include "../UserStructs/User.h"
#include "../UserStructs/Admin.h"
#include "../UserStructs/Developer.h"

#ifndef VEITEM_H
#define VEITEM_H

class viewEditItem: public QWidget{
	Q_OBJECT
	private:
		std::list<QLabel*>* labelList;
		std::map<std::string, QLineEdit*>* fieldList;
		MultimediaItem* toView;
		QPushButton* edit;
		QPushButton* get;
		QPushButton* save;
		QGridLayout* layout;
		const User* loggedUser;
		std::string getFromField(const std::string&) const;
		void buildFields();
		void cleanFields();
	public:
		viewEditItem(const User*, MultimediaItem* =0, QWidget* =0);
	public slots:
		void getItem();
		void setItem(MultimediaItem*);
		void enableFields();
		void saveEdits();
	signals:
		void switchWindow(int);
};

#endif
