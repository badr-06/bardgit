#include <gtest/gtest.h>

#include <set>

#include "s21_multiset.hpp"

TEST(multiset, ConstructorDefault) {
  std::multiset<int> orig_ms;
  s21::multiset<int> my_ms;
  EXPECT_EQ(orig_ms.empty(), my_ms.empty());
}

TEST(multiset, ConstructorInitialization) {
  std::multiset<int> orig_ms{1, 2, 3, 4, 1, 2, 3, 4};
  s21::multiset<int> my_ms{1, 2, 3, 4, 1, 2, 3, 4};
  ASSERT_EQ(orig_ms.size(), my_ms.size());
  auto my_it = my_ms.begin();
  auto orig_it = orig_ms.begin();
  for (; my_it != my_ms.end(); ++my_it, ++orig_it) {
    EXPECT_EQ(*my_it, *orig_it);
  }
}

TEST(multiset, ConstructorCopy) {
  std::multiset<int> orig_ms{1, 2, 3, 4, 1, 2, 3, 4};
  s21::multiset<int> my_ms{1, 2, 3, 4, 1, 2, 3, 4};
  std::multiset<int> orig_copy(orig_ms);
  s21::multiset<int> my_copy(my_ms);
  ASSERT_EQ(orig_copy.size(), my_copy.size());
  auto my_it = my_copy.begin();
  auto orig_it = orig_copy.begin();
  for (; my_it != my_copy.end(); ++my_it, ++orig_it) {
    EXPECT_EQ(*my_it, *orig_it);
  }
}

TEST(multiset, ConstructorMove) {
  std::multiset<int> orig_ms{1, 2, 3, 4, 1, 2, 3, 4};
  s21::multiset<int> my_ms{1, 2, 3, 4, 1, 2, 3, 4};
  std::multiset<int> orig_copy(std::move(orig_ms));
  s21::multiset<int> my_copy(std::move(my_ms));
  ASSERT_EQ(orig_copy.size(), my_copy.size());
  auto my_it = my_copy.begin();
  auto orig_it = orig_copy.begin();
  for (; my_it != my_copy.end(); ++my_it, ++orig_it) {
    EXPECT_EQ(*my_it, *orig_it);
  }
}

TEST(multiset, OperatorCopy) {
  std::multiset<int> orig_ms{1, 2, 3, 4, 1, 2, 3, 4};
  s21::multiset<int> my_ms{1, 2, 3, 4, 1, 2, 3, 4};
  std::multiset<int> orig_copy = orig_ms;
  s21::multiset<int> my_copy = my_ms;
  ASSERT_EQ(orig_copy.size(), my_copy.size());
  auto my_it = my_copy.begin();
  auto orig_it = orig_copy.begin();
  for (; my_it != my_copy.end(); ++my_it, ++orig_it) {
    EXPECT_EQ(*my_it, *orig_it);
  }
}

TEST(multiset, OperatorMove) {
  std::multiset<int> orig_ms{1, 2, 3, 4, 1, 2, 3, 4};
  s21::multiset<int> my_ms{1, 2, 3, 4, 1, 2, 3, 4};
  std::multiset<int> orig_copy = std::move(orig_ms);
  s21::multiset<int> my_copy = std::move(my_ms);
  ASSERT_EQ(orig_copy.size(), my_copy.size());
  auto my_it = my_copy.begin();
  auto orig_it = orig_copy.begin();
  for (; my_it != my_copy.end(); ++my_it, ++orig_it) {
    EXPECT_EQ(*my_it, *orig_it);
  }
}

TEST(multiset, FunctionClear) {
  s21::multiset<int> my_ms{1, 2, 3, 4, 1, 2, 3, 4};
  std::multiset<int> orig_ms{1, 2, 3, 4, 1, 2, 3, 4};

  ASSERT_EQ(my_ms.size(), orig_ms.size());
  my_ms.clear();
  orig_ms.clear();
  ASSERT_EQ(my_ms.size(), orig_ms.size());
}

TEST(multiset, FunctionInsert) {
  s21::multiset<int> my_ms{1, 2, 3, 4, 1, 2, 3, 4};
  std::multiset<int> orig_ms{1, 2, 3, 4, 1, 2, 3, 4};

  ASSERT_EQ(my_ms.size(), orig_ms.size());
  my_ms.clear();
  orig_ms.clear();
  ASSERT_EQ(my_ms.size(), orig_ms.size());

  my_ms.insert(1);
  orig_ms.insert(1);
  ASSERT_EQ(my_ms.size(), orig_ms.size());
}

TEST(multiset, FunctionErase) {
  s21::multiset<int> my_ms{1, 2, 3, 4, 1, 2, 3, 4};
  std::multiset<int> orig_ms{1, 2, 3, 4, 1, 2, 3, 4};

  ASSERT_EQ(my_ms.size(), orig_ms.size());
  auto my_it = my_ms.begin();
  auto orig_it = orig_ms.begin();
  my_it++;
  orig_it++;
  my_ms.erase(my_it);
  orig_ms.erase(orig_it);
  ASSERT_EQ(my_ms.size(), orig_ms.size());
  my_it = my_ms.begin();
  orig_it = orig_ms.begin();
  for (; my_it != my_ms.end(); ++my_it, ++orig_it) {
    EXPECT_EQ(*my_it, *orig_it);
  }
}

