#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Transaction.h"

#include <pqxx/pqxx>

class Database {
	Database();
	static std::unique_ptr<pqxx::connection> conn;
public:
	static pqxx::connection& getInstance();
};

void initializeUserDatabase();
void OpenDBAndConvertToVector(std::vector<Transaction>& mainDB, std::string tableName);