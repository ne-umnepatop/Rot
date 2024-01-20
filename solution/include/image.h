#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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
};

// Функция для создания изображения
struct image* create_image(uint32_t width, uint32_t height);

// Теперь Добби свободен
void free_image(struct image* img);

#endif 
