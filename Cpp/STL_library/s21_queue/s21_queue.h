#ifndef S21_QUEUE_H
#define S21_QUEUE_H

#include <initializer_list>
#include <stdexcept>
#include <utility>

namespace s21 {

template <typename T>
class queue {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

 private:
  struct Node {
    value_type data;
    Node* next;
    explicit Node(const_reference value) : data(value), next(nullptr) {}
    explicit Node(value_type&& value) : data(std::move(value)), next(nullptr) {}
  };

  Node* front_;
  Node* back_;
  size_type size_;

 public:
  // Конструкторы
  queue();
  queue(std::initializer_list<value_type> const& items);
  queue(const queue& other);
  queue(queue&& other) noexcept;

  // Деструктор
  ~queue();

  // Оператор присваивания
  queue& operator=(queue&& other);

  // Доступ к элементам
  const_reference front() const;
  const_reference back() const;

  // Утилиты
  bool empty() const noexcept;
  size_type size() const noexcept;

  // Модификаторы
  void push(const_reference value);
  void pop();
  void swap(queue& other) noexcept;

  template <typename... Args>
  void insert_many_back(Args&&... args);
};

}  // namespace s21

// Подключаем файл с реализацией методов
#include "s21_queue.tpp"

#endif  // S21_QUEUE_H
