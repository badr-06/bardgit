#include "../headers/main_test.h"

START_TEST(add_null_test_0) {
  s21_decimal num1 = {{7, 4, 1, 0}};
  s21_decimal num2 = {{5, 2, 0, 0}};
  ck_assert_int_eq(NULL_PTR, s21_add(num1, num2, NULL));
}
END_TEST

START_TEST(sub_null_test_0) {
  s21_decimal num1 = {{7, 4, 1, 0}};
  s21_decimal num2 = {{5, 2, 0, 0}};
  ck_assert_int_eq(NULL_PTR, s21_sub(num1, num2, NULL));
}
END_TEST

START_TEST(add_null_test) {
  s21_big_decimal num1 = {{7, 4}, 1, 13};
  s21_big_decimal num2 = {{5, 2}, 0, 0};
  ck_assert_int_eq(NULL_PTR, s21_big_add(num1, num2, NULL));
}
END_TEST

START_TEST(sub_null_test) {
  s21_big_decimal num1 = {{7, 4}, 1, 13};
  s21_big_decimal num2 = {{5, 2}, 0, 0};
  ck_assert_int_eq(NULL_PTR, s21_big_sub(num1, num2, NULL));
}
END_TEST

START_TEST(simple_add_1) {
  s21_big_decimal num1 = {{0, 0}, 0, 0};
  s21_big_decimal num2 = {{0, 0}, 0, 0};
  s21_big_decimal expected = {{0, 0}, 0, 0};
  s21_big_decimal result = {{0, 0}, 0, 0};
  ck_assert_int_eq(SUCCESS, s21_big_add(num1, num2, &result));
  ck_assert_int_eq(TRUE, s21_big_is_equal(result, expected));
}
END_TEST

START_TEST(simple_add_2) {
  s21_big_decimal num1 = {{0, 321}, 0, 0};
  s21_big_decimal num2 = {{0, 444}, 0, 0};
  s21_big_decimal expected = {{0, 321 + 444}, 0, 0};
  s21_big_decimal result = {{0, 0}, 0, 0};
  ck_assert_int_eq(SUCCESS, s21_big_add(num1, num2, &result));
  ck_assert_int_eq(TRUE, s21_big_is_equal(result, expected));
}
END_TEST

START_TEST(simple_add_3) {
  s21_big_decimal num1 = {{0, INT_MAX}, 0, 0};
  s21_big_decimal num2 = {{0, (INT_MAX + 1ul)}, 0, 0};
  s21_big_decimal expected = {{0, UINT_MAX}, 0, 0};
  s21_big_decimal result = {{0, 0}, 0, 0};
  ck_assert_int_eq(SUCCESS, s21_big_add(num1, num2, &result));
  ck_assert_int_eq(TRUE, s21_big_is_equal(result, expected));
}
END_TEST

START_TEST(simple_add_4) {
  s21_big_decimal num1 = {{0, LONG_MAX}, 0, 0};
  s21_big_decimal num2 = {{0, (LONG_MAX + 1ul)}, 0, 0};
  s21_big_decimal expected = {{0, ULONG_MAX}, 0, 0};
  s21_big_decimal result = {{0, 0}, 0, 0};
  ck_assert_int_eq(SUCCESS, s21_big_add(num1, num2, &result));
  ck_assert_int_eq(TRUE, s21_big_is_equal(result, expected));
}
END_TEST

START_TEST(simple_add_5) {
  s21_big_decimal num1 = {{0, ULONG_MAX}, 0, 0};
  s21_big_decimal num2 = {{0, 1}, 0, 0};
  s21_big_decimal expected = {{1, 0}, 0, 0};
  s21_big_decimal result = {{0, 0}, 0, 0};
  ck_assert_int_eq(SUCCESS, s21_big_add(num1, num2, &result));
  ck_assert_int_eq(TRUE, s21_big_is_equal(result, expected));
}
END_TEST

