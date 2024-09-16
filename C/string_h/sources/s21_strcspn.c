#include "../s21_string.h"

s21_size_t s21_strcspn(const char *str, const char *sym) {
  s21_size_t length = s21_strlen(str);
  for (s21_size_t i = 0; i < s21_strlen(sym); i++) {
    for (s21_size_t j = 0; j < length; j++) {
      if (str[j] == sym[i]) length = j;
    }
  }

  return length;
}