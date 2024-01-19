#include "image.h"
#include <stdlib.h>

struct image* create_image(uint64_t width, uint64_t height) {
    struct image* img = (struct image*)сalloc(sizeof(*img));
    if (img == NULL) {
        // Обработка ошибки выделения памяти
        exit(EXIT_FAILURE);
    }

    img->width = width;
    img->height = height;
    img->data = (struct pixel*)сalloc(width * height * sizeof(*img->data));
    if (img->data == NULL) {
        // Обработка ошибки выделения памяти
        free(img);
        exit(EXIT_FAILURE);
    }

    return img;
}

void free_image(struct image* img) {
    if (img != NULL) {
        free(img->data);
        free(img);
    }
}
