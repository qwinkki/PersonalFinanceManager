#include "main.h"

int main()
{
	initializeUserDatabase(); // creating if dont exist user table
	system("pause");

	std::string login;
	do {

		if (!authMenu(login)) return 0;

		std::vector<Transaction> mainDB;
		OpenDBAndConvertToVector(mainDB, login); 

		int mainChoice;
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
			switch (mainChoice) {
			case 1:
				addObjects(mainDB);
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
			case 6:
				// exit and save db
				break;
			default:
				std::cout << "\n\nWrong choice!";
				break;
			}
			system("cls");
		} while (mainChoice != 6);
	} while (login != "::exit");

	system("cls");
	system("pause");
}