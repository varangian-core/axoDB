//
// Created by Yormingandr on 10/1/2023.
//

#ifndef AXODB_LOCKMANAGER_H
#define AXODB_LOCKMANAGER_H

#include <unordered_map>
#include <mutex>
#include <condition_variable>


namespace axodb {

    enum class LockType {
        SHARED,
        EXCLUSIVE
    };


    class LockManager {
    public:
        LockManager() = default;

        bool AcquireLock(int resourceId, int transactionId, LockType lockType);

        void ReleaseLock(int resourceId, int transactionId);

    private:
        struct LockInfo {
            int transactionId;
            LockType lockType;
            int lockCount;
        };

        std::unordered_map<int, LockInfo> lockTable_;
        std::mutex lockMutex_;
        std::condition_variable cv_;
    };
}


#endif //AXODB_LOCKMANAGER_H
