#include "../include/bmp.h"

struct image* from_bmp(FILE *in) {
    // Чтение заголовка BMP
    struct bmp_header header;
    if (fread(&header, sizeof(struct bmp_header), 1, in) != 1)
    {
        struct image* img = create_image(0, 0);
        img->status = READ_HEAD_SOUND_ERROR;
        return img;
    }

    // Проверка сигнатуры BMP
    if (header.bfType != 0x4D42)
    {
        struct image* img = create_image(0, 0);
        img->status = READ_INVALID_SIGNATURE;
        return img;
    }

    struct image* img = create_image(header.biWidth, header.biHeight);

    if (img->status != OK) {
        return img;
    }

    uint32_t row_size = ROW_SIZE(img->width);
    uint8_t padding = PADDING(row_size);

    // Чтение пикселей с учетом padding
    for (uint32_t y = 0; y < header.biHeight; y++)
    {
        fread(&img->data[y * header.biWidth], sizeof(struct pixel), header.biWidth, in);

        // Пропускаем padding
        fseek(in, (long)padding, SEEK_CUR);
    }
    
    return img;
}

enum write_status to_bmp(FILE *out, const struct image *img) {
    // Инит
    struct bmp_header header;
    // Рассчитываю размер строки с учетом padding
    uint32_t row_size = ROW_SIZE(img->width);
    uint8_t padding = PADDING(row_size);

    header.bfileSize = sizeof(struct bmp_header) + (row_size + padding) * img->height; // капец, тут не 0
    header.bfType = 0x4D42;
    header.bfReserved = 0;
    header.bOffBits = sizeof(struct bmp_header);
    header.biSize = 40;
    header.biWidth = img->width;
    header.biHeight = img->height;
    header.biPlanes = 1;
    header.biBitCount = 24;
    header.biCompression = 0;
    header.biSizeImage = 0;
    header.biXPelsPerMeter = 0;
    header.biYPelsPerMeter = 0;
    header.biClrUsed = 0;
    header.biClrImportant = 0;

    // Запишу BMP заголовок
    if (fwrite(&header, sizeof(struct bmp_header), 1, out) != 1) {
        return WRITE_HEADER_ERROR;
    }

    // Накину пиксельности
    for (uint32_t y = 0; y < img->height; ++y) {
        if (fwrite(&img->data[y * img->width], sizeof(struct pixel), img->width, out) != img->width) {
            return WRITE_PIXEL_ERROR;
        }

        // paddение в ад
        for (uint32_t p = 0; p < padding; ++p) {
            if (fputc(0, out) == EOF) {
                return WRITE_PADDING_ERROR;
            }
        }
    }

    return WRITE_OK;
}