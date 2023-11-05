#include <iostream>
#include <algorithm>
#include "bitmapRW.h"

typedef enum borderType {
    NoBorder, Up, Dwn, Left, Right
} borderSize;

typedef struct border {
    borderSize widthBorder;
    borderSize heightBorder;
} border_t;

border_t checkBorder(long long int i, int width, int height) {
    borderSize widthBorder = NoBorder;
    borderSize heightBorder = NoBorder;

    long long int pxNo = i/3;

    //keeping in mind that bmp is (usually) written from down-right corner to up-left corner
    if (pxNo % width == 0) widthBorder = Right;
    else if (pxNo-1 % width == 0) widthBorder = Left;

    if (pxNo <= width) heightBorder = Up;
    else if ((pxNo <= width*height) && (pxNo >= width*(height-1))) heightBorder = Dwn;

    return {widthBorder, heightBorder};
}

int main() {
    byte *pixels;
    byte *pixels_filtered;
    int32_t width;
    int32_t height;
    uint32_t bytesPerPixel;

    clock_t start, end;

    start = clock();

    ReadImage("../data/img2.bmp", &pixels, &width, &height, &bytesPerPixel);


    pixels_filtered = (byte*) malloc(width * height *bytesPerPixel);

    for (int64_t i = 0; i < width * height * bytesPerPixel; i+=bytesPerPixel) {
        int chunk[9];
        border_t border = checkBorder(i, width, height);

        //central pixel
        chunk[0] = pixels[i];
        //on the L and R sides
        chunk[1] = pixels[i - bytesPerPixel] * (border.widthBorder != Left);
        chunk[2] = pixels[i + bytesPerPixel] * (border.widthBorder != Right);
        //on the U and D sides
        chunk[3] = (border.heightBorder != Dwn) ? pixels[i + bytesPerPixel * width] : 0;
        chunk[4] = (border.heightBorder != Up) ? pixels[i - bytesPerPixel * width] : 0;
        //upper corners
        chunk[5] = ((border.heightBorder != Up) && (border.widthBorder != Right)) ? pixels[i - bytesPerPixel * width + bytesPerPixel] : 0;
        chunk[6] = ((border.heightBorder != Up) && (border.widthBorder != Left)) ? pixels[i - bytesPerPixel * width - bytesPerPixel] : 0;
        //bottom corners
        chunk[7] = ((border.heightBorder != Dwn) && (border.widthBorder != Right)) ? pixels[i + bytesPerPixel * width + bytesPerPixel] : 0;
        chunk[8] = ((border.heightBorder != Dwn) && (border.widthBorder != Left)) ? pixels[i + bytesPerPixel * width - bytesPerPixel] : 0;


        std::sort(chunk, chunk + 9);

        pixels_filtered[i] = chunk[5];
        pixels_filtered[i+1] = chunk[5];
        pixels_filtered[i+2] = chunk[5];
    }

    WriteImage("../data/img3.bmp", pixels_filtered, width, height, bytesPerPixel);

    end = clock();
    double runtime = double(end - start) / double(CLOCKS_PER_SEC);


    printf("%f s\n", runtime);
    free(pixels);
}


