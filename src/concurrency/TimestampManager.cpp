//
// Created by Yormingandr on 10/3/2023.
//

#include "TimestampManager.h"

namespace axodb {
    TimestampManager::TimestampManager() : currentTimestamp_(0) {}

    int TimestampManager::AssignTimestamp() {
        std::lock_guard<std::mutex> lock(timestampMutex_);
        return ++currentTimestamp_;
    }

    int TimestampManager::GetCurrentTimestamp() const {
        return currentTimestamp_;
    }
}
