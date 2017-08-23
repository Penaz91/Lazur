/* Implementazione della registrazione nuovo utente */
#include "registrationForm.h"

registrationForm::registrationForm(std::list<User*>* userList, std::list<MultimediaItem*>* itemList, QWidget* parent): QWidget(parent), users(userList), items(itemList){
	userName = new QLineEdit(this);
	password1 = new QLineEdit(this);
	password2 = new QLineEdit(this);
	registrationBtn = new QPushButton("Conferma", this);
	cancelBtn = new QPushButton("Annulla", this);
	status = new QLabel("In attesa di input...");
	layout = new QVBoxLayout(this);
	userName->setPlaceholderText("La tua UserName");
	password1->setPlaceholderText("Inserisci qui la tua password");
	password2->setPlaceholderText("Ripeti qui la tua password");
	password1->setEchoMode(QLineEdit::Password);
	password2->setEchoMode(QLineEdit::Password);
	layout->addStretch();
	layout->addWidget(userName);
	layout->addWidget(password1);
	layout->addWidget(password2);
	layout->addWidget(registrationBtn);
	layout->addWidget(cancelBtn);
	layout->addWidget(status);
	layout->addStretch();
	setLayout(layout);
	registrationBtn->setEnabled(false);
	connect(registrationBtn, SIGNAL(clicked()), this, SLOT(sendRegistration()));
	connect(cancelBtn, SIGNAL(clicked()), this, SIGNAL(exitRegistration()));
	connect(password1, SIGNAL(textEdited(const QString&)), this, SLOT(checkPasswords()));
	connect(password2, SIGNAL(textEdited(const QString&)), this, SLOT(checkPasswords()));
}

void registrationForm::checkPasswords(){
	if(password1->text() != password2->text()){
		status->setText("Le due passwords non corrispondono!");
		registrationBtn->setEnabled(false);
	}else{
		status->setText("Le due passwords corrispondono");
		registrationBtn->setEnabled(true);
	}
}

void registrationForm::sendRegistration(){
	User* found = UserUtilities::findUser(users, (userName->text()).toStdString());
	if (found){
		status->setText("Questo Utente esiste Già.");
	}else{
		//UserUtilities::pushUser(users,new User((userName->text()).toStdString(), (password1->text()).toStdString(), items));
		users->push_back(new User((userName->text()).toStdString(), (password1->text()).toStdString()));
		XMLUtilities::saveUserList(users);
		emit exitRegistration();
	}
}
