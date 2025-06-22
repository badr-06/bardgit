#ifndef S21_ARRAY_TPP_
#define S21_ARRAY_TPP_

#include "s21_array.h"

namespace s21 {
template <typename T, std::size_t N>
array<T, N>::array() : sz(N) {}

template <typename T, std::size_t N>
array<T, N>::array(std::initializer_list<value_type> const &items) : array() {
  for (size_type i = 0; i < items.size(); i++) {
    arr[i] = *(items.begin() + i);
  }
}

template <typename T, std::size_t N>
array<T, N>::array(const array<T, N> &a) {
  for (size_type i = 0; i < sz; i++) {
    arr[i] = a.arr[i];
  }
}

template <typename T, std::size_t N>
array<T, N>::array(array<T, N> &&a) : array(a) {}

template <typename T, std::size_t N>
array<T, N>::~array() {}

template <typename T, std::size_t N>
array<T, N> &array<T, N>::operator=(array<T, N> &&a) {
  if (this != &a) {
    for (size_type i = 0; i < sz; i++) {
      arr[i] = a.arr[i];
    }
    sz = a.sz;
  }
  return *this;
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::at(size_type pos) {
  if (pos >= sz || sz == 0) throw std::out_of_range("Index out of range");

  return arr[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
  return *(arr + pos);
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::front() {
  return arr[0];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::back() {
  return arr[sz - 1];
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::data() {
  return arr;
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::begin() {
  return arr;
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::end() {
  return arr + sz;
}

template <typename T, std::size_t N>
bool array<T, N>::empty() {
  return sz == 0;
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::size() {
  return sz;
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::max_size() {
  return size();
}

template <typename T, std::size_t N>
void array<T, N>::swap(array &other) {
  for (size_type i = 0; i < sz; i++) {
    value_type tmp;
    tmp = other.arr[i];
    other.arr[i] = arr[i];
    arr[i] = tmp;
  }
}

template <typename T, std::size_t N>
void array<T, N>::fill(const_reference value) {
  for (size_type i = 0; i < sz; i++) {
    arr[i] = value;
  }
}

}  // namespace s21
#endif
