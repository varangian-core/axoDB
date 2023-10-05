//
// Created by Yormingandr on 10/4/2023.
//

#include "BitMapIndex.h"


namespace axodb {
    BitMap::BitMap() {}

    BitMap::~BitMap() {}

void BitMapIndex::insert(const std::string& value, int recordId) {
    index_[value].setBit(recordId, true);
}


BitMap BitMapIndex::search(const std::string& value) const {
    auto it = index_.find(value);
    if (it != index_.end()) {
        return it->second;
    }
    return BitMap();
}

} //namespace axodb
