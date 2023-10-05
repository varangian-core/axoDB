//
// Created by Yormingandr on 10/4/2023.
//

#ifndef AXODB_INDEXMAP_H
#define AXODB_INDEXMAP_H


#include "BitMapIndex.h"
#include <unordered_map>
#include <string>


namespace axodb {

    class IndexMap {
    public:
        IndexMap();
        ~IndexMap();


        void addIndex(const std::string& name, BitMapIndex* index);
        BitMapIndex* getIndex(const std::string& name) const;

    private:

        std::unordered_map<std::string, BitMapIndex*> map_;
    };


}
#endif //AXODB_INDEXMAP_H
