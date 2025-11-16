#include "main.h"
#include "Autorization.h"

int main()
{
	/*
	std::cout << "DB connected";
	Sleep(800);
	std::cout << " .";
	Sleep(800);
	std::cout << " .";
	Sleep(800);
	std::cout << " .";
	Sleep(800);
	system("cls");
	*/
	
	Autorize auth;
	int authChoice;
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
			std::string l, p;
			std::cout << "Login: ";
			std::cin >> l;
			std::cout << "Password: ";
			std::cin >> p;
			if (auth.login(l, p)) break;
			else {
				std::cout << "\n\nwrong password";
				system("pause");
			}
		}
		else if (authChoice == 2) {
			system("cls");
			std::string l, p;
			std::cout << "Create user\nLogin: ";
			std::cin >> l;
			std::cout << "Password: ";
			std::cin >> p;

			auth.registerUser(l, p);
			system("pause");
		}
		else if (authChoice == 3) return 0;

	}

	std::vector<Transaction> mainDB;
	OpenDBAndConvertToVector(mainDB);

	int choice;
	do {
		std::cout << std::string(7, '=') << "Personal Finance Manager" << std::string(7, '=') << '\n'
			<< "1. Add Transition\n"
			<< "2. Delete Transaction\n"
			<< "3. Show All Transactions\n"
			<< "4. Show Statistics\n"
			<< "5. Special\n"
			<< "6. Sava & Exit\n"
			<< "Your choice: ";
		std::cin >> choice;
		switch (choice) {
		case 1:
			break;
		case 2:
			break;
		case 3:
			ShowAllTransactions(mainDB);
			break;
		case 4:
			break;
		case 5:
			Special(mainDB);
			break;
		default:
			std::cout << "\n\nWrong choice!";
			break;
		}
		system("cls");
	} while (choice != 6);

	system("cls");
	system("pause");
}
