#include "../headers/main_test.h"

// Функция для сравнения двух s21_decimal структур
int compare_decimals(s21_decimal actual, s21_decimal expected) {
    for (int i = 0; i < 4; i++) {
        if (actual.bits[i] != expected.bits[i]) {
            return 0; // Тест не пройден
        }
    }
    return 1; // Тест пройден
}

START_TEST(test_from_float_to_decimal_positive) {
    s21_decimal result;
    float input = 1234567.0f;
    s21_decimal expected = {.bits = {1234567, 0, 0, 0}};
    int status = s21_from_float_to_decimal(input, &result);
    ck_assert_int_eq(status, 0);
    ck_assert_int_eq(compare_decimals(result, expected), 1);
}
END_TEST

START_TEST(test_from_float_to_decimal_negative) {
    s21_decimal result;
    float input = -1234567.0f;
    s21_decimal expected = {.bits = {1234567, 0, 0, 0x80000000}};
    int status = s21_from_float_to_decimal(input, &result);
    ck_assert_int_eq(status, 0);
    ck_assert_int_eq(compare_decimals(result, expected), 1);
}
END_TEST

START_TEST(test_from_float_to_decimal_scaled) {
    s21_decimal result;
    float input = 12345.67f;
    s21_decimal expected = {.bits = {1234567, 0, 0, 0x00020000}};
    int status = s21_from_float_to_decimal(input, &result);
    ck_assert_int_eq(status, 0);
    ck_assert_int_eq(compare_decimals(result, expected), 1);
}
END_TEST

START_TEST(test_from_float_to_decimal_scaled_negative) {
    s21_decimal result;
    float input = -12345.67f;
    s21_decimal expected = {.bits = {1234567, 0, 0, 0x80020000}};
    int status = s21_from_float_to_decimal(input, &result);
    ck_assert_int_eq(status, 0);
    ck_assert_int_eq(compare_decimals(result, expected), 1);
}
END_TEST

START_TEST(test_from_float_to_decimal_scaled_negative_1) {
    s21_decimal result;
    float input = -123456.7f;
    s21_decimal expected = {.bits = {1234567, 0, 0, 0x80010000}};
    int status = s21_from_float_to_decimal(input, &result);
    ck_assert_int_eq(status, 0);
    ck_assert_int_eq(compare_decimals(result, expected), 1);
}
END_TEST

START_TEST(test_from_float_to_decimal_scaled_1) {
    s21_decimal result;
    float input = 123456.7f;
    s21_decimal expected = {.bits = {1234567, 0, 0, 0x00010000}};
    int status = s21_from_float_to_decimal(input, &result);
    ck_assert_int_eq(status, 0);
    ck_assert_int_eq(compare_decimals(result, expected), 1);
}
END_TEST

START_TEST(test_from_float_to_decimal_1) {
    s21_decimal result;
    float input = 1.234567f;
    s21_decimal expected = {.bits = {1234567, 0, 0, 0x00060000}};
    int status = s21_from_float_to_decimal(input, &result);
    ck_assert_int_eq(status, 0);
    ck_assert_int_eq(compare_decimals(result, expected), 1);
}
END_TEST

START_TEST(test_from_float_to_decimal_2) {
    s21_decimal result;
    float input = -1.234567f;
    s21_decimal expected = {.bits = {1234567, 0, 0, 0x80060000}};
    int status = s21_from_float_to_decimal(input, &result);
    ck_assert_int_eq(status, 0);
    ck_assert_int_eq(compare_decimals(result, expected), 1);
}
END_TEST



TCase *tcase_s21_from_float_to_decimal(void) {
  TCase *tc = tcase_create("s21_from_float_to_decimal");

  tcase_add_test(tc, test_from_float_to_decimal_positive);
  tcase_add_test(tc, test_from_float_to_decimal_negative);
  tcase_add_test(tc, test_from_float_to_decimal_scaled);
  tcase_add_test(tc, test_from_float_to_decimal_scaled_negative);
  tcase_add_test(tc, test_from_float_to_decimal_scaled_negative_1);
  tcase_add_test(tc, test_from_float_to_decimal_scaled_1);
  tcase_add_test(tc, test_from_float_to_decimal_1);
  tcase_add_test(tc, test_from_float_to_decimal_2);

  return tc;
}