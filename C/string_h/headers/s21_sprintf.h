#ifndef S21_SPRINTF_H
#define S21_SPRINTF_H

// Вспомогательные функции для s21_sprintf

// '+' и ' ' несовместимы, как и 'l' с 'h'
// Вторичные флаги не должны повторяться, за исключением возможных двух l и двух
// h

#include <math.h>
#include <stdarg.h>
#include <stdlib.h>
#include <wchar.h>

// Так как у verter'а нет bits/types.h, я просто скопировал оттуда эти typedef'ы
typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;
typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;
typedef signed long __int64_t;
typedef unsigned long __uint64_t;

#include "../s21_string.h"

#define SPECS "%csdioxXufeEgGpn"

typedef struct spec_mode {
  char spec;  // Хранит символ спецификатора, или же код ошибки
  int precision;  // Кол-во знаков после запятой (математическое округление)
  int minLength;  // Минимальное кол-во занимаемых знаков (заполнитель - пробел)
  int alignment;  // При использовании минимальной длины заполнения, выравнивает
                  // слева
  int memSize;    // 1 - long, 2 - long long, 3 - short, 4 - short short
  int hashSign;  // Отображать систему счисления в целых или . в дробных числах
  int zeroPlaceholder;  // использовать '0' как заполнитель, вместо ' '
  char plusSignPlaceholder;  // '+' или ' ' на месте положительного знака
} spec_mode;

enum FLAG_CODES {
  ERROR = -1,
  DEFAULT = -2,
  LONG = 1,
  LLONG = 2,
  SHORT = 3,
  SSHORT = 4,

  RIGHT_ALIGNMENT = DEFAULT,  // По умолчанию выравнивание по правому краю
  LEFT_ALIGNMENT = 1,
};

// Ищет спецификаторы за знаком %
// возвращает кол-во символов, занятых описанием спецификатора,
// или -1(ERROR) при возникновении ошибки
int extract_specifier(const char *format, spec_mode *mode, va_list args);

int substitution_of_specifiers(char *currentPos, spec_mode *mode, int counter,
                               va_list args);

char *itoa(__int64_t num, char *dest);
char *utoa(__uint64_t num, char *dest, int notation);
char *ftoa(long double num, char *dest, int precision, int displayPointAlways,
           int toExp, int deleteZeros);

#endif  // S21_SPRINTF_H