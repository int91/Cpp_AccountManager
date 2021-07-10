#include <stdio.h>
#include <iostream>

#pragma once
class Account
{
private:
	std::string name;
	std::string password;
	std::string email;
	std::string application;
	std::string description;

public:
	Account(std::string _name, std::string pass, std::string _email, std::string app, std::string desc);
	std::string getName();
	std::string getPassword();
	std::string getEmail();
	std::string getApplication();
	std::string getDescription();

};

