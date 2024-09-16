#include <stdio.h>
#include <limits.h>
#include "s21_decimal.h"
#include "headers/secondary.h"

int main() {

  s21_decimal src = {.bits = {0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111,
                              0b10000000000111000000000000000000}};
  int res;
  s21_big_decimal crs = decimal_to_big(src);
//   s21_from_decimal_to_int(src, &res);
for(int i = 127, j = 0; i>=0; i--, j++){
    printf("%ld", (crs.bits[j / 64] >> i % 64) & 1);
}
printf("\n");

crs = div_by_ten(crs);
crs = div_by_ten(crs);

for(int i = 127, j = 0; i>=0; i--, j++){
    printf("%ld", (crs.bits[j / 64] >> i % 64) & 1);
}
// printf("%ld\n", crs.bits[0]);
// printf("%ld\n", crs.bits[1]);
// printf("%d\n", crs.scale);
0b00000000000000000000000000000000




printf("%d\n", res);
}