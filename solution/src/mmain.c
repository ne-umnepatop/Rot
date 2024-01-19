#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "files.h"
#include "bmp.h"
#include "rotation.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: ./image-transformer <source-image> <transformed-image>\n");
        return 1;
    }

    // Открываю данное
    enum file_status status_in;
    FILE* file_in = open_file(argv[1], "r", &status_in);
    if (file_in == NULL) {
        printf("Failed to open source\n");
        printf(status_in);
        return 1;
    }

    // Перевожу файл bmp во внутренний image 
    struct image img;
    enum read_status status_in = from_bmp(file_in, &img);
    if (status_in != READ_OK) {
        printf("Failed to translate bmp\n");
        close_file(file_in);
        return 1;
    }

    // Кручу-верчу
    struct image* rotated = rotate_90(&img);
    if (rotated == NULL) {
        printf("Failed to transpose\n");
        free_image(&img);
        close_file(file_in);
        return 1;
    }

    // Создаю выходной ( к сожалению только файл )
    enum file_status status_out;
    FILE* file_out = open_file(argv[2], "w", &status_out);
    if (file_out == NULL) {
        printf("Failed to open destination\n");
        printf(status_out);
        free_image(&img);
        free_image(rotated);
        close_file(file_in);
        return 1;
    }

    // Буду записывать повёрнутое
    enum write_status status_out = to_bmp(file_out, rotated);
    if (status_out != WRITE_OK) {
        printf("Failed to write destination\n");
        printf(status_out);
        return 1;
    }

    // Всё записал, сворачиваемся
    enum file_status close_status_in = close_file(file_in);
    enum file_status close_status_out = close_file(file_out);
    free_image(&img);
    free_image(rotated);

    return 0;
}