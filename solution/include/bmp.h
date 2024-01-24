#ifndef BMP_H
#define BMP_H

#include <stdint.h>
#include <stdlib.h>
#include "image.h"


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

void from_bmp(FILE *in, struct image *img);

void to_bmp(FILE *out, const struct image *img);

#endif