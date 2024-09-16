#include "../headers/main_test.h"
 
START_TEST(round_test_1) {
  s21_decimal exept = {{553402, 0, 0, 0}};

  s21_decimal src_1 = {{1, 2, 3, 917504}};
  
  s21_decimal result = {0};

  s21_round(src_1, &result);
  
  int res = s21_is_equal(result, exept);

  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(round_test_2) {
  s21_decimal exept = {{0, 0, 0, 0}};

  s21_decimal src_1 = {{10, 100, 3, 1376256}};
  
  s21_decimal result = {0};

  s21_round(src_1, &result);
  
  int res = s21_is_equal(result, exept);

  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(round_test_3) {
  s21_decimal exept = {{5534023, 0, 0, 0}};

  s21_decimal src_1 = {{16, 100, 3, 851968}};
  
  s21_decimal result = {0};

  s21_round(src_1, &result);
  
  int res = s21_is_equal(result, exept);

  ck_assert_int_eq(1, res);
}
END_TEST

TCase *tcase_s21_round(void) {
  TCase *tc = tcase_create("s21_round");

  tcase_add_test(tc, round_test_1);
  tcase_add_test(tc, round_test_2);
  tcase_add_test(tc, round_test_3);


  return tc;
}