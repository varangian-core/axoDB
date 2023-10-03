//
// Created by Yormingandr on 10/3/2023.
//

#include "VersionManager.h"


namespace axodb {

    void VersionManager::AddVersion(int dataItemId, const VersionRecord &version) {
        std::lock_guard<std::mutex> lock(versionMutex_);
        versionTable_[dataItemId].push_back(version);
    }

    VersionRecord VersionManager::GetVersion(int dataItemId, int transactionId) {
        std::lock_guard<std::mutex> lock(versionMutex_);
        for (auto it = versionTable_[dataItemId].rbegin(); it != versionTable_[dataItemId].rend(); ++it) {
            if (it->transactionId <= transactionId) {
                return *it;
            }
        }
        return VersionRecord();
    }

    void VersionManager::RemoveOldVersions(int dataItemId, int oldestVisibleTransactionId) {
        std::lock_guard<std::mutex> lock(versionMutex_);
        auto& versions = versionTable_[dataItemId];
        versions.remove_if([oldestVisibleTransactionId](const VersionRecord& version) {
            return version.transactionId < oldestVisibleTransactionId;
        });
    }
}  // namespace axodb