#pragma once
#include <iostream>
#include <string>

class Autorize {
	std::string username;
	std::string password;
	bool isRegistered = false;
public:
	bool registerUser(const std::string& name, const std::string& pass);
	bool login(const std::string& name, const std::string& pass);
	bool hasRegisteredUser() const;
};

std::string authMenu();