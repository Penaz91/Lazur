/*
 * Costruzione Di Editor
 */
#include "Editor.h"

class User;

Editor::Editor(const std::string& name, const std::string& pass, std::list<MultimediaItem*>*& items): User(name, pass, items){}

Editor::Editor(const std::string& name, const std::string& pass): User(name, pass){}
