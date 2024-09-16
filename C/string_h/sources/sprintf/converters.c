#include "../../headers/s21_sprintf.h"

static long double to_exponencial(long double num, int *ePow);
static void add_exp_suffix(char *ptr, int ePow, int uppercase);
static long double nround(long double num, int precision);
static char *ftoa_int_part(long double num, char *dest);
static char *str_reverse_cpy(char *dest, const char *str, int len);
static char *delete_zeros(char *end);

// Перевод беззнаковых целых чисел в строку
char *utoa(__uint64_t num, char *dest, int notation) {
  char reverse[21];
  int len = 0;
  for (; num != 0; len++) {
    reverse[len] = (int)(num % notation) + '0';
    num /= notation;
  }
  str_reverse_cpy(dest, reverse, len);
  if (len == 0) {
    dest[0] = '0';
    dest[1] = '\0';
  }

  return dest;
}

// Перевод целого числа в строку (с потерей знака)
char *itoa(__int64_t num, char *dest) {
  num = llabs(num);
  return utoa(num, dest, 10);
}

char *ftoa(long double num, char *dest, int precision, int displayPointAlways,
           int toExp, int deleteZeros) {
  num = fabsl(num);
  char *ptr = dest;
  int ePow = 0;
  long double nInt;
  long double fracPart;
  if (toExp && num > 0.0) {
    num = to_exponencial(num, &ePow);
  }

  num = nround(num, precision);
  fracPart = modfl(num, &nInt);
  ptr = ftoa_int_part(nInt, ptr);
  if (precision > 0 || displayPointAlways) {
    *ptr = '.';
    ptr++;
    *ptr = '\0';
  }
  if (precision > 0) {
    for (int i = 0; i < precision; i++) {
      fracPart *= 10;
      ptr = ftoa_int_part(fracPart, ptr);
      fracPart = modfl(fracPart, &fracPart);
    }
  }
  if (deleteZeros) ptr = delete_zeros(ptr);

  if (toExp) add_exp_suffix(ptr, ePow, toExp);

  return dest;
}

static char *delete_zeros(char *end) {
  end--;
  while (*end == '0') {
    *end = '\0';
    end--;
  }
  if (*end == '.') {
    *end = '\0';
    end--;
  }
  end++;
  return end;
}

static long double to_exponencial(long double num, int *ePow) {
  if (num >= 1.0L) {
    while (num >= 10.0L) {
      num /= 10.0L;
      (*ePow)++;
    }
  } else {
    while (num < 1.0L) {
      num *= 10.0L;
      (*ePow)--;
    }
  }
  return num;
}

static void add_exp_suffix(char *ptr, int ePow, int uppercase) {
  *ptr = uppercase > 1 ? 'E' : 'e';
  ptr++;
  if (ePow >= 0)
    *ptr = '+';
  else
    *ptr = '-';
  ptr++;
  if (ePow < 10 && ePow > -10) {
    *ptr = '0';
    ptr++;
  }
  itoa(ePow, ptr);
}

// Возвращает указатель на конец записи
static char *str_reverse_cpy(char *dest, const char *str, int len) {
  for (len -= 1; len >= 0; len--, dest++) *dest = str[len];
  *dest = '\0';
  return dest;
}

static long double nround(long double num, int precision) {
  long double fracPart = modfl(num, &fracPart);
  long double extremeRigthDigit = powl(10.0L, -precision);

  int firstLostDigit = fmodl(fracPart * powl(10.0L, precision + 1), 10.0L);
  if (firstLostDigit >= 5) num += extremeRigthDigit;
  return num;
}

// Возвращает указатель на конец
static char *ftoa_int_part(long double num, char *dest) {
  char *ptr = dest;
  const int BUFF_SIZE = 32;
  int buff_size = BUFF_SIZE;
  char *reverse = malloc(buff_size);
  int len = 0;
  if (num < 1) {
    *ptr = '0';
    ptr++;
  }
  for (; num >= 1; len++) {
    if (len % buff_size == buff_size - 2) {
      buff_size += BUFF_SIZE;
      reverse = realloc(reverse, buff_size);
    }

    reverse[len] = (int)(fmodl(num, 10.0L)) + '0';
    num /= 10.0L;
  }
  ptr = str_reverse_cpy(ptr, reverse, len);
  free(reverse);
  return ptr;
}