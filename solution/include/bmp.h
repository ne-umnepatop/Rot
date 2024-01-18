#ifndef BMP_H
#define BMP_H
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "image.h"
#pragma pack(push, 1)

// Структура для заголовка BMP-файла
struct bmp_header {
    uint16_t bfType;
    uint32_t bfileSize;
    uint32_t bfReserved;
    uint32_t bOffBits;
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};

#pragma pack(pop)

enum read_status {
    READ_OK = 0,
    READ_INVALID_SIGNATURE, // сигнатура помойка
    READ_INVALID_BITS, // не 24
    READ_INVALID_HEADER, // заголовок так себе
    READ_MEMORY_ERROR_ALLOCATION_PROBLEMS, // 4Гб оперативы всем хватит говорили они
    READ_HEAD_SOUND_ERROR, // ошибка чтения хедера
    READ_INVALID_INPUTING_PARAMETERS, // при вызове файла нас послали на 
    /* другие коды ошибок */
};

enum write_status {
    WRITE_OK = 0,
    WRITE_INVALID_PARAMETERS, // ерунду писать питается, там 0 какие-то
    WRITE_PADDING_ERROR, // отступы не отступы
    WRITE_HEADER_ERROR, // заголовок не всему голова
    WRITE_MAIN_IMAGE_NATION_ERROR // пишу изображение значит, а тут такое
    /* другие коды ошибок */
};

// TODO: Объявление других функций и структур для работы с BMP-файлами

enum read_status from_bmp(FILE* in, struct image* img );

enum write_status to_bmp(FILE* out, const struct image* img);

#endif