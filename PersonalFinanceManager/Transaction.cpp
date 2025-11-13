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