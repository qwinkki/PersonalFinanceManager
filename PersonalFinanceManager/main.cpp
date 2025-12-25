#include "main.h"

int main()
{
	initializeUserDatabase(); // creating if dont exist user table
	system("pause");

	bool isAuthorized = false;
	while(true) {

		std::string l, p;

		do {
			system("cls");
			std::cout << std::string(10, '=') << "Autorization" << std::string(10, '=')
				<< "\n1. Login\n"
				<< "2. Register\n"
				<< "3. Special\n"
				<< "4. Exit Program\n"
				<< "Your choice: ";

			char authChoice;
			std::cin >> authChoice; CINCHAR;

			if (authChoice == '1') {
				system("cls");
				std::cout << "Login: ";
				std::cin >> l;
				std::cout << "Password: ";
				std::cin >> p;

				if (loginUserFromDatabase(l, p)) {
					std::cout << COLORYELLOW << "\nWrong login or password\n" << COLORDEFAULT;
					system("pause");
				}
				else isAuthorized = true;
			}
			else if (authChoice == '2') {
				system("cls");
				std::cout << "Create user\nLogin: ";
				std::cin >> l;
				std::cout << "Password: ";
				std::cin >> p;

				if (registerUserAndInsertInDatabase(l, p))
					std::cout << "\n\nUser succesfully registered!\nTable " + l + " with transactions created\n";

				system("pause");
			}
			else if (authChoice == '3') {
				char authChoiceSpecial;
				do {
					system("cls");
					std::cout << "1. Delete User\n"
						<< "2. Delete Data in user Table\n"
						<< "3. Reset everything\n"
						<< "4. Exit\n\n"
						<< "Your choice: ";
					std::cin >> authChoiceSpecial; CINCHAR;

					switch (authChoiceSpecial)
					{
					case '1':
						deleteUserByName();
						break;
					case '2':
						ClearUserTable();
						break;
					case '3':
						resetEverything();
						break;
					case '4':
						break;
					default:
						std::cout << "enter number\n";
						system("pause");
						break;
					}
				} while (authChoiceSpecial != '4');
			}
			else if (authChoice == '4') { system("cls"); return 0; }
			else {
				std::cout << COLORYELLOW << "Wrong input\n" << COLORDEFAULT;
				system("pause");
			}
		} while (!isAuthorized);

		std::vector<Transaction> mainDB;
		std::string loggedInUser = l;
		OpenDBAndConvertToVector(mainDB, loggedInUser);

		char mainChoice;
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
			std::cin >> mainChoice; CINCHAR;

			switch (mainChoice)
			{
			case '1':
				addObjects(mainDB);
				break;
			case '2':
				deleteItem(mainDB);
				break;
			case '3':
				ShowAllTransactions(mainDB);
				system("pause");
				break;
			case '4':
				showStatistics(mainDB);
				break;
			case '5':
				Special(mainDB);
				break;
			case '6':
				CloseAndSaveDB(mainDB, loggedInUser);
				mainDB.clear();
				l = "";
				loggedInUser = "";
				isAuthorized = false;
				break;
			default:
				std::cout << COLORYELLOW << "wrong input\n" << COLORDEFAULT;
				system("pause");
				break;
			}
		} while (mainChoice != '6');
	}

	system("cls");
	system("pause");
}