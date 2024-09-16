#include "../s21_string.h"

char *s21_strchr(const char *str, int symbol) {
  const char *res = S21_NULL;
  while (*str) {
    if (*str == (char)symbol) {
      res = str;
      break;
    }
    str++;
  }
  if (symbol == '\0' && *str == '\0') {
    res = str;
  }
  return (char *)res;
}