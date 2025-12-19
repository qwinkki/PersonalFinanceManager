#pragma once
#include "common.h"

#include <unordered_map>
#include <stdexcept>

class Transaction {
	int id;
	std::string category;
	double amount;
	std::string date;
	std::string description;
	bool isIncome;
public:
    Transaction() = default;
    explicit Transaction(
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

	void setId(int newId) { id = newId; }

	int getId() const { return id; }
	const std::string& getCategory() const { return category; }
	double getAmount() const { return amount; }
	const std::string& getDate() const { return date; }
	const std::string& getDescription() const { return description; }
	bool getIsIncome() const { return isIncome; }

	friend std::ostream& operator<<(std::ostream& os, const Transaction& transaction);
};

struct  TransactionMap
{
	std::unordered_map<int, Transaction> data;
	double incomeSum = 0.0;
	double expenseSum = 0.0;

	int incomeCount = 0;
	int expenseCount = 0;

	void add(const Transaction& t) {
		if (data.contains(t.getId()))
			return;

		data.try_emplace(t.getId(), t);

		if (t.getIsIncome()){
			incomeSum += t.getAmount();
			incomeCount++;
		}
		else {
			expenseSum += t.getAmount();
			expenseCount++;
		}
	}

	double totalIncome() const {
		return incomeSum;
	}

	double totalExpense() const {
		return expenseSum;
	}

	double balance() const {
		return incomeSum - expenseSum;
	}

	double avgIncome() const {
		return incomeCount == 0 ? 0.0 : incomeSum / incomeCount;
	}

	double avgExpense() const {
		return expenseCount == 0 ? 0.0 : expenseSum / expenseCount;
	}

	void print() const { 
		system("cls");
		std::cout << "avg income: " << avgIncome()
			<< "\navg expense: " << avgExpense()
			<< "\n\ntotal income: " << totalIncome()
			<< "\ntotal expense: " << totalExpense()
			<< "\nbalance: " << (balance() >= 0 ? COLORGREEN : COLORRED) << balance() << COLORDEFAULT << "\n\n";
		system("pause");
	}
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
void deleteItem(std::vector<Transaction>& mainDB);

void showStatistics(std::vector<Transaction>& mainDB);