#include <stdlib.h>

#include "../s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  if (src == S21_NULL || str == S21_NULL) return S21_NULL;
  char *result = S21_NULL;

  s21_size_t len_src = s21_strlen(src);
  s21_size_t len_str = s21_strlen(str);
  if (start_index <= len_src) {
    result = malloc((len_src + len_str + 1) * sizeof(char));
    s21_strncpy(result, src, start_index);
    s21_strncpy(result + start_index, str, len_str);
    s21_strncpy(result + start_index + len_str, src + start_index,
                len_src - start_index);
    result[len_src + len_str] = '\0';
  }

  return result;
}