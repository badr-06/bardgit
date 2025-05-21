#ifndef S21_TEST_STACK_STL_CPP
#define S21_TEST_STACK_STL_CPP

#include <gtest/gtest.h>

#include <stack>

#include "s21_stack.h"

using namespace s21;

using namespace std;

/*1 default constructor
тут тестируются функции size()*/

TEST(simpleStackTests, defaultConstructor) {
  std::stack<double> origin;
  s21::stack<double> stack;

  EXPECT_EQ(origin.size(), stack.size());

  std::stack<int> origin1;
  s21::stack<int> stack1;

  EXPECT_EQ(origin1.size(), stack1.size());

  std::stack<std::string> origin2;
  s21::stack<std::string> stack2;

  EXPECT_EQ(origin2.size(), stack2.size());

  std::stack<bool> origin3;
  s21::stack<bool> stack3;

  EXPECT_EQ(origin3.size(), stack3.size());

  struct Point {
    int x = 0;
    int y = 0;
  };
  std::stack<Point> origin4;
  s21::stack<Point> stack4;

  EXPECT_EQ(origin4.size(), stack4.size());

  std::stack<int *> origin5;
  s21::stack<int *> stack5;

  EXPECT_EQ(origin5.size(), stack5.size());
}

/*2 initializer constructor
тут тестируются функции size()*/

TEST(simpleStackTests, initializerConstructor) {
  std::stack<double> origin({1.9, 2.547, 379, -4.1});
  s21::stack<double> stack({1.9, 2.547, 379, -4.1});

  EXPECT_EQ(origin.size(), stack.size());

  std::stack<int> origin1({8, 8, 7, 9, 8, 7, 2, 7, 4, 1});
  s21::stack<int> stack1({8, 8, 7, 9, 8, 7, 2, 7, 4, 1});

  EXPECT_EQ(origin1.size(), stack1.size());

  std::stack<std::string> origin2({"qwe", "xcv", "asd", "tyu"});
  s21::stack<std::string> stack2({"qwe", "xcv", "asd", "tyu"});

  EXPECT_EQ(origin2.size(), stack2.size());

  std::stack<bool> origin3({true, 1, false, 0});
  s21::stack<bool> stack3({true, 1, false, 0});

  EXPECT_EQ(origin3.size(), stack3.size());

  struct Point {
    int x = 0;
    int y = 0;
  };
  std::stack<Point> origin4({{1, 4}, {5, 2}, {7, 9}});
  s21::stack<Point> stack4({{1, 4}, {5, 2}, {7, 9}});

  EXPECT_EQ(origin4.size(), stack4.size());
}

/*3 push()
тут тестируются функции push() & size()*/
TEST(simpleStackTests, pushTest0) {
  /*в пустой стек кладем */

  std::stack<double> origin;
  s21::stack<double> stack;
  origin.push(5.5);
  stack.push(5.5);
  EXPECT_EQ(origin.size(), stack.size());

  std::stack<int> origin1;
  s21::stack<int> stack1;
  origin1.push(5.5);
  stack1.push(5.5);
  EXPECT_EQ(origin1.size(), stack1.size());

  std::stack<std::string> origin2;
  s21::stack<std::string> stack2;
  origin2.push("5.5");
  stack2.push("5.5");
  EXPECT_EQ(origin2.size(), stack2.size());

  std::stack<bool> origin3;
  s21::stack<bool> stack3;
  origin3.push(true);
  stack3.push(true);
  EXPECT_EQ(origin3.size(), stack3.size());

  struct Point {
    int x = 0;
    int y = 0;
  };

  std::stack<Point> origin4;
  s21::stack<Point> stack4;

  origin4.push({2, 4});
  stack4.push({2, 4});

  EXPECT_EQ(origin4.size(), stack4.size());

  std::stack<int *> origin5;
  s21::stack<int *> stack5;

  int b;
  origin5.push(&b);
  stack5.push(&b);

  EXPECT_EQ(origin5.size(), stack5.size());
}

