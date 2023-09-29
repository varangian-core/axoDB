#include "BTreeIndex.h"

template <typename KeyType, typename ValueType>
BTreeIndex<KeyType, ValueType>::BTreeIndex(size_t order, BufferPoolManager* buffer_pool_manager)
  : btree_(order), buffer_pool_manager_(buffer_pool_manager) {}

template <typename KeyType, typename ValueType>
BTreeIndex<KeyType, ValueType>::~BTreeIndex() {}

template <typename KeyType, typename ValueType>
void BTreeIndex<KeyType, ValueType>::Insert(const KeyType& key, const ValueType& value) {
  // Insert the key-value pair into the B-tree
  btree_.Insert(key, value);

  // Flush the B-tree root page to disk
  BufferFrame* root_buffer = buffer_pool_manager_->GetPage(btree_.GetRootPageID());
  buffer_pool_manager_->WritePage(root_buffer);
  buffer_pool_manager_->ReleasePage(root_buffer);
}

template <typename KeyType, typename ValueType>
void BTreeIndex<KeyType, ValueType>::Remove(const KeyType& key, const ValueType& value) {
  // Remove the key-value pair from the B-tree
  btree_.Remove(key, value);

  // Flush the B-tree root page to disk
  BufferFrame* root_buffer = buffer_pool_manager_->GetPage(btree_.GetRootPageID());
  buffer_pool_manager_->WritePage(root_buffer);
  buffer_pool_manager_->ReleasePage(root_buffer);
}

template <typename KeyType, typename ValueType>
std::vector<ValueType> BTreeIndex<KeyType, ValueType>::Find(const KeyType& key) const {
  // Find all values that match the given key in the B-tree
  return btree_.Find(key);
}

// Explicit template instantiation
template class BTreeIndex<int, int>;