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
				std::cout << COLORGREEN << "Database opened\n" << COLORDEFAULT;
			else {
				std::cout << COLORRED << "ERROR: Database in not opened\n" << COLORDEFAULT;
				exit(1);
			}
		}
		catch (const std::exception& e) {
			std::cerr << COLORRED << e.what() << '\n' << COLORDEFAULT;
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
		std::cerr << COLORRED << e.what() << '\n' << COLORDEFAULT;
	}
}




void OpenDBAndConvertToVector(std::vector<Transaction>& mainDB, std::string tableName) {
	try {
		pqxx::work w(Database::getInstance());
		pqxx::result r = w.exec("SELECT id, category, amount, date, description, is_income FROM " + w.quote_name(tableName));

		int id;
		std::string category;
		double amount;
		std::string date;
		std::string description;
		bool isIncome;

		mainDB.clear();
		if (!r.empty())
			for (const auto& row : r) {
				id = row["id"].as<int>();
				category = row["category"].as<std::string>();
				amount = row["amount"].as<double>();
				date = row["date"].as<std::string>();
				description = row["description"].as<std::string>();
				isIncome = row["is_income"].as<bool>();

				mainDB.push_back(Transaction(id, category, amount, date, description, isIncome));
			}
	}
	catch (const std::exception& e) {
		std::cerr << COLORRED << e.what() << '\n' << COLORDEFAULT;
	}
}

void CloseAndSaveDB(const std::vector<Transaction>& mainDB, const std::string& tableName) {
	if (tableName.empty()) {
		return;
	}

	try {
		pqxx::work w(Database::getInstance());
		w.exec("TRUNCATE TABLE " + w.quote_name(tableName) + " RESTART IDENTITY;");

		for (const auto& t : mainDB) {
			w.exec("INSERT INTO " + w.quote_name(tableName) +
				" (category, amount, date, description, is_income) VALUES (" +
				w.quote(t.getCategory()) + ", " +
				w.quote(t.getAmount()) + ", " +
				w.quote(t.getDate()) + ", " +
				w.quote(t.getDescription()) + ", " +
				w.quote(t.getIsIncome()) + ");");
		}

		w.commit();
	}
	catch (const std::exception& e) {
		std::cerr << COLORRED << e.what() << '\n' << COLORDEFAULT;
	}
}