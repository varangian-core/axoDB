//
// Created by Yormingandr on 10/4/2023.
//

#ifndef AXODB_INDEXMANAGER_H
#define AXODB_INDEXMANAGER_H


#include <string>
#include <unordered_map>

class IndexManager {
public:
    IndexManager();
    ~IndexManager();

    void createBitmapIndex(const std::string& tableName, const std::string& columnName);
    void deleteBitmapIndex(const std::string& tableName, const std::string& columnName);
    void insertValue(const std::string& tableName, const std::string& indexName, const std::string& value, int recordId);
    BitMap searchValue(const std::string& tableName, const std::string& indexName, const std::string& value); //Do I need indexName here?

private:
    std::unordered_map<std::string, std::unordered_map<std::string, BitmapIndex*>> indexTable_; //tableName -> columnName -> BitMap
    }

}; //namespace axodb


#endif //AXODB_INDEXMANAGER_H
