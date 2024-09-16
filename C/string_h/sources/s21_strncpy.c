#include "../s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  if (dest == S21_NULL || src == S21_NULL) return S21_NULL;
  char *temp_string = dest;

  while (n > 0 && *src != '\0') {
    *dest++ = *src++;
    n--;
  }
  while (n > 0) {
    *dest++ = '\0';
    n--;
  }

  return temp_string;
}