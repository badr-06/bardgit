#include "../headers/main_test.h"

START_TEST(test_s21_memcmp_1) {
  char str1[] = "Hello, world!\n";
  char str2[] = "Hello, world!\n";
  int len = strlen(str2);
  int result = s21_memcmp(str1, str2, len);
  int expected = memcmp(str1, str2, len);
  ck_assert_int_eq(sign_int(result), sign_int(expected));
}
END_TEST

START_TEST(test_s21_memcmp_2) {
  char str1[] = "Hello, world!\n";
  char str2[] = "Hello";
  int len = strlen(str2);
  int result = s21_memcmp(str1, str2, len);
  int expected = memcmp(str1, str2, len);
  ck_assert_int_eq(sign_int(result), sign_int(expected));
}
END_TEST

START_TEST(test_s21_memcmp_3) {
  char str1[] = "Hello, world!\n";
  char str2[] = "Hello";
  int len = strlen(str2);
  int result = s21_memcmp(str1, str2, len);
  int expected = memcmp(str1, str2, len);
  ck_assert_int_eq(sign_int(result), sign_int(expected));
}
END_TEST

START_TEST(test_s21_memcmp_4) {
  char str1[] = "abcde";
  char str2[] = "abCde";
  int len = strlen(str2);
  int result = s21_memcmp(str1, str2, len);
  int expected = memcmp(str1, str2, len);
  ck_assert_int_eq(sign_int(result), sign_int(expected));
}
END_TEST

START_TEST(test_s21_memcmp_5) {
  char str1[] = "abcDe";
  char str2[] = "abcde";
  int len = strlen(str2);
  int result = s21_memcmp(str1, str2, len);
  int expected = memcmp(str1, str2, len);
  ck_assert_int_eq(sign_int(result), sign_int(expected));
}
END_TEST

START_TEST(test_s21_memcmp_6) {
  char str1[] = "abcDe";
  char str2[] = "abcde";
  int len = strlen(str2);
  int result = s21_memcmp(str1, str2, len);
  int expected = memcmp(str1, str2, len);
  ck_assert_int_eq(sign_int(result), sign_int(expected));
}
END_TEST

START_TEST(test_s21_memcmp_7) {
  char str1[] = "Lorem ipsum dolor sit amet consectetur.";
  char str2[] = "Lorem.";
  int len = strlen(str2);
  int result = s21_memcmp(str1, str2, len);
  int expected = memcmp(str1, str2, len);
  ck_assert_int_eq(sign_int(result), sign_int(expected));
}
END_TEST

START_TEST(test_s21_memcmp_8) {
  char str1[] = "Lorem ipsum dolor sit amet consectetur.";
  char str2[] = "Lorem.";
  int len = 5;
  int result = s21_memcmp(str1, str2, len);
  int expected = memcmp(str1, str2, len);
  ck_assert_int_eq(sign_int(result), sign_int(expected));
}
END_TEST

START_TEST(test_s21_memcmp_9) {
  char str1[] = "0123456789";
  char str2[] = "0123356789";
  int len = strlen(str2);
  int result = s21_memcmp(str1, str2, len);
  int expected = memcmp(str1, str2, len);
  ck_assert_int_eq(sign_int(result), sign_int(expected));
}
END_TEST

START_TEST(test_s21_memcmp_10) {
  char str1[] = "0123356789";
  char str2[] = "0123456789";
  int len = strlen(str2);
  int result = s21_memcmp(str1, str2, len);
  int expected = memcmp(str1, str2, len);
  ck_assert_int_eq(result, expected);
}
END_TEST

TCase *tcase_s21_memcmp(void) {
  TCase *tcase = tcase_create("s21_memcmp");
  tcase_add_test(tcase, test_s21_memcmp_1);
  tcase_add_test(tcase, test_s21_memcmp_2);
  tcase_add_test(tcase, test_s21_memcmp_3);
  tcase_add_test(tcase, test_s21_memcmp_4);
  tcase_add_test(tcase, test_s21_memcmp_5);
  tcase_add_test(tcase, test_s21_memcmp_6);
  tcase_add_test(tcase, test_s21_memcmp_7);
  tcase_add_test(tcase, test_s21_memcmp_8);
  tcase_add_test(tcase, test_s21_memcmp_9);
  tcase_add_test(tcase, test_s21_memcmp_10);

  return tcase;
}