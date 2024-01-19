#include "image.h"
#include <stdlib.h>

struct image* create_image(uint64_t width, uint64_t height) {
    struct image* img = (struct image*)сalloc(sizeof(*img));
    if (img == NULL) {
        // Обработка ошибки выделения памяти
        return NULL;
    }

    img->width = width;
    img->height = height;
    if (width == 0 || height == 0) {
    // Обработка ошибки нулевой ширины или высоты
    free(img);
    return NULL;
    }
    img->data = (struct pixel*)сalloc(width * height * sizeof(*img->data));
    if (img->data == NULL) {
        // Обработка ошибки выделения памяти
        free(img);
        return NULL;
    }

    return img;
}

void free_image(struct image* img) {
    if (img != NULL) {
        free(img->data);
        img->data = NULL;
        free(img);
        img = NULL;
    }
}
