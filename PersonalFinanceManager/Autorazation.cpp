#include "Autorization.h"

//to use without database
/*
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
*/



bool authMenu(std::string& l) {
	int authChoice;
	std::string p;
	
	while (true) {
		system("cls");
		std::cout << std::string(10, '=') << "Autorization" << std::string(10, '=')
			<< "\n1. Login\n"
			<< "2. Register\n"
			<< "3. Special\n"
			<< "4. Exit Program\n"
			<< "Your choice: ";
		std::cin >> authChoice;

		if (authChoice == 1) {
			system("cls");
			std::cout << "Login: ";
			std::cin >> l;
			std::cout << "Password: ";
			std::cin >> p;
			
			if (!loginUserFromDatabase(l, p)) 
				return true;
		}
		else if (authChoice == 2) {
			system("cls");
			std::cout << "Create user\nLogin: ";
			std::cin >> l;
			std::cout << "Password: ";
			std::cin >> p;

			if (registerUserAndInsertInDatabase(l, p)) 
				std::cout << "\n\nUser succesfully registered!\nTable " + l + " with transactions created\n";

			system("pause");
		}
		else if (authChoice == 3) {
			int authChoiceSpecial;
			do {
				system("cls");
				std::cout << "\n1. Delete User\n"
					<< "2. Delete Table with Data by User\n"
					<< "3. Exit\n"
					<< "Your choice: ";
				std::cin >> authChoiceSpecial;

				switch (authChoiceSpecial) // do
				{
				case 1:
					break;
				case 2:
					break;
				default:
					break;
				}
			} while (authChoiceSpecial != 3);
		}
		else if (authChoice == 4) return false;
		else std::cout << "Wrong choice!";
	}
	return false;
}