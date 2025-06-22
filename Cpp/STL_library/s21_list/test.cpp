#ifndef S21_TEST_LIST_STL_CPP
#define S21_TEST_LIST_STL_CPP

#include <gtest/gtest.h>

#include <list>

#include "s21_list.h"

using namespace s21;

using namespace std;

/*1 - CONSTRUCTOR TEST
// проверка дефолтного конструктора и работы функции size() & empty()
*/
TEST(simpleTests, listConstructor0) {
  std::list<int> origin;
  s21::list<int> list;

  EXPECT_EQ(origin.empty(), true);
  EXPECT_EQ(list.empty(), true);
  EXPECT_EQ(origin.size(), 0);
  EXPECT_EQ(list.size(), 0);

  std::list<bool> origin1;
  s21::list<bool> list1;

  EXPECT_EQ(origin1.empty(), true);
  EXPECT_EQ(list1.empty(), true);
  EXPECT_EQ(origin1.size(), 0);
  EXPECT_EQ(list1.size(), 0);
}

TEST(simpleTests, listConstructor3) {
  std::list<int> origin(5);
  s21::list<int> list(5);

  EXPECT_EQ(origin.empty(), false);
  EXPECT_EQ(list.empty(), false);
  EXPECT_EQ(origin.size(), 5);
  EXPECT_EQ(list.size(), 5);
  EXPECT_EQ(origin.front(), 0);
  EXPECT_EQ(list.front(), 0);
  EXPECT_EQ(origin.back(), 0);
  EXPECT_EQ(list.back(), 0);

  std::list<bool> origin1(5);
  s21::list<bool> list1(5);

  EXPECT_EQ(origin1.empty(), false);
  EXPECT_EQ(list1.empty(), false);
  EXPECT_EQ(origin1.size(), 5);
  EXPECT_EQ(list1.size(), 5);
  EXPECT_EQ(origin1.front(), 0);
  EXPECT_EQ(list1.front(), 0);
  EXPECT_EQ(origin1.back(), 0);
  EXPECT_EQ(list1.back(), 0);
}

TEST(simpleTests, listConstructor5) {
  std::list<int> origin{9, 2, 4, 6, 2};
  s21::list<int> list{9, 2, 4, 6, 2};

  EXPECT_EQ(origin.empty(), false);
  EXPECT_EQ(list.empty(), false);
  EXPECT_EQ(origin.size(), 5);
  EXPECT_EQ(list.size(), 5);
  EXPECT_EQ(origin.size(), 5);
  EXPECT_EQ(list.size(), 5);
  EXPECT_EQ(origin.front(), 9);
  EXPECT_EQ(list.front(), 9);
  EXPECT_EQ(origin.back(), 2);
  EXPECT_EQ(list.back(), 2);
}

TEST(simpleTests, listConstructor_String) {
  std::list<std::string> origin{"first", "string", "Second"};
  s21::list<std::string> list{"string", "size", "equal"};
  EXPECT_EQ(origin.empty(), false);
  EXPECT_EQ(list.empty(), false);
  while (origin.size() > 0) {
    EXPECT_EQ(origin.empty(), false);
    EXPECT_EQ(list.empty(), false);
    origin.pop_back();
    list.pop_back();
  }
  EXPECT_EQ(origin.empty(), true);
  EXPECT_EQ(list.empty(), true);
}

TEST(simpleTests, listConstructor6) {
  std::list<int> origin = {9, 2, 4, 6, 2};
  s21::list<int> list = {9, 2, 4, 6, 2};

  EXPECT_EQ(origin.empty(), false);
  EXPECT_EQ(list.empty(), false);
  EXPECT_EQ(origin.size(), 5);
  EXPECT_EQ(list.size(), 5);

  EXPECT_EQ(origin.front(), 9);
  EXPECT_EQ(list.front(), 9);
  EXPECT_EQ(origin.back(), 2);
  EXPECT_EQ(list.back(), 2);
}

TEST(simpleTest, max_size_test) {
  size_t n = 1e4;
  s21::list<int> lst(n);
  EXPECT_EQ(lst.size(), n);
  EXPECT_TRUE(lst.max_size() != 0);
  lst.pop_back();
  lst.pop_front();
  EXPECT_EQ(lst.size(), (n - 2));
  int back = lst.back();
  int front = lst.front();
  EXPECT_EQ(back, 0);
  EXPECT_EQ(front, 0);
}

TEST(mediumTests, listConstructor7) {
  std::list<bool> origin(
      {true, false, true, true, true, 0, 1, 1, true, false, 0, 0, 0});
  s21::list<bool> list(
      {true, false, true, true, true, 0, true, 1, 1, 0, false, 0, false});
  EXPECT_EQ(origin.empty(), false);
  EXPECT_EQ(list.empty(), false);
  while (list.size() > 0) {
    EXPECT_EQ(origin.empty(), false);
    EXPECT_EQ(list.empty(), false);
    origin.pop_back();
    list.pop_back();
  }
  EXPECT_EQ(origin.empty(), true);
  EXPECT_EQ(list.empty(), true);
}

TEST(hardTest, constuctorCopyTest) {
  std::list<bool> origin(
      {true, false, true, true, true, 0, 1, 1, true, false, 0, 0, 0});
  s21::list<bool> list(
      {true, false, true, true, true, 0, true, 1, 1, 0, false, 0, false});

  EXPECT_EQ(origin.empty(), false);
  EXPECT_EQ(list.empty(), false);

  std::list<bool> originCP(origin);
  s21::list<bool> listCP(list);

  EXPECT_EQ(originCP.empty(), false);
  EXPECT_EQ(listCP.empty(), false);

  EXPECT_EQ(origin.empty(), false);
  EXPECT_EQ(list.empty(), false);

  EXPECT_NE(&origin, &originCP);
  EXPECT_NE(&list, &listCP);

  EXPECT_EQ(origin.size(), 13);
  EXPECT_EQ(list.size(), 13);
  EXPECT_EQ(originCP.size(), 13);
  EXPECT_EQ(listCP.size(), 13);

  EXPECT_EQ(origin.front(), true);
  EXPECT_EQ(list.front(), true);
  EXPECT_EQ(origin.back(), false);
  EXPECT_EQ(list.back(), false);
}

