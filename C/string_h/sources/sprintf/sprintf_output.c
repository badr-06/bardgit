#include "../../headers/s21_sprintf.h"

static int next_arg_to_str(va_list args, char *currentPos, spec_mode *mode,
                           int counter);
static char *fill_the_void(char *str, s21_size_t n, char placeHolder);
static int write_char(va_list args, char *currentPos, spec_mode *mode);
static int write_str(va_list args, char *currentPos, spec_mode *mode);
static char *int_arg_to_string(va_list args, char *str, spec_mode *mode);
static void align_int(char *dest, char *numString, long long int num,
                      spec_mode *mode);
static char *uint_arg_to_string(va_list args, char *str, spec_mode *mode,
                                unsigned long long int *ptrInt);
static void align_uint(char *dest, char *numString, unsigned long long int num,
                       spec_mode *mode);
static void toX16(char *str, int uppercase);
static int write_int(va_list args, char *currentPos, spec_mode *mode);
static int write_float(va_list args, char *currentPos, spec_mode *mode);
static s21_size_t double_int_part_length(long double num);
static void choose_double_mode(long double num, spec_mode *mode);
static int first_non_zero_digit_pos(long double num);
static void write_count_to_arg(va_list args, int counter, spec_mode *mode);
static int write_pointer(va_list args, char *currentPos, spec_mode *mode);

int substitution_of_specifiers(char *currentPos, spec_mode *mode, int counter,
                               va_list args) {
  if (mode->spec == '%') {
    *currentPos = '%';
    currentPos++;
    counter++;
    *currentPos = '\0';
  } else {
    counter = next_arg_to_str(args, currentPos, mode, counter);
  }
  return counter;
}

// Записывает аргумент в строку в соответствии со спецификатором
// Возвращает кол-во записанных символов
// При ошибке: mode->spec = ERROR
static int next_arg_to_str(va_list args, char *currentPos, spec_mode *mode,
                           int counter) {
  switch (mode->spec) {
    case 'c':
      counter += write_char(args, currentPos, mode);
      break;
    case 's':
      counter += write_str(args, currentPos, mode);
      break;
    case 'd':
      counter += write_int(args, currentPos, mode);
      break;
    case 'i':
      counter += write_int(args, currentPos, mode);
      break;
    case 'u':
      counter += write_int(args, currentPos, mode);
      break;
    case 'o':
      counter += write_int(args, currentPos, mode);
      break;
    case 'x':
      counter += write_int(args, currentPos, mode);
      break;
    case 'X':
      counter += write_int(args, currentPos, mode);
      break;
    case 'f':
      counter += write_float(args, currentPos, mode);
      break;
    case 'e':
      counter += write_float(args, currentPos, mode);
      break;
    case 'E':
      counter += write_float(args, currentPos, mode);
      break;
    case 'g':
      counter += write_float(args, currentPos, mode);
      break;
    case 'G':
      counter += write_float(args, currentPos, mode);
      break;
    case 'p':
      counter += write_pointer(args, currentPos, mode);
      break;
    case 'n':
      write_count_to_arg(args, counter, mode);
      break;
    default:
      mode->spec = ERROR;
      break;
  }
  return counter;
}

static char *fill_the_void(char *str, s21_size_t n, char placeHolder) {
  for (s21_size_t i = 0; i < n; i++) {
    *str = placeHolder;
    str++;
  }
  *str = '\0';
  return str;
}

static int write_char(va_list args, char *currentPos, spec_mode *mode) {
  char symbol = 0;
  int minLength = (mode->minLength > 1) ? mode->minLength - 1 : 0;
  int counter = minLength;
  int convResult = 0;
  if (mode->memSize == LONG) {
    wchar_t w_symbol = va_arg(args, wchar_t);
    // Преобразовываем w_char в char
    convResult = wcstombs(&symbol, &w_symbol, 1);
  } else {
    symbol = (char)va_arg(args, int);
  }
  if (convResult != ERROR) {
    if (mode->alignment == RIGHT_ALIGNMENT)
      currentPos = fill_the_void(currentPos, minLength, ' ');
    *currentPos = symbol;
    currentPos++;
    counter++;
    if (mode->alignment == LEFT_ALIGNMENT)
      currentPos = fill_the_void(currentPos, minLength, ' ');
  } else {
    mode->spec = ERROR;
  }
  *currentPos = '\0';
  return counter;
}

