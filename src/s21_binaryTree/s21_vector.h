#include <cstddef>
#include <iostream>
#include <iterator>
#include <limits>
#include <stdexcept>
#include <utility>

namespace s21 {
template <class T>
class VectorIterator {
 public:
  using value_type = T;
  using reference = value_type &;
  using pointer = value_type *;
  using difference_type = std::ptrdiff_t;

 protected:
  pointer iter;

 public:
  VectorIterator() : iter(nullptr) {}
  explicit VectorIterator(pointer ptr) : iter(ptr) {}
  VectorIterator(const VectorIterator &other) = default;
  VectorIterator(VectorIterator &&other) noexcept : iter(other.iter) {
    other.iter = nullptr;
  }
  ~VectorIterator() = default;

  reference operator*() const { return *iter; }
  pointer operator->() const { return iter; }

  VectorIterator &operator=(const VectorIterator &other) = default;
  VectorIterator &operator=(VectorIterator &&other) noexcept {
    if (this != &other) this->iter = std::exchange(other.iter, nullptr);
    return *this;
  }

  VectorIterator &operator--() {
    --iter;
    return *this;
  }

  VectorIterator operator--(int) {
    VectorIterator tmp(*this);
    --(*this);
    return tmp;
  }

  VectorIterator &operator++() {
    ++iter;
    return *this;
  }

  VectorIterator operator++(int) {
    VectorIterator tmp(*this);
    ++(*this);
    return tmp;
  }

  bool operator==(const VectorIterator &other) const {
    return this->iter == other.iter;
  }

  bool operator!=(const VectorIterator &other) const {
    return this->iter != other.iter;
  }

  VectorIterator &operator+=(int pos) {
    iter += pos;
    return *this;
  }

  VectorIterator &operator-=(int pos) {
    iter -= pos;
    return *this;
  }

  difference_type operator-(const VectorIterator &other) const {
    return this->iter - other.iter;
  }

  VectorIterator operator-(difference_type offset) const {
    return VectorIterator(iter - offset);
  }

  VectorIterator operator+(int n) const {
    VectorIterator copy(*this);
    return copy += n;
  }

  bool operator>(const VectorIterator &other) const {
    return this->iter > other.iter;
  }

  bool operator>=(const VectorIterator &other) const {
    return this->iter >= other.iter;
  }

  bool operator<(const VectorIterator &other) const {
    return this->iter < other.iter;
  }

  bool operator<=(const VectorIterator &other) const {
    return this->iter <= other.iter;
  }
};

template <class T>
class Vector {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using pointer = value_type *;
  using iterator = VectorIterator<value_type>;
  // using const_iterator = VectorConstIterator<value_type>;
  using size_type = size_t;

 private:
  size_type siz;
  size_type cap;
  value_type *arr;

 public:
  Vector() : siz(0U), cap(0U), arr(nullptr) {}

  Vector(size_type n) : siz(n), cap(n), arr(n ? new value_type[n] : nullptr) {
    std::fill(arr, arr + n, value_type());
  }

  Vector(std::initializer_list<value_type> const &items)
      : siz(items.size()),
        cap(items.size()),
        arr(new value_type[items.size()]) {
    std::copy(items.begin(), items.end(), arr);
  }

  Vector(const Vector &v) : siz(v.siz), cap(v.cap), arr(new value_type[v.cap]) {
    std::copy(v.arr, v.arr + v.siz, arr);
  }

  Vector(Vector &&v) noexcept : siz(v.siz), cap(v.cap), arr(v.arr) {
    v.arr = nullptr;
    v.siz = 0;
    v.cap = 0;
  }

  ~Vector() {
    delete[] arr;
    arr = nullptr;
    siz = 0;
    cap = 0;
  }

  iterator end() noexcept { return iterator(arr + siz); }
  iterator begin() noexcept { return empty() ? end() : iterator(arr); }

  Vector &operator=(const Vector &v) {
    if (this != &v) {
      value_type *copy_v = new value_type[v.cap];
      std::copy(v.arr, v.arr + v.siz, copy_v);
      delete[] arr;
      arr = copy_v;
      siz = v.siz;
      cap = v.cap;
    }
    return *this;
  }

  Vector &operator=(Vector &&v) noexcept {
    if (this != &v) {
      delete[] arr;
      siz = std::exchange(v.siz, 0);
      cap = std::exchange(v.cap, 0);
      arr = std::exchange(v.arr, nullptr);
    }
    return *this;
  }

  reference at(size_type pos) {
    if (pos >= siz) {
      throw std::out_of_range("Индекс выходит за пределы контейнера");
    }
    return arr[pos];
  }

  reference operator[](size_type pos) { return arr[pos]; }
  const_reference front() { return arr[0]; }
  const_reference back() { return arr[siz - 1]; }
  iterator data() noexcept { return iterator(arr); }

  bool empty() const noexcept { return siz == 0; }
  size_type size() const noexcept { return siz; }
  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(value_type) / 2;
  }

