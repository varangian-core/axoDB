//
// Created by Yormingandr on 9/29/2023.
//

#include "Btree.h"

template<typename KeyType, typename ValueType>
Btree<KeyType, ValueType>::Btree(size_t order) : order_(order), root_(std::make_shared<Node>(true)) {}

template <typename KeyType, typename ValueType>
Btree<KeyType, ValueType>::~Btree() {}

template<typename KeyType, typename ValueType>
void Btree<KeyType, ValueType>::Insert(const KeyType& key, const ValueType &value) {
    auto root = root_;
    if (root->key.size() == 2 * order_ - 1) {
        auto newRoot = std::make_shared<Node>(false);
        newRoot->children.push_back(root);
        SplitChild(newRoot, 0, root);
        root_ = newRoot;
    }
    InsertNonFull(root_, key, value);
}


template <typename KeyType, typename ValueType>
void Btree<KeyType, ValueType> :: SplitChild(std::shared_ptr<Node> parent, int index,
                                             std::shared_ptr<Node> child) {
    auto newNode = std::make_shared<Node>(child->isLeaf);
    parent->keys.insert(parent->keys.begin() + index, child->keys[order - 1]);

    newNode->keys.assign(child->keys.begin() + order, child->keys.end());
    child->keys.erase(child->keys.begin() + order - 1, child->keys.end());

    if (!child->isLeaf) {
        newNode->children.assign(child->children.begin() + order, child->children.end());
        child->children.erase(child->children.begin() + order, child->children.end());
    }
}


template <typename KeyType, typename ValueType>
void Btree<KeyType, ValueType>::InsertNonFull(std::shared_ptr<Node> node, const KeyType& key, const ValueType& value) {
    int i = node->keys.size() - 1;
    if (node->isLeaf) {
        node->keys.push_back(KeyType());
        node->values.push_back(ValueType());
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            node->values[i + 1] = node->values[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->values[i + 1] = value;
    } else {
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;
        if (node->children[i]->keys.size() == 2 * order - 1) {
            SplitChild(node, i, node->children[i]);
            if (key > node->keys[i]) {
                i++;
            }
        }
        InsertNonNull(node->children[i], key, value);
    }
}

template <typename KeyType, typename ValueType>
std::vector<ValueType> Btree<KeyType, ValueType>::Find(const KeyType& key) const {
    auto node = root_;
    while (node) {
        int i = 0;
        while (i < node->keys.size() && key > node->keys[i]) {
            i++;
        }
        if (i < node->keys.size() && key == node->keys[i]) {
            return node->values[i];
        } else if (node->isLeaf) {
            return std::vector<ValueType>();
        } else {
            node = node->children[i];
        }
    }
    return {};
}


template <typename KeyType, typename ValueType>
void Btree<KeyType, ValueType>::Remove(const KeyType& key) {
    RemoveNonFull(root_, key);
    if (root_->keys.size() == 0) {
        if (root_->isLeaf) {
            root_ = nullptr;
        } else {
            root_ = root_->children[0];
        }
    }
}

template class Btree<int ,  int >;