TEST(hardTest, constuctorMoveTest) {  // ERROR Valgrind
  std::list<int> origin;
  s21::list<int> list;

  int count = 1300;
  while (count > 0) {
    count--;
    origin.push_back(count);
    list.push_back(count);
  }

  std::list<int> originCP(std::move(origin));
  s21::list<int> listCP(std::move(list));

  EXPECT_EQ(origin.empty(), true);
  EXPECT_EQ(list.empty(), true);
  EXPECT_EQ(origin.size(), 0);
  EXPECT_EQ(list.size(), 0);
  EXPECT_EQ(originCP.empty(), false);
  EXPECT_EQ(listCP.empty(), false);
  EXPECT_EQ(originCP.size(), 1300);
  EXPECT_EQ(listCP.size(), 1300);

  EXPECT_EQ(originCP.front(), 1299);
  EXPECT_EQ(listCP.front(), 1299);
  EXPECT_EQ(originCP.back(), 0);
  EXPECT_EQ(listCP.back(), 0);
}

TEST(hardTest, constuctorMoveTest2) {
  std::list<bool> origin(
      {true, false, true, true, true, 0, 1, 1, true, false, 0, 0, 0});
  s21::list<bool> list(
      {true, false, true, true, true, 0, true, 1, 1, 0, false, 0, false});

  std::list<bool> originCP(std::move(origin));
  s21::list<bool> listCP(std::move(list));
  EXPECT_EQ(origin.empty(), true);
  EXPECT_EQ(list.empty(), true);
  EXPECT_EQ(originCP.empty(), false);
  EXPECT_EQ(listCP.empty(), false);
  EXPECT_EQ(origin.size(), 0);
  EXPECT_EQ(list.size(), 0);
  EXPECT_EQ(originCP.size(), 13);
  EXPECT_EQ(listCP.size(), 13);
}

TEST(hardTest, operatorEqMoveTest) {
  std::list<int> origin;
  s21::list<int> list;

  std::list<int> originCP({1, 2, 3, 4, 5, 6, 7});
  s21::list<int> listCP({1, 2, 3, 4, 5, 6, 7});

  originCP = std::move(origin);
  listCP = std::move(list);

  EXPECT_NE(&origin, &originCP);
  EXPECT_NE(&list, &listCP);

  EXPECT_EQ(origin.empty(), true);
  EXPECT_EQ(originCP.empty(), true);
  EXPECT_EQ(list.empty(), true);
  EXPECT_EQ(listCP.empty(), true);

  EXPECT_EQ(origin.size(), 0);
  EXPECT_EQ(originCP.size(), 0);
  EXPECT_EQ(list.size(), 0);
  EXPECT_EQ(listCP.size(), 0);
}

// оператор перемещения
// list<T> s21::list<T>::operator=(list&& l)
// падает с free(): double free detected in tcache 2

TEST(simpleTest, operatorEqMoveTest) {
  std::list<int> origin;
  s21::list<int> list;
  std::list<int> originCP;
  originCP = std::move(origin);
  s21::list<int> listCP;
  listCP = std::move(list);

  EXPECT_NE(&origin, &originCP);
  EXPECT_NE(&list, &listCP);
}

TEST(mediumTest, operatorEqMoveTest) {
  std::list<int> origin({1, 2, 3, 4, 5, 6, 7});
  s21::list<int> list({1, 2, 3, 4, 5, 6, 7});
  int size = origin.size();

  std::list<int> originCP;
  s21::list<int> listCP;

  originCP = std::move(origin);
  listCP = std::move(list);

  EXPECT_NE(&origin, &originCP);
  EXPECT_NE(&list, &listCP);

  EXPECT_EQ(origin.empty(), true);
  EXPECT_EQ(originCP.empty(), false);
  EXPECT_EQ(list.empty(), true);
  EXPECT_EQ(listCP.empty(), false);
  EXPECT_EQ(origin.size(), 0);
  EXPECT_EQ(originCP.size(), size);
  EXPECT_EQ(list.size(), 0);
  EXPECT_EQ(listCP.size(), size);

  while (size > 1) {
    EXPECT_EQ(listCP.size(), originCP.size());
    originCP.pop_back();
    listCP.pop_back();
    size--;
  }
}

TEST(simpleTest, operatorEqTest) {
  std::list<int> origin;
  s21::list<int> list;

  std::list<int> originCP = origin;
  s21::list<int> listCP = list;

  EXPECT_EQ(originCP.empty(), true);
  EXPECT_EQ(listCP.empty(), true);
}

TEST(hardTest, operatorEqTest) {
  std::list<bool> origin(
      {true, false, true, true, true, 0, 1, 1, true, false, 0, 0, 0});
  s21::list<bool> list(
      {true, false, true, true, true, 0, true, 1, 1, 0, false, 0, false});

  std::list<bool> originCP = origin;
  s21::list<bool> listCP = list;
  EXPECT_NE(&origin, &originCP);
  EXPECT_NE(&list, &listCP);
  EXPECT_EQ(origin.size(), 13);
  EXPECT_EQ(list.size(), 13);
  EXPECT_EQ(originCP.size(), 13);
  EXPECT_EQ(listCP.size(), 13);
}

// проверить что будет если  копировать пустой список в непустой список
// ожидаение оба списка стали пустые и размеры их нулевые
// адреса списков разные

/*2 тест на внесении в конце списка */
TEST(simpleTests, listPushBackTest) {
  std::list<int> origin;
  s21::list<int> list;
  origin.push_back(3);
  list.push_back(3);
  origin.push_back(4);
  list.push_back(4);
  EXPECT_EQ(origin.empty(), false);
  EXPECT_EQ(list.empty(), false);
  EXPECT_EQ(origin.size(), 2);
  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(origin.back(), 4);
  EXPECT_EQ(list.back(), 4);
}