TEST(multiset, FunctionSwap) {
  std::multiset<int> orig_ms{1, 2, 3, 4, 1, 2, 3, 4};
  s21::multiset<int> my_ms{1, 2, 3, 4, 1, 2, 3, 4};
  std::multiset<int> orig_copy{8, 9, 10};
  s21::multiset<int> my_copy{8, 9, 10};
  ASSERT_EQ(orig_ms.size(), my_ms.size());
  ASSERT_EQ(orig_copy.size(), my_copy.size());
  orig_copy.swap(orig_ms);
  my_copy.swap(my_ms);
  ASSERT_EQ(orig_ms.size(), my_ms.size());
  ASSERT_EQ(orig_copy.size(), my_copy.size());
  auto my_it = my_ms.begin();
  auto orig_it = orig_ms.begin();
  for (; my_it != my_ms.end(); ++my_it, ++orig_it) {
    EXPECT_EQ(*my_it, *orig_it);
  }
  my_it = my_copy.begin();
  orig_it = orig_copy.begin();
  for (; my_it != my_copy.end(); ++my_it, ++orig_it) {
    EXPECT_EQ(*my_it, *orig_it);
  }
}

TEST(multiset, FunctionMerge) {
  std::multiset<int> orig_ms{1, 2, 3, 4, 1, 2, 3, 4};
  s21::multiset<int> my_ms{1, 2, 3, 4, 1, 2, 3, 4};
  std::multiset<int> orig_copy{8, 9, 10};
  s21::multiset<int> my_copy{8, 9, 10};
  ASSERT_EQ(orig_ms.size(), my_ms.size());
  ASSERT_EQ(orig_copy.size(), my_copy.size());
  orig_ms.merge(orig_copy);
  my_ms.merge(my_copy);
  ASSERT_EQ(orig_ms.size(), my_ms.size());
  ASSERT_EQ(orig_copy.size(), my_copy.size());
  auto my_it = my_ms.begin();
  auto orig_it = orig_ms.begin();
  for (; my_it != my_ms.end(); ++my_it, ++orig_it) {
    EXPECT_EQ(*my_it, *orig_it);
  }
  ASSERT_EQ(my_copy.empty(), orig_copy.empty());
}

TEST(multiset, FunctionCount) {
  s21::multiset<int> my_ms{1, 1, 2, 1, 1, 2, 1, 3, 4, 5};
  s21::multiset<int> orig_ms{1, 1, 2, 1, 1, 2, 1, 3, 4, 5};
  EXPECT_EQ(my_ms.count(1), orig_ms.count(1));
}

TEST(multiset, FunctionFind) {
  s21::multiset<int> my_ms{1, 1, 2, 1, 1, 2, 1, 3, 4, 5};
  s21::multiset<int> orig_ms{1, 1, 2, 1, 1, 2, 1, 3, 4, 5};
  EXPECT_EQ(*my_ms.find(1), *orig_ms.find(1));
  EXPECT_EQ(*my_ms.find(2), *orig_ms.find(2));
}

TEST(multiset, FunctionEqual_range) {
  s21::multiset<int> my_ms{1, 1, 1, 1, 1, 2, 3, 2, 2};
  s21::multiset<int> orig_ms{1, 1, 1, 1, 1, 2, 3, 2, 2};
  auto my_it = my_ms.equal_range(1);
  auto orig_it = orig_ms.equal_range(1);
  for (; my_it.first != my_it.second; ++my_it.first, ++orig_it.first) {
    EXPECT_EQ(*my_it.first, *orig_it.first);
  }
}

TEST(multiset, FunctionLower_bound) {
  s21::multiset<int> my_ms{1, 1, 1, 1, 1, 2, 3, 2, 2};
  s21::multiset<int> orig_ms{1, 1, 1, 1, 1, 2, 3, 2, 2};
  auto my_it = my_ms.lower_bound(2);
  auto orig_it = orig_ms.lower_bound(2);
  for (; my_it != my_ms.end(); ++my_it, ++orig_it) {
    EXPECT_EQ(*my_it, *orig_it);
  }
}

TEST(multiset, FunctionUpper_bound) {
  s21::multiset<int> my_ms{1, 1, 1, 1, 1, 2, 3, 2, 2};
  s21::multiset<int> orig_ms{1, 1, 1, 1, 1, 2, 3, 2, 2};
  auto my_it = my_ms.upper_bound(2);
  auto orig_it = orig_ms.upper_bound(2);
  for (; my_it != my_ms.end(); --my_it, --orig_it) {
    EXPECT_EQ(*my_it, *orig_it);
  }
}

TEST(multiset, Insert_many) {
  s21::multiset<int> my_ms = {1, 2, 3};

  auto vec = my_ms.insert_many(1, 4);
  EXPECT_EQ(my_ms.size(), 5);

  auto it = vec.begin();
  EXPECT_TRUE(it->second == true);
  it++;
  EXPECT_TRUE(it->second == true);
}
