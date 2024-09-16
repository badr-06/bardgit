#include "../s21_string.h"

void *s21_memchr(const void *_data, int _c, s21_size_t _z) {
  const char *ptr = (const char *)_data;
  char ch = (char)_c;
  void *result = S21_NULL;
  int flag = 1;

  if (_z != 0) {
    for (s21_size_t i = 0; i < _z && flag == 1; i++) {
      if (*(ptr + i) == ch) {
        result = (void *)ptr + i;
        flag = 0;
      }
    }
  }

  return result;
}