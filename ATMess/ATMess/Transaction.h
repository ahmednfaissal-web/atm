#pragma once
#include <string>
#include <ctime>

using namespace std;

class Transaction
{
private:
    string transactionID;
    string type;
    double amount;
    time_t date;

public:
    Transaction(const string& id, const string& t, double a)
        : transactionID(id), type(t), amount(a), date(time(nullptr))
    {}

    // Getters are const so they also work on read-only transactions
    string getTransactionID() const { return transactionID; }
    string getType() const { return type; }
    double getAmount() const { return amount; }
    time_t getDate() const { return date; }
};