START_TEST(simple_add_6) {
  s21_big_decimal num1 = {{UINT_MAX, 0}, 0, 0};
  s21_big_decimal num2 = {{0, ULONG_MAX}, 0, 0};
  s21_big_decimal expected = {{UINT_MAX, ULONG_MAX}, 0, 0};
  s21_big_decimal result = {{0, 0}, 0, 0};
  ck_assert_int_eq(SUCCESS, s21_big_add(num1, num2, &result));
  ck_assert_int_eq(TRUE, s21_big_is_equal(result, expected));
}
END_TEST

START_TEST(simple_add_7) {
  s21_big_decimal num1 = {{355, 0}, 0, 0};
  s21_big_decimal num2 = {{174, 0}, 0, 0};
  s21_big_decimal expected = {{355 + 174, 0}, 0, 0};
  s21_big_decimal result = {{0, 0}, 0, 0};
  ck_assert_int_eq(SUCCESS, s21_big_add(num1, num2, &result));
  ck_assert_int_eq(TRUE, s21_big_is_equal(result, expected));
}
END_TEST

START_TEST(simple_add_8) {
  s21_big_decimal num1 = {{9273, ULONG_MAX}, 0, 0};
  s21_big_decimal num2 = {{3782923, ULONG_MAX}, 0, 0};
  s21_big_decimal expected = {{9273 + 3782923 + 1, ULONG_MAX - 1}, 0, 0};
  s21_big_decimal result = {{0, 0}, 0, 0};
  ck_assert_int_eq(SUCCESS, s21_big_add(num1, num2, &result));
  ck_assert_int_eq(TRUE, s21_big_is_equal(result, expected));
}
END_TEST

START_TEST(simple_add_9) {
  s21_big_decimal num1 = {{0, 0}, 1, 0};
  s21_big_decimal num2 = {{0, 0}, 0, 0};
  s21_big_decimal expected = {{0, 0}, 0, 0};
  s21_big_decimal result = {{0, 0}, 0, 0};
  ck_assert_int_eq(SUCCESS, s21_big_add(num1, num2, &result));
  ck_assert_int_eq(TRUE, s21_big_is_equal(result, expected));
}
END_TEST

START_TEST(simple_add_10) {
  s21_big_decimal num1 = {{0, 321}, 0, 0};
  s21_big_decimal num2 = {{0, 444}, 1, 0};
  s21_big_decimal expected = {{0, 444 - 321}, 1, 0};
  s21_big_decimal result = {{0, 0}, 0, 0};
  ck_assert_int_eq(SUCCESS, s21_big_add(num1, num2, &result));
  ck_assert_int_eq(TRUE, s21_big_is_equal(result, expected));
}
END_TEST

START_TEST(simple_add_11) {
  s21_big_decimal num1 = {{0, INT_MAX}, 1, 0};
  s21_big_decimal num2 = {{0, (INT_MAX + 1ul)}, 1, 0};
  s21_big_decimal expected = {{0, UINT_MAX}, 1, 0};
  s21_big_decimal result = {{0, 0}, 0, 0};
  ck_assert_int_eq(SUCCESS, s21_big_add(num1, num2, &result));
  ck_assert_int_eq(TRUE, s21_big_is_equal(result, expected));
}
END_TEST

START_TEST(simple_add_12) {
  s21_big_decimal num1 = {{0, LONG_MAX}, 1, 0};
  s21_big_decimal num2 = {{0, (LONG_MAX + 1ul)}, 1, 0};
  s21_big_decimal expected = {{0, ULONG_MAX}, 1, 0};
  s21_big_decimal result = {{0, 0}, 0, 0};
  ck_assert_int_eq(SUCCESS, s21_big_add(num1, num2, &result));
  ck_assert_int_eq(TRUE, s21_big_is_equal(result, expected));
}
END_TEST

