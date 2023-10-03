//
// Created by Yormingandr on 10/3/2023.
//

#ifndef AXODB_VERSIONMANAGER_H
#define AXODB_VERSIONMANAGER_H

#include <map>
#include <list>
#include <mutex>
#include <string>

namespace axodb {

    struct VersionRecord {
        int transactionId;
        std::string data;
    };

    class VersionManager {
    public:
        void AddVersion(int dataItemId, const VersionRecord& version);
        VersionRecord GetVersion(int dataItemId, int transactionId);
        void RemoveOldVersions(int dataItemId, int oldestVisibleTransactionId);

    private:
        std::mutex versionMutex_;
        std::map<int, std::list<VersionRecord>> versionTable_;  // Maps data item ID to its list of versions
    };

}  // namespace axodb

#endif //AXODB_VERSIONMANAGER_H