#include "../include/image.h"

struct image* create_image(uint32_t width, uint32_t height) {
    struct image *img = (struct image *)malloc(sizeof(struct image));
    if (img == NULL) {
        return NULL;
    }
    if (width == 0 || height == 0) {
        img->status = READ_INVALID_DIMENSIONS;
        return img;
    }

    img->width = width;
    img->height = height;
    img->data = (struct pixel *)malloc(width * height * sizeof(struct pixel));
    if (img->data == NULL) {
        img->status = READ_PIXEL_ERROR_ALLOCATION_PROBLEMS;
        return img;
    }

    uint8_t padding = (4 - (img->width * 3) % 4) % 4;
    img->padding = (uint8_t*)calloc(padding, sizeof(uint8_t));
    if (img->padding == NULL){
        img->status = READ_PADDING_ERROR_ALLOCATION_PROBLEMS;
        return img;
    }

    img->status = OK;

    return img;
}

struct pair* create_pair() {
    struct pair *imgs = (struct pair *)malloc(sizeof(struct pair));
    if (imgs==NULL){
        return NULL;
    }
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