TEST(simpleStackTests, pushTest1) {
  /*в не пустой стек кладем значения */
  std::stack<double> origin({1.9, 2.547, 379, -4.1});
  s21::stack<double> stack({1.9, 2.547, 379, -4.1});
  origin.push(5.5);
  stack.push(5.5);

  EXPECT_EQ(origin.size(), stack.size());

  std::stack<int> origin1({8, 8, 7, 9, 8, 7, 2, 7, 4, 1});
  s21::stack<int> stack1({8, 8, 7, 9, 8, 7, 2, 7, 4, 1});
  origin1.push(5.5);
  stack1.push(5.5);

  EXPECT_EQ(origin1.size(), stack1.size());

  std::stack<std::string> origin2({"qwe", "xcv", "asd", "tyu"});
  s21::stack<std::string> stack2({"qwe", "xcv", "asd", "tyu"});
  origin2.push("5.5");
  stack2.push("5.5");
  EXPECT_EQ(origin2.size(), stack2.size());

  std::stack<bool> origin3({true, 1, false, 0});
  s21::stack<bool> stack3({true, 1, false, 0});
  origin3.push(true);
  stack3.push(true);
  EXPECT_EQ(origin3.size(), stack3.size());

  struct Point {
    int x = 0;
    int y = 0;
  };
  std::stack<Point> origin4({{1, 4}, {5, 2}, {7, 9}});
  s21::stack<Point> stack4({{1, 4}, {5, 2}, {7, 9}});
  Point p;
  p.x = 4;
  p.y = 8;
  origin4.push(p);
  stack4.push(p);

  EXPECT_EQ(origin4.size(), stack4.size());
}

TEST(simpleStackTests, pushTest2) {
  std::stack<double> origin;
  s21::stack<double> stack;
  double d = 4.89;
  origin.push(d);
  stack.push(d);
  EXPECT_EQ(origin.size(), stack.size());

  std::stack<int> origin1;
  s21::stack<int> stack1;
  origin1.push(d);
  stack1.push(d);
  EXPECT_EQ(origin1.size(), stack1.size());

  std::stack<std::string> origin2;
  s21::stack<std::string> stack2;
  std::string str = "HELLO";
  origin2.push(str);
  stack2.push(str);
  EXPECT_EQ(origin2.size(), stack2.size());

  std::stack<bool> origin3;
  s21::stack<bool> stack3;
  bool b = false;
  origin3.push(b);
  stack3.push(b);
  EXPECT_EQ(origin3.size(), stack3.size());

  struct Point {
    int x = 0;
    int y = 0;
  };
  Point p;
  p.x = 4;
  p.y = 8;

  std::stack<Point> origin4;
  s21::stack<Point> stack4;
  origin4.push(p);
  stack4.push(p);

  EXPECT_EQ(origin4.size(), stack4.size());

  std::stack<int *> origin5;
  s21::stack<int *> stack5;

  int c;
  int *a = &c;
  origin5.push(a);
  stack5.push(a);

  EXPECT_EQ(origin5.size(), stack5.size());
}
TEST(mediumStackTests, pushTest1) {
  struct Point {
    int x = 0;
    int y = 0;
  };
  std::stack<Point> origin;
  s21::stack<Point> stack1;
  Point p;
  p.x = 6;
  p.y = 3;
  stack1.push(p);
  origin.push(p);
  EXPECT_EQ(origin.top().x, stack1.top().x);
  EXPECT_EQ(origin.top().y, stack1.top().y);
  EXPECT_NE(&origin.top(), &p);
  EXPECT_NE(&stack1.top(), &p);
  EXPECT_NE(&stack1.top(), &origin.top());

  // printf("address top element stack : %p & %p &%p" <<  &origin.top() <<
  // &stack1.top() << &p; p.x = 7; cout << "stack : %d & %d &%d" <<
  // origin.top().x <<  stack1.top().x, p.x; completedTO DO  разобраться :
  // оригинал делает копию структуры, моя версия пихает адрес структуры
}
/*4 pop()
тут тестируются функции pop() & size()*/
TEST(simpleStackTests, PopTest1) {
  std::stack<double> origin({1.9, 2.547, 379, -4.1});
  s21::stack<double> stack({1.9, 2.547, 379, -4.1});
  origin.pop();
  stack.pop();

  EXPECT_EQ(origin.size(), stack.size());

  std::stack<int> origin1({8, 8, 7, 9, 8, 7, 2, 7, 4, 1});
  s21::stack<int> stack1({8, 8, 7, 9, 8, 7, 2, 7, 4, 1});
  origin1.pop();
  stack1.pop();

  EXPECT_EQ(origin1.size(), stack1.size());

  std::stack<std::string> origin2({"qwe", "xcv", "asd", "tyu"});
  s21::stack<std::string> stack2({"qwe", "xcv", "asd", "tyu"});
  origin2.pop();
  stack2.pop();
  EXPECT_EQ(origin2.size(), stack2.size());

  std::stack<bool> origin3({true, 1, false, 0});
  s21::stack<bool> stack3({true, 1, false, 0});
  origin3.pop();
  stack3.pop();
  EXPECT_EQ(origin3.size(), stack3.size());

  struct Point {
    int x = 0;
    int y = 0;
  };
  std::stack<Point> origin4({{1, 4}, {5, 2}, {7, 9}});
  s21::stack<Point> stack4({{1, 4}, {5, 2}, {7, 9}});
  Point p;
  p.x = 4;
  p.y = 8;
  origin4.pop();
  stack4.pop();

  EXPECT_EQ(origin4.size(), stack4.size());
}

