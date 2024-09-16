#include "../s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  char *result = S21_NULL;
  if (str1 != S21_NULL || str2 != S21_NULL) {
    while (*str1 != '\0') {
      const char *s = str2;
      while (*s != '\0') {
        if (*str1 == *s) {
          result = (char *)str1;
        }
        s++;
      }
      if (result != S21_NULL) {
        break;
      }
      str1++;
    }
  }
  return result;
}