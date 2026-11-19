#pragma once
#include <string>
#include "Account.h"

using namespace std;

class Customer
{
private:
    string customerID;
    string name;
    string phone;
    string pin;
    Account account;

public:
    // Every customer gets their own account. Its number is built from the
    // customer ID (for example "ACC-C001") and it starts with initialBalance.
    Customer(const string& id, const string& fullName,
        const string& phoneNumber, const string& pinCode,
        double initialBalance = 0)
        : customerID(id), name(fullName), phone(phoneNumber),
        pin(pinCode), account("ACC-" + id, initialBalance)
    {}

    // Getters
    string getCustomerID() const {
        return customerID;
    }

    string getName() const {
        return name;
    }

    string getPhone() const {
        return phone;
    }

    string getPin() const {
        return pin;
    }

    // Return modifiable Account
    Account& getAccount() {
        return account;
    }

    // Return read-only Account
    const Account& getAccount() const {
        return account;
    }
};