  void reserve(size_type size) {
    if (size <= cap) return;
    if (size > max_size()) {
      throw std::length_error("Превышен лимит памяти");
    }
    value_type *buffer = new value_type[size];
    std::copy(arr, arr + siz, buffer);
    delete[] arr;
    arr = buffer;
    buffer = nullptr;
    cap = size;
  }

  size_type capacity() { return cap; }

  void shrink_to_fit() {
    if (siz == cap) return;
    value_type *buffer = new value_type[size];
    std::copy(begin(), end(), buffer);
    delete[] arr;
    arr = buffer;
    buffer = nullptr;
    cap = siz;
  }

  void clear() noexcept {
    for (size_type i = 0; i < siz; ++i) {
      arr[i].~value_type();
    }
    siz = 0;
  }

  iterator insert(iterator pos, const_reference value) {
    if (pos < begin() || pos > end()) {
      throw std::out_of_range("Позиция вставки вне диапазона контейнера");
    }
    size_type insert_pos = pos - begin();
    if (pos > begin() || pos < end()) {
      if (cap == siz) {
        reserve(siz * 2);
      }
      ++siz;
      for (size_type i = siz; i > insert_pos; --i) {
        arr[i] = arr[i - 1];
      }
      arr[insert_pos] = value;
    } else if (pos == end()) {
      push_back();
    }
    return begin() + insert_pos;
  }

  void erase(iterator pos) {
    if (pos < begin() || pos >= end()) {
      throw std::out_of_range("Позиция удаления вне диапазона контейнера");
    }
    size_type erase_pos = pos - begin();
    for (size_type i = erase_pos; i < siz - 1; ++i) {
      arr[i] = arr[i + 1];
    }
    --siz;
  }

  void push_back(const_reference value) {
    if (cap == siz) {
      reserve(siz * 2);
    }
    arr[siz] = value;
    ++siz;
  }

  void pop_back() { erase(end() - 1); }

  void swap(Vector &other) {
    std::swap(arr, other.arr);
    std::swap(siz, other.siz);
    std::swap(cap, other.cap);
  }
};
}  // namespace s21
/*int main () {
  std::vector<int> p({1, 2, 3, 4, 5});
  std::vector<int> b({7, 7, 7});
  Vector<int> q({1, 2, 3, 4, 5});
  Vector<int> s({7, 7, 7});

  std::cout << std::uppercase << "p.cap = " << std::dec << p.capacity() <<
  '\n'; std::cout << std::uppercase << "p.siz = " << std::dec << p.size() <<
  '\n'; std::cout << std::uppercase << "b.cap = " << std::dec << b.capacity()
  << '\n'; std::cout << std::uppercase << "b.siz = " << std::dec << b.size()
  << '\n'; std::cout << std::uppercase << "q.cap = " << std::dec <<
  q.capacity() << '\n'; std::cout << std::uppercase << "q.siz = " << std::dec
  << q.size() << '\n'; std::cout << std::uppercase << "s.cap = " << std::dec
  << s.capacity() << '\n'; std::cout << std::uppercase << "s.siz = " <<
  std::dec << s.size() << '\n';

  p.swap(b);
  q.swap(s);
  //std::cout << std::uppercase << "p.count = " << std::dec <<
  p.end()-p.begin()
<< '\n';
  //std::cout << std::uppercase << "q.count = " << std::dec <<
q.end()-q.begin()<< '\n'; std::cout << std::uppercase << "p.cap = " <<
std::dec
<< p.capacity() << '\n'; std::cout << std::uppercase << "p.siz = " <<
std::dec
<< p.size() << '\n'; std::cout << std::uppercase << "b.cap = " << std::dec <<
b.capacity() << '\n'; std::cout << std::uppercase << "b.siz = " << std::dec
<< b.size() << '\n'; std::cout << std::uppercase << "q.cap = " << std::dec <<
q.capacity() << '\n'; std::cout << std::uppercase << "q.siz = " << std::dec
<< q.size() << '\n'; std::cout << std::uppercase << "s.cap = " << std::dec <<
s.capacity() << '\n'; std::cout << std::uppercase << "s.siz = " << std::dec
<< s.size() << '\n'; std::cout << "p "; for (auto it = p.begin(); it !=
p.end();
++it) { std::cout << *it << ' ';
  }
  std::cout << "\nb ";
  for (auto it = b.begin(); it != b.end(); ++it) {
      std::cout << *it << ' ';
  }
  std::cout << "\nq ";
  for (VectorIterator<int> it = q.begin(); it != q.end(); ++it) {
      std::cout << *it << ' ';
  }
  std::cout << "\ns ";
  for (VectorIterator<int> it = s.begin(); it != s.end(); ++it) {
      std::cout << *it << ' ';
  }
  std::cout << '\n';

  std::cout << std::uppercase << "p.end = " << std::dec << *p.end() << '\n';
  std::cout << std::uppercase << "q.end = " << std::dec << *q.end() << '\n';

  return 0;
}*/