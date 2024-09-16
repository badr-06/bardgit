#include "../headers/main_test.h"

START_TEST(test_s21_floor_1) {
  s21_decimal exept = {{553402, 0, 0, 0}};
  s21_decimal src_1 = {{1, 2, 3, 917504}};

  s21_floor(src_1, &src_1);
  
  int res = s21_is_equal(src_1, exept);

  ck_assert_float_eq(1, res);
}
END_TEST

START_TEST(test_s21_floor_2) {
  s21_decimal exept = {{553403, 0, 0, -2147483648}};
  s21_decimal src_1 = {{1, 2, 3, -2146566144}};

  s21_floor(src_1, &src_1);
  
  int res = s21_is_equal(src_1, exept);

  ck_assert_float_eq(1, res);
}
END_TEST

START_TEST(test_s21_floor_3) {
  s21_decimal exept = {{56, 0, 0, -2147483648}};
  s21_decimal src_1 = {{33, 2, 3000, -2146107392}};

  s21_floor(src_1, &src_1);
  
  int res = s21_is_equal(src_1, exept);

  ck_assert_float_eq(1, res);
}
END_TEST

TCase *tcase_s21_floor(void) {
  TCase *tc = tcase_create("s21_floor");

  tcase_add_test(tc, test_s21_floor_1);
  tcase_add_test(tc, test_s21_floor_2);
  tcase_add_test(tc, test_s21_floor_3);

  return tc;
}