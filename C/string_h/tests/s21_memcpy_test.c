#include "../headers/main_test.h"

START_TEST(test_s21_memcpy_1) {
  char s21_dest[] = "Hello, world!\n";
  char dest[] = "Hello, world!\n";
  char src[] = "Hello, world!\n";
  int len = strlen(src) + 1;
  char* s21_result = s21_memcpy(s21_dest, src, len);
  char* result = memcpy(dest, src, len);
  ck_assert_ptr_eq(dest, result);
  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(test_s21_memcpy_2) {
  char s21_dest[] = "Lorem ipsum dolor sit amet consectetur.";
  char dest[] = "Lorem ipsum dolor sit amet consectetur.";
  char src[] = "123456";
  int len = strlen(src);
  char* s21_result = s21_memcpy(s21_dest, src, len);
  char* result = memcpy(dest, src, len);
  ck_assert_ptr_eq(dest, result);
  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(test_s21_memcpy_3) {
  char s21_dest[] = "1234567890\t1234567890\n";
  char dest[] = "1234567890\t1234567890\n";
  char src[] = "absolute";
  int len = strlen(src) - 2;
  char* s21_result = s21_memcpy(s21_dest, src, len);
  char* result = memcpy(dest, src, len);
  ck_assert_ptr_eq(dest, result);
  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(test_s21_memcpy_4) {
  char s21_dest[64] = "";
  char dest[64] = "";
  char src[] = "Hello\n";
  int len = strlen(src) + 1;
  char* s21_result = s21_memcpy(s21_dest, src, len);
  char* result = memcpy(dest, src, len);
  ck_assert_ptr_eq(dest, result);
  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(test_s21_memcpy_5) {
  char s21_dest[] = "Lorem ipsum dolor sit amet consectetur.\n";
  char dest[] = "Lorem ipsum dolor sit amet consectetur.\n";
  char src[] = "Hello\n";
  int len = 0;
  char* s21_result = s21_memcpy(s21_dest, src, len);
  char* result = memcpy(dest, src, len);
  ck_assert_ptr_eq(dest, result);
  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(test_s21_memcpy_6) {
  char s21_dest[] = "\0\0\0\0\0";
  char dest[] = "\0\0\0\0\0";
  char src[] = "\0";
  int len = 1;
  char* s21_result = s21_memcpy(s21_dest, src, len);
  char* result = memcpy(dest, src, len);
  ck_assert_ptr_eq(dest, result);
  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(test_s21_memcpy_7) {
  char s21_dest[] = "Lorem ipsum dolor sit amet consectetur.\n";
  char dest[] = "Lorem ipsum dolor sit amet consectetur.\n";
  char src[] = "!234";
  int len = 1;
  char* s21_result = s21_memcpy(s21_dest, src, len);
  char* result = memcpy(dest, src, len);
  ck_assert_ptr_eq(dest, result);
  ck_assert_str_eq(s21_result, result);
}
END_TEST

TCase* tcase_s21_memcpy(void) {
  TCase* tcase = tcase_create("s21_memcpy");
  tcase_add_test(tcase, test_s21_memcpy_1);
  tcase_add_test(tcase, test_s21_memcpy_2);
  tcase_add_test(tcase, test_s21_memcpy_3);
  tcase_add_test(tcase, test_s21_memcpy_4);
  tcase_add_test(tcase, test_s21_memcpy_5);
  tcase_add_test(tcase, test_s21_memcpy_6);
  tcase_add_test(tcase, test_s21_memcpy_7);

  return tcase;
}