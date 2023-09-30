//
// Created by Yormingandr on 9/29/2023.
//

#ifndef AXODB_BTREE_H
#define AXODB_BTREE_H

#include <vector>
#include <memory>


template <typename KeyType, typename ValueType>
class Btree {
public:
    struct Node {
        bool isLeaf;
        std::vector<KeyType> keys;
        std::vector<ValueType> values;
        std::vector<std::shared_ptr<Node>> children;

        Node(bool Leaf) : isLeaf(Leaf) {}
    };

    Btree(size_t order);
    ~Btree();


    void Insert(const KeyType& key, const ValueType& vylue);
    void Remove(const KeyType& key, const ValueType& vylue);
    std::vector<ValueType> Find(const KeyType& key) const;


    int GetRootPageID() const;


private:
    size_t order;
    std::shared_ptr<Node> root_;

};


#endif //AXODB_BTREE_H
