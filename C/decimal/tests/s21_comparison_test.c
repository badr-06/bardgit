#include "../headers/main_test.h"

START_TEST(test_s21_comparison_1) {
  int result;
  s21_decimal src_1 = {{1, 2, 3, 655360}};
  s21_decimal src_2 = {{3, 2, 1, -2146566144}};

  result = s21_is_less(src_1, src_2);

  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_comparison_2) {
  int result;
  s21_decimal src_1 = {{1,2,3,-2146828288}};
  s21_decimal src_2 = {{3,2,1,-2146828288}};

  result = s21_is_less(src_1, src_2);

  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_comparison_3) {
  int result;
  s21_decimal src_1 = {{1,2,3,-2146566144}};
  s21_decimal src_2 = {{3,2,1,-2146959360}};
  
  result = s21_is_less(src_1, src_2);

  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_comparison_4) {
  int result;
  s21_decimal src_1 = {{10,2,3,-2146566144}};
  s21_decimal src_2 = {{3,2,1,524288}};

  result = s21_is_less(src_1, src_2);

  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_comparison_5) {
  int result;
  s21_decimal src_1 = {{1,2,3,917504}};
  s21_decimal src_2 = {{1,2,3,917504}};

  result = s21_is_less(src_1, src_2);

  ck_assert_int_eq(result, 0);
}
END_TEST

//<=//
START_TEST(test_s21_comparison_6) {
  int result;
  s21_decimal src_1 = {{1, 2, 3, 655360}};
  s21_decimal src_2 = {{3, 2, 1, -2146566144}};

  result = s21_is_less_or_equal(src_1, src_2);

  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_comparison_7) {
  int result;
  s21_decimal src_1 = {{1,2,3,-2146828288}};
  s21_decimal src_2 = {{3,2,1,-2146828288}};

  result = s21_is_less_or_equal(src_1, src_2);

  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_comparison_8) {
  int result;
  s21_decimal src_1 = {{1,2,3,-2146566144}};
  s21_decimal src_2 = {{3,2,1,-2146959360}};

  result = s21_is_less_or_equal(src_1, src_2);

  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_comparison_9) {
  int result;
  s21_decimal src_1 = {{10,2,3,-2146566144}};
  s21_decimal src_2 = {{3,2,1,524288}};

  result = s21_is_less_or_equal(src_1, src_2);

  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_comparison_10) {
  int result;
  s21_decimal src_1 = {{1,2,3,917504}};
  s21_decimal src_2 = {{1,2,3,917504}};

  result = s21_is_less_or_equal(src_1, src_2);

  ck_assert_int_eq(result, 1);
}
END_TEST

//----------------- > -------------//
START_TEST(test_s21_comparison_11) {
  int result;
  s21_decimal src_1 = {{1, 2, 3, 655360}};
  s21_decimal src_2 = {{3, 2, 1, -2146566144}};

  result = s21_is_greater(src_1, src_2);

  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_comparison_12) {
  int result;
  s21_decimal src_1 = {{1,2,3,-2146828288}};
  s21_decimal src_2 = {{3,2,1,-2146828288}};

  result = s21_is_greater(src_1, src_2);

  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_comparison_13) {
  int result;
  s21_decimal src_1 = {{1,2,3,-2146566144}};
  s21_decimal src_2 = {{3,2,1,-2146959360}};

  result = s21_is_greater(src_1, src_2);

  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_comparison_14) {
  int result;
  s21_decimal src_1 = {{10,2,3,-2146566144}};
  s21_decimal src_2 = {{3,2,1,524288}};

  result = s21_is_greater(src_1, src_2);

  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_comparison_15) {
  int result;
  s21_decimal src_1 = {{1,2,3,917504}};
  s21_decimal src_2 = {{1,2,3,917504}};

  result = s21_is_greater(src_1, src_2);

  ck_assert_int_eq(result, 0);
}
END_TEST

//----------------- >= -------------//
START_TEST(test_s21_comparison_16) {
  int result;
  s21_decimal src_1 = {{1, 2, 3, 655360}};
  s21_decimal src_2 = {{3, 2, 1, -2146566144}};

  result = s21_is_greater_or_equal(src_1, src_2);

  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_comparison_17) {
  int result;
  s21_decimal src_1 = {{1,2,3,-2146828288}};
  s21_decimal src_2 = {{3,2,1,-2146828288}};

  result = s21_is_greater_or_equal(src_1, src_2);

  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_comparison_18) {
  int result;
  s21_decimal src_1 = {{1,2,3,-2146566144}};
  s21_decimal src_2 = {{3,2,1,-2146959360}};

  result = s21_is_greater_or_equal(src_1, src_2);

  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_comparison_19) {
  int result;
  s21_decimal src_1 = {{10,2,3,-2146566144}};
  s21_decimal src_2 = {{3,2,1,524288}};

  result = s21_is_greater_or_equal(src_1, src_2);

  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_comparison_20) {
  int result;
  s21_decimal src_1 = {{1,2,3,917504}};
  s21_decimal src_2 = {{1,2,3,917504}};

  result = s21_is_greater_or_equal(src_1, src_2);

  ck_assert_int_eq(result, 1);
}
END_TEST

