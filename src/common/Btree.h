//
// Created by Yormingandr on 9/29/2023.
//

#ifndef AXODB_BTREE_H
#define AXODB_BTREE_H


#include <vector>
#include <memory>

template<typename KeyType, typename ValueType>
class Btree {
public:
    Btree(size_t order);
    ~Btree();

    void Insert(const KeyType& key, const ValueType& value);
    std::vector<ValueType> Find(const KeyType& key) const;
    void Remove(const KeyType& key);

private:
    struct Node {
        bool isLeaf;
        std::vector<KeyType> keys;
        std::vector<ValueType> values;
        std::vector<std::shared_ptr<Node>> children;

        Node(bool isLeaf) : isLeaf(isLeaf) {}
    };

    size_t order_;
    std::shared_ptr<Node> root_;

    void InsertNonFull(std::shared_ptr<Node> node, const KeyType& key, const ValueType& value);
    void RemoveNonFull(std::shared_ptr<Node> node, const KeyType& key);
    void SplitChild(std::shared_ptr<Node> parent, int index, std::shared_ptr<Node> child);
};


#endif