#include "../include/rotation.h"

struct image* rotate_90(const struct image* source) {
    if (source->status != OK) {
        return NULL;
    }

    struct image *rotated = create_image(source->height, source->width);
    if (rotated->status!=OK) {
        return rotated;
    }

    size_t size = rotated->width * rotated->height;
    size_t x = 0;
    size_t y = 0;
    
    for (size_t i = 0; i < size; i++) {
        rotated->data[i] = source->data[(source->height - x - 1) * source->width + y];
        x = (x + 1) % rotated->width;
        if (x == 0) {
            y++;
        }
    }
    
    return rotated;
}