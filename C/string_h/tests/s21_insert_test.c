#include "../headers/main_test.h"

START_TEST(test_s21_insert_1) {
  char src[] = "Hello, world!\n";
  char str[] = "my ";
  s21_size_t start_index = 7;
  char *result = s21_insert(src, str, start_index);
  char *expected = "Hello, my world!\n";
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_insert_2) {
  char src[] = "world!\n";
  char str[] = "Hello, ";
  s21_size_t start_index = 0;
  char *result = s21_insert(src, str, start_index);
  char *expected = "Hello, world!\n";
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_insert_3) {
  char src[] = "Hello";
  char str[] = ", world!\n";
  s21_size_t start_index = 5;
  char *result = s21_insert(src, str, start_index);
  char *expected = "Hello, world!\n";
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_insert_4) {
  char src[] = "1234567 8910";
  char str[] = "xyz ";
  s21_size_t start_index = 8;
  char *result = s21_insert(src, str, start_index);
  char *expected = "1234567 xyz 8910";
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_insert_5) {
  char *src = "Lorem ipsum dolor sit amet consectetur.";
  char *str = S21_NULL;
  s21_size_t start_index = 0;
  char *result = s21_insert(src, str, start_index);
  ck_assert_ptr_null(result);
  free(result);
}
END_TEST

START_TEST(test_s21_insert_6) {
  char *src = S21_NULL;
  char *str = "S21_NULL";
  s21_size_t start_index = 0;
  char *result = s21_insert(src, str, start_index);
  ck_assert_ptr_null(result);
  free(result);
}
END_TEST

START_TEST(test_s21_insert_7) {
  char src[] = "Hello";
  char str[] = ", world!\n";
  s21_size_t start_index = 6;
  char *result = s21_insert(src, str, start_index);
  ck_assert_ptr_null(result);
  free(result);
}
END_TEST

START_TEST(test_s21_insert_8) {
  char src[] = "";
  char str[] = "";
  s21_size_t start_index = 0;
  char *result = s21_insert(src, str, start_index);
  char *expected = "";
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

TCase *tcase_s21_insert(void) {
  TCase *tcase = tcase_create("s21_insert");
  tcase_add_test(tcase, test_s21_insert_1);
  tcase_add_test(tcase, test_s21_insert_2);
  tcase_add_test(tcase, test_s21_insert_3);
  tcase_add_test(tcase, test_s21_insert_4);
  tcase_add_test(tcase, test_s21_insert_5);
  tcase_add_test(tcase, test_s21_insert_6);
  tcase_add_test(tcase, test_s21_insert_7);
  tcase_add_test(tcase, test_s21_insert_8);

  return tcase;
}