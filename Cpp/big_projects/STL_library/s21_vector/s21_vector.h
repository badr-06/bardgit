#ifndef S21_VECTOR_H_
#define S21_VECTOR_H_

#include <iostream>
#include <limits>

namespace s21 {
template <typename T>
class vector {
 public:
  // Vector Member type
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;
  // Vector Member functions
  vector();
  explicit vector(size_type n);
  vector(std::initializer_list<value_type> const &items);
  vector(const vector<T> &v);
  vector(vector<T> &&v);
  ~vector();
  vector<T> &operator=(vector<T> &&v);
  // Vector Element access
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  T *data();
  // Vector Iterators
  iterator begin();
  iterator end();
  // Vector Capacity
  bool empty();
  size_type size();
  size_type max_size();
  void reserve(size_type size);
  size_type capacity();
  void shrink_to_fit();
  // Vector Modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other);
  // Part 3. Дополнительно. Реализация методов
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <typename... Args>
  void insert_many_back(Args &&...args);

 private:
  T *arr;
  size_type sz;
  size_type cap;
};
}  // namespace s21

#include "s21_vector.tpp"

#endif
