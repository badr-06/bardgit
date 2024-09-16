#ifndef MAIN_TEST_H
#define MAIN_TEST_H

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "../s21_string.h"

Suite *string_suite();
int sign_int(int x);

TCase *tcase_s21_memchr();
TCase *tcase_s21_strlen();
TCase *tcase_s21_strerror();
TCase *tcase_s21_strstr();
TCase *tcase_s21_strpbrk();
TCase *tcase_s21_strcspn();
TCase *tcase_s21_strncat();
TCase *tcase_s21_memcmp();
TCase *tcase_s21_memcpy();
TCase *tcase_s21_memset();
TCase *tcase_s21_strtok();
TCase *tcase_s21_strchr();
TCase *tcase_s21_strrchr();
TCase *tcase_s21_strncmp();
TCase *tcase_s21_strncpy();
TCase *tcase_s21_trim();
TCase *tcase_s21_to_upper();
TCase *tcase_s21_insert();
TCase *tcase_s21_to_lower();

Suite *sprintf_suite();
Suite *sprintf_bonus_suite();

Suite *sscanf_suite();

#endif