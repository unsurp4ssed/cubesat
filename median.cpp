#include <iostream>
#include <algorithm>
#include "include/bitmapRW.h"
#include "include/border_checker.h"

#define INPUT "../data/img2.bmp"
#define OUTPUT "../data/img3.bmp"

int main() {
    byte *pixels; //array for data to be read from image
    byte *pixels_filtered; //array for data to be written to
    int32_t width;
    int32_t height;
    uint32_t bytesPerPixel;

    clock_t start, end;

    start = clock();

    ReadImage(INPUT, &pixels, &width, &height, &bytesPerPixel);

    pixels_filtered = (byte*) malloc(width * height *bytesPerPixel);

    for (int64_t i = 0; i < width * height * bytesPerPixel; i+=bytesPerPixel) {
        int chunk[9]; //chunk of pixels surrounding A0
//        [][  ][]
//        [][A0][]
//        [][  ][]
        border_t border = checkBorder(i, width, height);
        //central pixel
        chunk[0] = pixels[i];
        //on the L and R sides
        chunk[1] = (border.widthBorder != Left) ? pixels[i - bytesPerPixel] : 0;
        chunk[2] = (border.widthBorder != Right) ? pixels[i + bytesPerPixel] : 0;
        //on the U and D sides
        chunk[3] = (border.heightBorder != Dwn) ? pixels[i + bytesPerPixel * width] : 0;
        chunk[4] = (border.heightBorder != Up) ? pixels[i - bytesPerPixel * width] : 0;
        //upper corners
        chunk[5] = ((border.heightBorder != Up) && (border.widthBorder != Right)) ? pixels[i - bytesPerPixel * width + bytesPerPixel] : 0;
        chunk[6] = ((border.heightBorder != Up) && (border.widthBorder != Left)) ? pixels[i - bytesPerPixel * width - bytesPerPixel] : 0;
        //bottom corners
        chunk[7] = ((border.heightBorder != Dwn) && (border.widthBorder != Right)) ? pixels[i + bytesPerPixel * width + bytesPerPixel] : 0;
        chunk[8] = ((border.heightBorder != Dwn) && (border.widthBorder != Left)) ? pixels[i + bytesPerPixel * width - bytesPerPixel] : 0;

        std::sort(chunk, chunk + 9); //std::sort gets 2 address of the piece of memory to be sorted - beginning and the end.

        //after sorting, the median value gonna end up in the 5th place in the array
        pixels_filtered[i] = chunk[5];
        pixels_filtered[i+1] = chunk[5];
        pixels_filtered[i+2] = chunk[5];
    }

    WriteImage(OUTPUT, pixels_filtered, width, height, bytesPerPixel);

    end = clock();
    double runtime = double(end - start) / double(CLOCKS_PER_SEC);


    printf("%f s\n", runtime);
    free(pixels);
}


