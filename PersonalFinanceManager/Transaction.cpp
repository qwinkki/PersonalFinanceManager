#include "Transaction.h"

void ShowAllTransactions(std::vector<Transaction> Transactions) {
	system("cls");
	for (const auto& subTransactions : Transactions)
		std::cout << "id: " << subTransactions.id
		<< "\ncategory: " << subTransactions.category
		<< "\namount: " << subTransactions.amount
		<< "\ndate: " << subTransactions.date
		<< "\ndescription: " << subTransactions.description
		<< (subTransactions.isIncome ? "\nThis is income" : "\nThis isn't income") << "\n\n";
	system("pause");
}

void addObjects(std::vector<Transaction>& mainDB) {
	system("cls");
	Transaction tr;
	int howMuch;
	std::cout << "How much do you need transactions: ";
	std::cin >> howMuch;
	if (std::cin.fail()) 
	{
		std::cout << "wrong input";
		return;
	}
	try {
		for (int i = 0; i < howMuch; i++) {
			if (mainDB.size() > 0)
				tr.id = mainDB[mainDB.size() - 1].id + 1;
			else tr.id = 1;
			std::cout << "\n\nid: " << tr.id << "\ncategory: ";
			std::cin >> tr.category;
			std::cout << "amount: ";
			std::cin >> tr.amount;
			std::cout << "date: ";
			std::cin >> tr.date;
			std::cout << "description: ";
			std::cin >> tr.description;
			std::cout << "is it income? (y/n): ";
			char isIncome;
			std::cin >> isIncome;
			if (isIncome == 'y') tr.isIncome = true;
			else if (isIncome == 'n') tr.isIncome = false;

			mainDB.push_back(tr);
		}
		std::cout << "\n\nSuccesfully added!";
	}
	catch (std::exception e) { std::cout << e.what() << '\n'; }

}