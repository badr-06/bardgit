#include <ctype.h>
#include <limits.h>
#include <stdarg.h>
#include <stdlib.h>
#include <wchar.h>

#include "../s21_string.h"

typedef struct spec {
  char spec;
  char lenght;
  int width;
  int star;
} spec;

int s21_sscanf(const char *str, const char *format, ...);
int specificators_processing(va_list arg, spec specs, char *str, int read_chars,
                             int *res);
void int_processing(va_list arg, char *str, spec specs, int notation);
void unsigned_int_processing(va_list arg, char *str, spec specs, int notation);
void double_processing(va_list arg, char *str, spec specs);
void str_processing(va_list arg, char *str);
char *string_parcing(const char *str, spec specs, int *index);
int s21spaces(char c);
int is_number(char *str);
long conversion_number_system(char *str, int notation);
int is_hexadecimal_system(char c);

int s21_sscanf(const char *str, const char *format, ...) {
  char *lenght_spec = "hlL";
  char *base_spec = "cdieEfgGosuxXpn";
  char *s;

  int index, read_cahrs = 0;
  int count = 0;
  int res = 0;
  char digits[2];

  va_list arg;
  va_start(arg, format);

  for (; *format && *str; format++) {
    index = 0;
    spec specs = {'q', 'q', 0, 0};

    if (*format == '%') {
      format++;
      for (; *format; format++) {
        if (s21_strchr(base_spec, *format)) {
          specs.spec = *format;
          break;
        } else if (s21_strchr(lenght_spec, *format)) {
          specs.lenght = *format;
        } else if ((isdigit(*format) != 0)) {
          digits[0] = *format;
          if (count == 1) specs.width = specs.width * 10;
          specs.width += atoi(digits);
          count = 1;
        } else if ((*format == '*')) {
          specs.star = 1;
        } else {
          break;
        }
      }
    } else if (s21spaces(*format) == 1) {
      if (*format == *str) str++;
      for (; *str; str++) {
        if (!s21spaces(*str)) break;
      }
      continue;
    } else if (*str == *format) {
      str++;
      continue;
    } else {
      break;
    }

    s = string_parcing(str, specs, &index);
    if (index == -1) {
      va_arg(arg, int *);
      break;
      ;
    }
    specificators_processing(arg, specs, s, read_cahrs, &res);
    for (int i = 0; i < index || *str == ' ' || *str == '\n' || *str == '\t' ||
                    *str == '\f' || *str == '\r';
         i++)
      str++;
    read_cahrs = read_cahrs + index;
    free(s);
  }
  va_end(arg);

  return res;
}

void int_processing(va_list arg, char *str, spec specs, int notation) {
  long int tmp;
  if (specs.lenght == 'h') {
    short int *x = va_arg(arg, short int *);
    tmp = conversion_number_system(str, notation);
    *x = (short int)tmp;
  } else if (specs.lenght == 'l') {
    long int *x = va_arg(arg, long int *);
    tmp = conversion_number_system(str, notation);
    *x = tmp;
  } else {
    int *x = va_arg(arg, int *);
    tmp = conversion_number_system(str, notation);
    *x = (int)tmp;
  }
}

void unsigned_int_processing(va_list arg, char *str, spec specs, int notation) {
  unsigned long int tmp;
  if (specs.lenght == 'h') {
    unsigned short int *x = va_arg(arg, unsigned short int *);
    tmp = conversion_number_system(str, notation);
    *x = (unsigned short int)tmp;
  } else if (specs.lenght == 'l') {
    unsigned long int *x = va_arg(arg, unsigned long int *);
    tmp = conversion_number_system(str, notation);
    *x = tmp;
  } else {
    unsigned int *x = va_arg(arg, unsigned int *);
    tmp = conversion_number_system(str, notation);
    *x = (unsigned int)tmp;
  }
}

void double_processing(va_list arg, char *str, spec specs) {
  char *p;
  if (specs.lenght == 'L') {
    long double *f = va_arg(arg, long double *);
    *f = strtod(str, &p);
  } else if (specs.lenght == 'l') {
    double *lf = va_arg(arg, double *);
    *lf = strtod(str, &p);
  } else {
    float *f = va_arg(arg, float *);
    *f = strtod(str, &p);
  }
}

void str_processing(va_list arg, char *str) {
  char *p = va_arg(arg, char *);

  int str_index = 0;
  int p_index = 0;
  int name_index = 0;

  while (str[str_index] == ' ') {
    str_index++;
    continue;
  }

  // printf("str: <%s>\n", str);

  while (str[str_index] != ' ' && str[str_index] != '\0') {
    p[p_index] = str[str_index];
    str_index++;
    p_index++;
  }

  p[p_index] = '\0';

  if (p_index > 0) name_index += 1;
}

