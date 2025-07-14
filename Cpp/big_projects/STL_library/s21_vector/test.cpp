#ifndef S21_TEST_VECTOR_STL_CPP
#define S21_TEST_VECTOR_STL_CPP

#include <gtest/gtest.h>

#include <vector>

#include "s21_vector.h"

TEST(VectorTest, test_0) {
  s21::vector<int> v;
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), 0);
}

TEST(VectorTest, test_1) {
  const size_t size = 0;
  s21::vector<int> v(size);
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), size);
}

TEST(VectorTest, test_2) {
  const size_t size = 3;
  s21::vector<int> v(size);
  EXPECT_FALSE(v.empty());
  EXPECT_EQ(v.size(), size);
  for (size_t i = 0; i < size; i++) {
    EXPECT_EQ(v[i], 0);
  }
}

TEST(VectorTest, test_3) {
  s21::vector<int> v = {};
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), 0);
}

TEST(VectorTest, test_4) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_FALSE(v.empty());
  EXPECT_EQ(v.size(), 5);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[3], 4);
  EXPECT_EQ(v[4], 5);
}

TEST(VectorTest, test_5) {
  s21::vector<char> v;
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), 0);
}

TEST(VectorTest, test_6) {
  const size_t size = 0;
  s21::vector<char> v(size);
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), size);
}

TEST(VectorTest, test_7) {
  const size_t size = 3;
  s21::vector<char> v(size);
  EXPECT_FALSE(v.empty());
  EXPECT_EQ(v.size(), size);
  for (size_t i = 0; i < size; i++) {
    EXPECT_EQ(v[i], 0);
  }
}

TEST(VectorTest, test_8) {
  s21::vector<char> v = {};
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), 0);
}

TEST(VectorTest, test_9) {
  s21::vector<char> v = {'c', 'a', 'p', 'y', 'b', 'a', 'r', 'a'};
  EXPECT_FALSE(v.empty());
  EXPECT_EQ(v.size(), 8);
  EXPECT_EQ(v[0], 'c');
  EXPECT_EQ(v[1], 'a');
  EXPECT_EQ(v[2], 'p');
  EXPECT_EQ(v[3], 'y');
  EXPECT_EQ(v[4], 'b');
  EXPECT_EQ(v[5], 'a');
  EXPECT_EQ(v[6], 'r');
  EXPECT_EQ(v[7], 'a');
}

TEST(VectorTest, test_10) {
  s21::vector<std::string> v{"capybara", "engineering"};
  EXPECT_EQ(v[0], "capybara");
  EXPECT_EQ(v[1], "engineering");
}

TEST(VectorTest, copy_test_0) {
  s21::vector<int> v1;
  s21::vector<int> v2(v1);
  EXPECT_TRUE(v2.empty());
  EXPECT_EQ(v2.size(), 0);
}

TEST(VectorTest, copy_test_1) {
  s21::vector<int> v1 = {1, 2, 3, 4, 5};
  s21::vector<int> v2(v1);
  EXPECT_EQ(v2.size(), v1.size());
  for (size_t i = 0; i < v1.size(); i++) {
    EXPECT_EQ(v2[i], v1[i]);
  }
}

TEST(VectorTest, copy_test_3) {
  s21::vector<char> v1 = {'c', 'a', 'p', 'y', 'b', 'a', 'r', 'a'};
  s21::vector<char> v2(v1);
  EXPECT_FALSE(v2.empty());
  EXPECT_EQ(v2.size(), 8);
  EXPECT_EQ(v2[0], 'c');
  EXPECT_EQ(v2[1], 'a');
  EXPECT_EQ(v2[2], 'p');
  EXPECT_EQ(v2[3], 'y');
  EXPECT_EQ(v2[4], 'b');
  EXPECT_EQ(v2[5], 'a');
  EXPECT_EQ(v2[6], 'r');
  EXPECT_EQ(v2[7], 'a');
}

TEST(VectorTest, move_test_0) {
  s21::vector<int> v1;
  s21::vector<int> v2(std::move(v1));
  EXPECT_TRUE(v2.empty());
  EXPECT_EQ(v2.size(), 0);
}

TEST(VectorTest, move_test_1) {
  s21::vector<int> v1 = {0, 1, 2, 3, 4};
  s21::vector<int> v2(std::move(v1));
  EXPECT_EQ(v2.size(), 5);
  for (size_t i = 0; i < v1.size(); i++) {
    EXPECT_EQ(v2[i], i);
  }
  EXPECT_TRUE(v1.empty());
}

