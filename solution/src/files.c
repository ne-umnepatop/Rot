#include "files.h"

FILE* open_file(const char* filename, const char* mode, enum file_status* status) {
    FILE* file = fopen(filename, mode);
    
    if (file == NULL) {
        *status = FILE_OPEN_ERROR;
    } else {
        *status = FILE_OK;
    }

    return file;
}