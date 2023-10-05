//
// Created by Yormingandr on 10/4/2023.
//

#include "BitMap.h"


namespace axodb {

    BitMap::BitMap() {}

    BitMap::~BitMap() {}

    void BitMap::setBit(int position, bool value) {
        if (position >= bits_.size()) {
            bits_.resize(position + 1, false);
        }
        bits_[position] = value;
    }

    bool BitMap::getBit(int position) const {
        if (position < bits_.size()) {
            return bits_[position];
        }
        return false;
    }
} //namespace axodb