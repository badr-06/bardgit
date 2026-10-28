#pragma once
#include <stdint.h>
uint32_t crc32(uint8_t* buffer, uint32_t len, uint32_t crc_d);
int crc32_file(const char* file_name, char hash_sum[9]);