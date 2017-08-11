#include <stdio.h>
#include <esi.h>
#include "qdbmp.h"
#include <string.h>
int main(int argc, char *argv[])
{
    if(argc > 1) {
        BMP *bmp;
        FILE *file = fopen(argv[argc - 1], "rb");
        struct esi_image *image = load_esi_image(file);
        char *out_fn;
        if(!image) {
            return -1;
        }
        fclose(file);
        bmp = BMP_Create(image->width, image->height, image->bdepth * (image->grayscale ? 1 : 3));
        if(!bmp) {
            return -1;
        }
        for(uint64_t x = 0; x < image->width; x++){
            for(uint64_t y = 0; y < image->height; y++) {
                BMP_SetPixelRGB(bmp, x, y, image->data[((y * image->width)*3) + (x * 3)],
                                           image->data[((y * image->width)*3) + (x * 3) + 1],
                                           image->data[((y * image->width)*3) + (x * 3) + 2]);
            }
        }
        out_fn = malloc(strlen(argv[argc - 1]) + 5);
        strcpy(out_fn, argv[argc - 1]);
        strcat(out_fn, ".bmp");
        printf("Writing BMP to %s\n", out_fn);
        BMP_WriteFile(bmp, out_fn);
    }
    return 0;
}
