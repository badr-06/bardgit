#include "../headers/main_test.h"

Suite *string_suite();

int main() {
  SRunner *runner = srunner_create(string_suite());
  srunner_add_suite(runner, sprintf_suite());
  srunner_add_suite(runner, sprintf_bonus_suite());
  srunner_add_suite(runner, sscanf_suite());

  srunner_run_all(runner, CK_NORMAL);
  srunner_set_fork_status(runner, CK_FORK);
  int failed_count = 0;
  failed_count = srunner_ntests_failed(runner);
  srunner_free(runner);

  return failed_count == 0 ? 0 : 1;
}

Suite *string_suite() {
  Suite *s = suite_create("S21_STRING");

  suite_add_tcase(s, tcase_s21_strlen());
  suite_add_tcase(s, tcase_s21_strerror());
  suite_add_tcase(s, tcase_s21_memchr());
  suite_add_tcase(s, tcase_s21_strstr());
  suite_add_tcase(s, tcase_s21_strpbrk());
  suite_add_tcase(s, tcase_s21_strcspn());
  suite_add_tcase(s, tcase_s21_strncat());
  suite_add_tcase(s, tcase_s21_memcmp());
  suite_add_tcase(s, tcase_s21_memcpy());
  suite_add_tcase(s, tcase_s21_memset());
  suite_add_tcase(s, tcase_s21_strtok());
  suite_add_tcase(s, tcase_s21_strchr());
  suite_add_tcase(s, tcase_s21_strrchr());
  suite_add_tcase(s, tcase_s21_strncmp());
  suite_add_tcase(s, tcase_s21_strncpy());
  suite_add_tcase(s, tcase_s21_trim());
  suite_add_tcase(s, tcase_s21_to_upper());
  suite_add_tcase(s, tcase_s21_insert());
  suite_add_tcase(s, tcase_s21_to_lower());

  return s;
}

int sign_int(int x) { return x > 0 ? 1 : (x < 0 ? -1 : 0); }