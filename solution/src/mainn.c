#include <stdio.h>
#include "bmp.h"
#include "rotation.h"
#include "image.h"

int main(int argc, char *argv[]) {
    // Пример использования rotate_90_degrees
    struct image loaded_image;
    // Загрузка изображения из файла (используйте соответствующий формат)
    // ...

    // Поворот изображения на 90 градусов
    struct image rotated_image = rotate_90_degrees(loaded_image);

    // Сохранение повернутого изображения в файл (используйте соответствующий формат)
    // ...

    // Освобождение памяти
    free_image(&loaded_image);
    free_image(&rotated_image);

    return 0;
}
