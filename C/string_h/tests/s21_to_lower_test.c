#include "../headers/main_test.h"

START_TEST(test_s21_to_lower_1) {
  char str[] = "HeLLO, WoRlD!\n";
  char *result = s21_to_lower(str);
  char *expected = "hello, world!\n";
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_to_lower_2) {
  char *str = "ZXCVBNMLKJ_HGFDSAQWER_TYUIOP";
  char *result = s21_to_lower(str);
  char *expected = "zxcvbnmlkj_hgfdsaqwer_tyuiop";
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_to_lower_3) {
  char *str = "HELLO\nMy name\tis HENRY.\n";
  char *result = s21_to_lower(str);
  char *expected = "hello\nmy name\tis henry.\n";
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_to_lower_4) {
  char *str = "0123456789\t0123456789\v";
  char *result = s21_to_lower(str);
  char *expected = "0123456789\t0123456789\v";
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_to_lower_5) {
  char *str = "";
  char *result = s21_to_lower(str);
  char *expected = "";
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_to_lower_6) {
  char str[] = "hello, world!\n";
  char *result = s21_to_lower(str);
  char *expected = "hello, world!\n";
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_to_lower_7) {
  char *str = S21_NULL;
  char *result = s21_to_lower(str);
  ck_assert_ptr_null(result);
  free(result);
}
END_TEST

TCase *tcase_s21_to_lower(void) {
  TCase *tcase = tcase_create("s21_to_lower");
  tcase_add_test(tcase, test_s21_to_lower_1);
  tcase_add_test(tcase, test_s21_to_lower_2);
  tcase_add_test(tcase, test_s21_to_lower_3);
  tcase_add_test(tcase, test_s21_to_lower_4);
  tcase_add_test(tcase, test_s21_to_lower_5);
  tcase_add_test(tcase, test_s21_to_lower_6);
  tcase_add_test(tcase, test_s21_to_lower_7);

  return tcase;
}