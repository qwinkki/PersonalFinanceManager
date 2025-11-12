#include "Special.h"
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>

void Special(std::vector<Transaction>& mainDB) {
    system("cls");
    int choose;
    std::vector<Transaction> v;
    do {
        std::cout << "1. Generage Transactions"
            << "\n2. Delete all Transactions"
            << "\n3. Exit"
            << "\nYour choose: ";
        std::cin >> choose;
    
        switch (choose) {
        case 1:
            v = generateAndAddRndTransactions();
            mainDB.insert(mainDB.end(), v.begin(), v.end());
            system("pause");
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

std::vector<Transaction> generateAndAddRndTransactions() {
    int countTr;
    std::vector<Transaction> newEl;
    system("cls");
    std::cout << "Choose how much new Transactions you need: ";
    std::cin >> countTr;

    // Инициализация генератора случайных чисел
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> amountDist(10.0, 10000.0);
    std::uniform_int_distribution<int> idDist(1000, 9999);
    std::uniform_int_distribution<int> dayDist(1, 28);
    std::uniform_int_distribution<int> monthDist(1, 12);
    std::uniform_int_distribution<int> yearDist(2020, 2024);
    std::uniform_int_distribution<int> boolDist(0, 1);

    // Массивы для случайных данных
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

            // Генерация случайного ID
            transaction.id = idDist(gen);

            // Случайная категория
            std::uniform_int_distribution<int> catDist(0, categories.size() - 1);
            transaction.category = categories[catDist(gen)];

            // Случайная сумма
            transaction.amount = std::round(amountDist(gen) * 100) / 100; // Округление до 2 знаков

            // Случайная дата
            int day = dayDist(gen);
            int month = monthDist(gen);
            int year = yearDist(gen);
            transaction.date = std::to_string(day) + "." + std::to_string(month) + "." + std::to_string(year);

            // Случайное описание
            std::uniform_int_distribution<int> descDist(0, descriptions.size() - 1);
            transaction.description = descriptions[descDist(gen)];

            // Случайный тип транзакции (доход/расход)
            transaction.isIncome = boolDist(gen);

            newEl.push_back(transaction);
        }
    }
    catch (std::exception e) {
        std::cout << "Not succesfully generated\n\n";
    }

    std::cout << "Succesfully generated!\n\n";
    return newEl;
}

void deleteAllTransitions(std::vector<Transaction>& Transactions) {
    system("cls");
    Transactions.clear();
    std::cout << "Succesfully cleared!\n\n";
    system("pause");
}