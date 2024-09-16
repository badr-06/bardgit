#include <stdlib.h>

#include "../s21_string.h"

void *s21_to_lower(const char *str) {
  if (str == S21_NULL) return S21_NULL;

  s21_size_t len = s21_strlen(str);
  char *res = malloc(len + 1);
  for (s21_size_t i = 0; i <= len; i++) {
    if (str[i] >= 65 && str[i] <= 90) {
      res[i] = str[i] + 32;
    } else {
      res[i] = str[i];
    }
  }

  return res;
}