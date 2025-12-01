#include "Special.h"

void Special(std::vector<Transaction>& mainDB) {
    system("cls");
    int choose;
    do {
        std::cout << "1. Generage Transactions"
            << "\n2. Delete all Transactions"
            << "\n3. Exit"
            << "\nYour choose: ";
        std::cin >> choose;
    
        switch (choose) {
        case 1:
            generateAndAddRndTransactions(mainDB);
            break;
        case 2:
            deleteAllTransitions(mainDB);
            break;
        default:
            break;
        }
        system("cls");
    } while (choose != 3);
}

void generateAndAddRndTransactions(std::vector<Transaction>& mainDB) {
    int countTr;
    std::vector<Transaction> newEl;
    system("cls");
    std::cout << "Choose how much new Transactions you need: ";
    std::cin >> countTr;

    
    int newId = mainDB.size() > 0 ? mainDB[mainDB.size() - 1].id : 0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> amountDist(10.0, 10000.0);
    std::uniform_int_distribution<int> dayDist(1, 28);
    std::uniform_int_distribution<int> monthDist(1, 12);
    std::uniform_int_distribution<int> yearDist(2020, 2024);
    std::uniform_int_distribution<int> boolDist(0, 1);

    std::vector<std::string> categories = {
        "Food", "Transport", "Utilities", "Entertainment",
        "Healthcare", "Education", "Shopping", "Salary",
        "Investment", "Gifts", "Travel", "Other"
    };

    std::vector<std::string> descriptions = {
        "Monthly payment", "Online purchase", "Grocery shopping",
        "Bill payment", "Cash withdrawal", "Transfer",
        "Subscription", "Restaurant", "Fuel", "Medical expenses",
        "Bonus", "Freelance work", "Investment return"
    };

    try {
        for (int i = 0; i < countTr; i++) {
            Transaction transaction;

            newId++;
            transaction.id = newId;

            std::uniform_int_distribution<int> catDist(0, static_cast<int>(categories.size()) - 1);
            transaction.category = categories[catDist(gen)];

            transaction.amount = std::round(amountDist(gen) * 100) / 100;

            int day = dayDist(gen);
            int month = monthDist(gen);
            int year = yearDist(gen);
            transaction.date = std::to_string(day) + "." + std::to_string(month) + "." + std::to_string(year);

            std::uniform_int_distribution<int> descDist(0, static_cast<int>(descriptions.size()) - 1);
            transaction.description = descriptions[descDist(gen)];

            transaction.isIncome = boolDist(gen);

            newEl.push_back(transaction);
            std::cout << "Created new Transaction with id: " << transaction.id << '\n';
        }
    }
    catch (const std::exception& e) {
        std::cout << "\n\nNot succesfully generated: " << e.what() << "\n\n";
    }

    std::cout << "\n\nSuccesfully generated!\n\n";
    mainDB.insert(mainDB.end(), newEl.begin(), newEl.end());
    system("pause");
}

void deleteAllTransitions(std::vector<Transaction>& Transactions) {
    system("cls");
    std::cout << "Size transformered: " << Transactions.size() << " => ";
    Transactions.clear();
    std::cout << Transactions.size() << '\n'
        << (Transactions.size() == 0 ? "Succesfully cleared!\n\n" : "Err: Not Cleared.\n\n");
    system("pause");
}