TEST(VectorTest, move_test_2) {
  s21::vector<char> v1 = {'c', 'a', 'p', 'y', 'b', 'a', 'r', 'a'};
  s21::vector<char> v2(std::move(v1));

  EXPECT_TRUE(v1.empty());
  EXPECT_FALSE(v2.empty());

  EXPECT_EQ(v2.size(), 8);
  EXPECT_EQ(v2[0], 'c');
  EXPECT_EQ(v2[1], 'a');
  EXPECT_EQ(v2[2], 'p');
  EXPECT_EQ(v2[3], 'y');
  EXPECT_EQ(v2[4], 'b');
  EXPECT_EQ(v2[5], 'a');
  EXPECT_EQ(v2[6], 'r');
  EXPECT_EQ(v2[7], 'a');
}

TEST(VectorTest, destructor_test_0) {
  s21::vector<int> *v = new s21::vector<int>();
  delete v;
}

TEST(VectorTest, destructor_test_1) {
  s21::vector<int> *v = new s21::vector<int>{1, 2, 3, 4, 5};
  delete v;
}

TEST(VectorTest, assignment_test_0) {
  s21::vector<int> v1;
  s21::vector<int> v2 = std::move(v1);
  EXPECT_TRUE(v2.empty());
  EXPECT_EQ(v2.size(), 0);
}

TEST(VectorTest, assignment_test_1) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2 = std::move(v1);
  EXPECT_EQ(v2.size(), 3);
  EXPECT_TRUE(v1.empty());
}

TEST(VectorTest, at_test_0) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v.at(0), 1);
  EXPECT_EQ(v.at(2), 3);
  EXPECT_EQ(v.at(4), 5);
}

TEST(VectorTest, at_test_1) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_THROW(v.at(5), std::out_of_range);
}

TEST(VectorTest, index_test_0) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[4], 5);
}

TEST(VectorTest, index_test_1) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_ANY_THROW(v[5]);
}

TEST(VectorTest, front_test_0) {
  s21::vector<int> v;
  EXPECT_THROW(v.front(), std::out_of_range);
}

TEST(VectorTest, front_test_1) {
  s21::vector<int> v = {1, 2, 3};
  EXPECT_EQ(v.front(), 1);
}

TEST(VectorTest, front_test_2) {
  s21::vector<char> v = {'c', 'a', 'p', 'y', 'b', 'a', 'r', 'a'};
  EXPECT_EQ(v.front(), 'c');
}

TEST(VectorTest, front_test_3) {
  s21::vector<std::string> v{"capybara", "engineering"};
  EXPECT_EQ(v.front(), "capybara");
}

TEST(VectorTest, back_test_0) {
  s21::vector<int> v;
  EXPECT_THROW(v.back(), std::out_of_range);
}

TEST(VectorTest, back_test_1) {
  s21::vector<int> v = {1, 2, 3};
  EXPECT_EQ(v.back(), 3);
}

TEST(VectorTest, back_test_2) {
  s21::vector<char> v = {'c', 'a', 'p', 'y', 'b', 'a', 'r', 'a'};
  EXPECT_EQ(v.back(), 'a');
}

TEST(VectorTest, back_test_3) {
  s21::vector<std::string> v{"capybara", "engineering"};
  EXPECT_EQ(v.back(), "engineering");
}

TEST(VectorTest, data_test_0) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  int *ptr_data = v.data();
  EXPECT_EQ(*ptr_data, 1);
  *ptr_data = 10;
  EXPECT_EQ(v[0], 10);
}

TEST(VectorTest, data_test_1) {
  s21::vector<int> v;
  int *ptr_data = v.data();
  EXPECT_EQ(ptr_data, nullptr);
}

TEST(VectorTest, begin_test_0) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  auto it = v.begin();
  EXPECT_EQ(*it, 1);
  *it = 10;
  EXPECT_EQ(v[0], 10);
}

TEST(VectorTest, begin_test_1) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v.begin(), &v[0]);
}

TEST(VectorTest, begin_test_2) {
  s21::vector<std::string> v{"capybara", "engineering"};
  EXPECT_EQ(v.begin(), &v[0]);
}

TEST(VectorTest, begin_test_3) {
  s21::vector<int> v;
  EXPECT_EQ(v.begin(), v.end());
}

TEST(VectorTest, end_test_0) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  auto it = v.end();
  auto begin = v.begin();
  EXPECT_NE(it, begin);
}

TEST(VectorTest, end_test_1) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v.end(), &v[0] + 5);
}

TEST(VectorTest, end_test_2) {
  s21::vector<std::string> v{"capybara", "engineering"};
  EXPECT_EQ(v.end(), &v[0] + 2);
}

TEST(VectorTest, end_test_3) {
  s21::vector<int> v;
  EXPECT_EQ(v.end(), v.begin());
}

TEST(VectorTest, size_test_0) {
  s21::vector<int> v;
  EXPECT_EQ(v.size(), 0);
}

TEST(VectorTest, size_test_1) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v.size(), 5);
}

TEST(VectorTest, max_size_test_0) {
  s21::vector<int> v;
  EXPECT_GT(v.max_size(), 0);
}

