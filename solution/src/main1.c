#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "files.h"
#include "bmp.h"
#include "rotation.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: ./image-transformer <source-image> <transformed-image>\n");
        return 1;
    }

    // Load the source image
    const char* filename = argv[1];
    const char* mode = "r";
    enum file_status status;
    FILE* file = open_file(filename, mode, &status);
    if (file != NULL) {
        printf("File opened successfully\n");
    } else {
        printf("Failed to open file\n");
    }
    // Перевожу файл bmp во внутренний image 
    struct image img;
    enum read_status status = from_bmp(file, &img);
    if (status==READ_OK){

    }








        // Save the transformed image
    if (!save_bmp(rotatedImage, argv[2])) {
        printf("Failed to save the transformed image.\n");
        return 1;
    }

    // Cleanup
    free_image(image);
    free_image(rotatedImage);

    return 0;
}