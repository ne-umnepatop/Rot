#include "../include/bmp.h"

enum read_status read_pixels(FILE* in, struct image* img) {
    // на всякий я себе напомню:
    // in: указатель в input file stream.
    // img: указатель на image structure, куда я пиксели клал
    // Чтение изображения целыми строками
    for (uint32_t y = 0; y < img->height; ++y) {
        // Чтение целой строки пикселей
        size_t read_pixels = fread(&(img->data[y * img->width]), sizeof(struct pixel), img->width, in);
        if (read_pixels != img->width) {
            return READ_PIXELS_ERROR;
        }
        // Пропуск padding, если есть
        uint8_t read_padding = (uint8_t)fread(img->padding, 1, (size_t)img->padding, in);
        if (read_padding != *(img->padding)) {
            return READ_PADDING_ERROR;
        }
    }
    return READ_OK;
}

enum read_status from_bmp(FILE* in, struct image* img) {
    if (in == NULL || img == NULL) {
        return READ_INVALID_INPUTING_PARAMETERS;
    }
    // Чтение заголовка BMP
    struct bmp_header header;
    if (fread(&header, sizeof(struct bmp_header), 1, in) != 1) {
        return READ_HEAD_SOUND_ERROR;
    }
    // Проверка сигнатуры BMP
    if (header.bfType != 0x4D42) {
        return READ_INVALID_SIGNATURE;
    }
    // Проверка битовой глубины (должна быть 24 бита)
    // if (header.biBitCount != 24) {
    //     return READ_INVALID_BITS;
    // }
    
    // Выделение памяти для изображения
    if (header.biWidth == 0 || header.biHeight == 0)
    {
        return READ_INVALID_DIMENSIONS;
    }
    img = create_image(header.biWidth, header.biHeight);
    // img->data = (struct pixel*)calloc(img->width * img->height, sizeof(struct pixel));
    if (img->data == NULL) {
        return READ_MEMORY_ERROR_ALLOCATION_PROBLEMS;
    }

    if (img->padding == NULL)
    {
        return READ_PADDING_ERROR_ALLOCATION_PROBLEMS;
    }

    enum read_status status = read_pixels(in, img);
    if (status != READ_OK) {
        // Ошибка при чтении пикселей, освобождаем выделенную память
        free_image(img);
    }

    return status;
}

enum write_status to_bmp(FILE* out, const struct image* img) {
    // на всякий я себе напомню, тут аналогично по сути, см выше:
    // out: указатель в outpu file stream.
    // img: указатель на image structure, куда я пиксели клал
    if (out == NULL || img == NULL || img->width == 0 || img->height == 0) {
        return WRITE_INVALID_PARAMETERS;
    }

// Заголовок BMP-файла
    struct bmp_header header = {
        .bfType = 0x4D42,            // Сигнатура "BM"
        .bfileSize = 0,              // Размер файла, заполнится позже
        .bfReserved = 0,
        .bOffBits = sizeof(struct bmp_header), // Смещение данных изображения
        .biSize = 40,                // Размер структуры bi
        .biWidth = (uint32_t)img->width,
        .biHeight = (uint32_t)img->height,
        .biPlanes = 1,               // Количество плоскостей (должно быть 1)
        .biBitCount = 24,            // Бит на пиксель (24 для true color)
        .biCompression = 0,          // Без сжатия
        .biSizeImage = 0,            // Размер данных изображения, заполнится позже
        .biXPelsPerMeter = 0,        // Горизонтальное разрешение (пикселей на метр)
        .biYPelsPerMeter = 0,        // Вертикальное разрешение (пикселей на метр)
        .biClrUsed = 0,              // Количество используемых цветов (0 для true color)
        .biClrImportant = 0          // Количество важных цветов (0 для true color)
    };

 // Вычисление размера изображения и выделение памяти для данных BMP-файла
    uint8_t padding = (4 - (img->width * 3) % 4) % 4;
    header.biSizeImage = (img->width * 3 + padding) * img->height;
    header.bfileSize = header.biSizeImage + (uint32_t)sizeof(struct bmp_header);
    // Запись заголовка в файл
    if (fwrite(&header, sizeof(struct bmp_header), 1, out) != 1) {
        return WRITE_HEADER_ERROR;
    }
    // Запись данных изображения в файл
    for (uint32_t y = 0; y < img->height; ++y) {
        if (fwrite(&(img->data[y * img->width]), sizeof(struct pixel), img->width, out) != img->width) {
            return WRITE_MAIN_IMAGE_NATION_ERROR;
        }
        // Запись padding'а, если есть
        size_t written_padding = fwrite(img->padding, sizeof(uint8_t), padding, out);
        if (written_padding != padding) {
            return WRITE_PADDING_ERROR;
        }
    }
    
    return WRITE_OK;
}