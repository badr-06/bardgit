#include "../s21_string.h"

char *s21_strrchr(const char *str, int c) {
  char *result = S21_NULL;
  while (*str != '\0') {
    if (*str == (char)c) {
      result = (char *)str;
    }
    str++;
  }

  if ((char)c == '\0') {
    result = (char *)str;
  }

  return (char *)result;
}
