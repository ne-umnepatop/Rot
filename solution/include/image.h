#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum picture_status
{
    OK = 0,
    READ_INVALID_SIGNATURE,                // сигнатура помойка
    READ_INVALID_BITS,                     // не 24
    READ_INVALID_HEADER,                   // заголовок так себе
    READ_MEMORY_ERROR_ALLOCATION_PROBLEMS, // 4Гб оперативы всем хватит говорили они
    READ_PADDING_ERROR_ALLOCATION_PROBLEMS,
    READ_HEAD_SOUND_ERROR,            // ошибка чтения хедера
    READ_INVALID_INPUTING_PARAMETERS, // при вызове файла нас послали на
    READ_PADDING_ERROR,
    READ_INVALID_DIMENSIONS,
    READ_PIXELS_ERROR,
    DISSAPPEARED,
    WRITE_INVALID_PARAMETERS,     // ерунду писать питается, там 0 какие-то
    WRITE_PADDING_ERROR,          // отступы не отступы
    WRITE_HEADER_ERROR,           // заголовок не всему голова
    WRITE_MAIN_IMAGE_NATION_ERROR // пишу изображение значит, а тут такое
    /* другие коды ошибок */
};

// Структура для внутреннего представления картинки
struct pixel {
    // Поля, описывающие цвет пикселя
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

struct image {
    uint32_t width;
    uint32_t height;
    struct pixel* data;
    uint8_t* padding;
    enum picture_status status;
};

// Функция для создания изображения
struct image* create_image(uint32_t width, uint32_t height);

// Теперь Добби свободен
void free_image(struct image* img);

#endif 
