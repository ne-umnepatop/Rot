#ifndef ROTATION_H
#define ROTATION_H
#include "image.h"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

// Функция для поворота изображения на 90 градусов
struct image* rotate_90(const struct image* source);

#endif
