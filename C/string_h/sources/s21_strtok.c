#include "../s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *s;
  int i = 0, k = 0, flag1 = 1;

  if (str != S21_NULL) s = str;

  if (s != S21_NULL) {
    str = s;
  }

  if (s == S21_NULL || delim == S21_NULL || *s == '\0') {
    return S21_NULL;
  } else {
    while (*s != '\0' && flag1) {
      while (*delim != '\0') {
        if (*s == *delim) {
          flag1 = 0;

        } else {
          flag1 = 1;
        }
        delim++;
        s++;
        k++;
      }
      if (!flag1) {
        str[i] = '\0';
      } else {
        i++;
        s -= k;
        delim -= k;
        s++;
        k = 0;
      }
    }
  }
  return str;
}