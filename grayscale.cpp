//BMP RGB TO GRAYSCALE
//09.09.24

#include "include/bitmapRW.h"
#include <math.h>
#include <ctime>

//https://en.wikipedia.org/wiki/Grayscale#Converting_color_to_grayscale
byte RGBtoGRayscale(byte r, byte g, byte b) {
    float r_rgb = r/255; float g_rgb = g/255; float b_rgb = b/255;
    float r_lin = (r_rgb <= 0.04045) ? (r_rgb/12.92): (pow(((r_rgb+0.055)/1.055), 2.4)); 
    float g_lin = (g_rgb <= 0.04045) ? (g_rgb/12.92): (pow(((g_rgb+0.055)/1.055), 2.4)); 
    float b_lin = (b_rgb <= 0.04045) ? (b_rgb/12.92): (pow(((b_rgb+0.055)/1.055), 2.4)); 

    float y_lin = (0.2126*r_lin+0.7152*g_lin+0.0722*b_lin);
    byte y_rgb = (y_lin <= 0.0031308) ? ((byte)12.92*y_lin) : ((byte) 1.055*pow(y_lin, (1/2.4) - 0.055));
    return y_rgb;
}


int main(int argc, char *argv[]) {
    byte *pixels;
    int32_t width;
    int32_t height;
    uint32_t bytesPerPixel;

    clock_t start, end;

    start = clock();

    char* input = argv[1];
    char* output = argv[2];

    ReadImage(input, &pixels, &width, &height, &bytesPerPixel);

    //do stuff
    for (int64_t i = 0; i < (uint64_t) width*height*bytesPerPixel; i+=bytesPerPixel) {
        byte r, g, b;
        b = pixels[i];
        g = pixels[i+1];
        r = pixels[i+2];

        pixels[i] = RGBtoGRayscale(r, g, b);
        pixels[i+1] = RGBtoGRayscale(r, g, b);
        pixels[i+2] = RGBtoGRayscale(r, g, b);
    }

    WriteImage(output, pixels, width, height, bytesPerPixel);

    end = clock();
    double runtime = double(end - start) / double(CLOCKS_PER_SEC);

    printf("%f\n", runtime);

    free(pixels);
}
