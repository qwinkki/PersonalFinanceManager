#include "Database.h"

// MAIN CONNECTION
pqxx::connection& Database::getInstance() {
	if (!conn) static Database instance;
	return *conn;
}
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


void initializeUserDatabase() {
	try {
		pqxx::work w(Database::getInstance());
		w.exec("CREATE TABLE IF NOT EXISTS users (id SERIAL PRIMARY KEY, username TEXT NOT NULL UNIQUE, password TEXT NOT NULL, date TIMESTAMP DEFAULT DATE_TRUNC('SECOND', CURRENT_TIMESTAMP));");
		w.commit();
		std::cout << "Succesfully initialize user table in database.\n";
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
}




void OpenDBAndConvertToVector(std::vector<Transaction>& mainDB, std::string tableName) {
	try {
		pqxx::work w(Database::getInstance());
		pqxx::result r = w.exec("SELECT id, category, amount, date, description, is_income FROM " + w.quote_name(tableName));

		mainDB.clear();
		if (!r.empty())
			for (const auto& row : r) {
				Transaction t;
				t.id = row["id"].as<int>();
				t.category = row["category"].as<std::string>();
				t.amount = row["amount"].as<double>();
				t.date = row["date"].as<std::string>();
				t.description = row["description"].as<std::string>();
				t.isIncome = row["is_income"].as<bool>();

				mainDB.push_back(t);
			}
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
}

void CloseAndSaveDB(const std::vector<Transaction>& mainDB, const std::string& tableName) {
	if (tableName.empty()) {
		return;
	}

	try {
		pqxx::work w(Database::getInstance());
		w.exec("DELETE FROM " + w.quote_name(tableName) + ";");

		for (const auto& t : mainDB) {
			w.exec("INSERT INTO " + w.quote_name(tableName) +
				" (category, amount, date, description, is_income) VALUES (" +
				w.quote(t.category) + ", " +
				w.quote(t.amount) + ", " +
				w.quote(t.date) + ", " +
				w.quote(t.description) + ", " +
				w.quote(t.isIncome) + ");");
		}

		w.commit();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
}