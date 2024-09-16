#include "../headers/main_test.h"

START_TEST(test_s21_strtok_1) {
  char str1[] = "Hello, world!\n";
  char str2[] = "Hello, world!\n";
  char delim[] = ", ";

  char *result = s21_strtok(str1, delim);
  char *expected = strtok(str2, delim);
  while (result != S21_NULL || expected != NULL) {
    ck_assert_str_eq(result, expected);
    result = s21_strtok(S21_NULL, delim);
    expected = strtok(NULL, delim);
  }
}
END_TEST

START_TEST(test_s21_strtok_2) {
  char str1[] = "Hello, world!\n";
  char str2[] = "Hello, world!\n";
  char delim[] = "";

  char *result = s21_strtok(str1, delim);
  char *expected = strtok(str2, delim);
  while (result != S21_NULL || expected != NULL) {
    ck_assert_str_eq(result, expected);
    result = s21_strtok(S21_NULL, delim);
    expected = strtok(NULL, delim);
  }
}
END_TEST

START_TEST(test_s21_strtok_3) {
  char str1[] = " b ";
  char str2[] = " b ";
  char delim[] = "b";

  char *result = s21_strtok(str1, delim);
  char *expected = strtok(str2, delim);
  ck_assert_str_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strtok_4) {
  char str1[] = "Hello     is   my   new  string.";
  char str2[] = "Hello     is   my   new  string.";
  char delim[] = "i";

  char *result = s21_strtok(str1, delim);
  char *expected = strtok(str2, delim);
  while (result != S21_NULL || expected != NULL) {
    ck_assert_str_eq(result, expected);
    result = s21_strtok(S21_NULL, delim);
    expected = strtok(NULL, delim);
  }
}
END_TEST

START_TEST(test_s21_strtok_5) {
  char str1[] = "";
  char str2[] = "";
  char delim[] = " ,.-";

  char *result = s21_strtok(str1, delim);
  char *expected = strtok(str2, delim);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strtok_6) {
  char str1[] = ",,!./Hello, world!\n..,!/";
  char str2[] = ",,!./Hello, world!\n..,!/";
  char delim[] = "!";

  char *result = s21_strtok(str1, delim);
  char *expected = strtok(str2, delim);
  while (result != S21_NULL || expected != NULL) {
    ck_assert_str_eq(result, expected);
    result = s21_strtok(S21_NULL, delim);
    expected = strtok(NULL, delim);
  }
}
END_TEST

TCase *tcase_s21_strtok(void) {
  TCase *tcase = tcase_create("s21_strtok");
  tcase_add_test(tcase, test_s21_strtok_1);
  tcase_add_test(tcase, test_s21_strtok_2);
  tcase_add_test(tcase, test_s21_strtok_3);
  tcase_add_test(tcase, test_s21_strtok_4);
  tcase_add_test(tcase, test_s21_strtok_5);
  tcase_add_test(tcase, test_s21_strtok_6);

  return tcase;
}
