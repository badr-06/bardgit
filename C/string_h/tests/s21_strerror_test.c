#include "../headers/main_test.h"

START_TEST(test_s21_strerror_1) {
  for (int i = 1; i < 100; i++) {
    char *s21_error = s21_strerror(i);
    char *std_error = strerror(i);
    ck_assert_str_eq(s21_error, std_error);
  }
}
END_TEST

START_TEST(test_s21_strerror_2) {
  int error = 138;
  char *s21_error = s21_strerror(error);
  char *std_error = strerror(error);
  ck_assert_str_eq(s21_error, std_error);
}
END_TEST

START_TEST(test_s21_strerror_3) {
  int error = -1;
  char *s21_error = s21_strerror(error);
  char *std_error = strerror(error);
  ck_assert_str_eq(s21_error, std_error);
}
END_TEST

START_TEST(test_s21_strerror_4) {
  int error = 0;
  char *s21_error = s21_strerror(error);
  char *std_error = strerror(error);
  ck_assert_str_eq(s21_error, std_error);
}
END_TEST

START_TEST(test_s21_strerror_5) {
  int error = 255;
  char *s21_error = s21_strerror(error);
  char *std_error = strerror(error);
  ck_assert_str_eq(s21_error, std_error);
}
END_TEST

TCase *tcase_s21_strerror(void) {
  TCase *tcase = tcase_create("s21_strerror");
  tcase_add_test(tcase, test_s21_strerror_1);
  tcase_add_test(tcase, test_s21_strerror_2);
  tcase_add_test(tcase, test_s21_strerror_3);
  tcase_add_test(tcase, test_s21_strerror_4);
  tcase_add_test(tcase, test_s21_strerror_5);

  return tcase;
}
