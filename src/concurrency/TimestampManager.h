//
// Created by Yormingandr on 10/3/2023.
//

#ifndef AXODB_TIMESTAMPMANAGER_H
#define AXODB_TIMESTAMPMANAGER_H

#include <atomic>
#include <mutex>


namespace axodb {

class TimestampManager {
public:
    TimestampManager();

    int AssignTimestamp();
    int GetCurrentTimestamp() const;


private:
    std::atomic<int> currentTimestamp_;
    std::mutex timestampMutex_;
};

}  // namespace axodb

#endif //AXODB_TIMESTAMPMANAGER_H
