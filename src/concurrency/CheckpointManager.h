//
// Created by Yormingandr on 10/1/2023.
//

#ifndef AXODB_CHECKPOINTMANAGER_H
#define AXODB_CHECKPOINTMANAGER_H


#include <set>
#include <mutex>
#include "LogManager.h"


namespace axodb {

class CheckpointManager {
public:
    CheckpointManager(LogManager& logManager);
    void CreateCheckpoint();
    std::set<int> GetActiveTransactionsFromLastCheckpoint();

private:
    LogManager& logManager_;
    std::set<int> activeTransactionsAtLastCheckpoint_;
    mutable std::mutex checkpointMutex_;
};

}  // namespace axodb

#endif //AXODB_CHECKPOINTMANAGER_H
