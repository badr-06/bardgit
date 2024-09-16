#include "../headers/main_test.h"

START_TEST(test_s21_memset_1) {
  char s21_str[] = "Hello, world!\n";
  char str[] = "Hello, world!\n";
  char c = 'c';
  int n = 4;
  char* s21_result = s21_memset(s21_str, c, n);
  char* result = memset(str, c, n);
  ck_assert_ptr_eq(s21_result, s21_str);
  ck_assert_ptr_eq(result, str);
  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(test_s21_memset_2) {
  char s21_str[] = "0123456789\t0123456789\n";
  char str[] = "0123456789\t0123456789\n";
  char c = '*';
  int n = 9;
  char* s21_result = s21_memset(s21_str, c, n);
  char* result = memset(str, c, n);
  ck_assert_ptr_eq(s21_result, s21_str);
  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(test_s21_memset_3) {
  char s21_str[] = "Lorem ipsum dolor sit amet consectetur.";
  char str[] = "Lorem ipsum dolor sit amet consectetur.";
  char c = '\n';
  int n = strlen(str);
  char* s21_result = s21_memset(s21_str, c, n);
  char* result = memset(str, c, n);
  ck_assert_ptr_eq(s21_result, s21_str);
  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(test_s21_memset_4) {
  char s21_str[] = "Lorem ipsum dolor sit amet consectetur.";
  char str[] = "Lorem ipsum dolor sit amet consectetur.";
  char c = '.';
  int n = 1;
  char* s21_result = s21_memset(s21_str, c, n);
  char* result = memset(str, c, n);
  ck_assert_ptr_eq(s21_result, s21_str);
  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(test_s21_memset_5) {
  char s21_str[] = "\0\0\0\0\0";
  char str[] = "\0\0\0\0\0";
  char c = '\0';
  int n = 1;
  char* s21_result = s21_memset(s21_str, c, n);
  char* result = memset(str, c, n);
  ck_assert_ptr_eq(s21_result, s21_str);
  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(test_s21_memset_6) {
  char s21_str[] = "0123356789";
  char str[] = "0123356789";
  char c = '\04';
  int n = strlen(str);
  char* s21_result = s21_memset(s21_str, c, n);
  char* result = memset(str, c, n);
  ck_assert_ptr_eq(s21_result, s21_str);
  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(test_s21_memset_7) {
  char s21_str[] = "Lorem ipsum dolor sit amet consectetur.";
  char str[] = "Lorem ipsum dolor sit amet consectetur.";
  char c = '^';
  int n = 7;
  char* s21_result = s21_memset(s21_str, c, n);
  char* result = memset(str, c, n);
  ck_assert_ptr_eq(s21_result, s21_str);
  ck_assert_str_eq(s21_result, result);
}
END_TEST

TCase* tcase_s21_memset(void) {
  TCase* tcase = tcase_create("s21_memset");
  tcase_add_test(tcase, test_s21_memset_1);
  tcase_add_test(tcase, test_s21_memset_2);
  tcase_add_test(tcase, test_s21_memset_3);
  tcase_add_test(tcase, test_s21_memset_4);
  tcase_add_test(tcase, test_s21_memset_5);
  tcase_add_test(tcase, test_s21_memset_6);
  tcase_add_test(tcase, test_s21_memset_7);

  return tcase;
}