#ifndef BMP_H
#define BMP_H

#include <stdint.h>
#include <stdlib.h>
#include "image.h"

struct __attribute__((packed)) bmp_header{
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

enum write_status{
    WRITE_OK = 0,
    WRITE_PIXEL_ERROR,
    WRITE_INVALID_PARAMETERS,     // ерунду писать питается, там 0 какие-то
    WRITE_PADDING_ERROR,          // отступы не отступы
    WRITE_HEADER_ERROR,           // заголовок не всему голова
    WRITE_MAIN_IMAGE_NATION_ERROR // пишу изображение значит, а тут такое
};

struct image *from_bmp(FILE *in);

enum write_status to_bmp(FILE *out, const struct image *img);

#endif