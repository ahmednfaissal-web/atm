#pragma once
#include <map>
#include <stdexcept>
#include <string>
#include "Customer.h"

using namespace std;

class Bank {
private:
    map<string, Customer> customers;

public:
    Bank() {}

    // Adds a new customer. If a customer with the same ID already exists,
    // nothing is changed (the old account is kept) and false is returned.
    // Note: the bank stores a copy of the customer.
    bool addCustomer(const Customer& customer) {
        return customers.emplace(customer.getCustomerID(), customer).second;
    }

    bool validate(const string& customerID,
        const string& pin) const {
        auto it = customers.find(customerID);

        if (it != customers.end()) {
            return it->second.getPin() == pin;
        }

        return false;
    }

    Customer& getCustomer(const string& customerID) {
        auto it = customers.find(customerID);

        if (it != customers.end()) {
            return it->second;
        }

        throw invalid_argument("Customer not found");
    }

    Account& getAccount(const string& customerID) {
        return getCustomer(customerID).getAccount();
    }
};