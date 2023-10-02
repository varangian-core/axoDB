//
// Created by Yormingandr on 10/1/2023.
//

#include "LockManager.h"

namespace axodb {

    bool LockManager::AcquireLock(int resourceId, int transactionId, axodb::LockType lockType) {
        std::unique_lock<std::mutex> lock(lockMutex_);
        auto it = lockTable_.find(resourceId);
        if (it != lockTable_.end()) {
            if (lockType == LockType::SHARED && it->second.lockType == LockType::SHARED) {
                cv_.wait(lock);
                return false;
            }

            if (lockType == LockType::EXCLUSIVE && it->second.transactionId != transactionId) {
                cv_.wait(lock);
                return false;
            }
        }

        lockTable_[resourceId] = {transactionId, lockType, 1};
        return true;
    }

    void LockManager::ReleaseLock(int resourceId, int transactionId) {
        std::unique_lock<std::mutex> lck(lockMutex_);

        auto it = lockTable_.find(resourceId);
        if (it != lockTable_.end() && it->second.transactionId == transactionId) {
            it->second.lockCount--;
            if (it->second.lockCount == 0) {
                lockTable_.erase(it);
            }

            cv_.notify_all();
        }
    }
}