TEST(mediumTests, listPushPopBackTest) {
  std::list<int> origin;
  s21::list<int> list;
  int a = 2;
  list.push_back(a);
  origin.push_back(a);
  a = 8;
  list.push_back(a);
  origin.push_back(a);

  EXPECT_EQ(origin.empty(), false);
  EXPECT_EQ(list.empty(), false);
  EXPECT_EQ(origin.size(), 2);
  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(origin.back(), 8);
  EXPECT_EQ(list.back(), 8);

  list.pop_back();
  origin.pop_back();

  EXPECT_EQ(origin.empty(), false);
  EXPECT_EQ(list.empty(), false);
  EXPECT_EQ(origin.size(), 1);
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(origin.back(), 2);
  EXPECT_EQ(list.back(), 2);
}

TEST(mediumTests, listPushPopBackTest2) {
  std::list<int> origin;
  s21::list<int> list;

  list.push_back(2);
  origin.push_back(2);
  // вносим не интовое ожидаем что лист преобразует в дабл инт
  list.push_back(8.8);
  origin.push_back(8.8);

  EXPECT_EQ(origin.empty(), false);
  EXPECT_EQ(list.empty(), false);
  EXPECT_EQ(origin.size(), 2);
  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(origin.back(), 8);
  EXPECT_EQ(list.back(), 8);

  list.pop_back();
  origin.pop_back();

  EXPECT_EQ(origin.empty(), false);
  EXPECT_EQ(list.empty(), false);
  EXPECT_EQ(origin.size(), 1);
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(origin.back(), 2);
  EXPECT_EQ(list.back(), 2);
}

TEST(mediumTests, listPushPopBackTest_String) {
  std::list<std::string> origin;
  s21::list<std::string> list;
  std::string str = "HELLO";
  list.push_back(str);
  origin.push_back(str);

  EXPECT_EQ(origin.empty(), false);
  EXPECT_EQ(list.empty(), false);
  EXPECT_EQ(origin.size(), 1);
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(origin.back(), "HELLO");
  EXPECT_EQ(list.back(), "HELLO");

  list.pop_back();
  origin.pop_back();

  EXPECT_EQ(origin.empty(), true);
  EXPECT_EQ(list.empty(), true);
  EXPECT_EQ(origin.size(), 0);
  EXPECT_EQ(list.size(), 0);
}
TEST(mediumTests, listPushPopBackTest_String2) {
  std::list<std::string> origin;
  s21::list<std::string> list;
  origin.push_back("HELLO");
  origin.push_back("HELLO");
  list.push_back("WORLD");
  list.push_back("HELLO");
  origin.pop_back();
  list.pop_back();
  EXPECT_EQ(origin.empty(), false);
  EXPECT_EQ(list.empty(), false);
}

TEST(simpleTests, listPushPopBackTest3) {
  std::list<bool> origin;
  s21::list<bool> list;
  bool b = 0;
  list.push_back(b);
  origin.push_back(b);
  EXPECT_EQ(origin.empty(), false);
  EXPECT_EQ(list.empty(), false);
  EXPECT_EQ(origin.size(), 1);
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(origin.back(), false);
  EXPECT_EQ(list.back(), false);
}

TEST(hardTest, listPushPopBackTest_Big) {
  std::list<int> origin;
  s21::list<int> list;
  int count = 1300;
  while (count > 0) {
    count--;
    origin.push_back(count);
    list.push_back(count);
  }
  EXPECT_EQ(origin.size(), list.size());
  count = list.size();
  while (count > 0) {
    count--;
    origin.pop_back();
    list.pop_back();
    EXPECT_EQ(origin.size(), list.size());
  }
  EXPECT_EQ(origin.size(), list.size());
}

/*4 извлечение из начала списка */
TEST(simpleTests, listPopFrontTest0) {
  std::list<bool> origin;
  s21::list<bool> list;
  bool b = 0;
  list.push_back(b);
  origin.push_back(b);
  EXPECT_EQ(origin.empty(), false);
  EXPECT_EQ(list.empty(), false);
  EXPECT_EQ(origin.size(), 1);
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(origin.back(), false);
  EXPECT_EQ(list.back(), false);

  origin.pop_front();
  list.pop_front();
}

TEST(simpleTests, listPopFrontTest1) {
  std::list<int> origin(5);
  s21::list<int> list(5);

  int c = 5;
  while (c > 0) {
    c--;
    origin.pop_front();
    list.pop_front();
  }

  EXPECT_EQ(origin.empty(), true);
  EXPECT_EQ(list.empty(), true);
  EXPECT_EQ(origin.size(), 0);
  EXPECT_EQ(list.size(), 0);
}

TEST(simpleTests, listPopFrontTest2) {
  std::list<std::string> origin{"first", "string", "Second"};
  s21::list<std::string> list{"string", "size", "equal"};

  int c = 3;
  while (c > 0) {
    c--;
    origin.pop_front();
    list.pop_front();
  }

  EXPECT_EQ(origin.empty(), true);
  EXPECT_EQ(list.empty(), true);
  EXPECT_EQ(origin.size(), 0);
  EXPECT_EQ(list.size(), 0);
}

TEST(mediumTest, listPopFrontTest0) {
  std::list<int> origin = {9, 2, 4, 6, 2};
  s21::list<int> list = {9, 2, 4, 6, 2};

  EXPECT_EQ(origin.empty(), false);
  EXPECT_EQ(list.empty(), false);
  EXPECT_EQ(origin.size(), 5);
  EXPECT_EQ(list.size(), 5);

  origin.pop_front();
  list.pop_front();

  EXPECT_EQ(origin.front(), 2);
  EXPECT_EQ(list.front(), 2);

  origin.pop_front();
  list.pop_front();

  EXPECT_EQ(origin.front(), 4);
  EXPECT_EQ(origin.front(), 4);
}

/*5 //оперетор обмена swap(list &other) */

TEST(simpleTest, swapTest) {
  /*проверяем обмен пустых list
  ожидаемы результат : адреса такие же как и до обмена*/
  std::list<int> origin;
  s21::list<int> list;
  std::list<int> originCP;
  s21::list<int> listCP;

  const void *porigin = &origin;
  const void *plist = &list;
  const void *poriginCP = &originCP;
  const void *plistCP = &listCP;

  originCP.swap(origin);
  listCP.swap(list);

  EXPECT_EQ(&origin, porigin);
  EXPECT_EQ(&originCP, poriginCP);
  EXPECT_EQ(&list, plist);
  EXPECT_EQ(&listCP, plistCP);
}

