#pragma once
#include <iostream>
#include <string>
#include "Database.h"

// if you want to use project without database docker and else, just uncomment this class (delete database .h .cpp and code in authorization.cpp)
/*
class Autorize {
	std::string username;
	std::string password;
	bool isRegistered = false;
public:
	bool registerUser(const std::string& name, const std::string& pass);
	bool login(const std::string& name, const std::string& pass);
	bool hasRegisteredUser() const;
};
*/

bool authMenu(std::string& l);