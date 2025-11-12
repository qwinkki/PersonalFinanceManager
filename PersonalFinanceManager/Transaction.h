#pragma once
#include <string>
#include <vector>
#include "Transaction.h"


struct Transaction {
	int id;
	std::string category;
	double amount;
	std::string date;
	std::string description;
	bool isIncome;
};

void ShowAllTransactions(std::vector<Transaction> Transactions);