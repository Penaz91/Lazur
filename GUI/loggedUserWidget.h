/* Widget che mostra il nome dell'utente loggato, la sua classe e il pulsante di logoff*/

#ifndef LOGWDG_H
#define LOGWDG_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QHBoxLayout>
#include "../UserStructs/User.h"

class loggedUserWidget: public QWidget{
	Q_OBJECT
	public:
		loggedUserWidget(const User*, QWidget*);
	private:
		QLabel* status;
		QPushButton* logoff;
		const User* loggedUser;
		QHBoxLayout* layout;
	signals:
		void userLogout();
};

#endif
