//
// Created by Yormingandr on 10/1/2023.
//

#include "CheckpointManager.h"

namespace axodb {

    CheckpointManager::CheckpointManager(LogManager& logManager) : logManager_(logManager) {}

    void CheckpointManager::CreateCheckpoint() {
        std::lock_guard<std::mutex> lock(checkpointMutex_);

        // Fetch the current active transactions from the LogManager
        activeTransactionsAtLastCheckpoint_ = logManager_.GetActiveTransactions();

        // Log the checkpoint. This could be a special log record indicating a checkpoint
        LogRecord checkpointLog;
        checkpointLog.type = LogRecord::LogType::CHECKPOINT;
        logManager_.AppendLog(checkpointLog);
    }

    std::set<int> CheckpointManager::GetActiveTransactionsFromLastCheckpoint() const {
        std::lock_guard<std::mutex> lock(checkpointMutex_);
        return activeTransactionsAtLastCheckpoint_;
    }

}  // namespace axodb

