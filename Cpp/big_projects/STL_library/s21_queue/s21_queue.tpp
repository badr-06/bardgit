#ifndef S21_QUEUE_TPP
#define S21_QUEUE_TPP

namespace s21 {

// Конструкторы
template <typename T>
queue<T>::queue() : front_(nullptr), back_(nullptr), size_(0) {}

template <typename T>
queue<T>::queue(std::initializer_list<value_type> const& items) : queue() {
  for (const auto& item : items) push(item);
}

template <typename T>
queue<T>::queue(const queue& other)
    : front_(nullptr), back_(nullptr), size_(0) {
  for (Node* curr = other.front_; curr; curr = curr->next) push(curr->data);
}

template <typename T>
queue<T>::queue(queue&& other) noexcept
    : front_(other.front_), back_(other.back_), size_(other.size_) {
  other.front_ = other.back_ = nullptr;
  other.size_ = 0;
}

// Деструктор
template <typename T>
queue<T>::~queue() {
  while (!empty()) pop();  // Удаляем все элементы в деструкторе
}

template <typename T>
queue<T>& queue<T>::operator=(queue&& other) {
  if (this != &other) {
    while (!empty()) pop();  // Удаляем все элементы текущей очереди
    swap(other);
    other.front_ = other.back_ = nullptr;
    other.size_ = 0;
  }
  return *this;
}

// Доступ к элементам

template <typename T>
typename queue<T>::const_reference queue<T>::front() const {
  if (empty()) {
    throw std::out_of_range("queue is empty");
  }
  return front_->data;
}

template <typename T>
typename queue<T>::const_reference queue<T>::back() const {
  if (empty()) {
    throw std::out_of_range("queue is empty");
  }
  return back_->data;
}

// Утилиты
template <typename T>
bool queue<T>::empty() const noexcept {
  return size_ == 0;
}

template <typename T>
typename queue<T>::size_type queue<T>::size() const noexcept {
  return size_;
}

// Модификаторы
template <typename T>
void queue<T>::push(const_reference value) {
  Node* new_node = new Node(value);
  if (empty())
    front_ = new_node;
  else
    back_->next = new_node;
  back_ = new_node;
  ++size_;
}

template <typename T>
void queue<T>::pop() {
  if (empty()) {
    throw std::out_of_range("queue is empty");
  }

  Node* temp = front_;
  front_ = front_->next;
  delete temp;
  if (--size_ == 0) back_ = nullptr;
}

template <typename T>
void queue<T>::swap(queue& other) noexcept {
  std::swap(front_, other.front_);
  std::swap(back_, other.back_);
  std::swap(size_, other.size_);
}

template <typename T>
template <typename... Args>
void queue<T>::insert_many_back(Args&&... args) {
  (push(std::forward<Args>(args)), ...);
}

}  // namespace s21

#endif  // S21_QUEUE_TPP
