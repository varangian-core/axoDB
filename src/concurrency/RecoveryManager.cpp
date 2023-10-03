//
// Created by Yormingandr on 10/1/2023.
//

#include "RecoveryManager.h"

namespace axodb {

    RecoveryManager::RecoveryManager(LogManager& logManager) : logManager_(logManager) {}

    void RecoveryManager::Recover() {
        Analysis();
        Redo();
        Undo();
    }

    void RecoveryManager::Analysis() {
        // Identify the starting point for the REDO phase
        // Determine the set of transactions that were active at the time of the crash
        auto logs = logManager_.ReadLogs();
        for (const auto& log : logs) {
            //Perform REDO
            if (log.type == LogRecord::LogType::BEGIN) {
                activeTransactions_.insert(log.transactionId);
            } else if (log.type == LogRecord::LogType::COMMIT || log.type == LogRecord::LogType::ABORT) {
                    activeTransactions_.erase(log.transactionId);
            }
        }
    }

    void RecoveryManager::Redo() {
        // Re-apply all the updates to ensure that all logged updates are carried out and written to disk
        auto logs = logManager_.ReadLogs();
        for (const auto& log : logs) {
            // Check if the log needs to be redone and apply the necessary changes
            if (activeTransactions_.find(log.transactionId) != activeTransactions_.end()) {
                //TODO: ADD REDO logic
            }
        }
    }

    void RecoveryManager::Undo() {
        // Undo the actions of transactions that were not committed at the time of the crash
        auto logs = logManager_.ReadLogs();
        for (auto it = logs.rbegin(); it != logs.rend(); ++it) {
            // Check if the log needs to be undone and revert the changes
            if (activeTransactions_.find(it->transactionId) != activeTransactions_.end()) {
                //TODO: ADD UNDO logic
            }
        }
    }
}  // namespace axodb
