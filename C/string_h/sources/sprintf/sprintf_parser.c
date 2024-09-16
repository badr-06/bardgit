#include "../../headers/s21_sprintf.h"

static void find_secondary_flags(const char *start, char const *end,
                                 spec_mode *mode, va_list args);
static void length_precision_calculation(const char **end, spec_mode *mode);
static void length_precision_from_arg(const char **end, spec_mode *mode,
                                      va_list args);

int extract_specifier(const char *format, spec_mode *mode, va_list args) {
  char *start = (char *)(format + 1);
  int specLineLength = 0;
  char *end = s21_strpbrk(start, SPECS);
  if (end != S21_NULL) {
    mode->spec = *end;
    specLineLength = (end - start) + 1;
  } else {
    mode->spec = ERROR;
  }

  if (specLineLength >= 2) {
    end--;
    find_secondary_flags(start, end, mode, args);
  }

  return specLineLength;
}

static void find_secondary_flags(const char *start, char const *end,
                                 spec_mode *mode, va_list args) {
  for (; end >= start; end--) {
    switch (*end) {
      case 'L':
        mode->memSize = LLONG;
        break;
      case 'l':
        mode->memSize = mode->memSize == LONG ? LLONG : LONG;
        break;
      case 'h':
        mode->memSize = mode->memSize == SHORT ? SSHORT : SHORT;
        break;
      case '+':
        mode->plusSignPlaceholder = '+';
        break;
      case ' ':
        mode->plusSignPlaceholder = ' ';
        break;
      case '-':
        mode->alignment = LEFT_ALIGNMENT;
        break;
      case '#':
        mode->hashSign = '#';
        break;
      case '*':
        length_precision_from_arg(&end, mode, args);
        break;
      case '.':
        mode->precision = 0;
        break;
      default:
        if (*end >= '0' && *end <= '9')
          length_precision_calculation(&end, mode);
        else
          mode->spec = ERROR;
        break;
    }
  }
}

// Вычисляем длину или точность
static void length_precision_calculation(const char **end, spec_mode *mode) {
  int num = 0;
  char *_end = (char *)*end;
  char *start = _end;
  char *strOfNums = S21_NULL;
  s21_size_t length = 0;
  while (*start >= '0' && *start <= '9') start--;
  length = _end - start;
  strOfNums = calloc(length + 1, sizeof(char));
  s21_strncpy(strOfNums, start + 1, length);
  strOfNums[length] = '\0';

  num = atoi(strOfNums);
  if (*start == '.') {
    mode->precision = num;
    *end = start;
  } else {
    if (strOfNums[0] == '0') {
      mode->zeroPlaceholder = '0';
    }
    if (mode->minLength == DEFAULT && num > 0) mode->minLength = num;
    *end = start + 1;
  }
  free(strOfNums);
}

static void length_precision_from_arg(const char **end, spec_mode *mode,
                                      va_list args) {
  int value = va_arg(args, int);
  if (*(*end - 1) != '.') {
    if (value >= 0)
      mode->minLength = value;
    else {
      mode->minLength = -value;
      mode->alignment = LEFT_ALIGNMENT;
    }
  } else if (*(*end - 2) == '*') {
    if (value >= 0)
      mode->minLength = value;
    else {
      mode->minLength = -value;
      mode->alignment = LEFT_ALIGNMENT;
    }
    value = va_arg(args, int);
    (*end) -= 2;
    mode->precision = value >= 0 ? value : DEFAULT;
  } else {
    (*end)--;
    mode->precision = value >= 0 ? value : DEFAULT;
  }
}