#include "../headers/main_test.h"

START_TEST(mul_null) {
  int result;
  s21_decimal src_1 = {{0, 3, 0, 0}};
  s21_decimal src_2 = {{0, 4, 0, 0}};

  result = s21_mul(src_1, src_2, NULL);
  ck_assert_int_eq(result, NULL_PTR);
}
END_TEST

START_TEST(big_mul_null) {
  int result;
  s21_big_decimal src_1 = {{0, 3}, 0, 0};
  s21_big_decimal src_2 = {{0, 4}, 0, 0};

  result = s21_big_mul(src_1, src_2, NULL);
  ck_assert_int_eq(result, NULL_PTR);
}
END_TEST

START_TEST(mul) {
  int result;
  s21_decimal src_1 = {{2, 0, 0, 0}};
  s21_decimal src_2 = {{2, 0, 0, 0}};
  s21_decimal res = {{4, 0, 0, 0}};

  result = s21_mul(src_1, src_2, &res);
  ck_assert_int_eq(res.bits[0], 4);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_big_mul_1) {
  int result;
  s21_big_decimal src_1 = {{0, 3}, 0, 0};
  s21_big_decimal src_2 = {{0, 4}, 0, 0};
  s21_big_decimal res;

  result = s21_big_mul(src_1, src_2, &res);

  ck_assert_int_eq(res.bits[1], 12);
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_big_mul_2) {
  int result;
  s21_big_decimal src_1 = {{5, 3}, 0, 0};
  s21_big_decimal src_2 = {{6, 4}, 0, 0};
  s21_big_decimal res;

  result = s21_big_mul(src_1, src_2, &res);

  ck_assert_int_eq(res.bits[1], 12);
  ck_assert_int_eq(res.bits[0], 38);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_big_mul_3) {
  int result;
  s21_big_decimal src_1 = {{0b11111111111111111111111111111111, 0}, 0, 0};
  s21_big_decimal src_2 = {{0, 2}, 0, 0};
  s21_big_decimal res;

  result = s21_big_mul(src_1, src_2, &res);

  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_big_mul_4) {
  int result;
  s21_big_decimal src_1 = {{0, 2}, 0, 0};
  s21_big_decimal src_2 = {{0b11111111111111111111111111111111, 0}, 0, 0};
  s21_big_decimal res;

  result = s21_big_mul(src_1, src_2, &res);

  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_big_mul_scale_1) {
  s21_big_decimal src_1 = {{0, 5}, 0, 1};
  s21_big_decimal src_2 = {{0, 5}, 0, 0};
  s21_big_decimal res;

  s21_big_mul(src_1, src_2, &res);

  ck_assert_int_eq(res.scale, 1);
}
END_TEST

START_TEST(test_s21_big_mul_scale_2) {
  s21_big_decimal src_1 = {{0, 5}, 0, 0};
  s21_big_decimal src_2 = {{0, 5}, 0, 1};
  s21_big_decimal res;
  s21_big_mul(src_1, src_2, &res);

  ck_assert_int_eq(res.scale, 1);
}
END_TEST

START_TEST(test_s21_big_mul_scale_3) {
  s21_big_decimal src_1 = {{0, 5}, 0, 5};
  s21_big_decimal src_2 = {{0, 5}, 0, 5};
  s21_big_decimal res;
  s21_big_mul(src_1, src_2, &res);

  ck_assert_int_eq(res.scale, 10);
}
END_TEST

START_TEST(test_s21_big_mul_sign_1) {
  s21_big_decimal src_1 = {{0, 5}, 0, 0};
  s21_big_decimal src_2 = {{0, 5}, 0, 0};
  s21_big_decimal res;
  s21_big_mul(src_1, src_2, &res);

  ck_assert_int_eq(res.sign, 0);
}
END_TEST

START_TEST(test_s21_big_mul_sign_2) {
  s21_big_decimal src_1 = {{0, 5}, 1, 0};
  s21_big_decimal src_2 = {{0, 5}, 0, 0};
  s21_big_decimal res;
  s21_big_mul(src_1, src_2, &res);

  ck_assert_int_eq(res.sign, 1);
}
END_TEST

START_TEST(test_s21_big_mul_sign_3) {
  s21_big_decimal src_1 = {{0, 5}, 0, 0};
  s21_big_decimal src_2 = {{0, 5}, 1, 0};
  s21_big_decimal res;
  s21_big_mul(src_1, src_2, &res);

  ck_assert_int_eq(res.sign, 1);
}
END_TEST

START_TEST(test_s21_big_mul_sign_4) {
  s21_big_decimal src_1 = {{0, 5}, 1, 0};
  s21_big_decimal src_2 = {{0, 5}, 1, 0};
  s21_big_decimal res;
  s21_big_mul(src_1, src_2, &res);

  ck_assert_int_eq(res.sign, 0);
}
END_TEST

TCase *tcase_s21_mul(void) {
  TCase *tc = tcase_create("s21_big_mul");

  tcase_add_test(tc, mul_null);
  tcase_add_test(tc, big_mul_null);
  tcase_add_test(tc, mul);

  tcase_add_test(tc, test_s21_big_mul_1);
  tcase_add_test(tc, test_s21_big_mul_2);
  tcase_add_test(tc, test_s21_big_mul_3);
  tcase_add_test(tc, test_s21_big_mul_4);
  tcase_add_test(tc, test_s21_big_mul_scale_1);
  tcase_add_test(tc, test_s21_big_mul_scale_2);
  tcase_add_test(tc, test_s21_big_mul_scale_3);
  tcase_add_test(tc, test_s21_big_mul_sign_1);
  tcase_add_test(tc, test_s21_big_mul_sign_2);
  tcase_add_test(tc, test_s21_big_mul_sign_3);
  tcase_add_test(tc, test_s21_big_mul_sign_4);

  return tc;
}