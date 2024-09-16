#ifndef MAIN_TEST_H
#define MAIN_TEST_H

#include <check.h>
#include <limits.h>

#include "../headers/secondary.h"
#include "../s21_decimal.h"

Suite *decimal_suite();

TCase *tcase_s21_comparison();
TCase *tcase_s21_div();
TCase *tcase_s21_floor();
TCase *tcase_s21_add_sub();
TCase *tcase_s21_mul();
TCase *tcase_s21_negate();
TCase *tcase_s21_truncate();
TCase *tcase_s21_round();
TCase *tcase_s21_from_float_to_decimal();
TCase *tcase_s21_from_int_to_decimal();
TCase *tcase_s21_from_decimal_to_int();
TCase *tcase_s21_from_decimal_to_float();

int s21_decimal_compare(s21_decimal a, s21_decimal b);

#endif