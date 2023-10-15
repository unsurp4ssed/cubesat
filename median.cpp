#include <iostream>
#include "bitmapRW.h"

byte middle_of_3(byte a, byte b, byte c) {
    byte middle;
    if ((a <= b) && (a <= c)) { middle = (b <= c) ? b : c; }
    else if ((b <= a) && (b <= c))
    { middle = (a <= c) ? a : c; }
    else { middle = (a <= b) ? a : b; }
    return middle;}

int main() {
    byte *pixels;
    int32_t width;
    int32_t height;
    uint32_t bytesPerPixel;

    clock_t start, end;

    start = clock();

    ReadImage("../data/img2.bmp", &pixels, &width, &height, &bytesPerPixel);

    for (int64_t i = 0; i < width * height * bytesPerPixel; i+=bytesPerPixel) {
        if (i + 6 < width * height * bytesPerPixel) {
            pixels[i+3] = middle_of_3(pixels[i], pixels[i+3], pixels[i+6]);
            pixels[i+4] = pixels[i+3];
            pixels[i+5] = pixels[i+3];
        }
    }

    WriteImage("../data/img3.bmp", pixels, width, height, bytesPerPixel);

    end = clock();
    double runtime = double(end - start) / double(CLOCKS_PER_SEC);


    printf("%f s\n", runtime);
    free(pixels);
}


