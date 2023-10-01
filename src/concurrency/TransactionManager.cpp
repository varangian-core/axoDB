//
// Created by Yormingandr on 9/30/2023.
//

#include "TransactionManager.h"

TransactionManager::TransactionManager() : nextTransactionId(1) {}

TransactionManager::~TransactionManager() {}

int TransactionManager::Begin() {
    int txnId = nextTransactionId.fetch_add(1);
    activeTransactions.insert(txnId);
    return txnId;
}

bool TransactionManager::Commit(int transactionId) {
    //ARIES implementation requires a log flush before commit
    activeTransactions.erase(transactionId);
    logs.erase(transactionId);  // Clear logs after commit
    return true;
}

void TransactionManager::Abort(int transactionId) {
    // Use logs to undo changes
    // For simplicity, we're just removing the transaction and its logs
    activeTransactions.erase(transactionId);
    logs.erase(transactionId);
}

bool TransactionManager::IsActive(int transactionId) const {
    return activeTransactions.find(transactionId) != activeTransactions.end();
}

void TransactionManager::WriteLog(int transactionId, int pageId, int offset, const std::string& oldValue, const std::string& newValue) {
    LogRecord record{transactionId, pageId, offset, oldValue, newValue};
    logs[transactionId].push_back(record);
}
