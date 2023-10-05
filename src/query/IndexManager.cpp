//
// Created by Yormingandr on 10/4/2023.
//

#include "IndexManager.h"

namespace axodb {

    IndexManager::IndexManager() {}

    IndexManager::~IndexManager() {
        for (auto &tableEntry: index_table_) {
            for (auto &columnEntry: tableEntry.second) {
                delete columnEntry.second;
            }
        }
    }

    void IndexManager::createBitmapIndex(const std::string &tableName, const std::string &columnName) {
        if (index_table_[tableName].find(columnName) == index_table_[tableName].end()) {
            index_table_[tableName][columnName] = new BitMapIndex();
        }
    }

    void IndexManager::deleteBitmapIndex(const std::string &tableName, const std::string &columnName) {
        if (index_table_[tableName].find(columnName) != index_table_[tableName].end()) {
            delete index_table_[tableName][columnName];
            index_table_[tableName].erase(columnName);
        }
    }

    void IndexManager::insertValue(const std::string &tableName, const std::string &indexName, const std::string &value, int recordId) {
        if (index_table_[tableName].find(indexName) != index_table_[tableName].end()) {
            index_table_[tableName][indexName]->insert(value, recordId);
        }
    }

    BitMap IndexManager::searchValue(const std::string &tableName, const std::string &indexName, const std::string &value) {
        if (index_table_[tableName].find(indexName) != index_table_[tableName].end()) {
            return index_table_[tableName][indexName]->search(value);
        }
        return BitMap();  // Return an empty BitMap if not found.
    }

} //namespace axodb