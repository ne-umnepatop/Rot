#include "../include/image.h"

struct image* create_image(uint32_t width, uint32_t height) {
    struct image* img = (struct image *)malloc(sizeof(struct image));
    if (img == NULL) {
        // Обработка ошибки выделения памяти
        return NULL;
    }
    if (width == 0 || height == 0) {
    // Обработка ошибки нулевой ширины или высоты
    free_image(img);
    return NULL;
    }
    img->width = width;
    img->height = height;
    fprintf(stderr, "Creating2\n");
    img->data = (struct pixel *)malloc(width * height * sizeof(struct pixel));
    fprintf(stderr, "Created\n");
    if (img->data == NULL) {
        // Обработка ошибки выделения памяти
        free_image(img);
        return NULL;
    }

    uint8_t padding = (4 - (img->width * 3) % 4) % 4;
    img->padding = (uint8_t*)calloc(padding, sizeof(uint8_t));
    if (img->padding == NULL) {
        free_image(img);
        return NULL;
    }

    img->status = OK;

    return img;
}

struct pair* create_pair() {
    struct pair *imgs = (struct pair *)malloc(sizeof(struct pair));
    if (imgs==NULL){
        return NULL;
    }
    imgs->output = *create_image(100, 100);
    imgs->source = *create_image(100, 100);
    return imgs;
}

void free_image(struct image* img) {
    if (img != NULL) {
        if (img->data != NULL){
            free(img->data);}
        if (img->padding != NULL){
            free(img->padding);}
        free(img);
    }
}
