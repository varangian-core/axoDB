#include <vector>

template <typename KeyType, typename ValueType>
class Index {
public:
  virtual ~Index() {}

  // Insert a new key-value pair into the index
  virtual void Insert(const KeyType& key, const ValueType& value) = 0;

  // Remove a key-value pair from the index
  virtual void Remove(const KeyType& key, const ValueType& value) = 0;

  // Find all values that match a given key
  virtual std::vector<ValueType> Find(const KeyType& key) const = 0;
};