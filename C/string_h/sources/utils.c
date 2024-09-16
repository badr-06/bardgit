#include "../headers/s21_string_utils.h"
#include "../s21_string.h"

char *s21_strcpy(char *dest, const char *src) {
  s21_size_t len = s21_strlen(src);
  return s21_strncpy(dest, src, len);
}