// Implementazione loggedUserWidget

#include "loggedUserWidget.h"

loggedUserWidget::loggedUserWidget(const User* user, QWidget* parent): QWidget(parent), loggedUser(user){
	QString lbl = QString::fromStdString("Hai acceduto come: " + user->getUser() + " (" + user->getType() + ")");
	status = new QLabel(lbl, this);
	logoff = new QPushButton("LogOff", this);
	layout = new QHBoxLayout(this);
	layout->addWidget(status);
	layout->addWidget(logoff);
	layout->setStretch(0, 2);
	layout->setStretch(1, 1);
	setLayout(layout);
	connect(logoff, SIGNAL(clicked()), this, SIGNAL(userLogout()));
}