TEST(mediumTest, swapTest) {
  /*проверяем обмен пустого list с не пустым
  вх.данные : list источник не пуст list приемник пуст
  ожидаемый результат : после обмена list который был не пустым  стал пустым
  данные из не пустого list перешли в пустой list
  последний и первый элементы list приемника равны оригиналу*/
  std::list<int> origin({1, 2, 3, 4, 5, 6, 7});
  s21::list<int> list({1, 2, 3, 4, 5, 6, 7});
  std::list<int> originCP;
  s21::list<int> listCP;

  originCP.swap(origin);
  listCP.swap(list);

  EXPECT_EQ(origin.size(), 0);
  EXPECT_EQ(originCP.size(), 7);
  EXPECT_EQ(list.size(), 0);
  EXPECT_EQ(listCP.size(), 7);

  EXPECT_EQ(origin.empty(), true);
  EXPECT_EQ(originCP.empty(), false);
  EXPECT_EQ(list.empty(), true);
  EXPECT_EQ(listCP.empty(), false);

  EXPECT_EQ(originCP.back(), 7);
  EXPECT_EQ(listCP.back(), 7);

  EXPECT_EQ(originCP.front(), 1);
  EXPECT_EQ(listCP.front(), 1);
}

TEST(mediumTest, swapTest2) {
  /*проверяем обмен не пустого list с пустым
    вх.данные : list источник пуст list приемник не пуст
  ожидаемый результат : после обмена list который был не пустым  стал пустым
  данные из не пустого list перешли в пустой list
  последний и первый элементы list источника равны  list приемника*/
  std::list<int> origin;
  s21::list<int> list;
  std::list<int> originCP({1, 2, 3, 4, 5, 6, 7});
  s21::list<int> listCP({1, 2, 3, 4, 5, 6, 7});

  originCP.swap(origin);
  listCP.swap(list);

  EXPECT_EQ(origin.size(), 7);
  EXPECT_EQ(originCP.size(), 0);
  EXPECT_EQ(list.size(), 7);
  EXPECT_EQ(listCP.size(), 0);

  EXPECT_EQ(origin.empty(), false);
  EXPECT_EQ(originCP.empty(), true);
  EXPECT_EQ(list.empty(), false);
  EXPECT_EQ(listCP.empty(), true);

  EXPECT_EQ(origin.back(), 7);
  EXPECT_EQ(list.back(), 7);

  EXPECT_EQ(origin.front(), 1);
  EXPECT_EQ(list.front(), 1);
}

TEST(hardTest, swapTest1) {
  /*проверяем обмен не пустого list с не пустым
  вх.данные : list источник содержит 2 элемента  list приемник содержит 7
эелементов сигнатура проверки: после обмена list проверяем первые и последнии
элементы, проверяем их адреса*/
  std::list<int> origin({8, 9});
  s21::list<int> list({8, 9});
  std::list<int> originCP({1, 2, 3, 4, 5, 6, 7});
  s21::list<int> listCP({1, 2, 3, 4, 5, 6, 7});

  const void *poriginFront = &origin.front();
  const void *plistFront = &list.front();
  const void *poriginCPFront = &originCP.front();
  const void *plistCPFront = &listCP.front();

  originCP.swap(origin);
  listCP.swap(list);

  EXPECT_EQ(&origin.front(), poriginCPFront);
  EXPECT_EQ(&originCP.front(), poriginFront);
  EXPECT_EQ(&list.front(), plistCPFront);
  EXPECT_EQ(&listCP.front(), plistFront);

  EXPECT_EQ(origin.back(), 7);
  EXPECT_EQ(list.back(), 7);
  EXPECT_EQ(originCP.back(), 9);
  EXPECT_EQ(listCP.back(), 9);

  EXPECT_EQ(origin.front(), 1);
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(originCP.front(), 8);
  EXPECT_EQ(listCP.front(), 8);

  EXPECT_EQ(origin.size(), 7);
  EXPECT_EQ(originCP.size(), 2);
  EXPECT_EQ(list.size(), 7);
  EXPECT_EQ(listCP.size(), 2);
}

TEST(hardTest, swapTest2) {
  /*проверяем обмен не пустого list с не пустым в котором 1 элемент
вх.данные : list источник содержит 2 элемента  list приемник содержит 7
эелементов сигнатура проверки: после обмена list проверяем первые и последнии
элементы, проверяем их адреса*/
  std::list<int> origin({8, 9});
  s21::list<int> list({8, 9});
  std::list<int> originCP({1});
  s21::list<int> listCP{1};

  const void *poriginFront = &origin.front();
  const void *plistFront = &list.front();
  const void *poriginCPFront = &originCP.front();
  const void *plistCPFront = &listCP.front();

  originCP.swap(origin);
  listCP.swap(list);

  EXPECT_EQ(&origin.front(), poriginCPFront);
  EXPECT_EQ(&originCP.front(), poriginFront);
  EXPECT_EQ(&list.front(), plistCPFront);
  EXPECT_EQ(&listCP.front(), plistFront);

  EXPECT_EQ(origin.back(), 1);
  EXPECT_EQ(list.back(), 1);
  EXPECT_EQ(originCP.back(), 9);
  EXPECT_EQ(listCP.back(), 9);

  EXPECT_EQ(origin.front(), 1);
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(originCP.front(), 8);
  EXPECT_EQ(listCP.front(), 8);

  EXPECT_EQ(origin.size(), 1);
  EXPECT_EQ(originCP.size(), 2);
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(listCP.size(), 2);
}
/*push_front*/

/*6 //оперетор push_front(T data)  */

