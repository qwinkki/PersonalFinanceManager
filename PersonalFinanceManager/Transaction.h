#pragma once
#include "common.h"

#include <stdexcept>

class Transaction {
	int id;
	std::string category;
	double amount;
	std::string date;
	std::string description;
	bool isIncome;
public:
    Transaction(
        int _id,
        const std::string& _category,
        double _amount,
        const std::string& _date,
        const std::string& _description,
        bool _isIncome)
        : id(_id)
        , category(_category)
        , amount(_amount)
        , date(_date)
        , description(_description)
        , isIncome(_isIncome)
    {
        if (_amount < 0) {
            throw std::invalid_argument("\namount cannot be negative");
        }
		if (_category.empty()) {
			throw std::invalid_argument("\ncathegory cannot be empty");
		}
    }

	int getId() const { return id; }
	const std::string& getCategory() const { return category; }
	double getAmount() const { return amount; }
	const std::string& getDate() const { return date; }
	const std::string& getDescription() const { return description; }
	bool getIsIncome() const { return isIncome; }

	friend std::ostream& operator<<(std::ostream& os, const Transaction& transaction);
};

inline std::ostream& operator<<(std::ostream& os, const Transaction& transaction) {
	os << "id: " << transaction.id
		<< "\ncategory: " << transaction.category
		<< "\namount: " << transaction.amount
		<< "\ndate: " << transaction.date
		<< "\ndescription: " << transaction.description
		<< (transaction.isIncome ? "\nthis is income\n\n" : "\nthis isn't income\n\n");
	return os;
}

void ShowAllTransactions(std::vector<Transaction> Transactions);
void addObjects(std::vector<Transaction>& mainDB);