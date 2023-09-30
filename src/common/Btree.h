//
// Created by Yormingandr on 9/29/2023.
//

#ifndef AXODB_BTREE_H
#define AXODB_BTREE_H


#include <vector>
#include <memory>
#include "BufferFrame.h"

template<typename KeyType, typename ValueType>
class Btree {
public:
    Btree(size_t order);
    ~Btree();

    void Insert(const KeyType& key, const ValueType& value);
    std::vector<ValueType> Find(const KeyType& key) const;
    void Remove(const KeyType& key);
    page_id_t GetPageId() const;
    page_id_t GetRootPageID() const;

private:
    struct Node {
        void RemoveNonFull(std::shared_ptr<Node>, const KeyType& key);
        bool isLeaf;
        page_id_t page_id_;
        std::vector<KeyType> keys;
        std::vector<ValueType> values;
        std::vector<std::shared_ptr<Node>> children;

    };

    size_t order_;
    std::shared_ptr<Node> root_;

    void InsertNonFull(std::shared_ptr<Node> node, const KeyType& key, const ValueType& value);
    void RemoveNonFull(std::shared_ptr<Node> node, const KeyType& key);
    void SplitChild(std::shared_ptr<Node> parent, int index, std::shared_ptr<Node> child);
};


#endif