/*5 top()
тут тестируются функции top() & pop() & size()*/
TEST(simpleStackTests, topPopTest1) {
  std::stack<double> origin({1.9, 2.547, 379, -4.1});
  s21::stack<double> stack({1.9, 2.547, 379, -4.1});
  EXPECT_EQ(origin.top(), stack.top());
  origin.pop();
  stack.pop();
  EXPECT_EQ(origin.top(), stack.top());
  EXPECT_EQ(origin.size(), stack.size());
  origin.pop();
  stack.pop();
  EXPECT_EQ(origin.top(), stack.top());
  EXPECT_EQ(origin.size(), stack.size());

  std::stack<int> origin1({8, 8, 7, 9, 8, 7, 2, 7, 4, 1});
  s21::stack<int> stack1({8, 8, 7, 9, 8, 7, 2, 7, 4, 1});
  EXPECT_EQ(origin1.top(), stack1.top());
  origin1.pop();
  stack1.pop();
  EXPECT_EQ(origin1.top(), stack1.top());
  EXPECT_EQ(origin1.size(), stack1.size());
  origin1.pop();
  stack1.pop();
  EXPECT_EQ(origin1.top(), stack1.top());
  EXPECT_EQ(origin1.size(), stack1.size());

  std::stack<std::string> origin2({"qwe", "xcv", "asd", "tyu"});
  s21::stack<std::string> stack2({"qwe", "xcv", "asd", "tyu"});
  EXPECT_EQ(origin2.top(), stack2.top());
  origin2.pop();
  stack2.pop();
  EXPECT_EQ(origin2.top(), stack2.top());
  EXPECT_EQ(origin2.size(), stack2.size());
  origin2.pop();
  stack2.pop();
  EXPECT_EQ(origin2.top(), stack2.top());
  EXPECT_EQ(origin2.size(), stack2.size());

  std::stack<bool> origin3({true, 1, false, 0});
  s21::stack<bool> stack3({true, 1, false, 0});
  EXPECT_EQ(origin3.top(), stack3.top());
  origin3.pop();
  stack3.pop();
  EXPECT_EQ(origin3.top(), stack3.top());
  EXPECT_EQ(origin3.size(), stack3.size());
  origin3.pop();
  stack3.pop();
  EXPECT_EQ(origin3.top(), stack3.top());
  EXPECT_EQ(origin3.size(), stack3.size());

  struct Point {
    int x = 0;
    int y = 0;
  };
  std::stack<Point> origin4({{1, 4}, {5, 2}, {7, 9}});
  s21::stack<Point> stack4({{1, 4}, {5, 2}, {7, 9}});
  Point p1 = origin4.top();
  Point p2 = stack4.top();

  EXPECT_EQ(p1.x, p2.x);
  EXPECT_EQ(p1.y, p2.y);
  origin4.pop();
  stack4.pop();
  p1 = origin4.top();
  p2 = stack4.top();

  EXPECT_EQ(p1.x, p2.x);
  EXPECT_EQ(p1.y, p2.y);

  EXPECT_EQ(origin4.size(), stack4.size());
  origin4.pop();
  stack4.pop();
  p1 = origin4.top();
  p2 = stack4.top();

  EXPECT_EQ(p1.x, p2.x);
  EXPECT_EQ(p1.y, p2.y);

  EXPECT_EQ(origin4.size(), stack4.size());
}

