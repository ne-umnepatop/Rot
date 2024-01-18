#include "rotation.h"

struct image* rotate(const struct image* source) {
    // Реализация поворота изображения на 90 градусов
    struct image* rotated = (struct image*)malloc(sizeof(struct image));
    rotated->width = source->height;
    rotated->height = source->width;
    rotated->data = (struct pixel*)malloc(rotated->width * rotated->height * sizeof(struct pixel));
    rotated->padding = (uint8_t*)calloc(1, sizeof(uint8_t));

    if (rotated->data == NULL || rotated->padding == NULL) {
        // Handle memory allocation failure
        // ...
    }

    for (size_t y = 0; y < rotated->height; ++y) {
        for (size_t x = 0; x < rotated->width; ++x) {
            rotated->data[y * rotated->width + x] = source->data[(source->height - x - 1) * source->width + y];
        }
    }

    free(source->data);
    free(source->padding);

    return rotated;
}

