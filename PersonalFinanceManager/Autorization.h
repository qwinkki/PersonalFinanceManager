#pragma once
#include <iostream>
#include <string>
#include <cctype>
#include "Database.h"




bool loginUserFromDatabase(const std::string& name, const std::string& pass);
bool registerUserAndInsertInDatabase(const std::string& name, const std::string& pass);

void deleteUserByName();
void ClearUserTable();

void createUserTableInDatabase(const std::string& name);