START_TEST(simple_add_13) {
  s21_big_decimal num1 = {{0, ULONG_MAX}, 1, 0};
  s21_big_decimal num2 = {{0, 1}, 1, 0};
  s21_big_decimal expected = {{1, 0}, 1, 0};
  s21_big_decimal result = {{0, 0}, 0, 0};
  ck_assert_int_eq(SUCCESS, s21_big_add(num1, num2, &result));
  ck_assert_int_eq(TRUE, s21_big_is_equal(result, expected));
}
END_TEST

START_TEST(simple_add_14) {
  s21_big_decimal num1 = {{1, ULONG_MAX}, 1, 0};
  s21_big_decimal num2 = {{0, ULONG_MAX}, 0, 0};
  s21_big_decimal expected = {{1, 0}, 1, 0};
  s21_big_decimal result = {{0, 0}, 0, 0};
  ck_assert_int_eq(SUCCESS, s21_big_add(num1, num2, &result));
  ck_assert_int_eq(TRUE, s21_big_is_equal(result, expected));
}
END_TEST

START_TEST(simple_add_15) {
  s21_big_decimal num1 = {{355, 0}, 0, 0};
  s21_big_decimal num2 = {{174, 0}, 1, 0};
  s21_big_decimal expected = {{355 - 174, 0}, 0, 0};
  s21_big_decimal result = {{0, 0}, 0, 0};
  ck_assert_int_eq(SUCCESS, s21_big_add(num1, num2, &result));
  ck_assert_int_eq(TRUE, s21_big_is_equal(result, expected));
}
END_TEST

START_TEST(simple_add_16) {
  s21_big_decimal num1 = {{9273, ULONG_MAX}, 1, 0};
  s21_big_decimal num2 = {{3782923, ULONG_MAX}, 0, 0};
  s21_big_decimal expected = {{3782923 - 9273, 0}, 0, 0};
  s21_big_decimal result = {{0, 0}, 0, 0};
  ck_assert_int_eq(SUCCESS, s21_big_add(num1, num2, &result));
  ck_assert_int_eq(TRUE, s21_big_is_equal(result, expected));
}
END_TEST

// Тесты дробных чисел
START_TEST(floating_add_1) {
  s21_big_decimal num1 = {{0, 5}, 0, 1};
  s21_big_decimal num2 = {{0, 0}, 0, 0};
  s21_big_decimal expected = {{0, 5}, 0, 1};
  s21_big_decimal result = {{0, 0}, 0, 0};
  ck_assert_int_eq(SUCCESS, s21_big_add(num1, num2, &result));
  ck_assert_int_eq(TRUE, s21_big_is_equal(result, expected));
}
END_TEST

START_TEST(floating_add_2) {
  s21_big_decimal num1 = {{0, 321}, 0, 2};
  s21_big_decimal num2 = {{0, 444}, 0, 0};
  s21_big_decimal expected = {{0, 321 + 44400}, 0, 2};
  s21_big_decimal result = {{0, 0}, 0, 0};
  ck_assert_int_eq(SUCCESS, s21_big_add(num1, num2, &result));
  ck_assert_int_eq(TRUE, s21_big_is_equal(result, expected));
}
END_TEST

START_TEST(floating_add_3) {
  s21_big_decimal num1 = {{0, ULONG_MAX}, 0, 4};
  s21_big_decimal num2 = {{0, 1}, 0, 0};
  s21_big_decimal expected = {{1, 0b10011100001111}, 0, 4};
  s21_big_decimal result = {{0, 0}, 0, 0};
  ck_assert_int_eq(SUCCESS, s21_big_add(num1, num2, &result));
  ck_assert_int_eq(TRUE, s21_big_is_equal(result, expected));
}
END_TEST

START_TEST(floating_add_4) {
  s21_big_decimal num1 = {{355, 0}, 0, 1};
  s21_big_decimal num2 = {{174, 0}, 0, 1};
  s21_big_decimal expected = {{355 + 174, 0}, 0, 1};
  s21_big_decimal result = {{0, 0}, 0, 0};
  ck_assert_int_eq(SUCCESS, s21_big_add(num1, num2, &result));
  ck_assert_int_eq(TRUE, s21_big_is_equal(result, expected));
}
END_TEST

