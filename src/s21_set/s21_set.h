#ifndef S21_SET_H
#define S21_SET_H

#include "../s21_binaryTree/s21_binaryTree.h"

namespace s21 {
template <typename Key>
class Set : public BinaryTree<Key, Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename BinaryTree<Key, Key>::iterator;
  using const_iterator = const typename BinaryTree<Key, Key>::iterator;
  using size_type = size_t;

 public:
  Set() : BinaryTree<Key, Key>() {}
  Set(std::initializer_list<value_type> const& items) {
    for (const auto& item : items) {
      insert(item);
    }
  }
  Set(const Set& s) : BinaryTree<Key, Key>(s) {}
  Set(Set&& s) : BinaryTree<Key, Key>(std::move(s)) {}
  ~Set() {}
  Set& operator=(Set&& s) {
    if (this != &s) {
      BinaryTree<Key, Key>::operator=(std::move(s));
    }
    return *this;
  }

  iterator begin() { return BinaryTree<Key, Key>::begin(); }
  iterator end() { return BinaryTree<Key, Key>::end(); }

  bool empty() { return BinaryTree<Key, Key>::empty(); }
  size_type size() { return BinaryTree<Key, Key>::size(); }
  size_type max_size() { return BinaryTree<Key, Key>::max_size(); }

  void clear() { BinaryTree<Key, Key>::clear(); }
  std::pair<iterator, bool> insert(const value_type& value) {
    return BinaryTree<Key, Key>::insert(value, value);
  }
  void erase(iterator pos) { BinaryTree<Key, Key>::erase(pos); }
  void swap(Set& other) { BinaryTree<Key, Key>::swap(other); }
  void merge(Set& other) { BinaryTree<Key, Key>::merge(other); }

  iterator find(const Key& key) { return BinaryTree<Key, Key>::find(key); }
  bool contains(const Key& key) { return BinaryTree<Key, Key>::contains(key); }

  template <typename... Args>
  s21::Vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    return BinaryTree<Key, Key>::insert_many_Set(std::forward<Args>(args)...);
  }
};

}  // namespace s21

#endif  // S21_SET_H
