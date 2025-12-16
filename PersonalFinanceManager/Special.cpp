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


    int newId = mainDB.size() > 0 ? mainDB[mainDB.size() - 1].getId() : 0;

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

    int id;
    std::string category;
    double amount;
    std::string date;
    std::string description;
    bool isIncome;

    try {
        for (int i = 0; i < countTr; i++) {

            newId++;
            id = newId;

            std::uniform_int_distribution<int> catDist(0, static_cast<int>(categories.size()) - 1);
            category = categories[catDist(gen)];

            amount = std::round(amountDist(gen) * 100) / 100;

            int day = dayDist(gen);
            int month = monthDist(gen);
            int year = yearDist(gen);

            char dateBuffer[11];
            snprintf(dateBuffer, sizeof(dateBuffer), "%04d-%02d-%02d", year, month, day);
            date = dateBuffer;

            std::uniform_int_distribution<int> descDist(0, static_cast<int>(descriptions.size()) - 1);
            description = descriptions[descDist(gen)];

            isIncome = boolDist(gen);

            newEl.push_back(Transaction(id, category, amount, date, description, isIncome));
            std::cout << "Creating new Transaction with id: " << id << ".. " << COLORGREEN << "OK\n" << COLORDEFAULT;
        }
    }
    catch (const std::exception& e) {
        std::cout << COLORRED << e.what() << "\n" << COLORDEFAULT;
    }

    std::cout << "\n\nSuccesfully generated!\n\n";
    mainDB.insert(mainDB.end(), newEl.begin(), newEl.end());
    system("pause");
}

void deleteAllTransitions(std::vector<Transaction>& Transactions) {
    system("cls");
    std::cout << "Size transformered: " << Transactions.size() << " => ";
    Transactions.clear();
    std::cout << Transactions.size() << '\n';
        if (Transactions.size() == 0)
            std::cout << COLORGREEN << "succesfully cleared\n" << COLORDEFAULT;
        else std::cout << COLORRED << "ERR: Not succesfully cleared\n" << COLORDEFAULT;
    system("pause");
}