START_TEST(floating_add_5) {
  s21_big_decimal num1 = {{0, 5}, 1, 1};
  s21_big_decimal num2 = {{0, 0}, 0, 0};
  s21_big_decimal expected = {{0, 5}, 1, 1};
  s21_big_decimal result = {{0, 0}, 0, 0};
  ck_assert_int_eq(SUCCESS, s21_big_add(num1, num2, &result));
  ck_assert_int_eq(TRUE, s21_big_is_equal(result, expected));
}
END_TEST

START_TEST(floating_add_6) {
  s21_big_decimal num1 = {{0, 321}, 0, 2};
  s21_big_decimal num2 = {{0, 444}, 1, 0};
  s21_big_decimal expected = {{0, 44400 - 321}, 1, 2};
  s21_big_decimal result = {{0, 0}, 0, 0};
  ck_assert_int_eq(SUCCESS, s21_big_add(num1, num2, &result));
  ck_assert_int_eq(TRUE, s21_big_is_equal(result, expected));
}
END_TEST

START_TEST(floating_add_7) {
  s21_big_decimal num1 = {{0, ULONG_MAX}, 1, 4};
  s21_big_decimal num2 = {{0, 1}, 1, 0};
  s21_big_decimal expected = {{1, 0b10011100001111}, 1, 4};
  s21_big_decimal result = {{0, 0}, 0, 0};
  ck_assert_int_eq(SUCCESS, s21_big_add(num1, num2, &result));
  ck_assert_int_eq(TRUE, s21_big_is_equal(result, expected));
}
END_TEST

START_TEST(floating_add_8) {
  s21_big_decimal num1 = {{355, 0}, 0, 1};
  s21_big_decimal num2 = {{174, 0}, 1, 1};
  s21_big_decimal expected = {{355 - 174, 0}, 0, 1};
  s21_big_decimal result = {{0, 0}, 0, 0};
  ck_assert_int_eq(SUCCESS, s21_big_add(num1, num2, &result));
  ck_assert_int_eq(TRUE, s21_big_is_equal(result, expected));
}
END_TEST

START_TEST(floating_add_9) {
  s21_big_decimal num1 = {{376, 0}, 0, 2};
  s21_big_decimal num2 = {{14, 0}, 0, 2};
  s21_big_decimal expected = {{39, 0}, 0, 1};
  s21_big_decimal result = {{0, 0}, 0, 0};
  ck_assert_int_eq(SUCCESS, s21_big_add(num1, num2, &result));
  ck_assert_int_eq(TRUE, s21_big_is_equal(result, expected));
}
END_TEST

START_TEST(simple_sub_1) {
  s21_big_decimal num1 = {{0, 0}, 0, 0};
  s21_big_decimal num2 = {{0, 0}, 0, 0};
  s21_big_decimal expected = {{0, 0}, 0, 0};
  s21_big_decimal result = {{0, 0}, 0, 0};
  ck_assert_int_eq(SUCCESS, s21_big_sub(num1, num2, &result));
  ck_assert_int_eq(TRUE, s21_big_is_equal(result, expected));
}
END_TEST

START_TEST(simple_sub_2) {
  s21_big_decimal num1 = {{0, 321}, 0, 0};
  s21_big_decimal num2 = {{0, 444}, 0, 0};
  s21_big_decimal expected = {{0, 444 - 321}, 1, 0};
  s21_big_decimal result = {{0, 0}, 0, 0};
  ck_assert_int_eq(SUCCESS, s21_big_sub(num1, num2, &result));
  ck_assert_int_eq(TRUE, s21_big_is_equal(result, expected));
}
END_TEST

