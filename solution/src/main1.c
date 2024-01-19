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
    Image *image = load_bmp(argv[1]);
    if (image == NULL) {
        printf("Failed to load the source image.\n");
        return 1;
    }

    // Rotate the image counterclockwise by 90 degrees
    Image *rotatedImage = rotate_image(image, 90);

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