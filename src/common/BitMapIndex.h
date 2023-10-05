//
// Created by Yormingandr on 10/4/2023.
//

#ifndef AXODB_BITMAPINDEX_H
#define AXODB_BITMAPINDEX_H


#include "BitMap.h"
#include <unordered_map>
#include <string>


namespace axodb {

    class BitMapIndex {
    public:
        BitMapIndex();


        void insert(const std::string& value, int recordId);
        BitMap search(const std::string& value) const;


    private:
        std::unordered_map<std::string, BitMap> index_;

    };
}


#endif //AXODB_BITMAPINDEX_H