START_TEST(simple_sub_3) {
  s21_big_decimal num1 = {{0, INT_MAX}, 0, 0};
  s21_big_decimal num2 = {{0, (INT_MAX + 1ul)}, 0, 0};
  s21_big_decimal expected = {{0, 1}, 1, 0};
  s21_big_decimal result = {{0, 0}, 0, 0};
  ck_assert_int_eq(SUCCESS, s21_big_sub(num1, num2, &result));
  ck_assert_int_eq(TRUE, s21_big_is_equal(result, expected));
}
END_TEST

START_TEST(simple_sub_4) {
  s21_big_decimal num1 = {{ULONG_MAX, LONG_MAX}, 0, 0};
  s21_big_decimal num2 = {{ULONG_MAX, 0}, 0, 0};
  s21_big_decimal expected = {{0, LONG_MAX}, 0, 0};
  s21_big_decimal result = {{0, 0}, 0, 0};
  ck_assert_int_eq(SUCCESS, s21_big_sub(num1, num2, &result));
  ck_assert_int_eq(TRUE, s21_big_is_equal(result, expected));
}
END_TEST

START_TEST(simple_sub_5) {
  s21_big_decimal num1 = {{0, ULONG_MAX}, 1, 0};
  s21_big_decimal num2 = {{0, 1}, 0, 0};
  s21_big_decimal expected = {{1, 0}, 1, 0};
  s21_big_decimal result = {{0, 0}, 0, 0};
  ck_assert_int_eq(SUCCESS, s21_big_sub(num1, num2, &result));
  ck_assert_int_eq(TRUE, s21_big_is_equal(result, expected));
}
END_TEST

START_TEST(simple_sub_6) {
  s21_big_decimal num1 = {{1, 0}, 1, 0};
  s21_big_decimal num2 = {{0, ULONG_MAX}, 1, 0};
  s21_big_decimal expected = {{0, 1}, 1, 0};
  s21_big_decimal result = {{0, 0}, 0, 0};
  ck_assert_int_eq(SUCCESS, s21_big_sub(num1, num2, &result));
  ck_assert_int_eq(TRUE, s21_big_is_equal(result, expected));
}
END_TEST

START_TEST(simple_sub_7) {
  s21_big_decimal num1 = {{355, 0}, 0, 0};
  s21_big_decimal num2 = {{174, 0}, 1, 0};
  s21_big_decimal expected = {{355 + 174, 0}, 0, 0};
  s21_big_decimal result = {{0, 0}, 0, 0};
  ck_assert_int_eq(SUCCESS, s21_big_sub(num1, num2, &result));
  ck_assert_int_eq(TRUE, s21_big_is_equal(result, expected));
}
END_TEST

// Тесты дробных чисел
START_TEST(floating_sub_1) {
  s21_big_decimal num1 = {{0, 5}, 0, 1};
  s21_big_decimal num2 = {{0, 0}, 0, 0};
  s21_big_decimal expected = {{0, 5}, 0, 1};
  s21_big_decimal result = {{0, 0}, 0, 0};
  ck_assert_int_eq(SUCCESS, s21_big_sub(num1, num2, &result));
  ck_assert_int_eq(TRUE, s21_big_is_equal(result, expected));
}
END_TEST

START_TEST(floating_sub_2) {
  s21_big_decimal num1 = {{0, 321}, 0, 2};
  s21_big_decimal num2 = {{0, 444}, 0, 0};
  s21_big_decimal expected = {{0, 44400 - 321}, 1, 2};
  s21_big_decimal result = {{0, 0}, 0, 0};
  ck_assert_int_eq(SUCCESS, s21_big_sub(num1, num2, &result));
  ck_assert_int_eq(TRUE, s21_big_is_equal(result, expected));
}
END_TEST

START_TEST(floating_sub_3) {
  s21_big_decimal num1 = {{0, ULONG_MAX}, 0, 4};
  s21_big_decimal num2 = {{0, 1}, 0, 0};
  s21_big_decimal expected = {{0, ULONG_MAX - 10000}, 0, 4};
  s21_big_decimal result = {{0, 0}, 0, 0};
  ck_assert_int_eq(SUCCESS, s21_big_sub(num1, num2, &result));
  ck_assert_int_eq(TRUE, s21_big_is_equal(result, expected));
}
END_TEST

