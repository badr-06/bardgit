#include "../s21_string.h"

int s21_memcmp(const void *data_1, const void *data_2, s21_size_t _z) {
  const unsigned char *str_1 = (const unsigned char *)data_1;
  const unsigned char *str_2 = (const unsigned char *)data_2;

  unsigned int res = 0;

  for (s21_size_t i = 0; i < _z && !res; i++, str_1++, str_2++) {
    res = *str_1 - *str_2;
  }
  return res;
}