#pragma once
#include <string>
#include "Bank.h"
#include "Customer.h"
#include "CashDispenser.h"

using namespace std;

class ATM
{
    Bank bank;
    CashDispenser cashDispenser;
    double capacity;        // cash currently inside the machine (EGP)
    double maxWithdrawal;   // limit for one withdrawal (EGP)

public:
    ATM() : bank(), cashDispenser(),
        capacity(100000), maxWithdrawal(10000) {}

    // The ATM works with the customers of this bank
    // (it keeps its own copy of the bank).
    explicit ATM(const Bank& connectedBank) : bank(connectedBank),
        cashDispenser(), capacity(100000), maxWithdrawal(10000) {}

    // Returns the customer if the ID and PIN are correct, otherwise nullptr.
    const Customer* login(const string& customerID, const string& pin);

    bool deposit(const Customer& customer, double amount);
    bool withdraw(const Customer& customer, double amount);
    double checkBalance(const Customer& customer);

    // Runs the console menu.
    void methods();
};