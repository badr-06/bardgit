#include "../headers/main_test.h"

START_TEST(test_s21_strncmp_1) {
  char str1[] = "Hello, world!\n";
  char str2[] = "Hello, world!\n";
  int len = strlen(str2);
  int result = s21_strncmp(str1, str2, len);
  int expected = strncmp(str1, str2, len);
  ck_assert_int_eq(sign_int(result), sign_int(expected));
}
END_TEST

START_TEST(test_s21_strncmp_2) {
  char str1[] = "Hello, world!\n";
  char str2[] = "Hello!";
  int len = strlen(str2) - 1;
  int result = s21_strncmp(str1, str2, len);
  int expected = strncmp(str1, str2, len);
  ck_assert_int_eq(sign_int(result), sign_int(expected));
}
END_TEST

START_TEST(test_s21_strncmp_3) {
  char str1[] = "Hello, world!\n";
  char str2[] = "Hello.";
  int len = strlen(str2);
  int result = s21_strncmp(str1, str2, len);
  int expected = strncmp(str1, str2, len);
  ck_assert_int_eq(sign_int(result), sign_int(expected));
}
END_TEST

START_TEST(test_s21_strncmp_4) {
  char str1[] = "abcde";
  char str2[] = "abCde.";
  int len = strlen(str2);
  int result = s21_strncmp(str1, str2, len);
  int expected = strncmp(str1, str2, len);
  ck_assert_int_eq(sign_int(result), sign_int(expected));
}
END_TEST

START_TEST(test_s21_strncmp_5) {
  char str1[] = "abcDe";
  char str2[] = "abcde.";
  int len = strlen(str2);
  int result = s21_strncmp(str1, str2, len);
  int expected = strncmp(str1, str2, len);
  ck_assert_int_eq(sign_int(result), sign_int(expected));
}
END_TEST

START_TEST(test_s21_strncmp_6) {
  char str1[] = "0123456789";
  char str2[] = "0123356789";
  int len = strlen(str2);
  int result = s21_strncmp(str1, str2, len);
  int expected = strncmp(str1, str2, len);
  ck_assert_int_eq(sign_int(result), sign_int(expected));
}
END_TEST

START_TEST(test_s21_strncmp_7) {
  char str1[] = "0123446789";
  char str2[] = "0123456789";
  int len = strlen(str2);
  int result = s21_strncmp(str1, str2, len);
  int expected = strncmp(str1, str2, len);
  ck_assert_int_eq(sign_int(result), sign_int(expected));
}
END_TEST

START_TEST(test_s21_strncmp_8) {
  char str1[] = "Lorem ipsum dolor sit amet consectetur.\n";
  char str2[] = "Lorem ipsum\tdolor sit amet consectetur.\n";
  int len = 15;
  int result = s21_strncmp(str1, str2, len);
  int expected = strncmp(str1, str2, len);
  ck_assert_int_eq(sign_int(result), sign_int(expected));
}
END_TEST

START_TEST(test_s21_strncmp_9) {
  char str1[] = "Lorem ipsum dolor sit amet consectetur.\n";
  char str2[] = "Lorem ipsum\tdolor sit amet consectetur.\n";
  int len = 5;
  int result = s21_strncmp(str1, str2, len);
  int expected = strncmp(str1, str2, len);
  ck_assert_int_eq(sign_int(result), sign_int(expected));
}
END_TEST

START_TEST(test_s21_strncmp_10) {
  char str1[] = "";
  char str2[] = "Lorem.";
  int len = strlen(str2);
  int result = s21_strncmp(str1, str2, len);
  int expected = strncmp(str1, str2, len);
  ck_assert_int_eq(sign_int(result), sign_int(expected));
}
END_TEST

START_TEST(test_s21_strncmp_11) {
  char str1[] = "Lorem ipsum dolor sit amet consectetur.\n";
  char str2[] = "";
  int len = 1;
  int result = s21_strncmp(str1, str2, len);
  int expected = strncmp(str1, str2, len);
  ck_assert_int_eq(sign_int(result), sign_int(expected));
}
END_TEST

TCase* tcase_s21_strncmp(void) {
  TCase* tcase = tcase_create("s21_strncmp");
  tcase_add_test(tcase, test_s21_strncmp_1);
  tcase_add_test(tcase, test_s21_strncmp_2);
  tcase_add_test(tcase, test_s21_strncmp_3);
  tcase_add_test(tcase, test_s21_strncmp_4);
  tcase_add_test(tcase, test_s21_strncmp_5);
  tcase_add_test(tcase, test_s21_strncmp_6);
  tcase_add_test(tcase, test_s21_strncmp_7);
  tcase_add_test(tcase, test_s21_strncmp_8);
  tcase_add_test(tcase, test_s21_strncmp_9);
  tcase_add_test(tcase, test_s21_strncmp_10);
  tcase_add_test(tcase, test_s21_strncmp_11);

  return tcase;
}