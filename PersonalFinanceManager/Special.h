#pragma once
#include "Transaction.h"

void Special(std::vector<Transaction>& mainDB);

std::vector<Transaction> generateAndAddRndTransactions();
void deleteAllTransitions(std::vector<Transaction>& Transitions);