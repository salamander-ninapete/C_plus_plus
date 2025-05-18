#ifndef BINARYTREE_CPP
#define BINARYTREE_CPP

#include "s21_binaryTree.h"

namespace s21 {

template <typename Key, typename T>
Node<Key, T>::Node() : key_(0), value_(0) {}

template <typename Key, typename T>
Node<Key, T>::Node(Key key) : key_(key) {}

template <typename Key, typename T>
Node<Key, T>::Node(Key key, T value) : key_(key), value_(value) {}

template <typename Key, typename T>
Node<Key, T>* Node<Key, T>::FindMax() {
  if (this == nullptr) return nullptr;
  Node<Key, T>* current = this;
  while (current->right_ != nullptr) {
    current = current->right_;
  }
  return current;
}

template <typename Key, typename T>
Node<Key, T>* Node<Key, T>::FindMin() {
  Node<Key, T>* thic = this;
  if (thic == nullptr) return nullptr;
  Node<Key, T>* current = this;
  while (current->left_ != nullptr) {
    current = current->left_;
  }
  return current;
}

template <typename Key, typename T>
BinaryTree<Key, T>::BinaryTree() : root_(nullptr), size_(0) {}

template <typename Key, typename T>
BinaryTree<Key, T>::BinaryTree(std::initializer_list<value_type> const& items)
    : BinaryTree() {
  for (auto item : items) {
    insert(item.first, item.second);
  }
}

template <typename Key, typename T>
BinaryTree<Key, T>::BinaryTree(const BinaryTree& m)
    : root_(copyTree(m.root_)), size_(m.size_) {}

template <typename Key, typename T>
BinaryTree<Key, T>::BinaryTree(BinaryTree&& m) {
  root_ = m.root_;
  size_ = m.size_;
  m.root_ = nullptr;
  m.size_ = 0;
}

template <typename Key, typename T>
BinaryTree<Key, T>::~BinaryTree() {
  clear();
}

template <typename Key, typename T>
BinaryTree<Key, T>& BinaryTree<Key, T>::operator=(BinaryTree&& m) {
  if (&m != this) {
    clearHelper(root_);
    root_ = m.root_;
    size_ = m.size_;
    m.root_ = nullptr;
    m.size_ = 0;
  }
  return *this;
}

template <typename Key, typename T>
BinaryTree<Key, T>& BinaryTree<Key, T>::operator=(const BinaryTree& m) {
  if (this != &m) {
    clear();                    // Очищаем текущее дерево
    root_ = copyTree(m.root_);  // Копируем дерево с помощью функции copyTree
    size_ = m.size_;
  }
  return *this;
}

template <typename Key, typename T>
T& BinaryTree<Key, T>::at(const Key& key) {
  Node<Key, T>* fickleNode = root_;
  while (fickleNode != nullptr) {
    if (key == fickleNode->key_)
      return fickleNode->value_;
    else if (key > fickleNode->key_)
      fickleNode = fickleNode->right_;
    else
      fickleNode = fickleNode->left_;
  }
  throw std::out_of_range(" Key not found \\|0_0|/ ");
}

template <typename Key, typename T>
T& BinaryTree<Key, T>::operator[](const Key& key) {
  iterator it = find(key);
  if (it == end()) {
    std::pair<typename BinaryTree<Key, T>::iterator, bool> result =
        insertNode(root_, nullptr, key, T());
    it = result.first;
  }
  return it->value_;
}

template <typename Key, typename T>
typename BinaryTree<Key, T>::iterator BinaryTree<Key, T>::begin() {
  return iterator(root_, root_->FindMin());
}

template <typename Key, typename T>
typename BinaryTree<Key, T>::iterator BinaryTree<Key, T>::end() {
  return iterator(nullptr);
}

template <typename Key, typename T>
bool BinaryTree<Key, T>::empty() {
  return root_ == nullptr;
}

template <typename Key, typename T>
typename BinaryTree<Key, T>::size_type BinaryTree<Key, T>::size() {
  return size_;
}

template <typename Key, typename T>
typename BinaryTree<Key, T>::size_type BinaryTree<Key, T>::max_size() {
  return std::numeric_limits<size_t>::max();
}

// iterator
template <typename Key, typename T>
BinaryTree<Key, T>::iterator::iterator()
    : it_root_(nullptr), cur_node_(nullptr) {}

template <typename Key, typename T>
BinaryTree<Key, T>::iterator::iterator(Node<Key, T>* it_root,
                                       Node<Key, T>* cur_node)
    : it_root_(it_root), cur_node_(cur_node) {}

template <typename Key, typename T>
BinaryTree<Key, T>::iterator::iterator(Node<Key, T>* node) : cur_node_(node) {}

template <typename Key, typename T>
bool BinaryTree<Key, T>::iterator::operator==(const iterator& other) {
  return cur_node_ == other.cur_node_;
}

template <typename Key, typename T>
bool BinaryTree<Key, T>::iterator::operator==(
    const const_iterator& other) const {
  return this->cur_node_ == other.cur_node_;
}

template <typename Key, typename T>
bool BinaryTree<Key, T>::iterator::operator!=(const iterator& other) {
  return cur_node_ != other.cur_node_;
}

template <typename Key, typename T>
bool BinaryTree<Key, T>::iterator::operator!=(
    const const_iterator& other) const {
  return this->cur_node_ != other.cur_node_;
}

template <typename Key, typename T>
Node<Key, T>* BinaryTree<Key, T>::iterator::operator->() {
  return cur_node_;
}
template <typename Key, typename T>
Node<Key, T>* BinaryTree<Key, T>::iterator::get() {
  return cur_node_;
}

template <typename Key, typename T>
bool BinaryTree<Key, T>::contains(const Key& key) {
  return find(key) != end();
}

template <typename Key, typename T>
typename BinaryTree<Key, T>::iterator BinaryTree<Key, T>::find(const Key& key) {
  return findHelper(key, root_);
}

template <typename Key, typename T>
typename BinaryTree<Key, T>::size_type BinaryTree<Key, T>::count(
    const Key& key) {
  size_type count = 0;
  iterator it = find(key);

  while (it != end() && it->key_ == key) {
    ++count;
    ++it;
  }

  return count;
}

template <typename Key, typename T>
std::pair<typename BinaryTree<Key, T>::iterator,
          typename BinaryTree<Key, T>::iterator>
BinaryTree<Key, T>::equal_range(const Key& key) {
  return std::make_pair(lower_bound(key), upper_bound(key));
}

template <typename Key, typename T>
typename BinaryTree<Key, T>::iterator BinaryTree<Key, T>::lower_bound(
    const Key& key) {
  Node<Key, T>* current = root_;
  Node<Key, T>* result = nullptr;

  while (current != nullptr) {
    if (current->key_ >= key) {
      result = current;
      current = current->left_;
    } else {
      current = current->right_;
    }
  }

  return result ? iterator(result) : end();
}

template <typename Key, typename T>
typename BinaryTree<Key, T>::iterator BinaryTree<Key, T>::upper_bound(
    const Key& key) {
  Node<Key, T>* current = root_;
  Node<Key, T>* result = nullptr;

  while (current != nullptr) {
    if (current->key_ > key) {
      result = current;
      current = current->left_;
    } else {
      current = current->right_;
    }
  }

  return result ? iterator(result) : end();
}

// some functions
template <typename Key, typename T>
void BinaryTree<Key, T>::clear() {
  clearHelper(root_);
  root_ = nullptr;
  size_ = 0;
}

template <typename Key, typename T>
std::pair<typename BinaryTree<Key, T>::iterator, bool>
BinaryTree<Key, T>::insert(const value_type& value) {
  return insertNode(root_, nullptr, value.first, value.second);
}

template <typename Key, typename T>
std::pair<typename BinaryTree<Key, T>::iterator, bool>
BinaryTree<Key, T>::insertMSet(const Key& key) {
  return insertMSetNode(root_, nullptr, key, key);
}
template <typename Key, typename T>
std::pair<typename BinaryTree<Key, T>::iterator, bool>
BinaryTree<Key, T>::insert(const Key& key, const T& obj) {
  return insertNode(root_, nullptr, key, obj);
}

template <typename Key, typename T>
std::pair<typename BinaryTree<Key, T>::iterator, bool>
BinaryTree<Key, T>::insert_or_assign(const Key& key, const T& obj) {
  iterator it = find(key);
  bool inserted = false;

  if (it == end()) {
    auto result = insertNode(root_, nullptr, key, obj);
    it = result.first;
    inserted = result.second;
  } else {
    it->value_ = obj;
  }

  return std::make_pair(it, inserted);
}

template <typename Key, typename T>
void BinaryTree<Key, T>::erase(iterator pos) {
  if (pos == end()) return;
  Node<Key, T>* node = pos.get();
  Node<Key, T>* parent = nullptr;
  if (node->parent_ != nullptr)
    parent = (this->find(node->parent_->key_)).get();
  eraseHelper(node, parent);
}

template <typename Key, typename T>
void BinaryTree<Key, T>::swap(BinaryTree& other) {
  Node<Key, T>* tempRoot = root_;
  size_type tempSize = size_;

  root_ = other.root_;
  size_ = other.size_;

  other.root_ = tempRoot;
  other.size_ = tempSize;
}

template <typename Key, typename T>
void BinaryTree<Key, T>::merge(BinaryTree& other) {
  if (this == &other) return;
  for (auto it = other.begin(); it != other.end(); it++) {
    if (find(it->key_) == end()) {
      insert(it->key_, it->value_);
    }
  }

  other.clear();
}

template <typename Key, typename T>
std::pair<typename BinaryTree<Key, T>::iterator, bool>
BinaryTree<Key, T>::insertNode(Node<Key, T>*& node, Node<Key, T>* parent,
                               const Key& key, const T& obj) {
  std::pair<typename BinaryTree<Key, T>::iterator, bool> answer;
  if (node == nullptr) {
    node = new Node<Key, T>(key, obj);
    node->parent_ = parent;
    answer = std::make_pair(iterator(root_, node), true);
    size_++;
  } else if (key < node->key_) {
    answer = insertNode(node->left_, node, key, obj);
  } else if (key > node->key_) {
    answer = insertNode(node->right_, node, key, obj);
  } else {
    answer = std::make_pair(iterator(root_, node), false);
  }
  return answer;
}

template <typename Key, typename T>
std::pair<typename BinaryTree<Key, T>::iterator, bool>
BinaryTree<Key, T>::insertMSetNode(Node<Key, T>*& node, Node<Key, T>* parent,
                                   const Key& key, const T& obj) {
  std::pair<typename BinaryTree<Key, T>::iterator, bool> answer;
  if (node == nullptr) {
    node = new Node<Key, T>(key, obj);
    node->parent_ = parent;
    answer = std::make_pair(iterator(root_, node), true);
    size_++;
  } else if (key < node->key_) {
    answer = insertMSetNode(node->left_, node, key, obj);
  } else {
    answer = insertMSetNode(node->right_, node, key, obj);
  }
  return answer;
}

template <typename Key, typename T>
void BinaryTree<Key, T>::clearHelper(Node<Key, T>* node) {
  if (node != nullptr) {
    clearHelper(node->left_);
    clearHelper(node->right_);
    node->parent_ = nullptr;
    delete node;
  }
}

template <typename Key, typename T>
Node<Key, T>* BinaryTree<Key, T>::copyTree(Node<Key, T>* node) {
  Node<Key, T>* n_node = nullptr;
  if (node != nullptr) {
    n_node = new Node<Key, T>(node->key_, node->value_);
    n_node->parent_ = node->parent_;
    n_node->left_ = copyTree(node->left_);
    n_node->right_ = copyTree(node->right_);
  }
  return n_node;
}
template <typename Key, typename T>
typename BinaryTree<Key, T>::iterator BinaryTree<Key, T>::findHelper(
    const Key& key, Node<Key, T>* node) {
  iterator answer(end());

  while (node != nullptr) {
    if (key == node->key_) {
      answer = iterator(node);
      break;
    } else if (key > node->key_) {
      node = node->right_;
    } else {
      node = node->left_;
    }
  }
  return answer;
}

template <typename Key, typename T>
void BinaryTree<Key, T>::eraseHelper(Node<Key, T>*& node,
                                     Node<Key, T>* parent) {
  Node<Key, T>* child = nullptr;
  if (node->left_ == nullptr && node->right_ == nullptr) {
    if (parent) {
      if (parent->left_ == node) {
        parent->left_ = nullptr;
      } else {
        parent->right_ = nullptr;
      }
    } else {
      root_ = nullptr;
    }
  } else if (node->left_ != nullptr && node->right_ != nullptr) {
    Node<Key, T>* successor = node->right_->FindMin();
    node->key_ = successor->key_;
    node->value_ = successor->value_;
    erase(iterator(successor));
  } else {
    child = node->left_ ? node->left_ : node->right_;
    if (parent) {
      if (parent->left_ == node) {
        parent->left_ = child;
      } else {
        parent->right_ = child;
      }
    } else {
      root_ = child;
    }
    if (child) child->parent_ = parent;
  }
  delete node;
  size_--;
}

}  // namespace s21

#endif  // BINARYTREE_CPP