TEST(simpleTests, listPushFront_String0) {
  /*проверяем push_front с пустым list*/
  std::list<std::string> origin;
  s21::list<std::string> list;

  EXPECT_EQ(list.empty(), true);
  origin.push_front("first");
  list.push_front("first");
  EXPECT_EQ(list.empty(), false);
  EXPECT_EQ(list.size(), 1);

  EXPECT_EQ(origin.back(), "first");
  EXPECT_EQ(list.back(), "first");
  EXPECT_EQ(origin.front(), "first");
  EXPECT_EQ(list.front(), "first");

  origin.push_front("string");
  list.push_front("string");
  EXPECT_EQ(list.size(), 2);

  EXPECT_EQ(origin.back(), "first");
  EXPECT_EQ(list.back(), "first");
  EXPECT_EQ(origin.front(), "string");
  EXPECT_EQ(list.front(), "string");

  origin.push_front("Second");
  list.push_front("Second");
  EXPECT_EQ(list.size(), 3);

  EXPECT_EQ(origin.back(), "first");
  EXPECT_EQ(list.back(), "first");
  EXPECT_EQ(origin.front(), "Second");
  EXPECT_EQ(list.front(), "Second");
}

TEST(simpleTests, listPushFront_String1) {
  /*проверяем push_front с не пустым list*/
  std::list<std::string> origin{"first", "string", "Second"};
  s21::list<std::string> list{"string", "size", "equal"};

  EXPECT_EQ(list.empty(), false);
  origin.push_front("size");
  list.push_front("size");
  EXPECT_EQ(list.size(), 4);

  EXPECT_EQ(origin.front(), "size");
  EXPECT_EQ(list.front(), "size");
}

/*7 //оперетор void erase(iterator pos)  + проверка итератора*/

TEST(simpleTests, listErase1) {
  /*в непустом массиве убираем элемент 1
  проверяем размер массива до и после
  ожидаемый результат : размер уменьшился на 1 эелемен*/
  std::list<int> origin{9, 2, 4, 6, 2};
  s21::list<int> list{9, 2, 4, 6, 2};

  EXPECT_EQ(origin.size(), 5);
  EXPECT_EQ(list.size(), 5);
  std::list<int>::iterator it = origin.begin();
  s21::list<int>::iterator itl = list.begin();

  origin.erase(it);
  list.erase(itl);

  EXPECT_EQ(origin.size(), 4);
  EXPECT_EQ(list.size(), 4);

  EXPECT_EQ(origin.front(), 2);
  EXPECT_EQ(list.front(), 2);
}

TEST(simpleTests, listErase2) {
  /*в непустом массиве убираем элемент 2
  проверяем размер массива до и после
  ожидаемый результат : размер уменьшился на 1 эелемен*/
  std::list<int> origin{9, 2, 4, 6, 2};
  s21::list<int> list{9, 2, 4, 6, 2};

  EXPECT_EQ(origin.size(), 5);
  EXPECT_EQ(list.size(), 5);
  std::list<int>::iterator it = origin.begin();
  s21::list<int>::iterator itl = list.begin();
  // it++;
  itl++;

  origin.erase(++it);
  list.erase(itl);

  EXPECT_EQ(origin.size(), 4);
  EXPECT_EQ(list.size(), 4);

  EXPECT_EQ(origin.front(), 9);
  EXPECT_EQ(list.front(), 9);
}

TEST(simpleTests, listErase3) {
  /*в непустом массиве убираем элемент 1
  проверяем размер массива до и после
  ожидаемый результат : размер уменьшился на 1 эелемен*/
  std::list<bool> origin(5);
  s21::list<bool> list(5);

  EXPECT_EQ(origin.size(), 5);
  EXPECT_EQ(list.size(), 5);
  std::list<bool>::iterator it = origin.begin();
  s21::list<bool>::iterator itl = list.begin();

  origin.erase(it);
  list.erase(itl);

  EXPECT_EQ(origin.size(), 4);
  EXPECT_EQ(list.size(), 4);

  EXPECT_EQ(origin.front(), 0);
  EXPECT_EQ(list.front(), 0);
}

TEST(simpleTests, listErase4) {
  /*в непустом массиве убираем элемент пока не закончатся
  проверяем размер массива до и после
  ожидаемый результат : пустой list*/
  std::list<bool> origin(5);
  s21::list<bool> list(5);

  EXPECT_EQ(origin.size(), 5);
  EXPECT_EQ(list.size(), 5);
  std::list<bool>::iterator it = origin.begin();
  s21::list<bool>::iterator itl = list.begin();

  while (list.size() > 0) {
    it = origin.erase(it);
    itl = list.erase(itl);
  }

  EXPECT_EQ(origin.size(), 0);
  EXPECT_EQ(list.size(), 0);
}

TEST(simpleTests, listErase5) {
  /*в непустом массиве убираем элемент 1 конца
  проверяем размер массива до и после
  ожидаемый результат : размер уменьшился на 1 эелемен*/
  std::list<std::string> origin{"string", "size", "equal"};
  s21::list<std::string> list{"string", "size", "equal"};

  EXPECT_EQ(origin.size(), 3);
  EXPECT_EQ(list.size(), 3);
  std::list<std::string>::iterator it = origin.end();
  s21::list<std::string>::iterator itl = list.end();
  // it--;
  itl--;
  origin.erase(--it);
  list.erase(itl);

  EXPECT_EQ(origin.size(), 2);
  EXPECT_EQ(list.size(), 2);

  EXPECT_EQ(origin.back(), "size");
  EXPECT_EQ(list.back(), "size");
}

TEST(simpleTests, listErase6) {
  /*в непустом массиве убираем элемент с конца пока не закончатся
  проверяем размер массива до и после
  ожидаемый результат : пустой list*/
  std::list<std::string> origin{"first", "string", "Second"};
  s21::list<std::string> list{"string", "size", "equal"};

  EXPECT_EQ(origin.size(), 3);
  EXPECT_EQ(list.size(), 3);
  std::list<std::string>::iterator it = origin.end();
  s21::list<std::string>::iterator itl = list.end();
  // it--;
  itl--;
  while (list.size() > 0) {
    it = origin.erase(--it);
    itl = list.erase(itl);
    // it--;
    itl--;
  }

  EXPECT_EQ(origin.size(), 0);
  EXPECT_EQ(list.size(), 0);
}

