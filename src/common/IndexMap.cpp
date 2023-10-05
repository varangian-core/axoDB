//
// Created by Yormingandr on 10/4/2023.
//

#include <stdexcept>
#include "IndexMap.h"

namespace axodb {
    IndexMap::IndexMap() {}
    IndexMap::~IndexMap() {
        for (auto& pair: map_) {
            delete pair.second;
        }
    }


    void IndexMap::addIndex(const std::string& name, BitMapIndex* index) {
        if (map_.find(name) != map_.end()) {
            throw std::runtime_error("Index with name " + name + " already exists");
    }
        map_[name] = index;
    }


    BitMapIndex* IndexMap::getIndex(const std::string& name) const {
        auto it = map_.find(name);
        if (it != map_.end()) {
            return it->second;
        }
        throw std::runtime_error("Index with name " + name + " does not exist");
    }



