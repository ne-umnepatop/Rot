#ifndef FILES_H
#define FILES_H

#include <stdio.h>
#include <string.h>

enum file_status {
    FILE_OK = 0,
    FILE_OPEN_ERROR, // NULL пробрался подозрительно глубоко (не должно)
    FILE_CLOSE_ERROR, // хрень какая-то, посмотрим потом, откуда
    FILE_INVALID_ARGUMENT // нас послали на NULL
};
FILE* open_file(const char* filename, const char* mode, enum file_status* status);
enum file_status close_file(FILE* file);

#endif 