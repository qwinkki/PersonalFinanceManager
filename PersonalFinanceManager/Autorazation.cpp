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
			else {
				std::cout << "\nWrong login or password\n";
				system("pause");
			}
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
			while(true){
				system("cls");
				std::cout << "1. Delete User\n"
					<< "2. Delete Data in user Table\n"
					<< "3. Exit\n\n"
					<< "Your choice: ";
				std::cin >> authChoiceSpecial;

				
				if (authChoiceSpecial == 1) deleteUserByName();
				else if (authChoiceSpecial == 2) {}
				else if (authChoiceSpecial == 3) break;
				else {
					std::cout << "\nEnter number";
					system("cls");
				}
				
			}
		}
		else if (authChoice == 4) return false;
		else std::cout << "Wrong choice!";
	}
	return false;
}