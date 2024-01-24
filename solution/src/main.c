#include "../include/files.h"
#include "../include/bmp.h"
#include "../include/rotation.h"

int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("Usage: ./image-transformer <source-image> <transformed-image>\n");
        return 1;
    }

    struct pair *imgs = create_pair();

    // Открываю данное
    enum file_status status_in;
    FILE* file_in = open_file(argv[1], "rb", &status_in);
    if (status_in != FILE_OK) {
        fprintf(stderr, "Failed to open source: %s\n", strerror(status_in));
        printf("Error code: %d\n", status_in);
        return status_in;
    }

    // Перевожу исходник bmp во внутренний image
    imgs->source = *from_bmp(file_in);
    if ((&imgs->source)->status != OK) {
        printf("Failed to translate bmp\n");
        return (&imgs->source)->status;
    }

    // Исходник не нужен
    enum file_status close_status_in = close_file(file_in);
    if (close_status_in != FILE_OK) {
        printf("Failed to close source\n");
        return close_status_in;
    }

    // Кручу-верчу
    imgs->output = *rotate_90(&imgs->source);
    if ((&imgs->output)->status!=OK) {
        printf("Failed to transpose\n");
        return 1;
    }

    // Создаю выходной ( к сожалению только файл )
    enum file_status status_out;
    FILE* file_out = open_file(argv[2], "wb", &status_out);
    if (status_out != FILE_OK) {
        fprintf(stderr, "Failed to open destination: %s\n", strerror(status_out));
        printf("Error code: %d\n", status_out);
        free_image((&imgs->source));
        free_image((&imgs->output));
        return status_out;
    }

    // Буду записывать повёрнутое
    enum write_status stat_out = to_bmp(file_out, &imgs->output);
    if (stat_out != WRITE_OK) {
        printf("Failed to write destination\n");
        printf("%d", (&imgs->source)->status);
        return (&imgs->source)->status;
    }

    // Всё записал, сворачиваемся
    enum file_status close_status_out = close_file(file_out);
    if (close_status_out != FILE_OK) {
        printf("Failed to close destination\n");
        return close_status_out;
    }

    free_image((&imgs->source));

    return 0;
}
