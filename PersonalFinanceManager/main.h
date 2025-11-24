#pragma once
#include <iostream>
#include <vector>
#include "Windows.h"
#include "Transaction.h"
#include "Special.h"
#include "Autorization.h"

void OpenDBAndConvertToVector(std::vector<Transaction>& mainDB, std::string tableName);