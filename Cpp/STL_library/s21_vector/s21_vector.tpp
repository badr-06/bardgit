#ifndef S21_VECTOR_TPP_
#define S21_VECTOR_TPP_

#include <memory>
#include <utility>

#include "s21_vector.h"

namespace s21 {
template <typename T>
vector<T>::vector() : arr(nullptr), sz(0), cap(0) {}

template <typename T>
vector<T>::vector(size_type n) : arr(new value_type[n]), sz(n), cap(n) {
  std::fill_n(arr, n, value_type());
}

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const &items)
    : arr(new value_type[items.size()]), sz(items.size()), cap(items.size()) {
  std::copy(items.begin(), items.end(), arr);
}

template <typename T>
vector<T>::vector(const vector &v)
    : arr(new value_type[v.cap]), sz(v.sz), cap(v.cap) {
  std::copy(v.arr, v.arr + v.sz, arr);
}

template <typename T>
vector<T>::vector(vector &&v) {
  sz = std::exchange(v.sz, 0);
  cap = std::exchange(v.cap, 0);
  arr = std::exchange(v.arr, nullptr);
}

template <typename T>
vector<T>::~vector() {
  delete[] arr;
  sz = 0;
  cap = 0;
  arr = nullptr;
}

template <typename T>
vector<T> &vector<T>::operator=(vector<T> &&v) {
  if (this != &v) {
    this->swap(v);
    delete[] v.arr;
    v.sz = 0;
    v.cap = 0;
    v.arr = nullptr;
  }
  return *this;
}

template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= sz) throw std::out_of_range("Index out of range");

  return arr[pos];
}

template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
  if (pos >= sz) throw std::out_of_range("Index out of range");

  return arr[pos];
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() {
  if (!sz) throw std::out_of_range("Front: Vector is empty");

  return arr[0];
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() {
  if (!sz) throw std::out_of_range("Back: Vector is empty");

  return arr[sz - 1];
}

template <typename T>
typename vector<T>::iterator vector<T>::data() {
  return arr;
}

template <typename T>
typename vector<T>::iterator vector<T>::begin() {
  return iterator(arr);
}

template <typename T>
typename vector<T>::iterator vector<T>::end() {
  return iterator(arr + sz);
}

template <typename T>
bool vector<T>::empty() {
  return sz == 0 ? true : false;
}

template <typename T>
typename vector<T>::size_type vector<T>::size() {
  return sz;
}

template <typename T>
typename vector<T>::size_type vector<T>::max_size() {
  return std::numeric_limits<std::size_t>::max() / sizeof(value_type);
}

template <typename T>
void vector<T>::clear() {
  delete[] arr;
  arr = nullptr;
  sz = 0;
}

template <typename T>
void vector<T>::reserve(size_type size) {
  if (size <= cap) return;
  T *newarr = reinterpret_cast<T *>(new std::byte[size * sizeof(T)]);
  std::uninitialized_copy(arr, arr + sz, newarr);
  for (size_t i = 0; i < sz; i++) {
    (arr + i)->~T();
  }
  delete[] reinterpret_cast<std::byte *>(arr);
  arr = newarr;
  cap = size;
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() {
  return cap;
}

template <typename T>
void vector<T>::shrink_to_fit() {
  if (sz != cap) {
    vector<value_type> tmp(sz);
    for (size_type i = 0; i < sz; i++) {
      tmp.arr[i] = arr[i];
    }
    *this = std::move(tmp);
  }
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  size_type position = pos - begin();
  if (position > sz) {
    throw std::out_of_range("position out of range");
  }
  if (sz == cap) reserve(cap ? cap * 2 : 1);

  iterator new_position = begin() + position;
  for (iterator i = end(); i != new_position; --i) {
    *i = *(i - 1);
  }
  *new_position = value;
  sz++;
  return new_position;
}

template <typename T>
void vector<T>::erase(iterator pos) {
  size_type position = pos - arr;
  if (position > sz) throw std::out_of_range("Erase: Index out of range");

  for (iterator i = pos; i != end() - 1; ++i) {
    *i = *(i + 1);
  }
  sz--;
}

template <typename T>
void vector<T>::push_back(const_reference valye) {
  if (cap == sz) {
    reserve(cap ? cap * 2 : 1);
  }
  arr[sz] = valye;
  sz++;
}

template <typename T>
void vector<T>::pop_back() {
  if (sz > 0) sz--;
}

template <typename T>
void vector<T>::swap(vector<T> &other) {
  std::swap(arr, other.arr);
  std::swap(sz, other.sz);
  std::swap(cap, other.cap);
}
// Part 3. Дополнительно. Реализация методов
template <typename T>
template <typename... Args>
typename vector<T>::iterator vector<T>::insert_many(const_iterator pos,
                                                    Args &&...args) {
  vector<value_type> tmp{args...};
  iterator position = const_cast<iterator>(pos);
  for (size_type i = 0; i < tmp.size(); i++) {
    position = insert(position, tmp[i]) + 1;
  }
  return position;
}

template <typename T>
template <typename... Args>
void vector<T>::insert_many_back(Args &&...args) {
  insert_many(this->end(), args...);
}

}  // namespace s21

#endif
