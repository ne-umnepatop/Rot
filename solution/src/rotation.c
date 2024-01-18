#include "rotation.h"

struct image rotate(const struct image* source) {
    // Реализация поворота изображения на 90 градусов
    struct image rotated;
    rotated.width = source->height;
    rotated.height = source->width;
    rotated.data = (struct pixel*)malloc(rotated.width * rotated.height * sizeof(struct pixel));
    rotated.padding = (uint8_t*)calloc(1, sizeof(uint8_t)); // изошёл из бессмысленности инициализации не нулями

    for (uint64_t y = 0; y < rotated.height; ++y) {
        for (uint64_t x = 0; x < rotated.width; ++x) {
            rotated.data[y * rotated.width + x] = source->data[(source->height - x - 1) * source->width + y];
        }
    }

    return rotated;
}

