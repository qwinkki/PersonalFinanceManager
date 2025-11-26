#include "Database.h"

std::unique_ptr<pqxx::connection> Database::conn = nullptr;
Database::Database() {
	system("cls");
	std::cout << "Start connection to Database\n";
	if(!conn)
		try {
			conn = std::make_unique<pqxx::connection>("postgresql://postgres:123@localhost:5432/PersonalFinanceManager");
			if (conn->is_open())
				std::cout << "Database opened\n";
			else {
				std::cout << "ERROR: Database in not opened\n";
				exit(1);
			}
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
			exit(1);
		}
}

pqxx::connection& Database::getInstance() {
	if (!conn) static Database instance;
	return *conn;
}

//concept
void initializeUserDatabase() {
	try {
		pqxx::work w(Database::getInstance());
		w.exec("CREATE TABLE IF NOT EXISTS users (id SERIAL PRIMARY KEY, username TEXT NOT NULL UNIQUE, password TEXT NOT NULL);");
		w.commit();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
}

void OpenDBAndConvertToVector(std::vector<Transaction>& mainDB, std::string tableName) {
	Database::getInstance();
}