#include "../headers/main_test.h"

START_TEST(test_s21_trim_1) {
  char str1[] = "** *Hello, world!\n*  *";
  char trim_chars[] = "* ";
  char *result = s21_trim(str1, trim_chars);
  char *expected = "Hello, world!\n";
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_trim_2) {
  char str1[] = "abcd0123456789\t0123456789xyz";
  char trim_chars[] = "abcdxyz";
  char *result = s21_trim(str1, trim_chars);
  char *expected = "0123456789\t0123456789";
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_trim_3) {
  char str1[] = "=   #Lorem ipsum dolor sit amet consectetur,===";
  char trim_chars[] = "# =";
  char *result = s21_trim(str1, trim_chars);
  char *expected = "Lorem ipsum dolor sit amet consectetur,";
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_trim_4) {
  char str1[] = "--$$$000---$@";
  char trim_chars[] = "-$0@";
  char *result = s21_trim(str1, trim_chars);
  char *expected = "";
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_trim_5) {
  char str1[] = "************";
  char trim_chars[] = "*";
  char *result = s21_trim(str1, trim_chars);
  char *expected = "";
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_trim_6) {
  char *str1 = S21_NULL;
  char trim_chars[] = "*-ad";
  char *result = s21_trim(str1, trim_chars);
  ck_assert_ptr_null(result);
  free(result);
}
END_TEST

START_TEST(test_s21_trim_7) {
  char str1[] = "\n \v  \tLorem ipsum dolor sit amet consectetur.\r \t";
  char trim_chars[] = "";
  char *result = s21_trim(str1, trim_chars);
  char *expected = "\n \v  \tLorem ipsum dolor sit amet consectetur.\r \t";
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_trim_8) {
  char str1[] = "\n \v  \tLorem ipsum dolor sit amet consectetur.\r \t";
  char *trim_chars = S21_NULL;
  char *result = s21_trim(str1, trim_chars);
  ck_assert_ptr_null(result);
  free(result);
}
END_TEST

TCase *tcase_s21_trim(void) {
  TCase *tcase = tcase_create("s21_trim");
  tcase_add_test(tcase, test_s21_trim_1);
  tcase_add_test(tcase, test_s21_trim_2);
  tcase_add_test(tcase, test_s21_trim_3);
  tcase_add_test(tcase, test_s21_trim_4);
  tcase_add_test(tcase, test_s21_trim_5);
  tcase_add_test(tcase, test_s21_trim_6);
  tcase_add_test(tcase, test_s21_trim_7);
  tcase_add_test(tcase, test_s21_trim_8);

  return tcase;
}