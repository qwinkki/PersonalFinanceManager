#include "Transaction.h"

void ShowAllTransactions(std::vector<Transaction> Transactions) {
	system("cls");
	for (const auto& subTransactions : Transactions)
		std::cout << subTransactions;
	system("pause");
}

void addObjects(std::vector<Transaction>& mainDB) {
	system("cls");
	int howMuch;
	std::cout << "How much do you need transactions: ";
	std::cin >> howMuch;
	if (std::cin.fail()) 
	{
		std::cout << "\nwrong input";
		return;
	}

	int id;
	std::string category;
	double amount;
	std::string date;
	std::string description;
	bool isIncome;

	char isIncomeInput;

	try {
		for (int i = 0; i < howMuch; i++) {
			if (mainDB.size() > 0)
				id = mainDB[mainDB.size() - 1].getId() + 1;
			else id = 1;
			std::cout << "\n\nid: " << id << "\ncategory: ";
			std::cin >> category;
			std::cout << "amount: ";
			std::cin >> amount;
			std::cout << "date: ";
			std::cin >> date;
			std::cout << "description: ";
			std::cin >> description;
			std::cout << "is it income? (y/n): ";
			std::cin >> isIncomeInput;
			if (isIncomeInput == 'y') isIncome = true;
			else if (isIncomeInput == 'n') isIncome = false;

			mainDB.push_back(Transaction(id, category, amount, date, description, isIncome));
		}
		std::cout << "\n\nSuccesfully added!";
	}
	catch (std::exception e) { std::cout << e.what() << '\n'; }

}