/*8 //оперетор void sort() */
TEST(simpleTests, listSort1) {
  std::list<int> origin{9, 2, 4, 6, 2};
  s21::list<int> list{9, 2, 4, 6, 2};

  origin.sort();
  list.sort();

  EXPECT_EQ(origin.front(), 2);
  EXPECT_EQ(list.front(), 2);
  origin.pop_front();
  list.pop_front();
  EXPECT_EQ(origin.front(), 2);
  EXPECT_EQ(list.front(), 2);
  origin.pop_front();
  list.pop_front();
  EXPECT_EQ(origin.front(), 4);
  EXPECT_EQ(list.front(), 4);
  origin.pop_front();
  list.pop_front();
  EXPECT_EQ(origin.front(), 6);
  EXPECT_EQ(list.front(), 6);
  origin.pop_front();
  list.pop_front();
  EXPECT_EQ(origin.front(), 9);
  EXPECT_EQ(list.front(), 9);
}

TEST(simpleTests, listSort2) {
  std::list<std::string> origin{"first", "string", "Second"};
  s21::list<std::string> list{"first", "string", "Second"};

  origin.sort();
  list.sort();  // падает

  EXPECT_EQ(origin.front(), "Second");
  EXPECT_EQ(list.front(), "Second");

  origin.pop_front();
  list.pop_front();
  EXPECT_EQ(origin.front(), "first");
  EXPECT_EQ(list.front(), "first");

  origin.pop_front();
  list.pop_front();
  EXPECT_EQ(origin.front(), "string");
  EXPECT_EQ(list.front(), "string");
}

/*9 //оперетор void reverse()*/
TEST(simpleTests, listReverse1) {
  std::list<int> origin{9, 2, 4, 6, 2};
  s21::list<int> list{9, 2, 4, 6, 2};

  origin.reverse();
  list.reverse();

  EXPECT_EQ(origin.front(), 2);
  EXPECT_EQ(list.front(), 2);
  origin.pop_front();
  list.pop_front();
  EXPECT_EQ(origin.front(), 6);
  EXPECT_EQ(list.front(), 6);
  origin.pop_front();
  list.pop_front();
  EXPECT_EQ(origin.front(), 4);
  EXPECT_EQ(list.front(), 4);
  origin.pop_front();
  list.pop_front();
  EXPECT_EQ(origin.front(), 2);
  EXPECT_EQ(list.front(), 2);
  origin.pop_front();
  list.pop_front();
  EXPECT_EQ(origin.front(), 9);
  EXPECT_EQ(list.front(), 9);
}

TEST(simpleTests, listReverse2) {
  std::list<std::string> origin{"first", "string", "Second"};
  s21::list<std::string> list{"first", "string", "Second"};

  origin.reverse();
  list.reverse();

  EXPECT_EQ(origin.front(), "Second");
  EXPECT_EQ(list.front(), "Second");

  origin.pop_front();
  list.pop_front();

  EXPECT_EQ(origin.front(), "string");
  EXPECT_EQ(list.front(), "string");

  origin.pop_front();
  list.pop_front();

  EXPECT_EQ(origin.front(), "first");
  EXPECT_EQ(list.front(), "first");
}

TEST(simpleTests, listReverse3) {
  std::list<int> origin{9};
  s21::list<int> list{9};
  ;

  origin.reverse();
  list.reverse();

  EXPECT_EQ(origin.front(), 9);
  EXPECT_EQ(list.front(), 9);
}

TEST(simpleTests, listReverse4) {
  std::list<int> origin;
  s21::list<int> list;
  ;

  origin.reverse();
  list.reverse();
}

/*10 //оперетор  void list<T>::unique()*/
TEST(simpleTest, listUnique) {
  std::list<bool> origin{true, false, true,  true, true, 0, 1,
                         1,    true,  false, 0,    0,    0};
  s21::list<bool> list{true, false, true,  true, true, 0, 1,
                       1,    true,  false, 0,    0,    0};

  EXPECT_EQ(origin.size(), 13);
  EXPECT_EQ(list.size(), 13);

  origin.unique();
  list.unique();

  EXPECT_EQ(origin.empty(), false);
  EXPECT_EQ(list.empty(), false);

  EXPECT_EQ(origin.size(), 6);
  EXPECT_EQ(list.size(), 6);  // тут посчитал 5 вмето 6
}

