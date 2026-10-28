#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "crc32.h"

#define MAX_BUF_SIZE  8*1024U
static uint8_t buf_to_crc[MAX_BUF_SIZE];

/*
Входные данные:
buffer - Данные, которые нужно посчитать.
len - Длина данных.
crc_d - Предыдущий CRC, если расчет порциями (Начальное значение должно-быть 0xFFFFFFFFUL).

Возвращает, саму CRC32.
*/
uint32_t crc32(uint8_t* buffer, uint32_t len, uint32_t crc_d) {

	uint32_t crc_table[256];
	uint32_t crc;
	int32_t i, j;

	for (i = 0; i < 256; i++) {
		crc = i;
		for (j = 0; j < 8; j++)
			crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320UL : crc >> 1;

		crc_table[i] = crc;
	}

	while (len--)
		crc_d = crc_table[(crc_d ^ *buffer++) & 0xFF] ^ (crc_d >> 8);

	return crc_d;
}

/*
Функция посчитает CRC32 файла, файл делится порциями по MAX_BUF_SIZE по умолчанию 8КБ, можно увеличить.
Входные параметры:
file_name - Имя файла,
hash_sum - хэш-сумма файла.

Выходные параметры:
int результат работы функции.
*/
int crc32_file(const char* file_name, char hash_sum[9]) {

	//Начальное значение CRC
	uint32_t crc = 0xFFFFFFFFUL;

	FILE* src = fopen(file_name, "rb");
	if (src == NULL) {
		printf("%s- file not found\n", file_name);
		return 1;
	}

	size_t total_bytes = 0;

	while (!feof(src)) {
		size_t read_byte = fread(buf_to_crc, 1, MAX_BUF_SIZE, src);
		if ((read_byte != MAX_BUF_SIZE) && (!feof(src))) {
			printf("\nError read file\n");
			return 1;
		}
		crc = crc32(buf_to_crc, read_byte, crc);
		total_bytes += MAX_BUF_SIZE;
	}

	crc ^= 0xFFFFFFFFUL;
	fclose(src);
    if(crc == 0) snprintf(hash_sum, 9, "00000000");
    else snprintf(hash_sum, 9, "%x", crc);

    return 0;
}