#include "Transaction.h"

void checkIdVector(std::vector<Transaction>& mainDB) {
	for (int i = 0; i < mainDB.size(); i++) {
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
	unsigned int howMuch;
	std::cout << "How much do you need transactions: ";
	std::cin >> howMuch;
	if (std::cin.fail()) 
	{
		std::cout << COLORYELLOW << "wrong input\n" << COLORDEFAULT;
		return;
	}

	unsigned int id;
	std::string category;
	double amount;
	std::string date;
	std::string description;
	bool isIncome;

	std::string isIncomeInput;

	try {
		for (unsigned int i = 0; i < howMuch; i++) {
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
		std::cout << COLORGREEN << "\nSuccesfully added!" << COLORDEFAULT;
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



TransactionMap buildTransactionMap(const std::vector<Transaction>& mainDB) {
	TransactionMap map;

	for (const auto& t : mainDB)
		map.add(t);

	return map;
}

void sortBy(std::vector<Transaction> mainDB) {
	while (true) {
		system("cls");
		std::cout << "sort by"
			<< "\n1. id"
			<< "\n2. amount"
			<< "\n3. date"
			<< "\n4. description"
			<< "\n5. exit"
			<< "\n\nwhat type: ";
		char sort, reverse = 'n';
		std::cin >> sort; CINCHAR;

		if (sort == '1' || sort == '2') {
			std::cout << "reverse? (y/n) (default: n): ";
			std::cin >> reverse; CINCHAR;
		}

		if (sort == '1') {
			if (reverse == 'y') {
				std::sort(mainDB.begin(), mainDB.end(),
					[](const Transaction& a, const Transaction& b) {
						return a.getId() > b.getId();
					});
			}

			ShowAllTransactions(mainDB);
			system("pause");
			return;
		}
		else if (sort == '2') {
			if(reverse == 'y') {
				std::sort(mainDB.begin(), mainDB.end(),
					[](const Transaction& a, const Transaction& b) {
						return a.getAmount() < b.getAmount();
					});
			}
			else {
				std::sort(mainDB.begin(), mainDB.end(),
					[](const Transaction& a, const Transaction& b) {
						return a.getAmount() > b.getAmount();
					});
			}

			ShowAllTransactions(mainDB);
			system("pause");
			return;
		}
		else if (sort == '3') {
			std::sort(mainDB.begin(), mainDB.end(),
				[](const Transaction& a, const Transaction& b) {
					return a.getDate() < b.getDate();
				});

			ShowAllTransactions(mainDB);
			system("pause");
			return;
		}
		else if (sort == '4') {
			std::sort(mainDB.begin(), mainDB.end(),
				[](const Transaction& a, const Transaction& b) {
					return a.getDescription() < b.getDescription();
				});

			ShowAllTransactions(mainDB);
			system("pause");
			return;
		}
		else if (sort == '5') return;
		else {
			std::cout << COLORYELLOW << "wront input\n" << COLORDEFAULT;
			system("pause");
		}
	}
}

void showStatistics(std::vector<Transaction>& mainDB) {
	char choose;
	do {
		system("cls");
		std::cout << "1. sort by"
			<< "\n2. statistics of spends"
			<< "\n3. exit"
			<< "\nYour choice: ";
		std::cin >> choose; CINCHAR;

		TransactionMap mainDBMap = buildTransactionMap(mainDB);

		switch (choose)
		{
		case '1':
			sortBy(mainDB);
			break;
		case '2':
			mainDBMap.print();
			break;
		case '3':
			return;
			break;
		default:
			std::cout << COLORYELLOW << "wrong input\n" << COLORDEFAULT;
			system("pause");
			break;
		}
	} while (choose != '3');
}