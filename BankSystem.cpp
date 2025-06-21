#include "BankSystem.hpp"
#include <iostream>
#include <queue>
#include <set>

using namespace std;

BankSystem::BankSystem() : nextAccountId(1001) {
    createAccount("Alice", "1234", false);
    createAccount("Bob", "5678", false);
    createAccount("Charlie", "1111", false);
    createAccount("David", "2222", false);
    createAccount("Eve", "3333", false);
}

void BankSystem::createAccount(const string& name, const string& pin, bool showMessage) {
    int id = nextAccountId++;
    accounts[id] = Account(id, name, pin, 1000.0);
    userTrie.insert(name, id);
    if (showMessage) {
        cout << "Account created successfully for " << name << ". Your Account ID is: " << id << endl;
    }
}

Account* BankSystem::login(int accountId, const string& pin) {
    if (accounts.count(accountId) && accounts[accountId].pin == pin) {
        return &accounts[accountId];
    }
    return nullptr;
}

bool BankSystem::transferMoney(int fromId, int toId, double amount) {
    if (!accounts.count(fromId) || !accounts.count(toId)) {
        cout << "Error: Invalid sender or receiver account ID." << endl;
        return false;
    }
    if (accounts.at(fromId).balance < amount) {
        cout << "Error: Insufficient funds." << endl;
        return false;
    }

    accounts.at(fromId).withdraw(amount);
    accounts.at(fromId).addTransaction("Sent", amount, toId);
    accounts.at(toId).deposit(amount);
    accounts.at(toId).addTransaction("Received", amount, fromId);

    transactionGraph.addEdge(fromId, toId, amount);
    creditSystem.updateScore(accounts.at(fromId), amount, true);
    creditSystem.updateScore(accounts.at(toId), amount, false);

    if (recentTransactionsCache.find(fromId) == recentTransactionsCache.end()) {
        recentTransactionsCache.emplace(fromId, LRUCache<int, string>(5));
    }
    recentTransactionsCache.at(fromId).put(toId, accounts.at(toId).ownerName);

    cout << "Transfer successful." << endl;
    checkFraud(fromId);
    return true;
}

void BankSystem::checkFraud(int startNodeId) {
    if (fraudDetector.hasCycle(startNodeId, transactionGraph)) {
        cout << "\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
        cout << "!!! FRAUD ALERT: A potential cycle of transactions has been detected." << endl;
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
    }
}

void BankSystem::suggestConnections(int accountId) {
    cout << "--- Transaction Connection Suggestions (BFS) ---" << endl;
    queue<pair<int, int>> q;
    set<int> visited;

    q.push(make_pair(accountId, 0));
    visited.insert(accountId);

    while (!q.empty()) {
        pair<int, int> current = q.front();
        int currentId = current.first;
        int dist = current.second;
        q.pop();

        if (dist > 0 && dist <= 3) {
            cout << "  - Account #" << currentId << " (" << accounts.at(currentId).ownerName << "), "
                 << dist << " hop(s) away." << endl;
        }

        if (dist < 3 && transactionGraph.adjList.count(currentId)) {
            for (const auto& edge : transactionGraph.adjList.at(currentId)) {
                if (visited.find(edge.first) == visited.end()) {
                    visited.insert(edge.first);
                    q.push(make_pair(edge.first, dist + 1));
                }
            }
        }
    }
}

void BankSystem::searchUser(const string& query) {
    vector<pair<string, int>> results = userTrie.search(query);
    cout << "--- Search Results (Trie) ---" << endl;
    if (results.empty()) {
        cout << "No users found matching '" << query << "'." << endl;
    } else {
        for (const auto& result : results) {
            cout << "  - Name: " << result.first << ", Account ID: " << result.second << endl;
        }
    }
}

void BankSystem::displayRecentTransactions(Account* user) {
    if (recentTransactionsCache.count(user->accountId)) {
        recentTransactionsCache.at(user->accountId).display(user->ownerName);
    } else {
        cout << "No recent payees to display from cache." << endl;
    }
}

CreditSystem& BankSystem::getCreditSystem() {
    return creditSystem;
}

void BankSystem::displayAdminDashboard() {
    cout << "========================" << endl;
    cout << "=== ADMIN DASHBOARD ===" << endl;
    cout << "========================" << endl;

    creditSystem.printTopLowScores(5);
    cout << endl;

    transactionGraph.printGraph();
    cout << endl;

    cout << "--- User Transaction Clusters (Disjoint Set) ---" << endl;
    DisjointSet ds(nextAccountId);
    
    for (const auto& user_pair : transactionGraph.adjList) {
        int user = user_pair.first;
        const auto& transactions = user_pair.second;
        for (const auto& trans : transactions) {
            ds.unite(user, trans.first);
        }
    }

    unordered_map<int, vector<int>> clusters;
    for (const auto& acc_pair : accounts) {
        clusters[ds.find(acc_pair.first)].push_back(acc_pair.first);
    }

    int clusterCount = 1;
    for (const auto& cluster_pair : clusters) {
        const auto& members = cluster_pair.second;
        if (members.size() > 1) {
            cout << "Cluster " << clusterCount++ << ": ";
            for (size_t i = 0; i < members.size(); ++i) {
                cout << accounts.at(members[i]).ownerName << " (#" << members[i] << ")" << (i == members.size() - 1 ? "" : ", ");
            }
            cout << endl;
        }
    }
}