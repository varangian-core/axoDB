//
// Created by Yormingandr on 9/29/2023.
//
#include "Btree.h"

template<typename KeyType, typename ValueType>
page_id_t Btree<KeyType, ValueType>::GetPageId() const {
    return root_->page_id_;
}

template<typename KeyType, typename ValueType>
page_id_t Btree<KeyType, ValueType>::GetRootPageID() const {
    return root_->page_id_;
}

template<typename KeyType, typename ValueType>
Btree<KeyType, ValueType>::Btree(size_t order)
        : order_(order), root_(std::make_shared<Node>(true)) {}

template <typename KeyType, typename ValueType>
Btree<KeyType, ValueType>::~Btree() {}

template<typename KeyType, typename ValueType>
void Btree<KeyType, ValueType>::Insert(const KeyType& key, const ValueType &value) {
    auto root = root_;
    if (root->keys.size() == 2 * order_ - 1) {
        auto newRoot = std::make_shared<Node>(false);
        newRoot->children.push_back(root);
        SplitChild(newRoot, 0, root);
        root_ = newRoot;
    }
    InsertNonFull(root_, key, value);
}

template <typename KeyType, typename ValueType>
void Btree<KeyType, ValueType>::SplitChild(std::shared_ptr<Node> parent, int index, std::shared_ptr<Node> child) {
    auto newNode = std::make_shared<Node>(child->isLeaf);
    parent->keys.insert(parent->keys.begin() + index, child->keys[order_ - 1]);
    parent->values.insert(parent->values.begin() + index, child->values[order_ - 1]);

    newNode->keys.assign(child->keys.begin() + order_, child->keys.end());
    newNode->values.assign(child->values.begin() + order_, child->values.end());
    child->keys.erase(child->keys.begin() + order_ - 1, child->keys.end());
    child->values.erase(child->values.begin() + order_ - 1, child->values.end());

    if (!child->isLeaf) {
        newNode->children.assign(child->children.begin() + order_, child->children.end());
        child->children.erase(child->children.begin() + order_, child->children.end());
    }

    parent->children.insert(parent->children.begin() + index + 1, newNode);
}

template <typename KeyType, typename ValueType>
void Btree<KeyType, ValueType>::InsertNonFull(std::shared_ptr<Node> node, const KeyType& key, const ValueType& value) {
    int i = node->keys.size() - 1;
    if (node->isLeaf) {
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;
        node->keys.insert(node->keys.begin() + i, key);
        node->values.insert(node->values.begin() + i, value);
    } else {
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;
        if (node->children[i]->keys.size() == 2 * order_ - 1) {
            SplitChild(node, i, node->children[i]);
            if (key > node->keys[i]) {
                i++;
            }
        }
        InsertNonFull(node->children[i], key, value);
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
            return {node->values[i]};
        } else if (node->isLeaf) {
            return {};
        } else {
            node = node->children[i];
        }
    }
    return {};
}

template <typename KeyType, typename ValueType>
void Btree<KeyType, ValueType>::Remove(const KeyType& key) {
    RemoveNonFull(root_, key);

    //if root node has 0 keys, make the first child a root
    if (root_->keys.size() == 0 && !root_->isLeaf) {
        root_ = root_->children[0];
    }
}



template<typename KeyType, typename ValueType>
void Btree<KeyType, ValueType>::RemoveNonFull(std::shared_ptr<Node> node, const KeyType& key) {
    int i = 0;
    while (i < node->keys.size() && key > node->keys[i]) {
        i++;
    }
    if (i < node->keys.size() && key == node->keys[i]) {
        if (node->isLeaf) {
            node->keys.erase(node->keys.begin() + i);
            node->values.erase(node->values.begin() + i);
        } else {
            auto leftChild = node->children[i];
            auto rightChild = node->children[i + 1];
            if (leftChild->keys.size() >= order_) {
                auto predecessor = leftChild;
                while (!predecessor->isLeaf) {
                    predecessor = predecessor->children[predecessor->children.size() - 1];
                }
                node->keys[i] = predecessor->keys[predecessor->keys.size() - 1];
                node->values[i] = predecessor->values[predecessor->values.size() - 1];
                RemoveNonFull(leftChild, predecessor->keys[predecessor->keys.size() - 1]);
            } else if (rightChild->keys.size() >= order_) {
                auto successor = rightChild;
                while (!successor->isLeaf) {
                    successor = successor->children[0];
                }
                node->keys[i] = successor->keys[0];
                node->values[i] = successor->values[0];
                RemoveNonFull(rightChild, successor->keys[0]);
            } else {
                leftChild->keys.push_back(node->keys[i]);
                leftChild->values.push_back(node->values[i]);
                leftChild->keys.insert(leftChild->keys.end(), rightChild->keys.begin(), rightChild->keys.end());
                leftChild->values.insert(leftChild->values.end(), rightChild->values.begin(), rightChild->values.end());
                if (!leftChild->isLeaf) {
                    leftChild->children.insert(leftChild->children.end(), rightChild->children.begin(), rightChild->children.end());
                }
            }
        }
    }
}

template class Btree<int, int>;