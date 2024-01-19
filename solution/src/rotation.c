#include "rotation.h"

struct image* rotate_90(const struct image* source) {
    struct image* rotated = (struct image*)calloc(sizeof(struct image));
    if (rotated == NULL) {
        // Handle memory allocation failure
        return NULL;
    }
    rotated->width = source->height;
    rotated->height = source->width;
    rotated->data = (struct pixel*)calloc(rotated->width * rotated->height, sizeof(struct pixel));
    rotated->padding = (uint8_t*)calloc(1, sizeof(uint8_t));

    if (rotated->data == NULL || rotated->padding == NULL) {
        // Handle memory allocation failure
        free(rotated);
        return NULL;
    }

    size_t size = rotated->width * rotated->height;
    size_t x = 0;
    size_t y = 0;
    for (size_t i = 0; i < size; ++i) {
        rotated->data[i] = source->data[(source->height - x - 1) * source->width + y];
        x = (x + 1) % rotated->width;
        if (x == 0) {
            y++;
        }
    }

    return rotated;
}

