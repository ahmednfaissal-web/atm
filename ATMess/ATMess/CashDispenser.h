#pragma once
#include <cmath>
#include <iostream>

using namespace std;

// Pays out cash using 200, 100 and 50 EGP notes (biggest notes first).
class CashDispenser
{
public:
    // True if the amount can be paid exactly with these notes,
    // which means it is a multiple of 50 (50, 100, 150, ...).
    bool canDispense(double amount) const
    {
        const double biggestPayout = 1000000;

        return amount >= 50 && amount <= biggestPayout
            && std::fmod(amount, 50.0) == 0;
    }

    // Shows how many notes of each kind the customer receives.
    // Returns false (and prints nothing) if the amount cannot be paid exactly.
    bool dispense(double amount) const
    {
        if (!canDispense(amount))
            return false;

        int total = static_cast<int>(amount);

        int notes200 = total / 200;
        total %= 200;
        int notes100 = total / 100;
        total %= 100;
        int notes50 = total / 50;

        cout << "You will receive: \n";
        cout << "200 EGP notes: " << notes200 << endl;
        cout << "100 EGP notes: " << notes100 << endl;
        cout << "50 EGP notes: " << notes50 << endl;
        return true;
    }
};