#include "Database.h"

namespace {
	bool isValid(const std::string& str) {
		for (char c : str)
			if (!std::isalnum(c))
				return false;
		return true;
	}

	bool userExistsInDatabase(const std::string& name) {
		try {
			pqxx::work w(Database::getInstance());
			pqxx::result r = w.exec("SELECT * FROM users WHERE username = " + w.quote(name));
			return !r.empty();
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << '\n';
			return false;
		}
	}
}



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

bool loginUserFromDatabase(const std::string& name, const std::string& pass) {
	try {
		pqxx::work w(Database::getInstance());
		pqxx::result r = w.exec("SELECT * FROM users WHERE username = " + w.quote(name) + " AND password = " + w.quote(pass));
		return r.empty();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
		return false;
	}
}

bool registerUserAndInsertInDatabase(const std::string& name, const std::string& pass) {
	if (!isValid(name)) {
		std::cout << "Username contains special characters\n";
		return false;
	}

	if (userExistsInDatabase(name)) {
		std::cout << "User already exists\n";
		return false;
	}

	try {
		pqxx::work w(Database::getInstance());
		w.exec("INSERT INTO users (username, password) VALUES (" + w.quote(name) + ", " + w.quote(pass) + ")");
		w.commit();

		createUserTableInDatabase(name);
		
		return true;
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
		return false;
	}
}

void createUserTableInDatabase(const std::string& name) {
	try {
		pqxx::work w(Database::getInstance());

		std::string query = "CREATE TABLE IF NOT EXISTS " +
			w.conn().quote_name(name) +
			" (id SERIAL PRIMARY KEY, "
			"category VARCHAR(255) NOT NULL, "
			"amount DECIMAL(12, 2) NOT NULL, "
			"date DATE NOT NULL, "
			"description TEXT DEFAULT '', "
			"is_income BOOLEAN NOT NULL DEFAULT false);";

		w.exec(query);
		w.commit();
	}
	catch (const std::exception& e) {
		std::cerr << "Error creating table: " << e.what() << '\n';
	}
}

void viewAllUsers() {
	try {
		pqxx::work w(Database::getInstance());
		pqxx::result r = w.exec("SELECT id, username, date FROM users ORDER BY id;");

		system("cls");
		std::cout << std::string(7, '=') << "Users" << std::string(7, '=') << '\n';
		if (r.empty()) {
			std::cout << "\n\nNo users found\n";
			system("pause");
		}
		else
			for (const auto& row : r) 
				std::cout << row["id"].as<int>() << "\t" << row["username"].as<std::string>() << "\tDate Registration: " << row["date"].as<std::string>() << '\n';
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
}

void deleteUserByName() {
	viewAllUsers();

	std::string name, pass;
	std::cout << "\nEnter username to delete: ";
	std::cin >> name;

	try {
		pqxx::work w(Database::getInstance());
		pqxx::result r = w.exec("SELECT id, password FROM users WHERE username = " + w.quote(name));
		if (r.empty()) {
			std::cout << "\n\nWrong username, " << name << " not found\n";
			system("pause");
			return;
		}
		
		std::cout << "Enter password of " << name << ": ";
		std::cin >> pass;
		if (pass != r[0]["password"].as<std::string>()) {
			std::cout << "\n\nWrong password\n";
			system("pause");
			return;
		}
		
		w.exec("DELETE FROM users WHERE username = " + w.quote(name));
		w.exec("DROP TABLE IF EXISTS " + w.conn().quote_name(name));
		w.commit();
		std::cout << "User " << name << " with id " << r[0]["id"].as<int>() << " deleted\n\n";
		system("pause");
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
}





void OpenDBAndConvertToVector(std::vector<Transaction>& mainDB, std::string tableName) {
	Database::getInstance();
}