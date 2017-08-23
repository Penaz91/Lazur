/* Utilità per La gerarchia Utenti */
#ifndef USERUTILS_H
#define USERUTILS_H

#include "../UserStructs/User.h"

namespace UserUtilities{
	User* findUser(std::list<User*>*, const std::string&);
}

#endif
