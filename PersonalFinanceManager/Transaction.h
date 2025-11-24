#pragma once
#include <iostream>
#include <string>
#include <vector>

struct Transaction {
	int id;
	std::string category;
	double amount;
	std::string date;
	std::string description;
	bool isIncome;
};

void ShowAllTransactions(std::vector<Transaction> Transactions);
void addObjects(std::vector<Transaction>& mainDB);