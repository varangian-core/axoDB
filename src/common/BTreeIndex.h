
#include "Index.h"
#include "Btree.h"
#include "BufferPoolManager.h"

template <typename KeyType, typename ValueType>
class BTreeIndex : public Index<KeyType, ValueType> {
public:
  BTreeIndex(size_t order, BufferPoolManager* buffer_pool_manager);
  virtual ~BTreeIndex();

  // Insert a new key-value pair into the index
  virtual void Insert(const KeyType& key, const ValueType& value);

  // Remove a key-value pair from the index
  virtual void Remove(const KeyType& key, const ValueType& value);

  // Find all values that match a given key
  virtual std::vector<ValueType> Find(const KeyType& key) const;

private:
  Btree<KeyType, ValueType> btree_;
  BufferPoolManager* buffer_pool_manager_;
};