TEST(simpleStackTests, topPopTest2) {
  std::stack<std::string> origin({"first", "string", "Second"});
  s21::stack<std::string> stack({"first", "string", "Second"});
  EXPECT_EQ(origin.size(), stack.size());
  while (origin.size() > 0) {
    EXPECT_EQ(origin.size(), stack.size());
    EXPECT_EQ(origin.top(), stack.top());
    origin.pop();
    stack.pop();
  }
}
/*6 empty()
тут тестируются функции empty()*/
TEST(simpleStackTests, emptyTest1) {
  std::stack<double> origin;
  s21::stack<double> stack;

  EXPECT_EQ(origin.empty(), stack.empty());

  std::stack<int> origin1;
  s21::stack<int> stack1;

  EXPECT_EQ(origin1.empty(), stack1.empty());

  std::stack<std::string> origin2;
  s21::stack<std::string> stack2;

  EXPECT_EQ(origin2.empty(), stack2.empty());

  std::stack<bool> origin3;
  s21::stack<bool> stack3;

  EXPECT_EQ(origin3.empty(), stack3.empty());

  struct Point {
    int x = 0;
    int y = 0;
  };
  std::stack<Point> origin4;
  s21::stack<Point> stack4;

  EXPECT_EQ(origin4.empty(), stack4.empty());

  std::stack<int *> origin5;
  s21::stack<int *> stack5;

  EXPECT_EQ(origin5.empty(), stack5.empty());
}
TEST(simpleStackTests, emptyTest2) {
  std::stack<double> origin({1.9, 2.547, 379, -4.1});
  s21::stack<double> stack({1.9, 2.547, 379, -4.1});

  EXPECT_EQ(origin.empty(), stack.empty());

  std::stack<int> origin1({8, 8, 7, 9, 8, 7, 2, 7, 4, 1});
  s21::stack<int> stack1({8, 8, 7, 9, 8, 7, 2, 7, 4, 1});

  EXPECT_EQ(origin1.empty(), stack1.empty());

  std::stack<std::string> origin2({"qwe", "xcv", "asd", "tyu"});
  s21::stack<std::string> stack2({"qwe", "xcv", "asd", "tyu"});

  EXPECT_EQ(origin2.empty(), stack2.empty());

  std::stack<bool> origin3({true, 1, false, 0});
  s21::stack<bool> stack3({true, 1, false, 0});

  EXPECT_EQ(origin3.empty(), stack3.empty());

  struct Point {
    int x = 0;
    int y = 0;
  };
  std::stack<Point> origin4({{1, 4}, {5, 2}, {7, 9}});
  s21::stack<Point> stack4({{1, 4}, {5, 2}, {7, 9}});

  EXPECT_EQ(origin4.empty(), stack4.empty());
}
TEST(simpleStackTests, emptyPopTest3) {
  std::stack<double> origin({1.9});
  s21::stack<double> stack({1.9});
  origin.pop();
  stack.pop();
  EXPECT_EQ(origin.empty(), stack.empty());

  std::stack<int> origin1({8});
  s21::stack<int> stack1({8});
  origin1.pop();
  stack1.pop();
  EXPECT_EQ(origin1.empty(), stack1.empty());

  std::stack<std::string> origin2({"qwe"});
  s21::stack<std::string> stack2({"qwe"});
  origin2.pop();
  stack2.pop();
  EXPECT_EQ(origin2.empty(), stack2.empty());

  std::stack<bool> origin3({true});
  s21::stack<bool> stack3({true});
  origin3.pop();
  stack3.pop();
  EXPECT_EQ(origin3.empty(), stack3.empty());

  struct Point {
    int x = 0;
    int y = 0;
  };
  std::stack<Point> origin4({{1, 4}});
  s21::stack<Point> stack4({{1, 4}});
  origin4.pop();
  stack4.pop();
  EXPECT_EQ(origin4.empty(), stack4.empty());
}

/*7 size()*/
TEST(hardStackTest, sizeTest) {
  std::stack<int> origin;
  s21::stack<int> stack1;
  int count = 1300;
  while (count > 0) {
    count--;
    origin.push(count);
    stack1.push(count);
    EXPECT_EQ(origin.size(), stack1.size());
    EXPECT_EQ(origin.top(), stack1.top());
  }
  EXPECT_EQ(origin.size(), stack1.size());
}

