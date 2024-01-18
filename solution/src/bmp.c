#include "bmp.h"

enum read_status read_pixels(FILE* in, struct image* img) { // Выделяю больше функций, потому что потому
    // на всякий я себе напомню:
    // in: указатель в input file stream.
    // img: указатель на image structure, куда я пиксели клал
    // Чтение изображения пиксель за пикселем
    for (uint64_t y = 0; y < img->height; ++y) {
        for (uint64_t x = 0; x < img->width; ++x) {
            // Чтение компонент цвета пикселя
            fread(&(img->data[y * img->width + x]), sizeof(struct pixel), 1, in);
        }

        // Пропуск padding, если есть
        fread(img->padding, 1, img->padding, in);
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
    if (header.biBitCount != 24) {
        return READ_INVALID_BITS;
    }
    // Выделение памяти для изображения
    img->width = header.biWidth;
    img->height = header.biHeight;

    if (img->width != 0 && img->height != 0) {
        img->data = (struct pixel*)calloc(img->width * img->height, sizeof(struct pixel));

        if (img->data == NULL) {
            return READ_MEMORY_ERROR_ALLOCATION_PROBLEMS;
        }
    }

    int padding = (4 - (img->width * 3) % 4) % 4;
    img->padding = (uint8_t*)calloc(padding, sizeof(uint8_t));

    img->padding = padding;

    enum read_status status = read_pixels(in, img);
    if (status != READ_OK) {
        // Ошибка при чтении пикселей, освобождаем выделенную память
        free(img->data);
    }
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
    int padding = (4 - (img->width * 3) % 4) % 4;
    header.biSizeImage = (img->width * 3 + padding) * img->height;
    header.bfileSize = header.biSizeImage + sizeof(struct bmp_header);
    // Запись заголовка в файл
    if (fwrite(&header, sizeof(struct bmp_header), 1, out) != 1) {
        return WRITE_HEADER_ERROR;
    }
    // Запись данных изображения в файл
    for (uint64_t y = 0; y < img->height; ++y) {
        if (fwrite(&(img->data[y * img->width]), sizeof(struct pixel), img->width, out) != img->width) {
            return WRITE_MAIN_IMAGE_NATION_ERROR;
        }
        // Запись padding'а, если есть
        for (int i = 0; i < padding; ++i) {
            if (fputc(0, out) == EOF) {
                return WRITE_PADDING_ERROR;
            }
        }
    }

    return WRITE_OK;
}