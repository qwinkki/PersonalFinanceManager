#include "Autorization.h"

bool Autorize::registerUser(const std::string& name, const std::string& pass) {

	username = name;
	password = pass;
	isRegistered = true;

	return false;
}

bool Autorize::login(const std::string& name, const std::string& pass) {

	if (!isRegistered)
		return false;

	return (name == username && password == pass);
}

bool Autorize::hasRegisteredUser() const {
	return isRegistered;
}