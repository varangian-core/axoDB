//
// Created by Yormingandr on 10/1/2023.
//

#include "LockManager.h"

namespace axodb {

    LockManager::LockManager() = default;

    bool LockManager::AcquireLock(int resourceId, int transactionId, LockType lockType) {
        std::unique_lock<std::mutex> lock(lockMutex_);

        // Check if the resource is already locked
        auto it = lockTable_.find(resourceId);
        if (it == lockTable_.end()) {
            // If not locked, lock it
            lockTable_[resourceId] = {transactionId, lockType, 1};
            return true;
        } else {
            // If locked, check if it's by the same transaction
            if (it->second.transactionId == transactionId) {
                // If same transaction, increment lock count
                it->second.lockCount++;
                return true;
            } else {
                // If different transaction, wait for the lock to be released
                while (lockTable_.find(resourceId) != lockTable_.end()) {
                    cv_.wait(lock);
                }
                lockTable_[resourceId] = {transactionId, lockType, 1};
                return true;
            }
        }
        return false;
    }

    void LockManager::ReleaseLock(int resourceId, int transactionId) {
        std::unique_lock<std::mutex> lock(lockMutex_);

        auto it = lockTable_.find(resourceId);
        if (it != lockTable_.end() && it->second.transactionId == transactionId) {
            if (it->second.lockCount > 1) {
                // If multiple locks by the same transaction, decrement lock count
                it->second.lockCount--;
            } else {
                // If only one lock, remove from lock table
                lockTable_.erase(it);
                cv_.notify_all();  // Notify waiting transactions
            }
        }
    }

    std::set<int> LockManager::GetActiveTransactions() {
        std::set<int> activeTransactions;
        std::unique_lock<std::mutex> lock(lockMutex_);

        for (const auto& pair : lockTable_) {
            activeTransactions.insert(pair.second.transactionId);
        }

        return activeTransactions;
    }

}  // namespace axodb
