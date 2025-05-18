#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP
#include <iostream>
#include <limits>
#include <utility>

#include "s21_vector.h"  // ВОТ СЮДА ПУТЬ ДО VECTOR
namespace s21 {

template <typename Key, typename T>
class BinaryTree;

template <typename T>
class Vector;

template <typename Key, typename T>
class Node {
 public:
  Key key_ = 0;
  T value_ = 0;
  Node<Key, T>* left_ = nullptr;
  Node<Key, T>* right_ = nullptr;
  Node<Key, T>* parent_ = nullptr;

 public:
  Node();
  Node(Key key);
  Node(Key key, T value);
  Node<Key, T>* FindMax();
  Node<Key, T>* FindMin();
  friend class BinaryTree<Key, T>;
};

template <typename Key, typename T>
class BinaryTree {
 public:
  class iterator;

  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename BinaryTree<Key, T>::iterator;
  using const_iterator = const typename BinaryTree<Key, T>::iterator;
  using size_type = size_t;

  BinaryTree();
  BinaryTree(std::initializer_list<value_type> const& items);
  BinaryTree(const BinaryTree& m);
  BinaryTree(BinaryTree&& m);
  ~BinaryTree();
  BinaryTree& operator=(BinaryTree&& m);
  BinaryTree& operator=(const BinaryTree& m);

  T& at(const Key& key);
  T& operator[](const Key& key);

  iterator begin();
  iterator end();
  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insertMSet(const Key& key);
  std::pair<iterator, bool> insert(const Key& key, const T& obj);
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);
  void erase(iterator pos);
  void swap(BinaryTree& other);
  void merge(BinaryTree& other);

  bool contains(const Key& key);                              // map
  iterator find(const Key& key);                              // set
  size_type count(const Key& key);                            // multiset
  std::pair<iterator, iterator> equal_range(const Key& key);  // multiset
  iterator lower_bound(const Key& key);                       // multiset
  iterator upper_bound(const Key& key);                       // multiset

  std::pair<iterator, bool> insertNode(Node<Key, T>*& node,
                                       Node<Key, T>* parent, const Key& key,
                                       const T& obj);
  std::pair<iterator, bool> insertMSetNode(Node<Key, T>*& node,
                                           Node<Key, T>* parent, const Key& key,
                                           const T& obj);
  void clearHelper(Node<Key, T>* node);
  Node<Key, T>* copyTree(Node<Key, T>* node);
  iterator findHelper(const Key& key, Node<Key, T>* node);
  void eraseHelper(Node<Key, T>*& node, Node<Key, T>* parent);

 public:
  template <typename... Args>
  s21::Vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    s21::Vector<std::pair<iterator, bool>> results;
    results.reserve(sizeof...(Args));
    (results.push_back(insert(std::forward<Args>(args))), ...);
    return results;
  }

  template <typename... Args>
  s21::Vector<std::pair<iterator, bool>> insert_many_Set(Args&&... args) {
    s21::Vector<std::pair<iterator, bool>> results;
    results.reserve(sizeof...(Args));
    (results.push_back(
         insert(std::forward<Args>(args), std::forward<Args>(args))),
     ...);
    return results;
  }

  template <typename... Args>
  s21::Vector<std::pair<iterator, bool>> insert_many_MSet(Args&&... args) {
    s21::Vector<std::pair<iterator, bool>> results;
    results.reserve(sizeof...(Args));
    (results.push_back(insertMSet(std::forward<Args>(args))), ...);
    return results;
  }

 public:
  class iterator {
   public:
    iterator();
    iterator(Node<Key, T>* it_root, Node<Key, T>* cur_node);
    iterator(Node<Key, T>* node);
    iterator(const iterator& other)
        : it_root_(other.it_root_), cur_node_(other.cur_node_) {}

    iterator& operator=(const iterator& other) {
      if (this != &other) {
        it_root_ = other.it_root_;
        cur_node_ = other.cur_node_;
      }
      return *this;
    }

    iterator operator++(int) {
      iterator tmp(*this);
      operator++();
      return tmp;
    }

    iterator& operator++() {
      if (cur_node_ == nullptr) {
        return *this;
      }

      if (cur_node_->right_ != nullptr) {
        cur_node_ = cur_node_->right_->FindMin();
      } else {
        Node<Key, T>* parent = cur_node_->parent_;
        while (parent != nullptr && cur_node_ == parent->right_) {
          cur_node_ = parent;
          parent = parent->parent_;
        }
        cur_node_ = parent;
      }

      return *this;
    };

    bool operator==(const iterator& other);
    bool operator==(const const_iterator& other) const;
    bool operator!=(const iterator& other);
    bool operator!=(const const_iterator& other) const;
    Node<Key, T>* operator->();
    Node<Key, T>* get();

   private:
    Node<Key, T>* it_root_ = nullptr;
    Node<Key, T>* cur_node_ = nullptr;
    size_t it_count_ = 0;
    friend class binaryTree;
  };

 protected:
  Node<Key, T>* root_ = nullptr;
  size_t size_ = 0;
};

}  // namespace s21

#include "s21_binaryTree.cpp"

#endif  // BINARYTREE_HPP