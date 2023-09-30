#include "BTreeIndex.h"
#include "BufferFrame.h"
#include "Btree.h"

BufferFrame* ConvertPageToBufferFrame(Page* page) {
    if (page == nullptr) {
        return nullptr;
    }

    return new BufferFrame(page->GetPageId(), page->GetData());
}

template<typename KeyType, typename ValueType>
BTreeIndex<KeyType, ValueType>::BTreeIndex(size_t order, BufferPoolManager *buffer_pool_manager)
        : btree_(order), buffer_pool_manager_(buffer_pool_manager) {}

template<typename KeyType, typename ValueType>
BTreeIndex<KeyType, ValueType>::~BTreeIndex() {}

template<typename KeyType, typename ValueType>
void BTreeIndex<KeyType, ValueType>::Insert(const KeyType &key, const ValueType &value) {
    // Insert the key-value pair into the B-tree
    btree_.Insert(key, value);

    // Flush the B-tree root page to disk
    Page *tempPage = buffer_pool_manager_->FetchPage(btree_.GetRootPageID());
    BufferFrame *root_buffer = ConvertPageToBufferFrame(tempPage);
    buffer_pool_manager_->FlushPage(root_buffer->GetPageId());

    //Clean up the allocated memory
    delete root_buffer;
}

template<typename KeyType, typename ValueType>
void BTreeIndex<KeyType, ValueType>::Remove(const KeyType &key, const ValueType &value) {
    // Remove the key-value pair from the B-tree
    btree_.Remove(key);

    // Flush the B-tree root page to disk
    Page *tempPage = buffer_pool_manager_->FetchPage(btree_.GetRootPageID());
    BufferFrame *root_buffer = ConvertPageToBufferFrame(tempPage);
    buffer_pool_manager_->FlushPage(root_buffer->GetPageId());

    //Clean up the allocated memory
    delete root_buffer;
}

template<typename KeyType, typename ValueType>
std::vector<ValueType> BTreeIndex<KeyType, ValueType>::Find(const KeyType &key) const {
    // Find all values that match the given key in the B-tree
    return btree_.Find(key);
}

// Explicit template instantiation
template
class BTreeIndex<int, int>;