TEST(VectorTest, reserve_test_0) {
  s21::vector<int> v;
  v.reserve(21);
  EXPECT_EQ(v.capacity(), 21U);
}

TEST(VectorTest, reserve_test_1) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  v.reserve(2);
  EXPECT_EQ(v.capacity(), 5U);
}

TEST(VectorTest, reserve_test_2) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  v.reserve(21);
  EXPECT_EQ(v.capacity(), 21U);
}

TEST(VectorTest, capacity_test_0) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v.capacity(), 5U);
}

TEST(VectorTest, capacity_test_1) {
  s21::vector<int> v = {};
  EXPECT_EQ(v.capacity(), 0);
}

TEST(VectorTest, shrink_to_fit_test_0) {
  s21::vector<int> v;
  v.reserve(21);
  EXPECT_EQ(v.capacity(), 21U);
  v.shrink_to_fit();
  EXPECT_EQ(v.capacity(), 0);
}

TEST(VectorTest, shrink_to_fit_test_1) {
  s21::vector<int> v;
  v.shrink_to_fit();
  EXPECT_EQ(v.capacity(), 0);
}

TEST(VectorTest, shrink_to_fit_test_2) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v.capacity(), 5U);
  v.shrink_to_fit();
  EXPECT_EQ(v.capacity(), 5);
}

TEST(VectorTest, shrink_to_fit_test_3) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  v.reserve(21);
  EXPECT_EQ(v.capacity(), 21U);
  v.shrink_to_fit();
  EXPECT_EQ(v.capacity(), 5);
}

TEST(VectorTest, clear_test_0) {
  s21::vector<int> v = {};
  v.clear();
  EXPECT_EQ(v.size(), 0);
  EXPECT_TRUE(v.empty());
  EXPECT_GE(v.capacity(), 0);
}

TEST(VectorTest, clear_test_1) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  v.clear();
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), 0);
  EXPECT_GE(v.capacity(), 0);
}

TEST(VectorTest, insert_test_0) {
  s21::vector<int> v = {2, 3, 4, 5};
  v.insert(v.begin(), 1);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[3], 4);
  EXPECT_EQ(v[4], 5);
}

TEST(VectorTest, insert_test_1) {
  s21::vector<int> v = {1, 3, 4, 5};
  v.insert(v.begin() + 1, 2);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[3], 4);
  EXPECT_EQ(v[4], 5);
}

TEST(VectorTest, insert_test_2) {
  s21::vector<int> v = {1, 2, 3, 4};
  v.insert(v.end(), 5);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[3], 4);
  EXPECT_EQ(v[4], 5);
}

TEST(VectorTest, insert_test_3) {
  s21::vector<int> v = {1, 2, 3, 4};
  EXPECT_ANY_THROW(v.insert(v.end() + 1, 5));
}

TEST(VectorTest, erase_test_0) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  v.erase(v.begin());
  EXPECT_EQ(v.size(), 4);
  EXPECT_EQ(v[0], 2);
  EXPECT_EQ(v[1], 3);
  EXPECT_EQ(v[2], 4);
  EXPECT_EQ(v[3], 5);
}

TEST(VectorTest, erase_test_1) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  v.erase(v.begin() + 2);
  EXPECT_EQ(v.size(), 4);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 4);
  EXPECT_EQ(v[3], 5);
}

TEST(VectorTest, erase_test_2) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  v.erase(v.end() - 1);
  EXPECT_EQ(v.size(), 4);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[3], 4);
}

TEST(VectorTest, push_back_test_0) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  v.push_back(6);
  EXPECT_EQ(v.size(), 6);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[3], 4);
  EXPECT_EQ(v[4], 5);
  EXPECT_EQ(v[5], 6);
}

TEST(VectorTest, push_back_test_1) {
  s21::vector<int> v;
  v.push_back(1);
  EXPECT_EQ(v.size(), 1);
  EXPECT_EQ(v[0], 1);
}

TEST(VectorTest, pop_back_test_0) {
  s21::vector<int> v = {1, 2};
  v.pop_back();
  EXPECT_EQ(v.size(), 1);
  EXPECT_EQ(v[0], 1);
}

TEST(VectorTest, pop_back_test_1) {
  s21::vector<int> v = {1};
  v.pop_back();
  EXPECT_EQ(v.size(), 0);
}

TEST(VectorTest, pop_back_test_2) {
  s21::vector<int> v;
  v.pop_back();
  EXPECT_EQ(v.size(), 0);
}

TEST(VectorTest, insert_many_test_0) {
  s21::vector<int> v = {1, 5};
  auto pos = v.begin() + 1;
  v.insert_many(pos, 2, 3, 4);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[3], 4);
  EXPECT_EQ(v[4], 5);
}

TEST(VectorTest, insert_many_back_test_0) {
  s21::vector<int> v = {1};
  v.insert_many_back(2, 3, 4, 5);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[3], 4);
  EXPECT_EQ(v[4], 5);
}

#endif
