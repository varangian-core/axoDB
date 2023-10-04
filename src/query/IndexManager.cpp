//
// Created by Yormingandr on 10/4/2023.
//

#include "IndexManager.h"

namespace  axodb {

    IndexManager::IndexManager() {}

    //TODO: add indexMap, BitMapIndex, and BitMap to the namespace
    IndexManager::~IndexManager() {
        //Delete BitMapIndex pointers
        for (auto &tableEntry: indexMap) {
            for (auto &columnEntry: tableEntry.second) {
                delete columnEntry.second;
            }
        }
    }


    void IndexManager::createBitmapIndex(const std::string &tableName, const std::string &columnName) {
        if (indexMap[tableName].find(columnName) == indexMap[tableName].end()) {
            indexMap[tableName][columnName] = new BitMapIndex();
        }
    }


    void IndexManager::deleteBitmapIndex(const std::string &tableName, const std::string &columnName) {
        if (indexMap[tableName].find(columnName) != indexMap[tableName].end()) {
            delete indexMap[tableName][columnName];
            indexMap[tableName].erase(columnName);
        }
    }

    void IndexManager::insertValue(const std::string &tableName, const std::string &indexName, const std::string &value,
                                   int recordId) {
        if (indexMap[tableName].find(indexName) != indexMap[tableName].end()) {
            indexMap[tableName][indexName]->insert(value, recordId);
        }
    }

    void
    IndexManager::searchValue(const std::string &tableName, const std::string &indexName, const std::string &value) {
        if (indexMap[tableName].find(indexName) != indexMap[tableName].end()) {
            indexMap[tableName][indexName]->search(value);
        }
    }

} //namespace axodb
