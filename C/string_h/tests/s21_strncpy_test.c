#include "../headers/main_test.h"

START_TEST(test_s21_strncpy_1) {
  char s21_dest[] = "Hello, world!\n";
  char dest[] = "Hello, world!\n";
  char src[] = "Hello, world!\n";
  int len = strlen(src);
  char* s21_result = s21_strncpy(s21_dest, src, len);
  char* result = strncpy(dest, src, len);
  ck_assert_ptr_eq(s21_dest, s21_result);
  ck_assert_ptr_eq(dest, result);
  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(test_s21_strncpy_2) {
  char s21_dest[] = "Hello, world!\n";
  char dest[] = "Hello, world!\n";
  char src[] = "This is";
  int len = strlen(src);
  char* s21_result = s21_strncpy(s21_dest, src, len);
  char* result = strncpy(dest, src, len);
  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(test_s21_strncpy_3) {
  char s21_dest[] = "0123456789\n";
  char dest[] = "0123456789\n";
  char src[] = "abcdefghijklm";
  int len = strlen(dest);
  char* s21_result = s21_strncpy(s21_dest, src, len);
  char* result = strncpy(dest, src, len);
  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(test_s21_strncpy_4) {
  char s21_dest[] = "Hello, world!\n";
  char dest[] = "Hello, world!\n";
  char src[] = "0123456789";
  int len = 3;
  char* s21_result = s21_strncpy(s21_dest, src, len);
  char* result = strncpy(dest, src, len);
  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(test_s21_strncpy_5) {
  char s21_dest[256] = "Lorem ipsum dolor sit amet consectetur.\n";
  char dest[256] = "Lorem ipsum dolor sit amet consectetur.\n";
  char src[] = "!2345";
  int len = strlen(src);
  char* s21_result = s21_strncpy(s21_dest, src, len);
  char* result = strncpy(dest, src, len);
  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(test_s21_strncpy_6) {
  char s21_dest[] = "\0\0\0\0\0";
  char dest[] = "\0\0\0\0\0";
  char src[] = "\0";
  int len = strlen(src);
  char* s21_result = s21_strncpy(s21_dest, src, len);
  char* result = strncpy(dest, src, len);
  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(test_s21_strncpy_7) {
  char s21_dest[] = "Lorem ipsum dolor sit amet consectetur.\n";
  char dest[] = "Lorem ipsum dolor sit amet consectetur.\n";
  char src[] = "Hello\n";
  int len = 0;
  char* s21_result = s21_strncpy(s21_dest, src, len);
  char* result = strncpy(dest, src, len);
  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(test_s21_strncpy_8) {
  char s21_dest[] = "Lorem ipsum dolor sit amet consectetur.\n";
  char dest[] = "Lorem ipsum dolor sit amet consectetur.\n";
  char src[] = "Hello\n";
  int len = strlen(src) + 5;
  char* s21_result = s21_strncpy(s21_dest, src, len);
  char* result = strncpy(dest, src, len);
  ck_assert_str_eq(s21_result, result);
}
END_TEST

TCase* tcase_s21_strncpy(void) {
  TCase* tcase = tcase_create("s21_strncpy");
  tcase_add_test(tcase, test_s21_strncpy_1);
  tcase_add_test(tcase, test_s21_strncpy_2);
  tcase_add_test(tcase, test_s21_strncpy_3);
  tcase_add_test(tcase, test_s21_strncpy_4);
  tcase_add_test(tcase, test_s21_strncpy_5);
  tcase_add_test(tcase, test_s21_strncpy_6);
  tcase_add_test(tcase, test_s21_strncpy_7);
  tcase_add_test(tcase, test_s21_strncpy_8);

  return tcase;
}