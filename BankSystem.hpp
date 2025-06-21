#ifndef BANK_SYSTEM_HPP
#define BANK_SYSTEM_HPP

#include "Account.hpp"
#include "Graph.hpp"
#include "FraudDetector.hpp"
#include "Trie.hpp"
#include "CreditSystem.hpp"
#include "LRUCache.hpp"
#include "DisjointSet.hpp"
#include <string>
#include <unordered_map>

using namespace std;

class BankSystem {
public:
    BankSystem();
    
    void createAccount(const string& name, const string& pin, bool showMessage = true);

    Account* login(int accountId, const string& pin);
    bool transferMoney(int fromId, int toId, double amount);
    void checkFraud(int startNodeId);
    void suggestConnections(int accountId);
    void searchUser(const string& query);
    void displayRecentTransactions(Account* user);
    void displayAdminDashboard();
    CreditSystem& getCreditSystem();

private:
    unordered_map<int, Account> accounts;
    int nextAccountId;
    Graph transactionGraph;
    FraudDetector fraudDetector;
    Trie userTrie;
    CreditSystem creditSystem;
    unordered_map<int, LRUCache<int, string>> recentTransactionsCache;
};

#endif