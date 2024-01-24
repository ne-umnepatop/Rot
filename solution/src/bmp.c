#include "../include/bmp.h"

void read_pixels(FILE *in, struct image *img, struct bmp_header header)
{
    if (img->status != OK){
        return;
    }
    if (in == NULL || img == NULL)
    {
        img->status = READ_INVALID_INPUTING_PARAMETERS;
        return;
    }
    if (img->data == NULL || img->padding == NULL)
    {
        img->status = READ_MEMORY_ERROR_ALLOCATION_PROBLEMS;
        free_image(img);
        return;
    }
    if (img == NULL)
    {
        img->status = DISSAPPEARED;
        return;
    }
    for (uint32_t y = 0; y < img->height; ++y)
    {
        // Чтение целой строки пикселей
        size_t read_pixels = fread(&(img->data[y * img->width]), sizeof(struct pixel), img->width, in);

        //fprintf(stderr, "STATE: %d\n", read_pixels);
        if (read_pixels != img->width)
        {
            img->status = READ_PIXELS_ERROR;
            free_image(img);
            return;
        }
        // Пропуск padding, если есть
        fprintf(stderr, "STATE: %d\n", img->status);
        fprintf(stderr, "STATE: %p\n", (void *)img->padding);

        uint32_t row_size = img->width * sizeof(struct pixel);
        uint32_t padding = (4 - ((row_size) % 4)) % 4;

        // Чтение пикселей с учетом padding
        for (uint32_t y = 0; y < header.biHeight; ++y)
        {
            fread(&(*img)->data[y * header.biWidth], sizeof(struct pixel), header.biWidth, in);

            // Пропускаем padding
            fseek(in, (long)padding, SEEK_CUR);
        }
    }
    img->status = OK;
    return;
}
void from_bmp(FILE *in, struct image *img)
{
    if (in == NULL || img == NULL)
    {
        img->status = READ_INVALID_INPUTING_PARAMETERS;
    }
    // Чтение заголовка BMP
    struct bmp_header header;
    if (fread(&header, sizeof(struct bmp_header), 1, in) != 1)
    {
        img->status = READ_HEAD_SOUND_ERROR;
    }

    // Проверка сигнатуры BMP
    if (header.bfType != 0x4D42)
    {
        img->status = READ_INVALID_SIGNATURE;
    }
    // Проверка битовой глубины (должна быть 24 бита)
    // if (header.biBitCount != 24) {
    //     return READ_INVALID_BITS;
    // }

    // Выделение памяти для изображения
    if (header.biWidth == 0 || header.biHeight == 0)
    {
        img->status = READ_INVALID_DIMENSIONS;
    }
    img = create_image(header.biWidth, header.biHeight);
    // img->data = (struct pixel*)calloc(img->width * img->height, sizeof(struct pixel));
    if (img->data == NULL)
    {
        img->status = READ_MEMORY_ERROR_ALLOCATION_PROBLEMS;
    }

    if (img->padding == NULL)
    {
        img->status = READ_PADDING_ERROR_ALLOCATION_PROBLEMS;
    }

    read_pixels(in, img, header);
    if (img->status != OK)
    {
        // Ошибка при чтении пикселей, освобождаем выделенную память
        free_image(img);
    }

    return;
}
void to_bmp(FILE *out, const struct image *img)
{
    if (out == NULL || img == NULL || img->width == 0 || img->height == 0)
    {
        ((struct image *)img)->status = WRITE_INVALID_PARAMETERS;
        return;
    }

    struct bmp_header header = {
        .bfType = 0x4D42,
        .bfileSize = 0,
        .bfReserved = 0,
        .bOffBits = sizeof(struct bmp_header),
        .biSize = 40,
        .biWidth = (uint32_t)img->width,
        .biHeight = (uint32_t)img->height,
        .biPlanes = 1,
        .biBitCount = 24,
        .biCompression = 0,
        .biSizeImage = 0,
        .biXPelsPerMeter = 0,
        .biYPelsPerMeter = 0,
        .biClrUsed = 0,
        .biClrImportant = 0};

    uint8_t padding = (4 - (img->width * 3) % 4) % 4;
    header.biSizeImage = (img->width * 3 + padding) * img->height;
    header.bfileSize = header.biSizeImage + (uint32_t)sizeof(struct bmp_header);

    if (fwrite(&header, sizeof(struct bmp_header), 1, out) != 1)
    {
        ((struct image *)img)->status = WRITE_HEADER_ERROR;
        return;
    }

    for (uint32_t y = 0; y < img->height; ++y)
    {
        if (img->data != NULL && img->padding != NULL) // Added check for img->data and img->padding
        {
            if (fwrite(&(img->data[y * img->width]), sizeof(struct pixel), img->width, out) != img->width)
            {
                ((struct image *)img)->status = WRITE_MAIN_IMAGE_NATION_ERROR;
                return;
            }
            size_t written_padding = fwrite(img->padding, sizeof(uint8_t), padding, out);
            if (written_padding != padding)
            {
                ((struct image *)img)->status = WRITE_PADDING_ERROR;
                return;
            }
        }
        else
        {
            ((struct image *)img)->status = WRITE_INVALID_PARAMETERS;
            return;
        }
    }

    ((struct image *)img)->status = OK;
    return;
}