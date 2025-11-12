#include "Transaction.h"
#include <iostream>

void ShowAllTransactions(std::vector<Transaction> Transactions) {
	system("cls");
	for (const auto& sunTransactions : Transactions)
		std::cout << "id: " << sunTransactions.id
		<< "\ncategory: " << sunTransactions.category
		<< "\namount: " << sunTransactions.amount
		<< "\ndate: " << sunTransactions.date
		<< "\ndescription: " << sunTransactions.description
		<< (sunTransactions.isIncome ? "\nThis is income" : "\nThis isn't income") << "\n\n";
	system("pause");
}