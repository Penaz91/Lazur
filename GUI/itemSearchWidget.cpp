/* Implementazione widget di ricerca oggetti */

#include "itemSearchWidget.h"

itemSearchWidget::itemSearchWidget(const User* user, QWidget* parent): QWidget(parent), loggedUser(user){
	searchField = new QLineEdit(this);
	searchField->setPlaceholderText("Inserisci i termini da cercare");
	fieldToSearch = new QComboBox();
	fieldToSearch->setEditable(false);
	fieldToSearch->addItem("nome");
	fieldToSearch->addItem("developer");
	fieldToSearch->addItem("OS");
	fieldToSearch->addItem("autore");
	searchBtn = new QPushButton("Cerca...", this);
	connect(searchField, SIGNAL(returnPressed()), searchBtn, SIGNAL(clicked()));
	results = new QListWidget(this);
	layout = new QGridLayout(this);
	sublayout = new QHBoxLayout();
	QPushButton* currentBtn = new QPushButton("Visualizza Oggetto", this);
	connect(currentBtn, SIGNAL(clicked()), this, SLOT(view()));
	lowerButtons = new std::list<QPushButton*>();
	lowerButtons->push_back(currentBtn);
	if (dynamic_cast<const Editor*>(loggedUser)){
		currentBtn = new QPushButton("Elimina Oggetto", this);
		connect(currentBtn, SIGNAL(clicked()), this, SLOT(deleteItem()));
		lowerButtons->push_back(currentBtn);
	}
	resultList = std::vector<MultimediaItem*>();
	connect(searchBtn, SIGNAL(clicked()), this, SLOT(search()));
	layout->addWidget(searchField, 0, 0);
	layout->addWidget(fieldToSearch, 0, 1);
	layout->addWidget(searchBtn, 0, 2);
	layout->addWidget(results, 1, 0, 1, -1);
	layout->addLayout(sublayout, 2, 0, 1, -1);
	std::list<QPushButton*>::const_iterator it = lowerButtons->begin();
	for(int i=0; it!=lowerButtons->end(); it++, i++){
		sublayout->addWidget((*it), i);
		sublayout->setStretch(i, 1);
	}
}

void itemSearchWidget::search(){
	results->clear();
	//std::cout << "Compilazione Lista" << std::endl;
	resultList = loggedUser->search((fieldToSearch->currentText()).toStdString(), (searchField->text()).toStdString());
	//std::cout << "Stampa Lista" << std::endl;
	std::vector<MultimediaItem*>::const_iterator it = resultList.begin();
	for (; it != resultList.end(); it++){
		QString nome = QString::fromStdString((*it)->getNome());
		results->addItem(nome);
	}
}

void itemSearchWidget::view(){
	if (!resultList.empty() && results->currentRow() != -1){
		/* Robaccia da debug
		 * std::map<std::string, std::string> infos = (resultList[results->currentRow()])->readInfo();
		auto it = infos.begin();
		std::cout << "---------Stampa Oggetto in lista ---------------" << std::endl;
		for (; it!=infos.end(); it++){
			std::cout << std::get<0>((*it)) << " " << std::get<1>((*it)) << std::endl;
		}
		*/
		emit populateItemEditWindow(resultList[results->currentRow()]);
		emit switchWindow(4);
	}
}

void itemSearchWidget::deleteItem(){
	if (!resultList.empty() && results->currentRow() != -1){
		const Editor* ptr = dynamic_cast<const Editor*>(loggedUser);
		// Non faccio verifiche di esistenza, dato che il bottone elimina è invisibile se non si è Editor+
		if (ptr->hasPermission(resultList[results->currentRow()])){
			ptr->remove(resultList[results->currentRow()]);
			resultList.clear();
			results->clear();
		}else{
		QMessageBox* msg = new QMessageBox(QMessageBox::Information, "Ouch!", "Non hai il permesso di eliminare questo elemento!", QMessageBox::Ok, this);
			msg->show();
		}
	}
}
