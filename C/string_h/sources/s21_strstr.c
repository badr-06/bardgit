#include <stdlib.h>

#include "../s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  if (haystack == S21_NULL || needle == S21_NULL) return S21_NULL;

  char *result = S21_NULL;
  s21_size_t length = s21_strlen(needle);
  while (*haystack) {
    if (!s21_memcmp(haystack++, needle, length)) {
      result = (char *)(haystack - 1);
      break;
    }
  }

  return result;
}