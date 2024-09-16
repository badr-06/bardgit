#include "../s21_string.h"

void *s21_memset(void *destination, int c, s21_size_t n) {
  char *p = destination;
  for (int i = 0; i < (int)n; i++) {
    *p++ = c;
  }

  return destination;
}