/*8 constuctorCopy*/
TEST(hardStackTest, constuctorCopyTest0) {
  std::stack<bool> origin(
      {true, false, true, true, true, 0, 1, 1, true, false, 0, 0, 0});
  s21::stack<bool> stack1(
      {true, false, true, true, true, 0, true, 1, 1, 0, false, 0, false});
  std::stack<bool> originCP(origin);
  s21::stack<bool> stack1CP(stack1);
  EXPECT_NE(&origin, &originCP);
  EXPECT_NE(&stack1, &stack1CP);
  int count = 13;
  while (count > 0) {
    count--;
    EXPECT_NE(&origin.top(), &originCP.top());
    EXPECT_NE(&stack1.top(), &stack1CP.top());
    EXPECT_EQ(origin.top(), originCP.top());
    EXPECT_EQ(stack1.top(), stack1CP.top());
    EXPECT_EQ(origin.size(), originCP.size());
    EXPECT_EQ(stack1.size(), stack1CP.size());
    origin.pop();
    originCP.pop();
    stack1.pop();
    stack1CP.pop();
  }
}
TEST(hardStackTest, constuctorCopyTest1) {
  std::stack<double> origin({1.9, 2.547, 379, -4.1});
  s21::stack<double> stack1({1.9, 2.547, 379, -4.1});
  std::stack<double> originCP(origin);
  s21::stack<double> stack1CP(stack1);
  EXPECT_NE(&origin, &originCP);
  EXPECT_NE(&stack1, &stack1CP);
  int count = 4;
  while (count > 0) {
    count--;
    EXPECT_NE(&origin.top(), &originCP.top());
    EXPECT_NE(&stack1.top(), &stack1CP.top());
    EXPECT_EQ(origin.top(), originCP.top());
    EXPECT_EQ(stack1.top(), stack1CP.top());
    EXPECT_EQ(origin.size(), originCP.size());
    EXPECT_EQ(stack1.size(), stack1CP.size());
    origin.pop();
    originCP.pop();
    stack1.pop();
    stack1CP.pop();
  }
}
TEST(hardStackTest, constuctorCopyTest2) {
  std::stack<int> origin;
  s21::stack<int> stack1;

  int count = 1300;
  while (count > 0) {
    count--;
    origin.push(count);
    stack1.push(count);
  }

  std::stack<int> originCP(origin);
  s21::stack<int> stack1CP(stack1);
  count = 1300;
  while (count > 0) {
    count--;
    EXPECT_NE(&origin, &originCP);
    EXPECT_NE(&stack1, &stack1CP);
    EXPECT_NE(&origin.top(), &originCP.top());
    EXPECT_NE(&stack1.top(), &stack1CP.top());
    EXPECT_EQ(origin.top(), originCP.top());
    EXPECT_EQ(stack1.top(), stack1CP.top());
    EXPECT_EQ(origin.size(), originCP.size());
    EXPECT_EQ(stack1.size(), stack1CP.size());
    origin.pop();
    originCP.pop();
    stack1.pop();
    stack1CP.pop();
  }

  EXPECT_EQ(origin.empty(), true);
  EXPECT_EQ(stack1.empty(), true);
}
TEST(hardStackTest, constuctorCopyTest3) {
  struct Point {
    int x = 0;
    int y = 0;
  };
  std::stack<Point> origin({{1, 4}, {5, 2}, {7, 9}});
  s21::stack<Point> stack1({{1, 4}, {5, 2}, {7, 9}});

  std::stack<Point> originCP(origin);
  s21::stack<Point> stack1CP(stack1);
  int count = 3;
  while (count > 0) {
    count--;
    EXPECT_NE(&origin.top(), &originCP.top());
    EXPECT_NE(&stack1.top(), &stack1CP.top());
    EXPECT_EQ(origin.top().x, originCP.top().x);
    EXPECT_EQ(origin.top().y, originCP.top().y);
    EXPECT_EQ(stack1.top().x, stack1CP.top().x);
    EXPECT_EQ(stack1.top().y, stack1CP.top().y);
    EXPECT_EQ(origin.size(), originCP.size());
    EXPECT_EQ(stack1.size(), stack1CP.size());
    origin.pop();
    originCP.pop();
    stack1.pop();
    stack1CP.pop();
  }
}
/*9 constuctorMove*/
TEST(hardStackTest, constuctorMoveTest0) {
  std::stack<int> origin;
  s21::stack<int> stack1;

  int count = 1300;
  while (count > 0) {
    count--;
    origin.push(count);
    stack1.push(count);
  }
  const void *p1 = &origin.top();
  const void *p2 = &stack1.top();

  std::stack<int> originCP(std::move(origin));
  s21::stack<int> stack1CP(std::move(stack1));
  EXPECT_NE(&origin, &originCP);
  EXPECT_NE(&stack1, &stack1CP);
  EXPECT_EQ(origin.empty(), true);
  EXPECT_EQ(stack1.empty(), true);
  EXPECT_EQ(origin.size(), 0);
  EXPECT_EQ(stack1.size(), 0);

  EXPECT_EQ(&originCP.top(), p1);
  EXPECT_EQ(&stack1CP.top(), p2);
  count = 1300;
  while (count > 0) {
    count--;

    EXPECT_EQ(originCP.top(), stack1CP.top());

    EXPECT_EQ(originCP.size(), stack1CP.size());

    originCP.pop();

    stack1CP.pop();
  }
}

