#include "../headers/main_test.h"

START_TEST(test_s21_strncat_1) {
  char s21_dest[256] = "Hello, world!";
  char dest[256] = "Hello, world!";
  char src[] = "\nMy name is Henry";
  int len = strlen(src);
  char *s21_result = s21_strncat(s21_dest, src, len);
  char *result = strncat(dest, src, len);
  ck_assert_ptr_eq(s21_result, s21_dest);
  ck_assert_ptr_eq(result, dest);
  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(test_s21_strncat_2) {
  char s21_dest[10] = "";
  char dest[10] = "";
  char src[] = "123";
  int len = strlen(src);
  char *s21_result = s21_strncat(s21_dest, src, len);
  char *result = strncat(dest, src, len);
  ck_assert_ptr_eq(s21_result, s21_dest);
  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(test_s21_strncat_3) {
  char s21_dest[256] = "Lorem ipsum dolor sit amet consectetur.\n";
  char dest[256] = "Lorem ipsum dolor sit amet consectetur.\n";
  char src[10] = " ";
  int len = 10;
  char *s21_result = s21_strncat(s21_dest, src, len);
  char *result = strncat(dest, src, len);
  ck_assert_ptr_eq(s21_result, s21_dest);
  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(test_s21_strncat_4) {
  char s21_dest[] = "\0\0\0";
  char dest[] = "\0\0\0";
  char src[] = "^";
  int len = strlen(src);
  char *s21_result = s21_strncat(s21_dest, src, len);
  char *result = strncat(dest, src, len);
  ck_assert_ptr_eq(s21_result, s21_dest);
  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(test_s21_strncat_5) {
  char s21_dest[128] = "Hello, world!";
  char dest[128] = "Hello, world!";
  char src[] = "Hi, my name is Harry";
  int len = 5;
  char *s21_result = s21_strncat(s21_dest, src, len);
  char *result = strncat(dest, src, len);
  ck_assert_ptr_eq(s21_result, s21_dest);
  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(test_s21_strncat_6) {
  char s21_dest[128] = "Lorem ipsum dolor sit amet consectetur.\n";
  char dest[128] = "Lorem ipsum dolor sit amet consectetur.\n";
  char src[] = "";
  int len = strlen(src);
  char *s21_result = s21_strncat(s21_dest, src, len);
  char *result = strncat(dest, src, len);
  ck_assert_ptr_eq(s21_result, s21_dest);
  ck_assert_str_eq(s21_result, result);
}
END_TEST

START_TEST(test_s21_strncat_7) {
  char s21_dest[128] = "";
  char dest[128] = "";
  char src[] = "1234567890\t1234567890";
  int len = 11;
  char *s21_result = s21_strncat(s21_dest, src, len);
  char *result = strncat(dest, src, len);
  ck_assert_ptr_eq(s21_result, s21_dest);
  ck_assert_str_eq(s21_result, result);
}
END_TEST

TCase *tcase_s21_strncat(void) {
  TCase *tcase = tcase_create("s21_strccat");
  tcase_add_test(tcase, test_s21_strncat_1);
  tcase_add_test(tcase, test_s21_strncat_2);
  tcase_add_test(tcase, test_s21_strncat_3);
  tcase_add_test(tcase, test_s21_strncat_4);
  tcase_add_test(tcase, test_s21_strncat_5);
  tcase_add_test(tcase, test_s21_strncat_6);
  tcase_add_test(tcase, test_s21_strncat_7);

  return tcase;
}