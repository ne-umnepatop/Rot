#include "../include/bmp.h"

struct image* from_bmp(FILE *in)
{
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

    if (img->status != OK){
        return img;
    }

    uint32_t row_size = img-> width * sizeof(struct pixel);
    uint32_t padding = ((4 - ((row_size) % 4)) % 4);

    // Чтение пикселей с учетом padding
    for (uint32_t y = 0; y < header.biHeight; y++)
    {
        fread(&img->data[y * header.biWidth], sizeof(struct pixel), header.biWidth, in);

        // Пропускаем padding
        fseek(in, (long)padding, SEEK_CUR);
    }
    
    return img;
}


enum write_status to_bmp(FILE *out, const struct image *img)
{
    // Подготовка BMP заголовка
    struct bmp_header header;
    header.bfType = BMP_SIGNATURE;

    // Рассчитываем размер строки с учетом padding
    uint32_t row_size = ROW_SIZE(img);
    uint32_t padding = CALCULATE_PADDING(row_size);
    header.bfileSize = sizeof(struct bmp_header) + (row_size + padding) * img->height;

    header.bfReserved = 0;
    header.bOffBits = sizeof(struct bmp_header);
    header.biSize = BMP_HEADER_SIZE;
    header.biWidth = img->width;
    header.biHeight = img->height;
    header.biPlanes = 1;
    header.biBitCount = BITS_PER_PIXEL;
    header.biCompression = 0;
    header.biSizeImage = 0;
    header.biXPelsPerMeter = 0;
    header.biYPelsPerMeter = 0;
    header.biClrUsed = 0;
    header.biClrImportant = 0;

    // Запись BMP заголовка
    if (fwrite(&header, sizeof(struct bmp_header), 1, out) != 1)
    {
        return WRITE_ERROR; // Ошибка записи заголовка
    }

    // Запись пикселей с учетом padding
    for (uint32_t y = 0; y < img->height; ++y)
    {
        if (fwrite(&img->data[y * img->width], sizeof(struct pixel), img->width, out) != img->width)
        {
            return WRITE_ERROR; // Ошибка записи пикселей
        }

        // Добавляем padding
        for (uint32_t p = 0; p < padding; ++p)
        {
            if (fputc(0, out) == EOF)
            {
                return WRITE_ERROR; // Ошибка записи padding
            }
        }
    }

    return WRITE_OK;
}