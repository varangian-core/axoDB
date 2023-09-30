//
// Created by Yormingandr on 9/30/2023.
//
#include "Page.h"

#ifndef AXODB_NODE_H
#define AXODB_NODE_H

#include <vector>
#include <memory>

template<typename KeyType, typename ValueType>
class Btree;

template<typename KeyType, typename ValueType>
class Node {
    Node(bool isLeafFlag) : isLeaf(isLeafFlag) {};
    friend class Btree<KeyType, ValueType>;


private:
    bool isLeaf;
    std::vector<KeyType> keys;
    std::vector<ValueType> values;
    std::vector<std::shared_ptr<Node>> children;
    page_id_t page_id_;

};


#endif //AXODB_NODE_H
