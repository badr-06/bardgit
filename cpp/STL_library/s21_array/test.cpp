#ifndef S21_TEST_ARRAY_STL_CPP
#define S21_TEST_ARRAY_STL_CPP

#include <gtest/gtest.h>

#include <array>

#include "s21_array.h"

TEST(ArrayTest, test_0) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr.size(), 5);
  for (size_t i = 0; i < arr.size(); i++) {
    EXPECT_EQ(arr[i], static_cast<int>(i) + 1);
  }
}

TEST(ArrayTest, test_1) {
  s21::array<int, 5> arr;
  EXPECT_EQ(arr.size(), 5);
}

TEST(ArrayTest, test_2) {
  s21::array<int, 5> arr = {};
  EXPECT_EQ(arr.size(), 5);
}

TEST(ArrayTest, test_3) {
  s21::array<int, 5> arr{1, 2, 3, 4, 5};
  EXPECT_EQ(arr.size(), 5);
}

TEST(ArrayTest, copy_test_0) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  s21::array<int, 5> arr1(arr);
  EXPECT_EQ(arr.size(), arr1.size());
  EXPECT_EQ(arr[0], arr1[0]);
  EXPECT_EQ(arr[1], arr1[1]);
  EXPECT_EQ(arr[2], arr1[2]);
  EXPECT_EQ(arr[3], arr1[3]);
  EXPECT_EQ(arr[4], arr1[4]);
}

TEST(ArrayTest, move_test_0) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  s21::array<int, 5> arr1 = std::move(arr);
  EXPECT_EQ(arr1.size(), 5);
  EXPECT_EQ(arr1[0], 1);
  EXPECT_EQ(arr1[1], 2);
  EXPECT_EQ(arr1[2], 3);
  EXPECT_EQ(arr1[3], 4);
  EXPECT_EQ(arr1[4], 5);
}

TEST(ArrayTest, equal_test) {
  s21::array<int, 5> arr{1, 2, 3, 4, 5};
  s21::array<int, 5> arr1;
  arr1 = std::move(arr);

  EXPECT_EQ(arr.size(), 5U);
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr[2], 3);
  EXPECT_EQ(arr[3], 4);
  EXPECT_EQ(arr[4], 5);
}

TEST(ArrayTest, at_test_0) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr.at(0), 1);
  EXPECT_EQ(arr.at(2), 3);
  EXPECT_EQ(arr.at(4), 5);
}

TEST(ArrayTest, at_test_1) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_THROW(arr.at(5), std::out_of_range);
}

TEST(ArrayTest, at_test_2) {
  s21::array<int, 5> arr;
  EXPECT_THROW(arr.at(5), std::out_of_range);
}

TEST(ArrayTest, square_test_0) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr.size(), 5);
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr[2], 3);
  EXPECT_EQ(arr[3], 4);
  EXPECT_EQ(arr[4], 5);
}

TEST(ArrayTest, front_test_0) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr.front(), 1);
}

TEST(ArrayTest, back_test_0) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr.back(), 5);
}

TEST(ArrayTest, data_test_0) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr.data(), &arr[0]);
}

TEST(ArrayTest, begin_test_0) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr.begin(), &arr[0]);
}

TEST(ArrayTest, end_test_0) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr.end(), &arr[0] + 5);
}

TEST(ArrayTest, empty_test_0) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr.empty(), 0);
}

TEST(ArrayTest, empty_test_1) {
  s21::array<int, 0> arr;
  EXPECT_EQ(arr.empty(), 1);
}

TEST(ArrayTest, size_test_0) {
  s21::array<int, 0> arr;
  EXPECT_EQ(arr.size(), 0);
}

TEST(ArrayTest, size_test_1) {
  s21::array<int, 5> arr;
  EXPECT_EQ(arr.size(), 5);
}

TEST(ArrayTest, max_size_test_0) {
  s21::array<int, 5> arr;
  EXPECT_EQ(arr.max_size(), 5);
}

TEST(ArrayTest, swap_test_0) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  s21::array<int, 5> arr1;
  arr1.swap(arr);

  EXPECT_EQ(arr1[0], 1);
  EXPECT_EQ(arr1[1], 2);
  EXPECT_EQ(arr1[2], 3);
  EXPECT_EQ(arr1[3], 4);
  EXPECT_EQ(arr1[4], 5);
}

TEST(ArrayTest, fill_test_0) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  arr.fill(21);

  EXPECT_EQ(arr[0], 21);
  EXPECT_EQ(arr[1], 21);
  EXPECT_EQ(arr[2], 21);
  EXPECT_EQ(arr[3], 21);
  EXPECT_EQ(arr[4], 21);
}

#endif
