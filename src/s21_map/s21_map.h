#ifndef MAP_HPP
#define MAP_HPP

#include "../s21_binaryTree/s21_binaryTree.h"

namespace s21 {

template <typename Key, typename T>
class Map : public BinaryTree<Key, T> {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename BinaryTree<Key, T>::iterator;
  using const_iterator = const typename BinaryTree<Key, T>::iterator;
  using size_type = size_t;

  Map() : BinaryTree<Key, T>() {}
  Map(std::initializer_list<value_type> const& items)
      : BinaryTree<Key, T>(items) {}
  Map(const Map& m) : BinaryTree<Key, T>(m) {}
  Map(Map&& m) : BinaryTree<Key, T>(std::move(m)) {}
  ~Map() {}
  Map& operator=(Map&& m) {
    if (this != &m) {
      BinaryTree<Key, T>::operator=(std::move(m));
    }
    return *this;
  }

  T& at(const Key& key) { return BinaryTree<Key, T>::at(key); }
  T& operator[](const Key& key) { return BinaryTree<Key, T>::operator[](key); }

  iterator begin() { return BinaryTree<Key, T>::begin(); }
  iterator end() { return BinaryTree<Key, T>::end(); }

  bool empty() { return BinaryTree<Key, T>::empty(); }
  size_type size() { return BinaryTree<Key, T>::size(); }
  size_type max_size() { return BinaryTree<Key, T>::max_size(); }

  void clear() { BinaryTree<Key, T>::clear(); }
  std::pair<iterator, bool> insert(const value_type& value) {
    return BinaryTree<Key, T>::insert(value);
  }
  std::pair<iterator, bool> insert(const Key& key, const T& obj) {
    return BinaryTree<Key, T>::insert(key, obj);
  }
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj) {
    return BinaryTree<Key, T>::insert_or_assign(key, obj);
  }

  void erase(iterator pos) { BinaryTree<Key, T>::erase(pos); }
  void swap(Map& other) { BinaryTree<Key, T>::swap(other); }
  void merge(Map& other) { BinaryTree<Key, T>::merge(other); }

  bool contains(const Key& key) { return BinaryTree<Key, T>::contains(key); }

  template <typename... Args>
  s21::Vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    return BinaryTree<Key, T>::insert_many(std::forward<Args>(args)...);
  }
};

}  // namespace s21

#endif  // MAP_HPP