TEST(hardStackTest, constuctorMoveTest1) {
  std::stack<bool> origin(
      {true, false, true, true, true, 0, 1, 1, true, false, 0, 0, 0});
  s21::stack<bool> stack1(
      {true, false, true, true, true, 0, true, 1, 1, 0, false, 0, false});

  const void *p1 = &origin.top();
  const void *p2 = &stack1.top();

  std::stack<bool> originCP(std::move(origin));
  s21::stack<bool> stack1CP(std::move(stack1));
  EXPECT_EQ(origin.empty(), true);
  EXPECT_EQ(stack1.empty(), true);
  EXPECT_EQ(origin.size(), 0);
  EXPECT_EQ(stack1.size(), 0);

  EXPECT_EQ(&originCP.top(), p1);
  EXPECT_EQ(&stack1CP.top(), p2);
  int count = 13;
  while (count > 0) {
    count--;

    EXPECT_EQ(originCP.top(), stack1CP.top());

    EXPECT_EQ(originCP.size(), stack1CP.size());

    originCP.pop();

    stack1CP.pop();
  }
}
TEST(simpleStackTest, operatorEqTest) {
  std::stack<int> origin;
  s21::stack<int> stack1;

  std::stack<int> originCP = origin;
  s21::stack<int> stack1CP = stack1;
  EXPECT_NE(&origin, &originCP);
  EXPECT_NE(&stack1, &stack1CP);
  EXPECT_EQ(origin.empty(), true);
  EXPECT_EQ(stack1.empty(), true);
  EXPECT_EQ(originCP.empty(), true);
  EXPECT_EQ(stack1CP.empty(), true);
  EXPECT_EQ(origin.size(), originCP.size());
  EXPECT_EQ(stack1.size(), stack1CP.size());
}
TEST(hardStackTest, operatorEqTest) {
  std::stack<bool> origin(
      {true, false, true, true, true, 0, 1, 1, true, false, 0, 0, 0});
  s21::stack<bool> stack1(
      {true, false, true, true, true, 0, true, 1, 1, 0, false, 0, false});

  std::stack<bool> originCP = origin;
  s21::stack<bool> stack1CP = stack1;
  EXPECT_NE(&origin, &originCP);
  EXPECT_NE(&stack1, &stack1CP);
  int count = 13;
  while (count > 0) {
    count--;
    EXPECT_NE(&origin.top(), &originCP.top());
    EXPECT_NE(&stack1.top(), &stack1CP.top());
    EXPECT_EQ(origin.top(), originCP.top());
    EXPECT_EQ(stack1.top(), stack1CP.top());
    EXPECT_EQ(origin.size(), originCP.size());
    EXPECT_EQ(stack1.size(), stack1CP.size());
    origin.pop();
    originCP.pop();
    stack1.pop();
    stack1CP.pop();
  }
}
// если не пустому стеку присвоить пустой стек
// проверить что будет если  копировать пустой стек в непустой стек

TEST(simpleStackTest, operatorEqMoveTest) {
  std::stack<int> origin;
  s21::stack<int> stack;
  std::stack<int> originCP;
  originCP = std::move(origin);
  s21::stack<int> stackCP;
  stackCP = std::move(stack);

  EXPECT_NE(&origin, &originCP);
  EXPECT_NE(&stack, &stackCP);
}
TEST(mediumStackTest, operatorEqMoveTest) {
  std::stack<int> origin({1, 2, 3, 4, 5, 6, 7});
  s21::stack<int> stack({1, 2, 3, 4, 5, 6, 7});
  int size = origin.size();

  std::stack<int> originCP;
  s21::stack<int> stackCP;

  originCP = std::move(origin);
  stackCP = std::move(stack);

  EXPECT_NE(&origin, &originCP);
  EXPECT_NE(&stack, &stackCP);

  EXPECT_EQ(origin.empty(), true);
  EXPECT_EQ(originCP.empty(), false);
  EXPECT_EQ(stack.empty(), true);
  EXPECT_EQ(stackCP.empty(), false);

  EXPECT_EQ(origin.size(), 0);
  EXPECT_EQ(originCP.size(), size);
  EXPECT_EQ(stack.size(), 0);
  EXPECT_EQ(stackCP.size(), size);

  while (size > 1) {
    EXPECT_EQ(stackCP.top(), originCP.top());
    EXPECT_EQ(stackCP.size(), originCP.size());
    originCP.pop();
    stackCP.pop();
    size--;
  }
}
TEST(hardStackTest, operatorEqMoveTest) {
  std::stack<int> origin;
  s21::stack<int> stack;

  std::stack<int> originCP({1, 2, 3, 4, 5, 6, 7});
  s21::stack<int> stackCP({1, 2, 3, 4, 5, 6, 7});

  originCP = std::move(origin);
  stackCP = std::move(stack);

  EXPECT_NE(&origin, &originCP);
  EXPECT_NE(&stack, &stackCP);

  EXPECT_EQ(origin.empty(), true);
  EXPECT_EQ(originCP.empty(), true);
  EXPECT_EQ(stack.empty(), true);
  EXPECT_EQ(stackCP.empty(), true);

  EXPECT_EQ(origin.size(), 0);
  EXPECT_EQ(originCP.size(), 0);
  EXPECT_EQ(stack.size(), 0);
  EXPECT_EQ(stackCP.size(), 0);
}
// оперетор обмена swap(stack &other)

