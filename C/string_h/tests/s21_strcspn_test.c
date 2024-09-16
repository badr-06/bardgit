#include "../headers/main_test.h"

START_TEST(test_s21_strcspn_1) {
  char str1[] = "Hello, world!\n";
  char str2[] = "lvk";
  s21_size_t result = s21_strcspn(str1, str2);
  s21_size_t expected = strcspn(str1, str2);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strcspn_2) {
  char str1[] = "Hello, world!\n";
  char str2[] = "Hi";
  s21_size_t result = s21_strcspn(str1, str2);
  s21_size_t expected = strcspn(str1, str2);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strcspn_3) {
  char str1[] = "1234567890\t1234567890\n";
  char str2[] = "157";
  s21_size_t result = s21_strcspn(str1, str2);
  s21_size_t expected = strcspn(str1, str2);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strcspn_4) {
  char str1[] = "Lorem ipsum dolor sit amet consectetur.\n";
  char str2[] = "_!\t\n";
  s21_size_t result = s21_strcspn(str1, str2);
  s21_size_t expected = strcspn(str1, str2);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strcspn_5) {
  char str1[] = "Lorem ipsum dolor sit amet consectetur.\n";
  char str2[] = "123456";
  s21_size_t result = s21_strcspn(str1, str2);
  s21_size_t expected = strcspn(str1, str2);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strcspn_6) {
  char str1[] = "";
  char str2[] = "Hello";
  s21_size_t result = s21_strcspn(str1, str2);
  s21_size_t expected = strcspn(str1, str2);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strcspn_7) {
  char str1[] = "Lorem ipsum dolor sit amet consectetur.";
  char str2[] = "";
  s21_size_t result = s21_strcspn(str1, str2);
  s21_size_t expected = strcspn(str1, str2);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strcspn_8) {
  char str1[] = "";
  char str2[] = "";
  s21_size_t result = s21_strcspn(str1, str2);
  s21_size_t expected = strcspn(str1, str2);
  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strcspn_9) {
  char str1[256] = "_;,-!()*&^$#";
  char str2[12] = "abs";
  s21_size_t result = s21_strcspn(str1, str2);
  s21_size_t expected = strcspn(str1, str2);
  ck_assert_int_eq(result, expected);
}
END_TEST

TCase *tcase_s21_strcspn(void) {
  TCase *tcase = tcase_create("s21_strcspn");
  tcase_add_test(tcase, test_s21_strcspn_1);
  tcase_add_test(tcase, test_s21_strcspn_2);
  tcase_add_test(tcase, test_s21_strcspn_3);
  tcase_add_test(tcase, test_s21_strcspn_4);
  tcase_add_test(tcase, test_s21_strcspn_5);
  tcase_add_test(tcase, test_s21_strcspn_6);
  tcase_add_test(tcase, test_s21_strcspn_7);
  tcase_add_test(tcase, test_s21_strcspn_8);
  tcase_add_test(tcase, test_s21_strcspn_9);

  return tcase;
}