static int write_str(va_list args, char *currentPos, spec_mode *mode) {
  char *str;
  int counter = 0;
  int minLength = 0;
  int len = 0;
  int convRes = 0;
  if (mode->memSize == LONG) {
    wchar_t *w_str = va_arg(args, wchar_t *);
    len = wcslen(w_str);
    str = calloc(len + 1, sizeof(char));
    convRes = wcstombs(str, w_str, len);
    str[len] = '\0';
  } else {
    str = va_arg(args, char *);
    len = s21_strlen(str);
  }
  if (convRes != ERROR) {
    len =
        (mode->precision >= 0 && mode->precision < len) ? mode->precision : len;
    minLength = (mode->minLength > len) ? mode->minLength - len : 0;
    if (mode->alignment == RIGHT_ALIGNMENT) {
      currentPos = fill_the_void(currentPos, minLength, ' ');
      counter += minLength;
    }
    for (int i = 0; i < len; i++) {
      *currentPos = str[i];
      counter++;
      currentPos++;
    }
    if (mode->alignment == LEFT_ALIGNMENT) {
      currentPos = fill_the_void(currentPos, minLength, ' ');
      counter += minLength;
    }
  } else {
    mode->spec = ERROR;
  }
  *currentPos = '\0';

  if (mode->memSize == LONG) free(str);

  return counter;
}

static char *int_arg_to_string(va_list args, char *str, spec_mode *mode) {
  long long int num = 0;
  int minLength =
      mode->precision > mode->minLength ? mode->precision : mode->minLength;
  minLength = minLength > 21 ? minLength - 21 : 0;
  char *numString = malloc(21 + minLength + 1);
  switch (mode->memSize) {
    case LONG:
      num = va_arg(args, long int);
      break;
    case LLONG:
      num = va_arg(args, long long int);
      break;
    case SHORT:
      num = (short)va_arg(args, int);
      break;
    case SSHORT:
      num = (char)va_arg(args, int);
      break;
    default:
      num = va_arg(args, int);
      break;
  }
  itoa(num, numString);
  align_int(str, numString, num, mode);
  free(numString);
  return str;
}

static void align_int(char *dest, char *numString, long long int num,
                      spec_mode *mode) {
  int minLength;
  int len = s21_strlen(numString);
  if (mode->zeroPlaceholder != DEFAULT && mode->precision == DEFAULT &&
      mode->alignment == RIGHT_ALIGNMENT) {
    minLength = mode->minLength > len ? mode->minLength - len : 0;
    if (num < 0 && minLength > 0)
      minLength--;
    else if (mode->plusSignPlaceholder != DEFAULT && minLength > 0)
      minLength--;
  } else
    minLength = mode->precision > len ? mode->precision - len : 0;

  if (num < 0) {
    *dest = '-';
    dest++;
  } else if (mode->plusSignPlaceholder != DEFAULT) {
    *dest = mode->plusSignPlaceholder;
    dest++;
  }
  dest = fill_the_void(dest, minLength, '0');
  for (int i = 0; i < len; i++) {
    *dest = numString[i];
    dest++;
  }
  *dest = '\0';
}

static char *uint_arg_to_string(va_list args, char *str, spec_mode *mode,
                                unsigned long long int *ptrInt) {
  unsigned long long int num = 0;
  int minLength =
      mode->precision > mode->minLength ? mode->precision : mode->minLength;
  minLength = minLength > 21 ? minLength - 21 : 0;
  char *numString = malloc(21 + minLength + 3);
  if (ptrInt == S21_NULL) switch (mode->memSize) {
      case LONG:
        num = va_arg(args, unsigned long int);
        break;
      case LLONG:
        num = va_arg(args, unsigned long long int);
        break;
      case SHORT:
        num = (unsigned short)va_arg(args, unsigned int);
        break;
      case SSHORT:
        num = (unsigned char)va_arg(args, unsigned int);
        break;
      default:
        num = va_arg(args, unsigned int);
        break;
    }
  else
    num = *ptrInt;

  switch (mode->spec) {
    case 'u':
      utoa(num, numString, 10);
      break;
    case 'o':
      utoa(num, numString, 8);
      break;
    case 'x':
      utoa(num, numString, 16);
      toX16(numString, 0);
      break;
    case 'X':
      utoa(num, numString, 16);
      toX16(numString, 1);
      break;
    default:
      break;
  }

  align_uint(str, numString, num, mode);
  free(numString);
  return str;
}

