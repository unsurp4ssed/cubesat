#include "bitmapRW.h"
#include <iostream>

#define MIN_BRIGHTNESS 50

int main() {
    byte *pixels;
    int32_t width;
    int32_t height;
    uint32_t bytesPerPixel;

    clock_t start, end;

    start = clock();

    ReadImage("../data/stars.bmp", &pixels, &width, &height, &bytesPerPixel);
    //printf("%dx%d %d-byte colour\n", width, height, bytesPerPixel);

    for (int64_t i = 0; i < width*height*bytesPerPixel; i+=bytesPerPixel) {
        byte r, g, b;
        b = pixels[i];
        g = pixels[i+1];
        r = pixels[i+2];
        double brightness = (0.2989*r+0.5870*g+0.1140*b);
        //int brightness = r+g+b;
        //if (brightness < 330)
        if (brightness < MIN_BRIGHTNESS)
        {
            pixels[i] = 0;
            pixels[i+1] = 0;
            pixels[i+2] = 0;
        }
        else {
            pixels[i] = 0xff;
            pixels[i+1] = 0xff;
            pixels[i+2] = 0xff;
        }
    }

    WriteImage("../data/img2.bmp", pixels, width, height, bytesPerPixel);

    end = clock();
    double runtime = double(end - start) / double(CLOCKS_PER_SEC);

    printf("%fs\n", runtime);
    free(pixels);
}