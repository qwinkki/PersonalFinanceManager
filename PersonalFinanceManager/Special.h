#pragma once
#include "Transaction.h"
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>

void Special(std::vector<Transaction>& mainDB);

void generateAndAddRndTransactions(std::vector<Transaction>& mainDB);
void deleteAllTransitions(std::vector<Transaction>& Transitions);