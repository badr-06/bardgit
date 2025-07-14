#ifndef S21_STACK_TPP_
#define S21_STACK_TPP_

#include "s21_stack.h"

namespace s21 {

template <typename T>
stack<T>::stack() : header(NULL), ssize(0) {}

template <typename T>
stack<T>::stack(std::initializer_list<s21_value_type> const &items) : stack() {
  for (auto s : items) {
    push(s);
  }
}

template <typename T>
stack<T>::stack(const stack &s) : stack() {
  if (!s.empty()) this->copyStack(s);
}

template <typename T>
stack<T>::stack(stack &&s) : stack() {
  this->header = s.header;
  this->ssize = s.ssize;
  s.header = NULL;
  s.ssize = 0;
}

template <typename T>
stack<T> &stack<T>::operator=(stack &&s) {
  this->destroyStack();
  if (!s.empty() && (this != &s)) {
    this->copyStack(s);
    ssize = s.ssize;
    s.destroyStack();
  }
  return *this;
}

template <typename T>
stack<T>::~stack() {
  this->destroyStack();
  ssize = 0;
  header = NULL;
}

template <typename T>
s21_const_reference stack<T>::top() const {
  return header->data;
}
template <typename T>
bool stack<T>::empty() const {
  if (header == NULL)
    return true;
  else
    return false;
}

template <typename T>
s21_size_type stack<T>::size() const {
  return ssize;
}
template <typename T>
void stack<T>::push(s21_const_reference value) noexcept {
  node<T> *n = new node<T>();
  n->tail = header;
  n->data = value;
  header = n;
  ssize++;
}
template <typename T>
void stack<T>::pop() noexcept {
  node<T> *n = header->tail;
  delete header;
  header = n;
  ssize--;
}
template <typename T>
void stack<T>::swap(stack &other) noexcept {
  if (this != &other) {
    node<T> *tmp = other.header;
    other.header = this->header;
    this->header = tmp;

    s21_size_type tmpSize = other.ssize;
    other.ssize = this->ssize;
    this->ssize = tmpSize;
  }
}
template <typename T>
void stack<T>::copyStack(const stack &s) noexcept {
  node<T> el = *s.header;
  stack copy;
  while (el.tail != NULL) {
    copy.push(el.data);
    el = *el.tail;
  }
  copy.push(el.data);

  while (!copy.empty()) {
    this->push(copy.top());
    copy.pop();
  }
}
template <typename T>
void stack<T>::destroyStack() noexcept {
  while (this->ssize > 0) {
    this->pop();
  }
}

template <typename T>
template <typename... Args>
void stack<T>::insert_many_back(Args &&...args) {
  std::initializer_list<T> a({static_cast<T>(args)...});
  if (a.size() > 0)
    for (auto item : a) push(item);
}

}  // namespace s21
#endif
