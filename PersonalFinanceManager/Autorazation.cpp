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

std::string authMenu() {
	int authChoice;
	std::string l, p;
	Autorize auth;
	while (true) {
		system("cls");
		std::cout << std::string(10, '=') << "Autorization" << std::string(10, '=')
			<< "\n1. Login\n"
			<< "2. Register\n"
			<< "3. Exit Program\n"
			<< "Your choice: ";
		std::cin >> authChoice;

		if (authChoice == 1) {
			system("cls");
			std::cout << "Login: ";
			std::cin >> l;
			std::cout << "Password: ";
			std::cin >> p;
			if (auth.login(l, p)) {
				return l;
			}
			else {
				std::cout << "\n\nwrong password";
				system("pause");
			}
		}
		else if (authChoice == 2) {
			system("cls");
			std::cout << "Create user\nLogin: ";
			std::cin >> l;
			std::cout << "Password: ";
			std::cin >> p;

			auth.registerUser(l, p);
			system("pause");
		}
		else if (authChoice == 3) return "::exit";
		else std::cout << "Wrong choice!";
	}
	return "-ERROR";
}