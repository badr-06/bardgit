#include "../headers/main_test.h"

START_TEST(test_s21_strstr_1) {
  char str1[] = "Hello, world!\n";
  char str2[] = " wo";
  char *result = s21_strstr(str1, str2);
  char *expected = strstr(str1, str2);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strstr_2) {
  char str1[] = "Hello, world!\tIt's a good day\n";
  char str2[] = "!\t";
  char *result = s21_strstr(str1, str2);
  char *expected = strstr(str1, str2);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strstr_3) {
  char str1[] = "0123456789\n0123456789";
  char str2[] = "789";
  char *result = s21_strstr(str1, str2);
  char *expected = strstr(str1, str2);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strstr_4) {
  char str1[] = "Hello! My name is Henry\n";
  char str2[] = "He";
  char *result = s21_strstr(str1, str2);
  char *expected = strstr(str1, str2);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strstr_5) {
  char str1[] = "";
  char str2[] = "abc";
  char *result = s21_strstr(str1, str2);
  char *expected = strstr(str1, str2);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strstr_6) {
  char str1[] = "";
  char str2[] = "abc";
  char *result = s21_strstr(str1, str2);
  char *expected = strstr(str1, str2);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strstr_7) {
  char str1[] =
      "Lorem ipsum dolor sit amet consectetur, adipisicing elit.Veniam, \
      totam !";
  char str2[] = "";
  char *result = s21_strstr(str1, str2);
  char *expected = strstr(str1, str2);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strstr_8) {
  char str1[] = "Lorem ipsum dolor sit amet.";
  char str2[] = "amet";
  char *result = s21_strstr(str1, str2);
  char *expected = strstr(str1, str2);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strstr_9) {
  char str1[] = "Lorem ipsum dolor sit amet.";
  char str2[] = "127";
  char *result = s21_strstr(str1, str2);
  char *expected = strstr(str1, str2);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strstr_10) {
  char str1[50] = "Lorem ipsum dolor sit amet.";
  char str2[50] = "Lorem ipsum dolor sit amet.";
  char *result = s21_strstr(str1, str2);
  char *expected = strstr(str1, str2);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

TCase *tcase_s21_strstr(void) {
  TCase *tcase = tcase_create("s21_strstr");
  tcase_add_test(tcase, test_s21_strstr_1);
  tcase_add_test(tcase, test_s21_strstr_2);
  tcase_add_test(tcase, test_s21_strstr_3);
  tcase_add_test(tcase, test_s21_strstr_4);
  tcase_add_test(tcase, test_s21_strstr_5);
  tcase_add_test(tcase, test_s21_strstr_6);
  tcase_add_test(tcase, test_s21_strstr_7);
  tcase_add_test(tcase, test_s21_strstr_8);
  tcase_add_test(tcase, test_s21_strstr_9);
  tcase_add_test(tcase, test_s21_strstr_10);

  return tcase;
}