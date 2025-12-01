#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <cctype>
#include "Transaction.h"

#include <pqxx/pqxx>

class Database {
	Database();
	static std::unique_ptr<pqxx::connection> conn;
public:
	static pqxx::connection& getInstance();
};

void initializeUserDatabase();
bool loginUserFromDatabase(const std::string& name, const std::string& pass);
bool registerUserAndInsertInDatabase(const std::string& name, const std::string& pass);

void deleteUserByName();

void createUserTableInDatabase(const std::string& name);

void OpenDBAndConvertToVector(std::vector<Transaction>& mainDB, std::string tableName);