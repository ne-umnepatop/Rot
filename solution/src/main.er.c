#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "files.h"
#include "bmp.h"
#include "rotation.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source-image> <transformed-image>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *source_filename = argv[1];
    const char *transformed_filename = argv[2];

    FILE *source_file = fopen(source_filename, "rb");
    if (source_file == NULL) {
        fprintf(stderr, "Error opening source file: %s\n", source_filename);
        return EXIT_FAILURE;
    }

    // Чтение изображения из BMP-файла
    struct image *original_image = create_image(0, 0);
    enum read_status read_result = from_bmp(source_file, original_image);

    fclose(source_file);

    if (read_result != READ_OK) {
        fprintf(stderr, "Error reading source image: %d\n", read_result);
        free_image(original_image);
        return EXIT_FAILURE;
    }

    // Поворот изображения на 90 градусов
    struct image *rotated_image = rotate_90(original_image);

    // Сохранение трансформированного изображения в BMP-файл
    FILE *transformed_file = fopen(transformed_filename, "wb");
    if (transformed_file == NULL) {
        fprintf(stderr, "Error opening transformed file: %s\n", transformed_filename);
        free_image(original_image);
        free_image(rotated_image);
        return EXIT_FAILURE;
    }

    enum write_status write_result = to_bmp(transformed_file, rotated_image);

    fclose(transformed_file);

    free_image(original_image);
    free_image(rotated_image);

    if (write_result != WRITE_OK) {
        fprintf(stderr, "Error writing transformed image: %d\n", write_result);
        return EXIT_FAILURE;
    }

    printf("Image transformation successful.\n");

    return EXIT_SUCCESS;
}
