#include "CreditSystem.hpp"
#include <iostream>

using namespace std;

void CreditSystem::updateScore(Account& account, double transactionAmount, bool isSender) {
    if (scores.find(account.accountId) == scores.end()) {
        scores[account.accountId] = 500;
    }

    double impact = transactionAmount / 100.0;
    if (isSender) {
        scores[account.accountId] -= impact;
    } else {
        scores[account.accountId] += impact * 0.5;
    }

    if (scores[account.accountId] < 0) scores[account.accountId] = 0;
    if (scores[account.accountId] > 1000) scores[account.accountId] = 1000;
}

double CreditSystem::getScore(int accountId) {
    if (scores.find(accountId) != scores.end()) {
        return scores[accountId];
    }
    return 500;
}

void CreditSystem::printTopLowScores(int count) {
    priority_queue<CreditScore, vector<CreditScore>, greater<CreditScore>> minHeap;

    for (const auto& pair : scores) {
        minHeap.push({pair.first, pair.second});
    }
    
    cout << "--- Lowest Credit Scores ---" << endl;
    int i = 0;
    while (!minHeap.empty() && i < count) {
        CreditScore cs = minHeap.top();
        minHeap.pop();
        cout << "Account #" << cs.accountId << " | Score: " << cs.score << endl;
        i++;
    }
}