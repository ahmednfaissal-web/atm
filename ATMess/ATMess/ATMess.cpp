#include "ATM.h"

int main()
{
    // Create the bank and its customers
    // (ID, name, phone, PIN, starting balance)
    Bank bank;
    bank.addCustomer(Customer("C001", "Omar Hassan", "01000000001", "1234", 5000));
    bank.addCustomer(Customer("C002", "Mona Khaled", "01000000002", "4321", 12000));

    // Connect the ATM to the bank and start the menu
    ATM atm(bank);
    atm.methods();

    return 0;
}