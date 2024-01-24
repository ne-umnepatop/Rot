#include "../include/files.h"

FILE* open_file(const char* filename, const char* mode, enum file_status* status) {
    // вернёт указатель file
        if (filename == NULL || mode == NULL || status == NULL) {
        *status = FILE_INVALID_ARGUMENT;
        return NULL;
    }
    
    // Режим открытия
    if ( strcmp(mode, "rb") != 0 && strcmp(mode, "wb") != 0) {
        *status = FILE_INVALID_ARGUMENT;
        return NULL;
    }
    

    FILE* file = fopen(filename, mode);
    
    if (file == NULL) {
        fprintf(stderr, "Error opening file\n");
        *status = FILE_OPEN_ERROR;
    } else {    
        *status = FILE_OK;
    }
    return file;
}

enum file_status close_file(FILE* file) {
    if (file == NULL) {
        return FILE_INVALID_ARGUMENT;
    }
    if (fclose(file) == EOF) {
        file = NULL;
        return FILE_CLOSE_ERROR;
    } else {
        return FILE_OK;
    }
}