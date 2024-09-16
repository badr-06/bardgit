#include "../s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *_dest = (char *)dest;
  char *_src = (char *)src;
  for (s21_size_t i = 0; i < n; i++) {
    _dest[i] = _src[i];
  }
  return (void *)_dest;
}