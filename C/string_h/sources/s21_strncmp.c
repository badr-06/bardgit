#include "../s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int result = 0;
  for (s21_size_t i = 0; i < n; i++) {
    unsigned char s1 = (unsigned char)*str1++;
    unsigned char s2 = (unsigned char)*str2++;
    if (s1 != s2) {
      result = s1 - s2;
      i = n;
    }
  }

  return result;
}