int is_number(char *str) {
  int res = -1;
  for (int i = 0; i < (int)s21_strlen(str); i++) {
    if (isdigit(str[i])) res = 0;
  }
  return res;
}

long conversion_number_system(char *str, int notation) {
  long int res;
  char *p;
  if (notation == 10) {
    res = strtol(str, &p, 10);
  } else if (notation == 0) {
    if ((*str == '0') && ((*(str + 1) == 'x') || (*(str + 1) == 'X'))) {
      res = strtol(str, &p, 16);
    } else if (*str == '0') {
      res = strtol(str, &p, 8);
    } else {
      res = strtol(str, &p, 10);
    }
  } else if (notation == 8) {
    res = strtol(str, &p, 8);
  } else if (notation == 16) {
    res = strtol(str, &p, 16);
  }

  return res;
}

char *string_parcing(const char *str, spec specs, int *index) {
  char *decimal_str = "duo";
  char *float_str = "eEfgG";
  char *x_system = "xX";
  char *str_specs = "sc";
  char *s = (char *)calloc(s21_strlen(str) + 1, sizeof(char));
  int was_digit = 0;

  for (int i = 0;
       *str &&
       ((specs.width != 0 && i < specs.width) ||
        ((specs.width == 0) &&
         ((specs.spec == 'c') || (specs.spec != 'c' && s21spaces(*str) == 0))));
       str++) {
    if (((s21_strchr(decimal_str, specs.spec) ||
          (s21_strchr(float_str, specs.spec) && *str != '.' && *str != 'e' &&
           *str != 'E') ||
          (specs.spec == 'i' && is_hexadecimal_system(*str) == 0)) &&
         (isdigit(*str) == 0) && (s21spaces(*str) == 0) && (*str != '-') &&
         *str != '+') ||
        (((*str == '-') || (*str == '+')) && (was_digit == 1) && *str != 'e' &&
         !s21_strchr(str_specs, specs.spec)))
      break;
    if ((specs.spec == 'o' && *str >= '8') ||
        (s21_strchr(x_system, specs.spec) &&
         (is_hexadecimal_system(*str) == 0) && *str != '-' && *str != '+'))
      break;
    *index = *index + 1;
    s[i] = *str;
    if (specs.spec == 'c')
      break;
    else if (isdigit(*str))
      was_digit = 1;
    if ((specs.width == 0) || (specs.width != 0 && s21spaces(*str) == 0)) i++;
  }

  if (is_number(s) == -1 && !s21_strchr(str_specs, specs.spec)) *index = -1;
  return s;
}

int is_hexadecimal_system(char c) {
  int x = 0;
  if ((isdigit(c)) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F') ||
      (c == 'x') || (c == 'X')) {
    x = 1;
  }

  return x;
}

int s21spaces(char c) {
  return ((c == ' ') || (c == '\n') || (c == '\t') || (c == '\f') ||
          (c == '\r'));
}

int specificators_processing(va_list arg, spec specs, char *str, int read_chars,
                             int *res) {
  if (specs.star == 1) {
    return 0;
  }

  switch (specs.spec) {
    case 'd':
      int_processing(arg, str, specs, 10);
      *res = *res + 1;
      break;
    case 'u':
      unsigned_int_processing(arg, str, specs, 10);
      *res = *res + 1;
      break;
    case 'X':
    case 'x':
      unsigned_int_processing(arg, str, specs, 16);
      *res = *res + 1;
      break;
    case 'i':
      int_processing(arg, str, specs, 0);
      *res = *res + 1;
      break;
    case 'o':
      unsigned_int_processing(arg, str, specs, 8);
      *res = *res + 1;
      break;
    case 's':
      str_processing(arg, str);
      *res = *res + 1;
      break;
    case 'c':
      if (specs.lenght == 'l') {
        wchar_t *c = va_arg(arg, wchar_t *);
        *c = str[0];
      } else {
        char *c = va_arg(arg, char *);
        *c = str[0];
      }
      *res = *res + 1;
      break;
    case 'e':
    case 'E':
    case 'g':
    case 'G':
    case 'f':
      double_processing(arg, str, specs);
      *res = *res + 1;
      break;
    case 'n':
      int *n = va_arg(arg, int *);
      *n = read_chars;
      *res = *res + 1;
      break;
    case 'p':
      void **p = va_arg(arg, void *);
      *p = (void *)conversion_number_system(str, 16);
      *res = *res + 1;
      break;
    default:
      break;
  }

  return 0;
}