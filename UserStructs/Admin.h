/*
Classe derivata da Editor - Amministratore
*/

#ifndef ADMIN_H
#define ADMIN_H

#include "Editor.h"
#include "User.h"
#include "../Utilities/UserUtilities.h"
#include "../Utilities/XMLUtilities.h"
#include <list>

class Admin: public Editor{
	private:
		std::list<User*>* userList;
	public:
		Admin(const std::string&, const std::string&, std::list<MultimediaItem*>*&, std::list<User*>*&);
		Admin(const std::string&, const std::string&, std::list<User*>*&);
		Admin(const std::string&, const std::string&);
		/* Uso la keyword "override" di c++11 per assicurarmi di fare override sui metodi*/
		void add(MultimediaItem*) const override;
		void remove(MultimediaItem*) const override;
		void replace(MultimediaItem*, MultimediaItem*) const override;
		std::string getType() const override;
		void addUser(User*) const;
		void removeUser(User*);
		void replaceUser(User*,User*) const;
		bool hasPermission(MultimediaItem*) const override;
		// Il distruttore ereditato da User dovrebbe andare bene
};
#endif