static void align_uint(char *dest, char *numString, unsigned long long int num,
                       spec_mode *mode) {
  int minLength;
  int len = s21_strlen(numString);
  if (mode->zeroPlaceholder != DEFAULT && mode->precision == DEFAULT &&
      mode->alignment == RIGHT_ALIGNMENT)
    minLength = mode->minLength > len ? mode->minLength - len : 0;
  else
    minLength = mode->precision > len ? mode->precision - len : 0;
  if (mode->hashSign != DEFAULT && num > 0 && mode->spec != 'u') {
    *dest = '0';
    dest++;
    if (mode->spec == 'x' || mode->spec == 'X') {
      *dest = mode->spec;
      dest++;
    } else if (minLength > 0) {
      minLength--;
    }
  }

  dest = fill_the_void(dest, minLength, '0');
  for (int i = 0; i < len; i++) {
    *dest = numString[i];
    dest++;
  }
  *dest = '\0';
}

static void toX16(char *str, int uppercase) {
  while (*str != '\0') {
    if (*str > '9' && *str <= '9' + 6) {
      if (uppercase)
        *str += 'A' - ('9' + 1);
      else
        *str += 'a' - ('9' + 1);
    }
    str++;
  }
}

static int write_int(va_list args, char *currentPos, spec_mode *mode) {
  int counter = 0;
  int minLength = 0;
  int len = mode->precision > 21 ? mode->precision + 3 : 24;
  len = mode->minLength > len ? mode->minLength + 3 : len;
  char *numString = calloc(len, sizeof(char));

  if (mode->spec == 'u' || mode->spec == 'o' || mode->spec == 'x' ||
      mode->spec == 'X')
    numString = uint_arg_to_string(args, numString, mode, S21_NULL);
  else
    numString = int_arg_to_string(args, numString, mode);

  len = s21_strlen(numString);
  minLength = (mode->minLength > len) ? mode->minLength - len : 0;
  if (mode->alignment == RIGHT_ALIGNMENT) {
    currentPos = fill_the_void(currentPos, minLength, ' ');
    counter += minLength;
  }
  for (int i = 0; i < len; i++) {
    *currentPos = numString[i];
    currentPos++;
    counter++;
  }
  if (mode->alignment == LEFT_ALIGNMENT) {
    currentPos = fill_the_void(currentPos, minLength, ' ');
    counter += minLength;
  }
  free(numString);
  *currentPos = '\0';
  return counter;
}

static int write_float(va_list args, char *currentPos, spec_mode *mode) {
  int counter = 0;
  long double num;
  int deleteZeros = 0;
  if (mode->memSize == LLONG)
    num = va_arg(args, long double);
  else
    num = va_arg(args, double);
  if (mode->precision == DEFAULT) mode->precision = 6;
  if (mode->spec == 'g' || mode->spec == 'G') {
    choose_double_mode(num, mode);
    deleteZeros = mode->hashSign == DEFAULT ? 1 : 0;
  }
  int precision = mode->precision;
  char *numString = malloc(double_int_part_length(num) + precision + 3);
  char *strptr = numString;
  int len = 0;
  int minLength = 0;

  if (signbit(num) &&
      (mode->zeroPlaceholder == DEFAULT || mode->alignment == LEFT_ALIGNMENT)) {
    *strptr = '-';
    strptr++;
  } else if (mode->plusSignPlaceholder != DEFAULT &&
             (mode->zeroPlaceholder == DEFAULT ||
              mode->alignment == LEFT_ALIGNMENT)) {
    *strptr = mode->plusSignPlaceholder;
    strptr++;
  }
  if (mode->spec == 'e')
    ftoa(num, strptr, precision, mode->hashSign != DEFAULT, 1, deleteZeros);
  else if (mode->spec == 'E')
    ftoa(num, strptr, precision, mode->hashSign != DEFAULT, 2, deleteZeros);
  else
    ftoa(num, strptr, precision, mode->hashSign != DEFAULT, 0, deleteZeros);

  len = s21_strlen(numString);
  minLength = (mode->minLength > len) ? mode->minLength - len : 0;
  if (mode->alignment == RIGHT_ALIGNMENT) {
    if (signbit(num) && mode->zeroPlaceholder != DEFAULT) {
      *currentPos = '-';
      currentPos++;
      counter++;
      minLength -= minLength > 0 ? 1 : 0;
    } else if (mode->plusSignPlaceholder != DEFAULT &&
               mode->zeroPlaceholder != DEFAULT) {
      *currentPos = mode->plusSignPlaceholder;
      currentPos++;
      counter++;
      minLength -= minLength > 0 ? 1 : 0;
    }
    if (mode->zeroPlaceholder != DEFAULT)
      currentPos = fill_the_void(currentPos, minLength, '0');
    else
      currentPos = fill_the_void(currentPos, minLength, ' ');
    counter += minLength;
  }
  for (int i = 0; i < len; i++) {
    *currentPos = numString[i];
    counter++;
    currentPos++;
  }
  if (mode->alignment == LEFT_ALIGNMENT) {
    currentPos = fill_the_void(currentPos, minLength, ' ');
    counter += minLength;
  }
  free(numString);
  *currentPos = '\0';
  return counter;
}