TEST(simpleStackTest, swapTest) {
  std::stack<int> origin;
  s21::stack<int> stack;
  std::stack<int> originCP;
  s21::stack<int> stackCP;

  const void *porigin = &origin;
  const void *pstack = &stack;
  const void *poriginCP = &originCP;
  const void *pstackCP = &stackCP;

  originCP.swap(origin);
  stackCP.swap(stack);

  EXPECT_EQ(&origin, porigin);
  EXPECT_EQ(&originCP, poriginCP);
  EXPECT_EQ(&stack, pstack);
  EXPECT_EQ(&stackCP, pstackCP);
}
TEST(mediumStackTest, swapTest) {
  std::stack<int> origin({1, 2, 3, 4, 5, 6, 7});
  s21::stack<int> stack({1, 2, 3, 4, 5, 6, 7});
  std::stack<int> originCP;
  s21::stack<int> stackCP;

  const void *porigin = &origin;
  const void *pstack = &stack;
  const void *poriginCP = &originCP;
  const void *pstackCP = &stackCP;

  originCP.swap(origin);
  stackCP.swap(stack);

  EXPECT_EQ(&origin, porigin);
  EXPECT_EQ(&originCP, poriginCP);
  EXPECT_EQ(&stack, pstack);
  EXPECT_EQ(&stackCP, pstackCP);

  EXPECT_EQ(origin.size(), 0);
  EXPECT_EQ(originCP.size(), 7);
  EXPECT_EQ(stack.size(), 0);
  EXPECT_EQ(stackCP.size(), 7);

  EXPECT_EQ(origin.empty(), true);
  EXPECT_EQ(originCP.empty(), false);
  EXPECT_EQ(stack.empty(), true);
  EXPECT_EQ(stackCP.empty(), false);

  EXPECT_EQ(originCP.top(), 7);
  EXPECT_EQ(stackCP.top(), 7);

  originCP.pop();
  stackCP.pop();

  EXPECT_EQ(originCP.top(), 6);
  EXPECT_EQ(stackCP.top(), 6);
}

TEST(mediumStackTest, swapTest2) {
  std::stack<int> origin;
  s21::stack<int> stack;
  std::stack<int> originCP({1, 2, 3, 4, 5, 6, 7});
  s21::stack<int> stackCP({1, 2, 3, 4, 5, 6, 7});

  const void *porigin = &origin;
  const void *pstack = &stack;
  const void *poriginCP = &originCP;
  const void *pstackCP = &stackCP;

  originCP.swap(origin);
  stackCP.swap(stack);

  EXPECT_EQ(&origin, porigin);
  EXPECT_EQ(&originCP, poriginCP);
  EXPECT_EQ(&stack, pstack);
  EXPECT_EQ(&stackCP, pstackCP);

  EXPECT_EQ(origin.size(), 7);
  EXPECT_EQ(originCP.size(), 0);
  EXPECT_EQ(stack.size(), 7);
  EXPECT_EQ(stackCP.size(), 0);

  EXPECT_EQ(origin.empty(), false);
  EXPECT_EQ(originCP.empty(), true);
  EXPECT_EQ(stack.empty(), false);
  EXPECT_EQ(stackCP.empty(), true);

  EXPECT_EQ(origin.top(), 7);
  EXPECT_EQ(stack.top(), 7);

  origin.pop();
  stack.pop();
  origin.pop();
  stack.pop();

  EXPECT_EQ(origin.top(), 5);
  EXPECT_EQ(stack.top(), 5);
}

TEST(hardStackTest, swapTest1) {
  std::stack<int> origin({8, 9});
  s21::stack<int> stack({8, 9});
  std::stack<int> originCP({1, 2, 3, 4, 5, 6, 7});
  s21::stack<int> stackCP({1, 2, 3, 4, 5, 6, 7});

  const void *porigin = &origin;
  const void *pstack = &stack;
  const void *poriginCP = &originCP;
  const void *pstackCP = &stackCP;

  const void *poriginTOP = &origin.top();
  const void *pstackTOP = &stack.top();
  const void *poriginCPtop = &originCP.top();
  const void *pstackCPtop = &stackCP.top();

  originCP.swap(origin);
  stackCP.swap(stack);

  EXPECT_EQ(&origin, porigin);
  EXPECT_EQ(&originCP, poriginCP);
  EXPECT_EQ(&stack, pstack);
  EXPECT_EQ(&stackCP, pstackCP);

  EXPECT_EQ(&origin.top(), poriginCPtop);
  EXPECT_EQ(&originCP.top(), poriginTOP);
  EXPECT_EQ(&stack.top(), pstackCPtop);
  EXPECT_EQ(&stackCP.top(), pstackTOP);

  EXPECT_EQ(origin.size(), 7);
  EXPECT_EQ(originCP.size(), 2);
  EXPECT_EQ(stack.size(), 7);
  EXPECT_EQ(stackCP.size(), 2);

  EXPECT_EQ(origin.empty(), false);
  EXPECT_EQ(originCP.empty(), false);
  EXPECT_EQ(stack.empty(), false);
  EXPECT_EQ(stackCP.empty(), false);

  EXPECT_EQ(origin.top(), 7);
  EXPECT_EQ(stack.top(), 7);
  EXPECT_EQ(originCP.top(), 9);
  EXPECT_EQ(stackCP.top(), 9);

  origin.pop();
  stack.pop();
  origin.pop();
  stack.pop();

  EXPECT_EQ(origin.top(), 5);
  EXPECT_EQ(stack.top(), 5);

  originCP.pop();
  stackCP.pop();

  EXPECT_EQ(originCP.top(), 8);
  EXPECT_EQ(stackCP.top(), 8);
}

