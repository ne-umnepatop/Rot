#include "files.h"

FILE* open_file(const char* filename, const char* mode, enum file_status* status) {
    // вернёт указатель file
    if (filename == NULL || mode == NULL) {
        *status = FILE_INVALID_ARGUMENT;
        return NULL;
    }
    
    FILE* file = fopen(filename, mode);
    
    if (file == NULL) {
        perror("Error opening file");
        *status = FILE_OPEN_ERROR;
    } else {    
        *status = FILE_OK;
    }

    return file;
}

enum file_status close_file(FILE* file) {
    if (fclose(file) == 0) {
        return FILE_OK;
    } else {
        return FILE_CLOSE_ERROR;
    }
}