#include "Account.h"

Account::Account(std::string _name, std::string pass, std::string _email, std::string app, std::string desc) {
	name = _name;
	password = pass;
	email = _email;
	application = app;
	description = desc;
}

std::string Account::getName() { return name; }
std::string Account::getPassword() { return password; }
std::string Account::getEmail() { return email; }
std::string Account::getApplication() { return application; }
std::string Account::getDescription() { return description; }