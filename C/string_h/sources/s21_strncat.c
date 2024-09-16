#include "../s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  if (dest != S21_NULL && src != S21_NULL) {
    s21_size_t i;
    s21_size_t dest_length = s21_strlen(dest);

    for (i = 0; i < n && src[i] != '\0'; i++) {
      dest[dest_length + i] = src[i];
    }
    dest[dest_length + i] = '\0';
  }
  return dest;
}