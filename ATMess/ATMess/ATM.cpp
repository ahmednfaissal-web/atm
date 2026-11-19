#include "ATM.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

namespace
{
    template <typename T>
    bool readValue(T& value)
    {
        if (cin >> value)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return true;
        }

        if (!cin.eof())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        return false;
    }
    string money(double value)
    {
        ostringstream out;
        out << fixed << setprecision(2) << value << " EGP";
        return out.str();
    }
}

const Customer* ATM::login(const string& customerID, const string& pin)
{
    if (!bank.validate(customerID, pin))
        return nullptr;

    return &bank.getCustomer(customerID);
}

double ATM::checkBalance(const Customer& customer)
{
    return bank.getAccount(customer.getCustomerID()).getBalance();
}

bool ATM::deposit(const Customer& customer, double amount)
{
    if (!isfinite(amount) || amount <= 0)
    {
        cout << "Amount must be greater than zero.\n";
        return false;
    }

    Account& account = bank.getAccount(customer.getCustomerID());
    return account.deposit(amount);
}

bool ATM::withdraw(const Customer& customer, double amount)
{
    if (!isfinite(amount) || amount <= 0)
    {
        cout << "Amount must be greater than zero.\n";
        return false;
    }

    if (amount > maxWithdrawal)
    {
        cout << "The maximum withdrawal is " << money(maxWithdrawal) << ".\n";
        return false;
    }

    // Check this BEFORE taking money from the account
    if (!cashDispenser.canDispense(amount))
    {
        cout << "Amount must be a multiple of 50 EGP.\n";
        return false;
    }

    if (amount > capacity)
    {
        cout << "This ATM does not have enough cash.\n";
        return false;
    }

    Account& account = bank.getAccount(customer.getCustomerID());

    if (!account.withdraw(amount))
    {
        cout << "Insufficient balance.\n";
        return false;
    }

    cashDispenser.dispense(amount);
    capacity -= amount;
    return true;
}

void ATM::methods()
{
    string id, pin;

    cout << "Enter Customer ID: ";
    readValue(id);

    cout << "Enter PIN: ";
    readValue(pin);

    const Customer* customer = login(id, pin);

    if (customer == nullptr)
    {
        cout << "\nInvalid Customer ID or PIN!\n";
        return;
    }

    cout << "\nLogin Successful!\n";
    cout << "Welcome " << customer->getName() << endl;
    cout << "Balance: " << money(checkBalance(*customer)) << endl;

    int choice = 0;

    while (choice != 4)
    {
        cout << "\nChoose the method you want to use:\n";
        cout << "1. Deposit\n";
        cout << "2. Withdraw\n";
        cout << "3. Check Balance\n";
        cout << "4. Exit\n";

        cout << "Enter your choice: ";

        if (!readValue(choice))
        {
            if (cin.eof())      
                break;

            cout << "Invalid input. Please enter a number from 1 to 4.\n";
            choice = 0;
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            double amount;

            cout << "Enter deposit amount: ";
            if (!readValue(amount))
            {
                cout << "Invalid amount!\n";
                break;
            }

            if (deposit(*customer, amount))
                cout << "Deposit successful!\n";
            else
                cout << "Deposit failed!\n";

            break;
        }

        case 2:
        {
            double amount;

            cout << "Enter withdrawal amount: ";
            if (!readValue(amount))
            {
                cout << "Invalid amount!\n";
                break;
            }

            if (withdraw(*customer, amount))
                cout << "Withdrawal successful!\n";
            else
                cout << "Withdrawal failed!\n";

            break;
        }

        case 3:
            cout << "Current Balance: "
                << money(checkBalance(*customer)) << endl;
            break;

        case 4:
            cout << "Thank you for using our ATM. Goodbye!\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }
    }
}