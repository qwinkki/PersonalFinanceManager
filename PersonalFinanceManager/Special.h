#pragma once
#include "common.h"

#include "Transaction.h"
#include <random>
#include <ctime>

void Special(std::vector<Transaction>& mainDB);

void generateAndAddRndTransactions(std::vector<Transaction>& mainDB);
void deleteAllTransitions(std::vector<Transaction>& Transitions);