static void choose_double_mode(long double num, spec_mode *mode) {
  num = fabsl(num);
  int intLen = double_int_part_length(num);
  if (intLen > mode->precision) {
    mode->spec = mode->spec == 'g' ? 'e' : 'E';
    mode->precision--;
  } else if (num < powl(10.0L, -4.0L) && (num != 0.0L && num != -0.0L)) {
    mode->spec = mode->spec == 'g' ? 'e' : 'E';
    mode->precision--;
  } else {
    mode->spec = 'f';
    if (mode->precision == 0) mode->precision = 6;
    if (num < 1.0L)
      mode->precision += first_non_zero_digit_pos(num);
    else
      mode->precision -= intLen;
  }
}

static int first_non_zero_digit_pos(long double num) {
  int n = 0;
  double frac = modf(num, &frac);
  while (frac < 1.0L && n < 6) {
    frac *= 10;
    frac = modf(frac, &frac);
    n++;
  }
  if (n == 6) n = 0;
  if (num == 0.0L || num == -0.0L) n = -1;

  return n;
}

static s21_size_t double_int_part_length(long double num) {
  num = fabsl(num);
  s21_size_t len = 0;
  while (num > 1.0L) {
    len++;
    num /= 10.0L;
  }
  return len;
}

static void write_count_to_arg(va_list args, int counter, spec_mode *mode) {
  void *ptr = va_arg(args, void *);
  switch (mode->memSize) {
    case LLONG:
      *((long long *)ptr) = counter;
      break;
    case LONG:
      *((long *)ptr) = counter;
      break;
    case SSHORT:
      *((signed char *)ptr) = (signed char)counter;
      break;
    case SHORT:
      *((short *)ptr) = (short)counter;
      break;
    default:
      *((int *)ptr) = counter;
      break;
  }
}

static int write_pointer(va_list args, char *currentPos, spec_mode *mode) {
  unsigned long long int pointer = (unsigned long long int)va_arg(args, void *);
  mode->spec = 'x';
  mode->hashSign = '#';
  int counter = 0;
  int minLength = 0;
  int len = mode->minLength > 21 ? mode->precision + 3 : 24;
  char *numString = calloc(len, sizeof(char));

  numString = uint_arg_to_string(args, numString, mode, &pointer);

  len = s21_strlen(numString);
  minLength = (mode->minLength > len) ? mode->minLength - len : 0;
  if (mode->alignment == RIGHT_ALIGNMENT) {
    currentPos = fill_the_void(currentPos, minLength, ' ');
    counter += minLength;
  }
  for (int i = 0; i < len; i++) {
    *currentPos = numString[i];
    currentPos++;
    counter++;
  }
  if (mode->alignment == LEFT_ALIGNMENT) {
    currentPos = fill_the_void(currentPos, minLength, ' ');
    counter += minLength;
  }
  free(numString);
  *currentPos = '\0';
  return counter;
}