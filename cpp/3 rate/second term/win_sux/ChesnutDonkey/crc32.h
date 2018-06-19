#pragma once
#include <windows.h>

static unsigned long Crc32(BYTE* pbData, size_t len)
{
    unsigned long crc, crc_table[256]; 
 
    for (int i = 0; i < 256; i++)
    {
        crc = i;
        for (int j = 0; j < 8; j++)
            crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320UL : crc >> 1;
 
        crc_table[i] = crc;
    };
 
    crc = 0xFFFFFFFFUL;
 
    while (len--) 
        crc = crc_table[(crc ^ *pbData++) & 0xFF] ^ (crc >> 8);
 
    return crc ^ 0xFFFFFFFFUL;
}
