#include <stdio.h>
enum file_status {
    FILE_OK = 0,
    FILE_OPEN_ERROR, // NULL пробрался подозрительно глубоко (не должно)
    FILE_CLOSE_ERROR, // хрень какая-то, посмотрим потом, откуда
    FILE_INVALID_ARGUMENT // нас послали на NULL
};