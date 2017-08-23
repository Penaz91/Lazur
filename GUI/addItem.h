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

#ifndef ADDITEM_H
#define ADDITEM_H

class addItem: public QWidget{
	Q_OBJECT
	public:
		enum FileType {SOFTWARE, VIDEO};
		addItem(const User*, QWidget* =0);
		void buildFields();
	private:
		std::list<QLabel*>* labelList;
		std::map<std::string, QLineEdit*>* fieldList;
		QPushButton* save;
		QGridLayout* layout;
		const User* loggedUser;
		std::string getFromField(const std::string&) const;
		FileType type;
		void cleanFields() const;
	public slots:
		void saveEdits();
		void setFileType(addItem::FileType);
	signals:
		void switchWindow(int);
};

#endif
