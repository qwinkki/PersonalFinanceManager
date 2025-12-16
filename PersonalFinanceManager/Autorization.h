#pragma once
#include <iostream>
#include <string>
#include <cctype>
#include "Database.h"

#define COLORGREEN "\033[32m"
#define COLORRED "\033[31m"
#define COLORDEFAULT "\033[0m"

bool loginUserFromDatabase(const std::string& name, const std::string& pass);
bool registerUserAndInsertInDatabase(const std::string& name, const std::string& pass);

void deleteUserByName();
void ClearUserTable();
bool resetEverything();

void createUserTableInDatabase(const std::string& name);
