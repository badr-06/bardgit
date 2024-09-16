#include "../headers/main_test.h"

START_TEST(test_s21_strpbrk_1) {
  char str1[] = "Hello, world!\n";
  char str2[] = "He";
  char *result = s21_strpbrk(str1, str2);
  char *expected = strpbrk(str1, str2);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strpbrk_2) {
  char str1[] = "1234567890\t1234567890\n";
  char str2[] = "567";
  char *result = s21_strpbrk(str1, str2);
  char *expected = strpbrk(str1, str2);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strpbrk_3) {
  char str1[] = "Lorem ipsum dolor sit amet consectetur.\n";
  char str2[] = "\n";
  char *result = s21_strpbrk(str1, str2);
  char *expected = strpbrk(str1, str2);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strpbrk_4) {
  char str1[] = "Lorem ipsum dolor sit amet consectetur.\n";
  char str2[] = "ur.";
  char *result = s21_strpbrk(str1, str2);
  char *expected = strpbrk(str1, str2);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strpbrk_5) {
  char str1[256] = "Lorem ipsum dolor\tsit amet consectetur.\n";
  char str2[5] = "\t";
  char *result = s21_strpbrk(str1, str2);
  char *expected = strpbrk(str1, str2);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strpbrk_6) {
  char str1[] = "";
  char str2[] = "Ok";
  char *result = s21_strpbrk(str1, str2);
  char *expected = strpbrk(str1, str2);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strpbrk_7) {
  char str1[] = "Hello, world!\n";
  char str2[] = "";
  char *result = s21_strpbrk(str1, str2);
  char *expected = strpbrk(str1, str2);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strpbrk_8) {
  char str1[] = "Lorem ipsum dolor sit amet.\n";
  char str2[] = "_!_";
  char *result = s21_strpbrk(str1, str2);
  char *expected = strpbrk(str1, str2);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

START_TEST(test_s21_strpbrk_9) {
  char str1[] = "1234567890\t1234567890\n";
  char str2[] = "789 ";
  char *result = s21_strpbrk(str1, str2);
  char *expected = strpbrk(str1, str2);
  ck_assert_ptr_eq(result, expected);
}
END_TEST

TCase *tcase_s21_strpbrk(void) {
  TCase *tcase = tcase_create("s21_strpbrk");
  tcase_add_test(tcase, test_s21_strpbrk_1);
  tcase_add_test(tcase, test_s21_strpbrk_2);
  tcase_add_test(tcase, test_s21_strpbrk_3);
  tcase_add_test(tcase, test_s21_strpbrk_4);
  tcase_add_test(tcase, test_s21_strpbrk_5);
  tcase_add_test(tcase, test_s21_strpbrk_6);
  tcase_add_test(tcase, test_s21_strpbrk_7);
  tcase_add_test(tcase, test_s21_strpbrk_8);
  tcase_add_test(tcase, test_s21_strpbrk_9);

  return tcase;
}