//
// Created by Yormingandr on 10/1/2023.
//


#ifndef AXODB_RECOVERYMANAGER_H
#define AXODB_RECOVERYMANAGER_H

#include "LogManager.h"
#include <vector>
#include <set>

namespace axodb {

    class RecoveryManager {
    public:
        RecoveryManager(LogManager &logManager);
        void Recover();
    private:
        void Analysis();
        void Redo();
        void Undo();
        LogManager& logManager_;
        std::set<int> activeTransactions_;
    };

}  // namespace axodb

#endif //AXODB_RECOVERYMANAGER_H
