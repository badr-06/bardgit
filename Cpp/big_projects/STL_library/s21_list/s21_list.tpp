/* в конструкторы list(size_type n) и list(list&& other) добавлена инициализация
через базовый конструктор без параметров все размещено в namespace s21 позволит
писать list<T> вместо s21::list<T> замена обявления функции согласно задания с
push_back(T data) , push_front(T data) на   push_front(const_reference value) и
push_back(const_reference value)
*/

#include "s21_list.h"

namespace s21 {
template <typename T>
list<T>::list() : length(0) {
  init_sentinel();
}

template <typename T>
list<T>::list(size_type n) : list() {
  for (size_type i = 0; i < n; ++i) {
    this->push_back(0);
  }
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const& items) : length(0) {
  init_sentinel();

  for (const auto& it : items) {
    this->push_back(it);
  }
}

template <typename T>
list<T>::list(const list& other) : length(0) {
  init_sentinel();

  for (const auto& it : other) {
    this->push_back(it);
  }
}

template <typename T>
list<T>::list(list&& other) : list() {
  if (this != &other) {
    clear();
    delete sentinel;
    this->sentinel = other.sentinel;
    this->length = other.length;
    other.init_sentinel();
  }
}

template <typename T>
list<T> list<T>::operator=(list&& l) {
  if (this != &l) {
    this->clear();
    delete sentinel;
    this->sentinel = l.sentinel;
    this->length = l.length;
    l.init_sentinel();
  }
  return *this;
}

template <typename T>
list<T>::~list() {
  clear();
  delete sentinel;
}

template <typename T>
void list<T>::pop_back() {
  if (length) {
    Node* del = sentinel->pPrev;
    sentinel->pPrev = del->pPrev;
    del->pPrev->pNext = sentinel;

    delete del;
    length--;
  }
}

template <typename T>
void list<T>::pop_front() {
  if (length) {
    Node* del = sentinel->pNext;
    sentinel->pNext = del->pNext;
    del->pNext->pPrev = sentinel;

    delete del;
    length--;
  }
}

template <typename T>
void list<T>::swap(list& other) {
  Node* newNode = other.sentinel;
  other.sentinel = this->sentinel;
  this->sentinel = newNode;

  size_type temp = other.length;
  other.length = this->length;
  this->length = temp;
}

template <typename T>
void list<T>::merge(list& other) {
  if (other.length) {
    list<T> NewList = merge_sort(*this, other);
    other.clear();
    this->swap(NewList);
  }
}

template <typename T>
void list<T>::splice(const_iterator pos, list& other) {
  if (other.length) {
    Node* other_head = other.sentinel->pNext;
    Node* other_tail = other.sentinel->pPrev;

    Node* this_head = pos.current->pPrev;
    Node* this_tail = pos.current;

    this_head->pNext = other_head;
    other_head->pPrev = this_head;

    other_tail->pNext = this_tail;
    this_tail->pPrev = other_tail;

    this->sentinel->data = (this->length += other.length);

    delete other.sentinel;

    other.init_sentinel();
    other.length = 0;
  }
}

// sentinel->5->2->sentinel | 2
template <typename T>
void list<T>::reverse() {
  if (length <= 1) {
    return;  // Ничего не делаем для пустого или одноэлементного списка
  }

  Node* head = sentinel->pNext;
  Node* tail = sentinel->pPrev;

  Node* current = head;
  Node* temp = nullptr;

  while (current != sentinel) {
    temp = current->pNext;
    current->pNext = current->pPrev;
    current->pPrev = temp;

    current = current->pPrev;
  }

  tail->pPrev = sentinel;
  head->pNext = sentinel;

  sentinel->pNext = tail;
  sentinel->pPrev = head;
}

template <typename T>
void list<T>::unique() {
  if (length <= 1) {
    return;
  }

  auto it2 = begin();

  for (auto it1 = begin(); it2 != end(); ++it1) {
    ++it2;
    while (it1 == it2 && length > 1 && it2 != end()) {
      it2 = erase(it2);
    }
  }
}

template <typename T>
void list<T>::sort() {
  Node* head = sentinel->pNext;

  list<T> Newlist = sortList(head);

  this->swap(Newlist);
  Newlist.clear();
}

template <typename T>
typename s21::list<T> list<T>::sortList(Node* head) {
  if (head == sentinel || head->pNext == sentinel) {
    list<T> newlist;
    newlist.push_back(head->data);
    return newlist;
  }

  Node* mid = midNode(head);
  list<T> left = sortList(head);
  list<T> ritgh = sortList(mid);
  return merge_sort(left, ritgh);
}

template <typename T>
typename s21::list<T> list<T>::merge_sort(list l1, list l2) {
  list<T> NewList;
  auto it1 = l1.begin();
  auto it2 = l2.begin();

  while (it1 != l1.end() && it2 != l2.end()) {
    if (*it1 <= *it2) {
      NewList.push_back(*it1);
      ++it1;
    } else {
      NewList.push_back(*it2);
      ++it2;
    }
  }

  while (it1 != l1.end()) {
    NewList.push_back(*it1);
    ++it1;
  }
  while (it2 != l2.end()) {
    NewList.push_back(*it2);
    ++it2;
  }

  return NewList;
}

template <typename T>
typename list<T>::Node* list<T>::midNode(Node* head) {
  Node* midPrev = head;
  head = head->pNext;

  while (head != sentinel && head->pNext != sentinel) {
    midPrev = midPrev->pNext;
    head = head->pNext->pNext;
  }

  Node* mid = midPrev->pNext;
  midPrev->pNext = sentinel;
  return mid;
}

template <typename T>
void list<T>::clear() {
  while (length) {
    this->pop_back();
  }
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  Node* newNode = new Node(value);

  newNode->pNext = pos.current;
  newNode->pPrev = pos.current->pPrev;

  pos.current->pPrev->pNext = newNode;
  pos.current->pPrev = newNode;

  length++;
  return iterator(pos.current);
}

template <typename T>
typename list<T>::iterator list<T>::erase(iterator pos) {
  Node* newNode = pos.current;

  pos.current = newNode->pNext;

  pos.current->pNext = newNode->pNext->pNext;
  pos.current->pPrev = newNode->pPrev;

  newNode->pPrev->pNext = pos.current;

  newNode->pNext = nullptr;
  newNode->pPrev = nullptr;

  delete newNode;
  sentinel->data = (--length);
  return iterator(pos.current);
}

template <typename T>
bool list<T>::empty() {
  return this->length == 0 ? true : false;
}

template <typename T>
void list<T>::init_sentinel() {
  sentinel = new Node();
  sentinel->pNext = sentinel;
  sentinel->pPrev = sentinel;
  length = 0;
}

template <typename T>
inline void list<T>::push_front(const_reference value) {
  if (this->length == 0) {
    Node* newNode = new Node(value, sentinel, sentinel);
    this->sentinel->pNext = newNode;
    this->sentinel->pPrev = newNode;
  } else {
    Node* head = this->sentinel->pNext;

    Node* new_head = new Node(value, head, sentinel);
    sentinel->pNext = new_head;
    head->pPrev = new_head;
  }
  length++;
}

template <typename T>
inline void list<T>::push_back(const_reference value) {
  if (this->length == 0) {
    Node* newNode = new Node(value, sentinel, sentinel);
    sentinel->pNext = newNode;
    sentinel->pPrev = newNode;
  } else {
    Node* tail = this->sentinel->pPrev;

    Node* new_tail = new Node(value, sentinel, tail);
    sentinel->pPrev = new_tail;
    tail->pNext = new_tail;
  }

  length++;
}

// Part 3. Дополнительно
template <typename T>
template <typename... Args>
typename list<T>::iterator list<T>::insert_many(const_iterator pos,
                                                Args&&... args) {
  iterator it(pos.current);
  (insert(it, std::forward<Args>(args)), ...);
  return it;
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_back(Args&&... args) {
  std::initializer_list<value_type> values = {std::forward<Args>(args)...};
  for (const auto& value : values) {
    push_back(value);
  }
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_front(Args&&... args) {
  std::initializer_list<value_type> values = {std::forward<Args>(args)...};
  for (auto it = values.end(); it != values.begin();) {
    --it;
    push_front(*it);
  }
}

}  // namespace s21
