#pragma once
#include <cmath>
#include <stdexcept>
#include <string>
#include <vector>
#include "Transaction.h"

using namespace std;

class Account
{
private:
    string accountnumber;
    double balance;
    vector<Transaction> transactions;

    // Only positive, real numbers are valid amounts
    // (rejects 0, negative numbers, NaN and infinity).
    static bool validAmount(double amount)
    {
        return std::isfinite(amount) && amount > 0;
    }

    // Saves a record of a successful deposit or withdrawal.
    void record(const string& type, double amount)
    {
        string id = accountnumber + "-T" + to_string(transactions.size() + 1);
        transactions.push_back(Transaction(id, type, amount));
    }

public:
    Account() : accountnumber("default"), balance(0) {}

    Account(const string& id, double initialBalance)
        : accountnumber(id), balance(initialBalance)
    {
        if (!std::isfinite(initialBalance) || initialBalance < 0)
            throw invalid_argument("Initial balance must be zero or more");
    }

    string getAccountNumber() const {
        return accountnumber;
    }

    double getBalance() const {
        return balance;
    }

    const vector<Transaction>& getTransactions() const {
        return transactions;
    }

    bool deposit(double amount)
    {
        if (!validAmount(amount))
            return false;

        balance += amount;
        record("Deposit", amount);
        return true;
    }

    // Takes the money out of the account. Returns false (and changes
    // nothing) if the amount is invalid or bigger than the balance.
    // The ATM rules (limit, available notes) are checked in ATM::withdraw.
    bool withdraw(double amount)
    {
        if (!validAmount(amount) || amount > balance)
            return false;

        balance -= amount;
        record("Withdrawal", amount);
        return true;
    }
};