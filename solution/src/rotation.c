#include "rotation.h"

struct image* rotate_90(const struct image* source) {
    struct image* rotated = (struct image*)calloc(sizeof(struct image));
    if (rotated == NULL) {
        // Handle memory allocation failure
        free(source->data);
        free(source->padding);
        return NULL;
    }
    rotated->width = source->height;
    rotated->height = source->width;
    rotated->data = (struct pixel*)calloc(rotated->width * rotated->height, sizeof(struct pixel));
    rotated->padding = (uint8_t*)calloc(1, sizeof(uint8_t));

    if (rotated->data == NULL || rotated->padding == NULL) {
        // Handle memory allocation failure
        free(rotated);
        free(source->data);
        free(source->padding);
        return NULL;
    }

    for (size_t i = 0; i < rotated->width * rotated->height; ++i) {
        size_t x = i % rotated->width;
        size_t y = i / rotated->width;
        rotated->data[i] = source->data[(source->height - x - 1) * source->width + y];
    }

    return rotated;
}

