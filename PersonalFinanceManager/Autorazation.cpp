#include "Autorization.h"

//to use without database
/*
bool Autorize::registerUser(const std::string& name, const std::string& pass) {

	username = name;
	password = pass;
	isRegistered = true;

	return false;
}

bool Autorize::login(const std::string& name, const std::string& pass) {

	if (!isRegistered)
		return false;

	return (name == username && password == pass);
}

bool Autorize::hasRegisteredUser() const {
	return isRegistered;
}
*/



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
			"date VARCHAR(255) DEFAULT '', "
			"description TEXT DEFAULT '', "
			"is_income BOOLEAN NOT NULL DEFAULT false);";

		w.exec(query);
		w.commit();
	}
	catch (const std::exception& e) {
		std::cerr << "Error creating table: " << e.what() << '\n';
	}
}

bool viewAllUsers() {
	try {
		pqxx::work w(Database::getInstance());
		pqxx::result r = w.exec("SELECT id, username, date FROM users ORDER BY id;");

		system("cls");
		std::cout << std::string(7, '=') << "Users" << std::string(7, '=') << '\n';
		if (r.empty()) {
			std::cout << "\n\nNo users found\n";
			system("pause");
			return false;
		}
		else
			for (const auto& row : r)
				std::cout << row["id"].as<int>() << "\t" << row["username"].as<std::string>() << "\tDate Registration: " << row["date"].as<std::string>() << '\n';
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	return true;
}

void deleteUserByName() {
	if (!viewAllUsers()) return;

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

void ClearUserTable() {
	if (!viewAllUsers()) return;

	std::cout << "\nEnter username to delete all trunsaction: ";
	std::string name, pass;
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

		w.exec("DELETE FROM " + w.quote_name(name) + ";");
		w.commit();
		std::cout << "All " << name << " transactions with id " << r[0]["id"].as<int>() << " are deleted\n";
		system("pause");
	}
	catch (std::exception& e) {
		std::cerr << e.what();
	}
}