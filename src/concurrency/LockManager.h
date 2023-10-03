//
// Created by Yormingandr on 10/1/2023.
//

#ifndef AXODB_LOCKMANAGER_H
#define AXODB_LOCKMANAGER_H

#include <map>
#include <set>
#include <mutex>
#include <condition_variable>

namespace axodb {

    class LockManager {
    public:
        enum class LockType {
            SHARED,
            EXCLUSIVE
        };

        struct LockInfo {
            int transactionId;
            LockType lockType;
            int lockCount;
        };

        LockManager();

        bool AcquireLock(int resourceId, int transactionId, LockType lockType);
        void ReleaseLock(int resourceId, int transactionId);
        std::set<int> GetActiveTransactions();

    private:
        std::map<int, LockInfo> lockTable_;
        std::mutex lockMutex_;
        std::condition_variable cv_;
    };

}  // namespace axodb

#endif //AXODB_LOCKMANAGER_H
