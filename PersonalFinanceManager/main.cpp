#include "main.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	initializeUserDatabase(); // creating if dont exist user table
	system("pause");

	std::string authChoice;
	bool isAuthorized = false;
	do {

		std::string l, p;

		do {
			system("cls");
			std::cout << std::string(10, '=') << "Autorization" << std::string(10, '=')
				<< "\n1. Login\n"
				<< "2. Register\n"
				<< "3. Special\n"
				<< "4. Exit Program\n"
				<< "Your choice: ";
			std::cin >> authChoice;

			if (authChoice == "1") {
				system("cls");
				std::cout << "Login: ";
				std::cin >> l;
				std::cout << "Password: ";
				std::cin >> p;

				if (loginUserFromDatabase(l, p)) {
					std::cout << "\nWrong login or password\n";
					system("pause");
				}
				else isAuthorized = true;
			}
			else if (authChoice == "2") {
				system("cls");
				std::cout << "Create user\nLogin: ";
				std::cin >> l;
				std::cout << "Password: ";
				std::cin >> p;

				if (registerUserAndInsertInDatabase(l, p))
					std::cout << "\n\nUser succesfully registered!\nTable " + l + " with transactions created\n";

				system("pause");
			}
			else if (authChoice == "3") {
				std::string authChoiceSpecial;

				while (true) {
					system("cls");
					std::cout << "1. Delete User\n"
						<< "2. Delete Data in user Table\n"
						<< "3. Reset everything\n"
						<< "4. Exit\n\n"
						<< "Your choice: ";
					std::cin >> authChoiceSpecial;


					if (authChoiceSpecial == "1") deleteUserByName();
					else if (authChoiceSpecial == "2") ClearUserTable();
					else if (authChoiceSpecial == "3") { if (resetEverything()) return 1; }
					else if (authChoiceSpecial == "4") break;
					else {
						std::cout << "\nEnter number";
						system("cls");
					}

				}
			}
			else if (authChoice == "4") { system("cls"); return 0; }
			else std::cout << "Wrong choice!";
		} while (!isAuthorized);

		std::vector<Transaction> mainDB;
		std::string loggedInUser = l;
		OpenDBAndConvertToVector(mainDB, loggedInUser);

		std::string mainChoice;
		do {
			system("cls");
			std::cout << std::string(7, '=') << "Personal Finance Manager" << std::string(7, '=') << '\n'
				<< "1. Add Transition\n"
				<< "2. Delete Transaction\n"
				<< "3. Show All Transactions\n"
				<< "4. Show Statistics\n"
				<< "5. Special\n"
				<< "6. Sava & Exit\n\n"
				<< "Your choice: ";
			std::cin >> mainChoice;

			if(mainChoice == "1")
				addObjects(mainDB);
			else if (mainChoice == "2") {}
			else if (mainChoice == "3")
				ShowAllTransactions(mainDB);
			else if (mainChoice == "4") {}
			else if (mainChoice == "5")
				Special(mainDB);
			else if (mainChoice == "6") {
				CloseAndSaveDB(mainDB, loggedInUser);
				mainDB.clear();
				l = "";
				loggedInUser = "";
				isAuthorized = false;
			}
			else std::cout << "\n\nWrong choice!";
			system("cls");
		} while (mainChoice != "6");
	} while (true);

	system("cls");
	system("pause");
}