/*11 //void list<T>::merge(list& other)*/
/*объеденение пустых list*/
TEST(simpleTests, listMerge0) {
  std::list<int> l1;
  std::list<int> l2;
  s21::list<int> s21_l1;
  s21::list<int> s21_l2;
  l1.merge(l2);
  s21_l1.merge(s21_l2);
  EXPECT_EQ(l1.empty(), s21_l1.empty());
  EXPECT_EQ(l2.empty(), s21_l2.empty());
}
/*объеденение не пустых list*/
TEST(simpleTests, listMerge1) {
  std::list<int> l1(5);
  std::list<int> l2(5);
  s21::list<int> s21_l1(5);
  s21::list<int> s21_l2(5);
  l1.merge(l2);
  s21_l1.merge(s21_l2);

  EXPECT_EQ(l1.empty(), s21_l1.empty());
  EXPECT_EQ(l2.empty(), s21_l2.empty());
  EXPECT_EQ(l1.size(), s21_l1.size());
  EXPECT_EQ(l2.size(), s21_l2.size());
}
/*объеденение list в которых по одному элементу*/
TEST(simpleTests, listMerge2) {
  std::list<int> l1{9};
  std::list<int> l2{9};
  s21::list<int> s21_l1{3};
  s21::list<int> s21_l2{3};
  l1.merge(l2);
  s21_l1.merge(s21_l2);
  EXPECT_EQ(l1.size(), s21_l1.size());
}
/*объеденение list в которых разное количество элементов*/
TEST(simpleTests, listMerge3) {
  std::list<int> l1{9, 2, 4, 6, 2};
  std::list<int> l2{9, 2, 4, 6, 2};
  s21::list<int> s21_l1{9, 2, 4, 6, 2};
  s21::list<int> s21_l2{9, 2, 4, 6, 2};
  l1.merge(l2);
  s21_l1.merge(s21_l2);

  EXPECT_EQ(l1.size(), s21_l1.size());
  EXPECT_EQ(l2.size(), s21_l2.size());
}
/*объеденение list в которых разное количество элементов
проверяем работу объеденения через последовательное сравнение элементов
раобы оригинального листа и написанного по заданию */
TEST(simpleTests, listMerge4) {
  std::list<int> l1{9};
  std::list<int> l2{9};
  s21::list<int> s21_l1{9};  // стояли 3 исправил на 9
  s21::list<int> s21_l2{9};  // стояли 3 исправил на 9

  l1.merge(l2);
  s21_l1.merge(s21_l2);

  std::list<int>::iterator it = l1.begin();
  s21::list<int>::iterator s21_it = s21_l1.begin();

  while ((s21_l1.size() > 0) && (l1.size() > 0)) {
    EXPECT_EQ(l1.front(), s21_l1.front());
    it = l1.erase(it);
    s21_it = s21_l1.erase(s21_it);
  }
}
TEST(simpleTests, listMerge5) {
  std::list<int> l1{9, 2, 4, 6, 2};
  std::list<int> l2{9, 2, 4, 6, 2};
  s21::list<int> s21_l1{9, 2, 4, 6, 2};
  s21::list<int> s21_l2{9, 2, 4, 6, 2};

  l1.merge(l2);
  s21_l1.merge(s21_l2);

  std::list<int>::iterator it = l1.begin();
  s21::list<int>::iterator s21_it = s21_l1.begin();

  while ((s21_l1.size() > 0) && (l1.size() > 0)) {
    EXPECT_EQ(l1.front(), s21_l1.front());
    it = l1.erase(it);
    s21_it = s21_l1.erase(s21_it);
  }
}

/*12 //insert(iterator pos, const_reference value)*/
/*вставка в начало пустого списка*/
TEST(simpleTests, listInsert0) {
  std::list<int> l1;
  s21::list<int> s21_l1;

  std::list<int>::iterator it = l1.begin();
  s21::list<int>::iterator s21_it = s21_l1.begin();
  EXPECT_EQ(l1.empty(), s21_l1.empty());
  int a = 2;
  l1.insert(it, a);
  s21_l1.insert(s21_it, a);
  EXPECT_EQ(l1.empty(), s21_l1.empty());
}
/*вставка в начало не пустого списка*/
TEST(simpleTests, listInsert1) {
  std::list<int> l1(5);
  s21::list<int> s21_l1(5);

  std::list<int>::iterator it = l1.begin();
  s21::list<int>::iterator s21_it = s21_l1.begin();
  int a = 2;
  l1.insert(it, a);
  s21_l1.insert(s21_it, a);
  EXPECT_EQ(l1.front(), s21_l1.front());
}
/*вставка в начало не пустого списка*/
TEST(simpleTests, listInsert2) {
  std::list<int> l1{9, 2, 4, 6, 2};
  s21::list<int> s21_l1{9, 2, 4, 6, 2};

  std::list<int>::iterator it = l1.begin();
  s21::list<int>::iterator s21_it = s21_l1.begin();
  int a = 2;
  l1.insert(it, a);
  s21_l1.insert(s21_it, a);
  EXPECT_EQ(l1.front(), s21_l1.front());
  EXPECT_EQ(l1.size(), s21_l1.size());
}
/*вставка в конец не пустого списка*/
TEST(simpleTests, listInsert3) {
  std::list<int> l1{9, 2, 4, 6, 2};
  s21::list<int> s21_l1{9, 2, 4, 6, 2};

  std::list<int>::iterator it = l1.end();
  s21::list<int>::iterator s21_it = s21_l1.end();
  int a = 2;
  l1.insert(it, a);
  s21_l1.insert(s21_it, a);
  EXPECT_EQ(l1.front(), s21_l1.front());
  EXPECT_EQ(l1.size(), s21_l1.size());
}
/*вставка в середину не пустого списка
проверяем последовательно равенство элементов*/
TEST(simpleTests, listInsert4) {
  std::list<int> l1{9, 2, 4, 6, 2};
  s21::list<int> s21_l1{9, 2, 4, 6, 2};

  std::list<int>::iterator it = l1.begin();
  s21::list<int>::iterator s21_it = s21_l1.begin();
  int cnt = 0;
  while (cnt < 2) {
    ++it;
    ++s21_it;
    cnt++;
  }
  int a = 2;
  l1.insert(it, a);
  s21_l1.insert(s21_it, a);
  EXPECT_EQ(l1.front(), s21_l1.front());
  EXPECT_EQ(l1.size(), s21_l1.size());

  it = l1.begin();
  s21_it = s21_l1.begin();

  while ((s21_l1.size() > 0) && (l1.size() > 0)) {
    EXPECT_EQ(l1.front(), s21_l1.front());
    it = l1.erase(it);
    s21_it = s21_l1.erase(s21_it);
  }
}

