#include "../headers/main_test.h"

int main() {
  SRunner *runner = srunner_create(decimal_suite());

  srunner_set_fork_status(runner, CK_FORK);
  srunner_run_all(runner, CK_NORMAL);
  srunner_ntests_failed(runner);
  srunner_free(runner);

  return 0;
}

Suite *decimal_suite() {
  Suite *d = suite_create("S21_DECIMAL");

  suite_add_tcase(d, tcase_s21_add_sub());
  suite_add_tcase(d, tcase_s21_comparison());
  suite_add_tcase(d, tcase_s21_div());
  suite_add_tcase(d, tcase_s21_floor());
  suite_add_tcase(d, tcase_s21_mul());
  suite_add_tcase(d, tcase_s21_negate());
  suite_add_tcase(d, tcase_s21_truncate());
  suite_add_tcase(d, tcase_s21_from_decimal_to_int());
  suite_add_tcase(d, tcase_s21_from_decimal_to_float());
  suite_add_tcase(d, tcase_s21_from_float_to_decimal());
  suite_add_tcase(d, tcase_s21_from_int_to_decimal());
  suite_add_tcase(d, tcase_s21_round());

  return d;
}