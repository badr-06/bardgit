#include "../headers/main_test.h"

START_TEST(test_s21_strrchr_1) {
  char str[] = "Hello, world!\n";
  char c = ',';
  char* result = s21_strrchr(str, c);
  char* expected = strrchr(str, c);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strrchr_2) {
  char str[] = "Hello, world!\n";
  char c = 'H';
  char* result = s21_strrchr(str, c);
  char* expected = strrchr(str, c);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strrchr_3) {
  char str[] = "Hello, world!\n";
  char c = '\n';
  char* result = s21_strrchr(str, c);
  char* expected = strrchr(str, c);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strrchr_4) {
  char str[] = "1234567890\t1234567890\n";
  char c = '9';
  char* result = s21_strrchr(str, c);
  char* expected = strrchr(str, c);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strrchr_5) {
  char str[] = "Lorem ipsum dolor sit amet consectetur.\n";
  char c = '7';
  char* result = s21_strrchr(str, c);
  char* expected = strrchr(str, c);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strrchr_6) {
  char str[256] = "";
  char c = 'a';
  char* result = s21_strrchr(str, c);
  char* expected = strrchr(str, c);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strrchr_7) {
  char str[] = "Lorem ipsum dolor\0sit amet consectetur.\n";
  char c = '.';
  char* result = s21_strrchr(str, c);
  char* expected = strrchr(str, c);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strrchr_8) {
  char str[] = "Lorem ipsum dolor\tsittamet\tconsectetur.\n";
  char c = '\t';
  char* result = s21_strrchr(str, c);
  char* expected = strrchr(str, c);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strrchr_9) {
  char str[] = "\0\0\0";
  char c = '\0';
  char* result = s21_strrchr(str, c);
  char* expected = strrchr(str, c);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

TCase* tcase_s21_strrchr(void) {
  TCase* tcase = tcase_create("s21_strrchr");
  tcase_add_test(tcase, test_s21_strrchr_1);
  tcase_add_test(tcase, test_s21_strrchr_2);
  tcase_add_test(tcase, test_s21_strrchr_3);
  tcase_add_test(tcase, test_s21_strrchr_4);
  tcase_add_test(tcase, test_s21_strrchr_5);
  tcase_add_test(tcase, test_s21_strrchr_6);
  tcase_add_test(tcase, test_s21_strrchr_7);
  tcase_add_test(tcase, test_s21_strrchr_8);
  tcase_add_test(tcase, test_s21_strrchr_9);

  return tcase;
}