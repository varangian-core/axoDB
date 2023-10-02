//
// Created by Yormingandr on 9/30/2023.
//

#include <atomic>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>

struct LogRecord {
    int transactionId;
    int pageId;  // The ID of the page being modified
    int offset;  // Offset within the page
    std::string oldValue;  // Value before the modification
    std::string newValue;  // Value after the modification
};

class TransactionManager {
public:
    TransactionManager();
    ~TransactionManager();

    int Begin();
    bool Commit(int transactionId);
    void Abort(int transactionId);
    bool IsActive(int transactionId) const;

    void WriteLog(int transactionId, int pageId, int offset, const std::string& oldValue, const std::string& newValue);

private:
    std::atomic<int> nextTransactionId;
    std::unordered_set<int> activeTransactions;
    std::unordered_map<int, std::vector<LogRecord>> logs;  // Logs indexed by transaction ID
};