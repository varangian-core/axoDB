//
// Created by Yormingandr on 10/4/2023.
//

#ifndef AXODB_INDEXMANAGER_H
#define AXODB_INDEXMANAGER_H


#include <string>
#include <unordered_map>
#include "../common/BitMap.h"
#include "../common/BitMapIndex.h"

class BitMapIndex;

namespace axodb {
    class IndexManager {
    public:
        IndexManager();

        ~IndexManager();

        void createBitmapIndex(const std::string &tableName, const std::string &columnName);

        void deleteBitmapIndex(const std::string &tableName, const std::string &columnName);

        void insertValue(const std::string &tableName, const std::string &indexName, const std::string &value, int recordId);

        BitMap searchValue(const std::string &tableName, const std::string &indexName, const std::string &value);

    private:
        std::unordered_map<std::string, std::unordered_map<std::string, BitMapIndex* >> index_table_;

    };

}; //namespace axodb


#endif //AXODB_INDEXMANAGER_H
