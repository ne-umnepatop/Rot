#include "files.h"
#include "bmp.h"

enum file_status status;
FILE* file = open_file("example.txt", "r", &status);

if (file != NULL) {
    printf("File opened successfully\n");
} else {
    printf("Failed to open file\n");
}

struct image img;
enum read_status read_status = from_bmp(file, &img);

if (read_status == READ_OK) {
    // Successfully read the image
} else {
    // Handle the error
}

fclose(file);