#include <gtest/gtest.h>

#include "s21_queue.h"

// Группа тестов для проверки конструкторов
TEST(QueueTest, ConstructorTests) {
  // Тест по умолчанию
  {
    s21::queue<int> q;
    EXPECT_TRUE(q.empty());
    EXPECT_EQ(q.size(), 0);
  }

  // Тест с инициализационным списком
  {
    s21::queue<int> q({1, 2, 3});
    EXPECT_FALSE(q.empty());
    EXPECT_EQ(q.size(), 3);
    EXPECT_EQ(q.front(), 1);
    EXPECT_EQ(q.back(), 3);
  }

  // Тест копирования
  {
    s21::queue<int> q1({1, 2, 3});
    s21::queue<int> q2(q1);
    EXPECT_EQ(q1.size(), q2.size());
    EXPECT_EQ(q2.front(), 1);
    EXPECT_EQ(q2.back(), 3);
  }

  // Тест перемещения
  {
    s21::queue<int> q1({1, 2, 3});
    s21::queue<int> q2(std::move(q1));
    EXPECT_TRUE(q1.empty());
    EXPECT_EQ(q2.size(), 3);
    EXPECT_EQ(q2.front(), 1);
    EXPECT_EQ(q2.back(), 3);
  }
}

// Группа тестов для проверки операторов присваивания
TEST(QueueTest, AssignmentOperators) {
  // Перемещение
  {
    s21::queue<int> q1;
    q1.push(1);
    q1.push(2);

    s21::queue<int> q2;
    q2 = std::move(q1);

    EXPECT_EQ(q2.size(), 2);
    EXPECT_EQ(q2.front(), 1);
    EXPECT_EQ(q2.back(), 2);
    EXPECT_TRUE(q1.empty());
  }
}

// Группа тестов для проверки методов push и pop
TEST(QueueTest, PushAndPop) {
  s21::queue<int> q;

  // Проверка push
  q.push(1);
  q.push(2);
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 2);

  // Проверка pop
  q.pop();
  EXPECT_EQ(q.front(), 2);
  EXPECT_EQ(q.size(), 1);
}

// Группа тестов для проверки доступа к элементам
TEST(QueueTest, AccessElements) {
  s21::queue<int> q({42, 55});

  // Константный доступ
  {
    const s21::queue<int> const_q({100, 200});
    EXPECT_EQ(const_q.front(), 100);
    EXPECT_EQ(const_q.back(), 200);
  }
}

// Группа тестов для проверки утилит empty и size
TEST(QueueTest, UtilityFunctions) {
  s21::queue<int> q;

  // Проверка empty
  EXPECT_TRUE(q.empty());
  q.push(1);
  EXPECT_FALSE(q.empty());

  // Проверка size
  EXPECT_EQ(q.size(), 1);
  q.push(2);
  EXPECT_EQ(q.size(), 2);
  q.pop();
  EXPECT_EQ(q.size(), 1);
}

// Группа тестов для проверки обработки пустой очереди
TEST(QueueTest, EmptyQueueBehavior) {
  s21::queue<int> q;

  // Проверка методов на пустой очереди
  EXPECT_THROW(q.front(), std::out_of_range);
  EXPECT_THROW(q.back(), std::out_of_range);
  EXPECT_THROW(q.pop(), std::out_of_range);

  // Проверка после удаления последнего элемента
  q.push(1);
  q.pop();
  EXPECT_THROW(q.pop(), std::out_of_range);
  EXPECT_THROW(q.front(), std::out_of_range);
  EXPECT_THROW(q.back(), std::out_of_range);
}

// Группа тестов для проверки метода insert_many_back
TEST(QueueTest, InsertManyBack) {
  s21::queue<int> q({1});
  q.insert_many_back(2, 3, 4);

  EXPECT_EQ(q.size(), 4);
  EXPECT_EQ(q.back(), 4);
  q.pop();
  EXPECT_EQ(q.front(), 2);
}

// Группа тестов для проверки крайних случаев
TEST(QueueTest, EdgeCases) {
  s21::queue<int> q1;
  q1.push(1);
  q1.pop();

  EXPECT_TRUE(q1.empty());
  EXPECT_EQ(q1.size(), 0);

  s21::queue<int> q2(std::move(q1));
  EXPECT_TRUE(q2.empty());
}

// Группа тестов для проверки метода swap
TEST(QueueTest, SwapMethod) {
  s21::queue<int> q1({1, 2, 3});
  s21::queue<int> q2({4, 5, 6});

  q1.swap(q2);

  EXPECT_EQ(q1.size(), 3);
  EXPECT_EQ(q1.front(), 4);
  EXPECT_EQ(q1.back(), 6);

  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q2.back(), 3);
}

// Группа тестов для проверки обработки исключений
TEST(QueueTest, ExceptionHandling) {
  // Проверка front() на пустой очереди
  {
    s21::queue<int> q;
    EXPECT_THROW(q.front(), std::out_of_range);
  }

  // Проверка back() на пустой очереди
  {
    s21::queue<int> q;
    EXPECT_THROW(q.back(), std::out_of_range);
  }

  // Проверка pop() на пустой очереди
  {
    s21::queue<int> q;
    EXPECT_THROW(q.pop(), std::out_of_range);
  }

  // Проверка const front() на пустой очереди
  {
    const s21::queue<int> q;
    EXPECT_THROW(q.front(), std::out_of_range);
  }

  // Проверка const back() на пустой очереди
  {
    const s21::queue<int> q;
    EXPECT_THROW(q.back(), std::out_of_range);
  }
}
