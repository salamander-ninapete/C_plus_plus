#ifndef S21_MULTISET_H
#define S21_MULTISET_H

#include "../s21_binaryTree/s21_binaryTree.h"

namespace s21 {

template <typename Key>
class Multiset : public BinaryTree<Key, Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename BinaryTree<Key, Key>::iterator;
  using const_iterator = const typename BinaryTree<Key, Key>::iterator;
  using size_type = size_t;

 public:
  Multiset() : BinaryTree<Key, Key>() {}
  Multiset(const Multiset& ms) : BinaryTree<Key, Key>(ms) {}
  Multiset(Multiset&& ms) : BinaryTree<Key, Key>(std::move(ms)) {}
  ~Multiset() {}
  Multiset& operator=(const Multiset& other) {
    if (this != &other) {
      // Вначале вызываем оператор присваивания для базового класса
      BinaryTree<Key, Key>::operator=(other);
    }
    return *this;
  }
  // Оператор присваивания для перемещения
  Multiset& operator=(Multiset&& other) noexcept {
    if (this != &other) {
      // Вначале вызываем оператор перемещения для базового класса
      BinaryTree<Key, Key>::operator=(std::move(other));
    }
    return *this;
  }

  iterator begin() { return BinaryTree<Key, Key>::begin(); }
  iterator end() { return BinaryTree<Key, Key>::end(); }

  bool empty() { return BinaryTree<Key, Key>::empty(); }
  size_type size() { return BinaryTree<Key, Key>::size(); }
  size_type max_size() { return BinaryTree<Key, Key>::max_size(); }

  void clear() { BinaryTree<Key, Key>::clear(); }

  iterator insert(const value_type& value) {
    return BinaryTree<Key, Key>::insertMSet(value).first;
  }
  void erase(iterator pos) { BinaryTree<Key, Key>::erase(pos); }
  void swap(Multiset& other) { BinaryTree<Key, Key>::swap(other); }
  void merge(Multiset& other) { BinaryTree<Key, Key>::merge(other); }

  size_type count(const Key& key) { return BinaryTree<Key, Key>::count(key); }
  iterator find(const Key& key) { return BinaryTree<Key, Key>::find(key); }
  bool contains(const Key& key) { return BinaryTree<Key, Key>::contains(key); }
  std::pair<iterator, iterator> equal_range(const Key& key) {
    return BinaryTree<Key, Key>::equal_range(key);
  }
  iterator lower_bound(const Key& key) {
    return BinaryTree<Key, Key>::lower_bound(key);
  }
  iterator upper_bound(const Key& key) {
    return BinaryTree<Key, Key>::upper_bound(key);
  }

  template <typename... Args>
  s21::Vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    return BinaryTree<Key, Key>::insert_many_MSet(std::forward<Args>(args)...);
  }
};

}  // namespace s21

#endif  // S21_MULTISET_H