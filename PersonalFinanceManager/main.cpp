#include "main.h"

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
			break;
		}
		system("cls");
	} while (choice != 6);

	system("cls");
	system("pause");
}
