#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "files.h"
#include "bmp.h"
#include "rotation.h"

const int ROTATION_ANGLE = 90;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: ./image-transformer <source-image> <transformed-image>\n");
        return 1;
    }

    // Validate input file paths
    if (!is_valid_file_path(argv[1])) {
        fprintf(stderr, "Invalid source image file path.\n");
        return 1;
    }
    if (!is_valid_file_path(argv[2])) {
        fprintf(stderr, "Invalid transformed image file path.\n");
        return 1;
    }

    // Load the source image
    Image *image = load_bmp(argv[1]);
    if (image == NULL) {
        fprintf(stderr, "Failed to load the source image.\n");
        return 1;
    }

    // Rotate the image counterclockwise using the constant rotation angle
    Image *rotatedImage = rotate_image(image, ROTATION_ANGLE);

    // Check if rotation operation failed
    if (rotatedImage == NULL) {
        printf("Failed to rotate the image.\n");
        free_image(image);
        return 1;
    }

    // Save the transformed image
    if (!save_bmp(rotatedImage, argv[2])) {
        fprintf(stderr, "Failed to save the transformed image.\n");
        free_image(image);
        free_image(rotatedImage);
        return 1;
    }

    // Cleanup
    free_image(image);
    free_image(rotatedImage);

    return 0;
}