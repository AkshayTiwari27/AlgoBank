#include <iostream>
#include <string>
#include <limits>
#include "BankSystem.hpp"
#include "Account.hpp"
#include "utils.hpp"

using namespace std;

void showLoggedInMenu(BankSystem& bank, Account* user);

void showLoginMenu(BankSystem& bank) {
    int accountId;
    string pin;
    
    cout << "\n--- Login ---" << endl;
    cout << "Enter Account ID: ";
    cin >> accountId;
    cout << "Enter PIN: ";
    cin >> pin;
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Account* user = bank.login(accountId, pin);
    if (user) {
        cout << "Login successful! Welcome, " << user->ownerName << "." << endl;
        pressEnterToContinue();
        showLoggedInMenu(bank, user);
    } else {
        cout << "Invalid Account ID or PIN." << endl;
        pressEnterToContinue();
    }
}

void showCreateAccountMenu(BankSystem& bank) {
    string name, pin;
    cout << "\n--- Create New Account ---" << endl;
    cout << "Enter your full name: ";
    getline(cin, name);
    cout << "Create a PIN: ";
    cin >> pin;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    bank.createAccount(name, pin);
    pressEnterToContinue();
}

int main() {
    BankSystem bank;
    int choice = 0;

    while (choice != 9) {
        clearScreen();
        cout << "===================================" << endl;
        cout << "=== Welcome to AlgoBank System ===" << endl;
        cout << "===================================" << endl;
        cout << "1. Login" << endl;
        cout << "2. Create Account" << endl;
        cout << "3. Admin Dashboard" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            choice = 0; 
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                showLoginMenu(bank);
                break;
            case 2:
                showCreateAccountMenu(bank);
                break;
            case 3:
                clearScreen();
                bank.displayAdminDashboard();
                pressEnterToContinue();
                break;
            case 9:
                cout << "Thank you for using AlgoBank. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                pressEnterToContinue();
        }
    }
    return 0;
}

void showLoggedInMenu(BankSystem& bank, Account* user) {
    int choice = 0;
    while (choice != 9) {
        clearScreen();
        cout << "--- Welcome " << user->ownerName << " (Account #" << user->accountId << ") ---" << endl;
        cout << "Balance: $" << user->balance << endl;
        cout << "Credit Score: " << bank.getCreditSystem().getScore(user->accountId) << endl;
        cout << "------------------------------------" << endl;
        cout << "1. Transfer Money" << endl;
        cout << "2. View Transaction History" << endl;
        cout << "3. View Recent Payees (LRU Cache)" << endl;
        cout << "4. Get Connection Suggestions (BFS)" << endl;
        cout << "5. Search for a User (Trie)" << endl;
        cout << "6. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            choice = 0;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');


        switch (choice) {
            case 1: {
                int toId;
                double amount;
                cout << "Enter recipient Account ID: ";
                cin >> toId;
                cout << "Enter amount: $";
                cin >> amount;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                bank.transferMoney(user->accountId, toId, amount);
                pressEnterToContinue();
                break;
            }
            case 2: {
                cout << "\n--- Transaction History ---" << endl;
                for (const auto& t : user->transactionHistory) {
                    cout << t << endl;
                }
                pressEnterToContinue();
                break;
            }
            case 3:
                bank.displayRecentTransactions(user);
                pressEnterToContinue();
                break;
            case 4:
                bank.suggestConnections(user->accountId);
                pressEnterToContinue();
                break;
            case 5: {
                string query;
                cout << "Enter name prefix to search: ";
                getline(cin, query);
                bank.searchUser(query);
                pressEnterToContinue();
                break;
            }
            case 9:
                cout << "Logging out..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                pressEnterToContinue();
        }
    }
}