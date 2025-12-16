#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Transaction.h"

#include <pqxx/pqxx>

#define COLORGREEN "\033[32m"
#define COLORRED "\033[31m"
#define COLORDEFAULT "\033[0m"

class Database {
	Database();
	static std::unique_ptr<pqxx::connection> conn;
public:
	static pqxx::connection& getInstance();
};

void initializeUserDatabase();

void OpenDBAndConvertToVector(std::vector<Transaction>& mainDB, std::string tableName);
void CloseAndSaveDB(const std::vector<Transaction>& mainDB, const std::string& tableName);