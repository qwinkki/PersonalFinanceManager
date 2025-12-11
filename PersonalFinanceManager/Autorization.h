#pragma once
#include <iostream>
#include <string>
#include <cctype>
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


bool loginUserFromDatabase(const std::string& name, const std::string& pass);
bool registerUserAndInsertInDatabase(const std::string& name, const std::string& pass);

void deleteUserByName();
void ClearUserTable();

void createUserTableInDatabase(const std::string& name);