START_TEST(floating_sub_4) {
  s21_big_decimal num1 = {{355, 0}, 0, 1};
  s21_big_decimal num2 = {{174, 0}, 0, 1};
  s21_big_decimal expected = {{355 - 174, 0}, 0, 1};
  s21_big_decimal result = {{0, 0}, 0, 0};
  ck_assert_int_eq(SUCCESS, s21_big_sub(num1, num2, &result));
  ck_assert_int_eq(TRUE, s21_big_is_equal(result, expected));
}
END_TEST

START_TEST(floating_sub_5) {
  s21_big_decimal num1 = {{0, 5}, 1, 1};
  s21_big_decimal num2 = {{0, 0}, 0, 0};
  s21_big_decimal expected = {{0, 5}, 1, 1};
  s21_big_decimal result = {{0, 0}, 0, 0};
  ck_assert_int_eq(SUCCESS, s21_big_sub(num1, num2, &result));
  ck_assert_int_eq(TRUE, s21_big_is_equal(result, expected));
}
END_TEST

START_TEST(floating_sub_6) {
  s21_big_decimal num1 = {{0, 321}, 0, 2};
  s21_big_decimal num2 = {{0, 444}, 1, 0};
  s21_big_decimal expected = {{0, 44400 + 321}, 0, 2};
  s21_big_decimal result = {{0, 0}, 0, 0};
  ck_assert_int_eq(SUCCESS, s21_big_sub(num1, num2, &result));
  ck_assert_int_eq(TRUE, s21_big_is_equal(result, expected));
}
END_TEST

TCase *tcase_s21_add_sub() {
  TCase *tc = tcase_create("add");
  tcase_add_test(tc, add_null_test_0);
  tcase_add_test(tc, sub_null_test_0);

  tcase_add_test(tc, add_null_test);
  tcase_add_test(tc, sub_null_test);

  tcase_add_test(tc, simple_add_1);
  tcase_add_test(tc, simple_add_2);
  tcase_add_test(tc, simple_add_3);
  tcase_add_test(tc, simple_add_4);
  tcase_add_test(tc, simple_add_5);
  tcase_add_test(tc, simple_add_6);
  tcase_add_test(tc, simple_add_7);
  tcase_add_test(tc, simple_add_8);
  tcase_add_test(tc, simple_add_9);
  tcase_add_test(tc, simple_add_10);
  tcase_add_test(tc, simple_add_11);
  tcase_add_test(tc, simple_add_12);
  tcase_add_test(tc, simple_add_13);
  tcase_add_test(tc, simple_add_14);
  tcase_add_test(tc, simple_add_15);
  tcase_add_test(tc, simple_add_16);

  tcase_add_test(tc, floating_add_1);
  tcase_add_test(tc, floating_add_2);
  tcase_add_test(tc, floating_add_3);
  tcase_add_test(tc, floating_add_4);
  tcase_add_test(tc, floating_add_5);
  tcase_add_test(tc, floating_add_6);
  tcase_add_test(tc, floating_add_7);
  tcase_add_test(tc, floating_add_8);
  tcase_add_test(tc, floating_add_9);

  tcase_add_test(tc, simple_sub_1);
  tcase_add_test(tc, simple_sub_2);
  tcase_add_test(tc, simple_sub_3);
  tcase_add_test(tc, simple_sub_4);
  tcase_add_test(tc, simple_sub_5);
  tcase_add_test(tc, simple_sub_6);
  tcase_add_test(tc, simple_sub_7);

  tcase_add_test(tc, floating_sub_1);
  tcase_add_test(tc, floating_sub_2);
  tcase_add_test(tc, floating_sub_3);
  tcase_add_test(tc, floating_sub_4);
  tcase_add_test(tc, floating_sub_5);
  tcase_add_test(tc, floating_sub_6);
  return tc;
}