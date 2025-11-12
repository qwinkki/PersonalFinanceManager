#pragma once
#include <iostream>
#include <vector>
#include "Windows.h"
#include "Transaction.h"
#include "Special.h"

void OpenDBAndConvertToVector(std::vector<Transaction>& Transactions) {

	Transaction a, b;
	a.id = 12414;
	a.category = "abc";
	a.amount = 123.123;
	a.date = "12:32 12.01.2001";
	a.description = "skfjghkyusg";
	a.isIncome = true;
	b.id = 14524352;
	b.category = "asdsaadf";
	b.amount = 321.321;
	b.date = "12312312312312";
	b.description = "123ouhfgiud";
	b.isIncome = false;

	Transactions.push_back(a);
	Transactions.push_back(b);
}