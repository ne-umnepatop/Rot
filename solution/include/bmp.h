#ifndef BMP_H
#define BMP_H

#include <stdint.h>
#include <stdlib.h>
#include "image.h"

#define BMP_SIGNATURE 0x4D42
#define BMP_HEADER_SIZE 40
#define BITS_PER_PIXEL 24

#define CALCULATE_PADDING(row_size) ((4 - ((row_size) % 4)) % 4)
#define ROW_SIZE(img) ((img)->width * sizeof(struct pixel))

// // Структура для заголовка BMP-файла
// struct bmp_header {
//     uint16_t bfType;
//     uint32_t bfileSize;
//     uint32_t bfReserved;
//     uint32_t bOffBits;
//     uint32_t biSize;
//     uint32_t biWidth;
//     uint32_t biHeight;
//     uint16_t biPlanes;
//     uint16_t biBitCount;
//     uint32_t biCompression;
//     uint32_t biSizeImage;
//     uint32_t biXPelsPerMeter;
//     uint32_t biYPelsPerMeter;
//     uint32_t biClrUsed;
//     uint32_t biClrImportant;
// };

struct __attribute__((packed)) bmp_header
{
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

enum write_status
{
    WRITE_OK = 0,
    WRITE_ERROR
};

struct image *from_bmp(FILE *in);

enum write_status to_bmp(FILE *out, const struct image *img);

#endif