TEST(hardStackTest, swapTest2) {
  std::stack<int> origin({8, 9});
  s21::stack<int> stack({8, 9});
  std::stack<int> originCP({1});
  s21::stack<int> stackCP{1};

  const void *porigin = &origin;
  const void *pstack = &stack;
  const void *poriginCP = &originCP;
  const void *pstackCP = &stackCP;

  const void *poriginTOP = &origin.top();
  const void *pstackTOP = &stack.top();
  const void *poriginCPtop = &originCP.top();
  const void *pstackCPtop = &stackCP.top();

  originCP.swap(origin);
  stackCP.swap(stack);

  EXPECT_EQ(&origin, porigin);
  EXPECT_EQ(&originCP, poriginCP);
  EXPECT_EQ(&stack, pstack);
  EXPECT_EQ(&stackCP, pstackCP);

  EXPECT_EQ(&origin.top(), poriginCPtop);
  EXPECT_EQ(&originCP.top(), poriginTOP);
  EXPECT_EQ(&stack.top(), pstackCPtop);
  EXPECT_EQ(&stackCP.top(), pstackTOP);

  EXPECT_EQ(origin.size(), 1);
  EXPECT_EQ(originCP.size(), 2);
  EXPECT_EQ(stack.size(), 1);
  EXPECT_EQ(stackCP.size(), 2);

  EXPECT_EQ(origin.empty(), false);
  EXPECT_EQ(originCP.empty(), false);
  EXPECT_EQ(stack.empty(), false);
  EXPECT_EQ(stackCP.empty(), false);

  EXPECT_EQ(origin.top(), 1);
  EXPECT_EQ(stack.top(), 1);
  EXPECT_EQ(originCP.top(), 9);
  EXPECT_EQ(stackCP.top(), 9);

  origin.pop();
  stack.pop();
  EXPECT_EQ(origin.size(), 0);
  EXPECT_EQ(stack.size(), 0);

  EXPECT_EQ(origin.empty(), true);
  EXPECT_EQ(stack.empty(), true);

  originCP.pop();
  stackCP.pop();

  EXPECT_EQ(originCP.top(), 8);
  EXPECT_EQ(stackCP.top(), 8);

  originCP.pop();
  stackCP.pop();

  EXPECT_EQ(originCP.size(), 0);
  EXPECT_EQ(stackCP.size(), 0);

  EXPECT_EQ(originCP.empty(), true);
  EXPECT_EQ(stackCP.empty(), true);
}

TEST(simpleStackTests, insertManyTest) {
  s21::stack<int> stack({8, 9});
  stack.insert_many_back(1);
  EXPECT_EQ(stack.top(), 1);
}

TEST(mediumStackTests, insertManyTest) {
  s21::stack<int> stack({8, 9});
  stack.insert_many_back(1, 4, 18);
  EXPECT_EQ(stack.top(), 18);
  EXPECT_EQ(stack.size(), 5);
}

TEST(mediumStackTests, insertManyTest1) {
  s21::stack<int> stack({8, 9});
  stack.insert_many_back();
  EXPECT_EQ(stack.top(), 9);
  EXPECT_EQ(stack.size(), 2);
}

TEST(mediumStackTests, insertManyTest2) {
  s21::stack<int> stack({8, 9});
  stack.insert_many_back(4, 3.6);  // static_cast()
  EXPECT_EQ(stack.top(), 3);
  EXPECT_EQ(stack.size(), 4);
}

TEST(hardStackTests, insertManyTest) {
  s21::stack<int> stack({8, 9});
  stack.insert_many_back(4, 3, 'v');  // static_cast()
  EXPECT_EQ(stack.top(), 'v');
  EXPECT_EQ(stack.size(), 5);
}

#endif
