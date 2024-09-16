#include <stdlib.h>

#include "../s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  if (src == S21_NULL || trim_chars == S21_NULL) return S21_NULL;

  int index = 0;
  for (s21_size_t i = 0; i < s21_strlen(src); i++) {
    if (s21_strchr(trim_chars, src[i]))
      ++index;
    else
      break;
  }

  char *ltext = (char *)calloc(s21_strlen(src) - index + 1, sizeof(char));

  for (s21_size_t i = 0; i < s21_strlen(src); i++) ltext[i] = src[index + i];

  char *rtext = ltext + s21_strlen(ltext);
  for (int i = s21_strlen(ltext); i > 0; i--) {
    if (s21_strchr(trim_chars, *rtext))
      rtext--;
    else
      *(rtext + 1) = '\0';
  }

  return ltext;
}
