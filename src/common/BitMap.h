//
// Created by Yormingandr on 10/4/2023.
//

#ifndef AXODB_BITMAP_H
#define AXODB_BITMAP_H

#include <vector>

namespace axodb {
    class BitMap {
    public:
        BitMap();
        ~BitMap();

        void setBit(int position, bool value);
        bool getBit(int position) const;


    private:
        std::vector<bool> bits_;
    };


#endif //AXODB_BITMAP_H

}