#include "../../headers/s21_sprintf.h"

static void resetMode(spec_mode *mode);

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  int counter = 0;
  spec_mode mode = {DEFAULT, DEFAULT, DEFAULT, DEFAULT,
                    DEFAULT, DEFAULT, DEFAULT, DEFAULT};
  va_start(args, format);

  str[0] = '\0';
  for (s21_size_t i = 0; format[i] != '\0' && mode.spec != ERROR; i++) {
    if (format[i] == '%') {
      // Сканируем, что за спецификатор указан за %, его доп аргументы,
      // и сохраняем все детали в spec_mode
      resetMode(&mode);

      i += extract_specifier(&format[i], &mode, args);
      counter = substitution_of_specifiers(&str[counter], &mode, counter, args);
    } else {
      str[counter] = format[i];
      counter++;
      str[counter] = '\0';
    }
  }

  va_end(args);
  return mode.spec != ERROR ? counter : ERROR;
}

static void resetMode(spec_mode *mode) {
  mode->spec = DEFAULT;
  mode->precision = DEFAULT;
  mode->minLength = DEFAULT;
  mode->alignment = DEFAULT;
  mode->memSize = DEFAULT;
  mode->hashSign = DEFAULT;
  mode->zeroPlaceholder = DEFAULT;
  mode->plusSignPlaceholder = DEFAULT;
}