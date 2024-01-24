#include "../include/files.h"
#include "../include/bmp.h"
#include "../include/rotation.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: ./image-transformer <source-image> <transformed-image>\n");
        return 1;
    }
    fprintf(stderr, "STATE: %d\n", 50);
    // Открываю данное
    enum file_status status_in;
    FILE* file_in = open_file(argv[1], "rb", &status_in);
    if (file_in == NULL) {
        fprintf(stderr, "Failed to open source: %s\n", strerror(status_in));
        printf("Error code: %d\n", status_in);
        return status_in;
    }
    fprintf(stderr, "STATE: %d\n", 51);
    // Перевожу файл bmp во внутренний image
    struct image image;
    struct image* img = &image;
    fprintf(stderr, "STATE: %d\n", 511);
    from_bmp(file_in, img);
    fprintf(stderr, "STATE: %d\n", 5111);
    if (img->status != OK)
    {
        printf("Failed to translate bmp\n");
        printf("%d", img->status);
        close_file(file_in);
        return img->status;
    }
    printf("%d", status_in);
    fprintf(stderr, "STATE: %d\n", 52);
    // Кручу-верчу
    struct image* rotated = rotate_90(img);
    if (rotated == NULL) {
        printf("Failed to transpose\n");
        close_file(file_in);
        return 1;
    }
    fprintf(stderr, "STATE: %d\n", 53);
    // Создаю выходной ( к сожалению только файл )
    enum file_status status_out;
    FILE* file_out = open_file(argv[2], "wb", &status_out);
    if (file_out == NULL) {
        fprintf(stderr, "Failed to open destination: %s\n", strerror(status_out));
        printf("Error code: %d\n", status_out);
        free_image(img);
        free_image(rotated);
        close_file(file_in);
        return status_out;
    }
    fprintf(stderr, "STATE: %d\n", 54);
    // Буду записывать повёрнутое
    to_bmp(file_out, rotated);
    if (img->status != OK)
    {
        printf("Failed to write destination\n");
        printf("%d", img->status);
        return img->status;
    }
    fprintf(stderr, "STATE: %d\n", 55);
    // Всё записал, сворачиваемся
    enum file_status close_status_in = close_file(file_in);
    if (close_status_in != FILE_OK) {
        printf("Failed to close source\n");
        return close_status_in;
    }
    fprintf(stderr, "STATE: %d\n", 56);
    enum file_status close_status_out = close_file(file_out);
    if (close_status_out != FILE_OK) {
        printf("Failed to close destination\n");
        return close_status_out;
    }
    fprintf(stderr, "STATE: %d\n", 57);
    free_image(img);
 
    return 0;
}