//----------------- == -------------//
START_TEST(test_s21_comparison_21) {
  int result;
  s21_decimal src_1 = {{1, 2, 3, 655360}};
  s21_decimal src_2 = {{3, 2, 1, -2146566144}};

  result = s21_is_equal(src_1, src_2);

  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_comparison_22) {
  int result;
  s21_decimal src_1 = {{1,2,3,-2146828288}};
  s21_decimal src_2 = {{3,2,1,-2146828288}};

  result = s21_is_equal(src_1, src_2);

  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_comparison_23) {
  int result;
  s21_decimal src_1 = {{1,2,3,-2146566144}};
  s21_decimal src_2 = {{3,2,1,-2146959360}};

  result = s21_is_equal(src_1, src_2);

  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_comparison_24) {
  int result;
  s21_decimal src_1 = {{10,2,3,-2146566144}};
  s21_decimal src_2 = {{3,2,1,524288}};

  result = s21_is_equal(src_1, src_2);

  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_comparison_25) {
  int result;
  s21_decimal src_1 = {{1,2,3,917504}};
  s21_decimal src_2 = {{1,2,3,917504}};

  result = s21_is_equal(src_1, src_2);

  ck_assert_int_eq(result, 1);
}
END_TEST

//----------------- != -------------//
START_TEST(test_s21_comparison_26) {
  int result;
  s21_decimal src_1 = {{1, 2, 3, 655360}};
  s21_decimal src_2 = {{3, 2, 1, -2146566144}};

  result = s21_is_not_equal(src_1, src_2);

  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_comparison_27) {
  int result;
  s21_decimal src_1 = {{1,2,3,-2146828288}};
  s21_decimal src_2 = {{3,2,1,-2146828288}};

  result = s21_is_not_equal(src_1, src_2);

  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_comparison_28) {
  int result;
  s21_decimal src_1 = {{1,2,3,-2146566144}};
  s21_decimal src_2 = {{3,2,1,-2146959360}};

  result = s21_is_not_equal(src_1, src_2);

  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_comparison_29) {
  int result;
  s21_decimal src_1 = {{10,2,3,-2146566144}};
  s21_decimal src_2 = {{3,2,1,524288}};

  result = s21_is_not_equal(src_1, src_2);

  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_comparison_30) {
  int result;
  s21_decimal src_1 = {{1,2,3,917504}};
  s21_decimal src_2 = {{1,2,3,917504}};

  result = s21_is_not_equal(src_1, src_2);

  ck_assert_int_eq(result, 0);
}
END_TEST


TCase *tcase_s21_comparison(void) {
  TCase *tc = tcase_create("s21_comparison");

  tcase_add_test(tc, test_s21_comparison_1);
  tcase_add_test(tc, test_s21_comparison_2);
  tcase_add_test(tc, test_s21_comparison_3);
  tcase_add_test(tc, test_s21_comparison_4);
  tcase_add_test(tc, test_s21_comparison_5);
  tcase_add_test(tc, test_s21_comparison_6);
  tcase_add_test(tc, test_s21_comparison_7);
  tcase_add_test(tc, test_s21_comparison_8);
  tcase_add_test(tc, test_s21_comparison_9);
  tcase_add_test(tc, test_s21_comparison_10);
  tcase_add_test(tc, test_s21_comparison_11);
  tcase_add_test(tc, test_s21_comparison_12);
  tcase_add_test(tc, test_s21_comparison_13);
  tcase_add_test(tc, test_s21_comparison_14);
  tcase_add_test(tc, test_s21_comparison_15);
  tcase_add_test(tc, test_s21_comparison_16);
  tcase_add_test(tc, test_s21_comparison_17);
  tcase_add_test(tc, test_s21_comparison_18);
  tcase_add_test(tc, test_s21_comparison_19);
  tcase_add_test(tc, test_s21_comparison_20);
  tcase_add_test(tc, test_s21_comparison_21);
  tcase_add_test(tc, test_s21_comparison_22);
  tcase_add_test(tc, test_s21_comparison_23);
  tcase_add_test(tc, test_s21_comparison_24);
  tcase_add_test(tc, test_s21_comparison_25);
  tcase_add_test(tc, test_s21_comparison_26);
  tcase_add_test(tc, test_s21_comparison_27);
  tcase_add_test(tc, test_s21_comparison_28);
  tcase_add_test(tc, test_s21_comparison_29);
  tcase_add_test(tc, test_s21_comparison_30);

  return tc;
}