/*13 //void splice(const_iterator pos, list& other)*/
TEST(simpleTests, listSplice0) {
  std::list<int> l1;
  std::list<int> l2;
  s21::list<int> s21_l1;
  s21::list<int> s21_l2;
  l1.splice(l1.begin(), l2);
  s21_l1.splice(s21_l1.begin(), s21_l2);  // падает в ошибку
  EXPECT_EQ(l1.empty(), s21_l1.empty());
  EXPECT_EQ(l2.empty(), s21_l2.empty());
}
TEST(simpleTests, listSplice1) {
  std::list<int> l1(5);
  std::list<int> l2(5);
  s21::list<int> s21_l1(5);
  s21::list<int> s21_l2(5);

  std::list<int>::iterator it = l1.begin();
  s21::list<int>::iterator s21_it = s21_l1.begin();

  l1.splice(it, l2);
  s21_l1.splice(s21_it, s21_l2);

  EXPECT_EQ(l1.empty(), s21_l1.empty());
  EXPECT_EQ(l2.empty(), s21_l2.empty());
  EXPECT_EQ(l1.size(), s21_l1.size());
  EXPECT_EQ(l2.size(), s21_l2.size());
}
TEST(simpleTests, listSplice2) {
  std::list<int> l1{9};
  std::list<int> l2{9};
  s21::list<int> s21_l1{3};
  s21::list<int> s21_l2{3};

  std::list<int>::iterator it = l1.begin();
  s21::list<int>::iterator s21_it = s21_l1.begin();

  l1.splice(it, l2);
  s21_l1.splice(s21_it, s21_l2);

  EXPECT_EQ(l1.size(), s21_l1.size());
}
TEST(simpleTests, listSplice3) {
  std::list<int> l1{9, 2, 4, 6, 2};
  std::list<int> l2{9, 2, 4, 6, 2};
  s21::list<int> s21_l1{9, 2, 4, 6, 2};
  s21::list<int> s21_l2{9, 2, 4, 6, 2};
  std::list<int>::iterator it = l1.begin();
  s21::list<int>::iterator s21_it = s21_l1.begin();

  l1.splice(it, l2);
  s21_l1.splice(s21_it, s21_l2);

  EXPECT_EQ(l1.size(), s21_l1.size());
  EXPECT_EQ(l2.size(), s21_l2.size());
}
TEST(simpleTests, listSplice4) {
  std::list<int> l1{9};
  std::list<int> l2{9};
  s21::list<int> s21_l1{9};
  s21::list<int> s21_l2{9};

  std::list<int>::iterator it = l1.begin();
  s21::list<int>::iterator s21_it = s21_l1.begin();

  l1.splice(it, l2);
  s21_l1.splice(s21_it, s21_l2);

  it = l1.begin();
  s21_it = s21_l1.begin();

  while ((s21_l1.size() > 0) && (l1.size() > 0)) {
    EXPECT_EQ(l1.front(), s21_l1.front());
    it = l1.erase(it);
    s21_it = s21_l1.erase(s21_it);
  }
}
TEST(simpleTests, listSplice5) {
  std::list<int> l1{9, 2, 4, 6, 2};
  std::list<int> l2{9, 2, 4, 6, 2};
  s21::list<int> s21_l1{9, 2, 4, 6, 2};
  s21::list<int> s21_l2{9, 2, 4, 6, 2};

  std::list<int>::iterator it = l1.begin();
  s21::list<int>::iterator s21_it = s21_l1.begin();

  l1.splice(it, l2);
  s21_l1.splice(s21_it, s21_l2);

  it = l1.begin();
  s21_it = s21_l1.begin();

  while ((s21_l1.size() > 0) && (l1.size() > 0)) {
    EXPECT_EQ(l1.front(), s21_l1.front());
    it = l1.erase(it);
    s21_it = s21_l1.erase(s21_it);
  }
}

/* не получилось внести структуру и в оригинальый лист */
TEST(simpleTests, listPushPopBackTest_Struct) {
  struct Point {
    int x = 0;
    int y = 0;
  };
  std::list<Point> origin;
  s21::list<Point> list;
  EXPECT_EQ(origin.size(), 0);
  EXPECT_EQ(list.size(), 0);

  Point p;
  p.x = 4;
  p.y = 8;

  list.push_back(p);
  origin.push_back(p);

  EXPECT_EQ(origin.empty(), false);
  EXPECT_EQ(list.empty(), false);
  EXPECT_EQ(origin.size(), 1);
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(origin.back().x, 4);
  EXPECT_EQ(list.back().x, 4);
}

/* в лист не кладется адрес пfдает на этапе инициализации */
TEST(mediumTests, listPushTest_Addres) {
  std::list<int *> origin;
  s21::list<int *> list;

  int a = 2;
  int *p = &a;

  list.push_back(p);
  origin.push_back(p);

  EXPECT_EQ(origin.back(), &a);
  EXPECT_EQ(list.back(), &a);
}

// Part_3
// вставка в пустой список
TEST(InsertMany, EmptyList) {
  s21::list<int> list;
  list.insert_many_back(1, 2, 3);

  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 3);

  auto it = list.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 3);
}

// вставка в начало непустого списка
TEST(InsertMany, FrontNonEmptyList) {
  s21::list<int> list = {4, 5, 6};
  list.insert_many_front(1, 2, 3);

  EXPECT_EQ(list.size(), 6);
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 6);

  auto it = list.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 3);
  EXPECT_EQ(*it++, 4);
  EXPECT_EQ(*it++, 5);
  EXPECT_EQ(*it++, 6);
}

// вставка в конец непустого списка
TEST(InsertMany, BackNonEmptyList) {
  s21::list<int> list = {1, 2, 3};
  list.insert_many_back(4, 5, 6);

  EXPECT_EQ(list.size(), 6);
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 6);

  auto it = list.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 3);
  EXPECT_EQ(*it++, 4);
  EXPECT_EQ(*it++, 5);
  EXPECT_EQ(*it++, 6);
}

// вставка в произвольную позицию
TEST(InsertMany, MiddlePosition) {
  s21::list<int> list = {1, 4, 5};
  auto it = list.begin();
  ++it;
  list.insert_many(it, 2, 3);

  EXPECT_EQ(list.size(), 5);
  auto check_it = list.begin();
  EXPECT_EQ(*check_it++, 1);
  EXPECT_EQ(*check_it++, 2);
  EXPECT_EQ(*check_it++, 3);
  EXPECT_EQ(*check_it++, 4);
  EXPECT_EQ(*check_it++, 5);
}

// работа с разными типами данных
TEST(InsertMany, TypeHandling) {
  s21::list<std::string> list;
  list.insert_many_back("Hello", "World");

  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list.front(), "Hello");
  EXPECT_EQ(list.back(), "World");
}

// множественные операции вставки
TEST(InsertMany, MultipleOperations) {
  s21::list<int> list;
  list.insert_many_back(1, 2);
  list.insert_many_front(3, 4);
  list.insert_many(list.begin(), 5, 6);

  EXPECT_EQ(list.size(), 6);
  EXPECT_EQ(list.front(), 5);
  EXPECT_EQ(list.back(), 2);
}

#endif
