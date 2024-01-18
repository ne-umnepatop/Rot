#include <stdio.h>
#include "bmp.h"
#include "image.h"

int main() {
    // Открываем BMP-файл для чтения
    FILE* input_file = fopen("input.bmp", "rb");

    if (input_file == NULL) {
        fprintf(stderr, "Ошибка открытия файла для чтения.\n");
        return 1;
    }

    // Чтение изображения из BMP-файла
    struct image* img = create_image(0, 0);  // Создаем временное изображение

    if (from_bmp(input_file, img) != READ_OK) {
        fprintf(stderr, "Ошибка чтения BMP-файла.\n");
        fclose(input_file);
        free_image(img);
        return 1;
    }

    // Вывод размеров изображения
    printf("Ширина: %lu, Высота: %lu\n", img->width, img->height);

    // Закрываем BMP-файл
    fclose(input_file);

    // Открываем BMP-файл для записи
    FILE* output_file = fopen("output.bmp", "wb");

    if (output_file == NULL) {
        fprintf(stderr, "Ошибка открытия файла для записи.\n");
        free_image(img);
        return 1;
    }

    // Запись изображения в BMP-файл
    if (to_bmp(output_file, img) != WRITE_OK) {
        fprintf(stderr, "Ошибка записи BMP-файла.\n");
        fclose(output_file);
        free_image(img);
        return 1;
    }

    // Закрываем BMP-файл
    fclose(output_file);

    // Освобождаем память
    free_image(img);

    return 0;
}
