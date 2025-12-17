#include "Transaction.h"

void checkIdVector(std::vector<Transaction>& mainDB) {
	for (std::size_t i = 0; i < mainDB.size(); i++) {
		mainDB[i].setId(i + 1);
	}
}

void ShowAllTransactions(std::vector<Transaction> Transactions) {
	system("cls");
	for (const auto& subTransactions : Transactions)
		std::cout << subTransactions;
}

void addObjects(std::vector<Transaction>& mainDB) {
	system("cls");
	int howMuch;
	std::cout << "How much do you need transactions: ";
	std::cin >> howMuch;
	if (std::cin.fail()) 
	{
		std::cout << COLORYELLOW << "\nwrong input" << COLORDEFAULT;
		return;
	}

	int id;
	std::string category;
	double amount;
	std::string date;
	std::string description;
	bool isIncome;

	std::string isIncomeInput;

	try {
		for (int i = 0; i < howMuch; i++) {
			if (mainDB.size() > 0)
				id = mainDB[mainDB.size() - 1].getId() + 1;
			else id = 1;
			std::cout << "\n\nid: " << id << "\ncategory: ";
			std::cin >> category;
			std::cout << "amount (must be positive): ";
			std::cin >> amount;
			std::cout << "date: ";
			std::cin >> date;
			std::cout << "description: ";
			std::cin >> description;
			std::cout << "is it income? (y/n default: n): ";
			std::cin >> isIncomeInput;
			if (isIncomeInput == "y" || isIncomeInput == "Y") isIncome = true;
			else if (isIncomeInput == "n" || isIncomeInput == "N") isIncome = false;

			mainDB.push_back(Transaction(id, category, amount, date, description, isIncome));
		}
		std::cout << COLORGREEN << "\n\nSuccesfully added!" << COLORDEFAULT;
	}
	catch (std::exception e) { 
		std::cout << COLORRED << e.what() << '\n' << COLORDEFAULT; 
	}

	checkIdVector(mainDB);
}

void deleteItem(std::vector<Transaction>& mainDB) {
	system("cls");
	if (mainDB.size() == 0) {
		std::cout << "transactions are empty\n";
		system("pause");
		return;
	}

	std::size_t size = mainDB.size();
	ShowAllTransactions(mainDB);

	int chosenId;
	std::cout << "\nenter id of trunsaction to delete: ";
	std::cin >> chosenId;

	if (chosenId < 1 || chosenId > static_cast<int>(mainDB.size())) {
		std::cout << COLORYELLOW << "invalid ID!\n" << COLORDEFAULT;
		system("pause");
		return;
	}

	auto it = mainDB.begin() + chosenId - 1;
	mainDB.erase(it);

	checkIdVector(mainDB);
	
	if (size - 1 == mainDB.size())
		std::cout << COLORGREEN << "succesfully deleted\n" << COLORDEFAULT;
	else
		std::cout << COLORYELLOW << "not deleted\n" << COLORDEFAULT;
	system("pause");
}