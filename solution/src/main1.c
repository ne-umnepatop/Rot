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
    const char* filename_in = argv[1];
    const char* mode_in = "r";
    enum file_status status_in;
    FILE* file_in = open_file(filename_in, mode_in, &status_in);
    if ( file_in != NULL) {
        printf("File opened successfully\n");

        // Перевожу файл bmp во внутренний image 
        struct image img;
        enum read_status status_in = from_bmp( file_in, &img );
        if (status_in == READ_OK){

            // Кручу-верчу
            struct image* rotated = rotate_90(&img);
            if (rotated != NULL){

                // Создаю выходной ( к сожалению только файл )
                enum file_status status_out;
                const char* filename_out = argv[2];
                const char* mode_out = "w";
                FILE* file_out = open_file( filename_out, mode_out, &status_out );
                if (status_out == READ_OK){

                    // Буду записывать повёрнутое
                    enum write_status status_out = to_bmp(file_out, &rotated);
                    if (status_out == READ_OK){

                        // Всё записал, сворачиваемся
                        enum file_status close_status_in = close_file(file_in);
                        enum file_status close_status_out = close_file(file_out);
                        free_image(&img);
                        free_image(&rotated);
                        return 0;
                        
                    } else {
                        printf("Failed to write destination\n");
                    }
                } else {
                    printf("Failed to open destination\n");
                }
            } else {
                printf("Failed to transpose\n");
            }
        } else {
            printf("Failed to translate bmp\n");
        }
    } else {
        printf("Failed to open source\n");
    }
    