#include <iostream>
#include <algorithm>
#include "bitmapRW.h"

#define INPUT "../data/img3.bmp"
#define OUTPUT "../data/img4.bmp"


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

    long long int pxNo = i / 3;

    //keeping in mind that bmp is sometimes written from down-right corner to up-left corner
    //in that case L swaps with R amd U swaps with D, obviously
    //TODO auto-detect how pixel data is written (UL to DR or DR to UL)
    if (pxNo % width == 0) widthBorder = Right;
    else if (pxNo - 1 % width == 0) widthBorder = Left;

    if (pxNo <= width) heightBorder = Up;
    else if ((pxNo <= width * height) && (pxNo >= width * (height - 1))) heightBorder = Dwn;

    return { widthBorder, heightBorder };
}


int main()
{
    byte* pixels; //array for data to be read from image
//    byte* pixels_filtered; //array for data to be written to
//    byte* pixels_prefiltered;
    int32_t width;
    int32_t height;
    uint32_t bytesPerPixel;

    clock_t start, end;

    start = clock();

    ReadImage(INPUT, &pixels, &width, &height, &bytesPerPixel);

    byte* pixels_filtered = (byte*)malloc(width * height * bytesPerPixel);
    byte* pixels_prefiltered = (byte*)malloc(width * height * bytesPerPixel);

    for (int64_t i = 0; i < width * height * bytesPerPixel; i += bytesPerPixel)
    {
        pixels_filtered[i] = 0;
        pixels_filtered[i+1] = 0;
        pixels_filtered[i+2] = 0;
    }

    for (int64_t i = 0; i < width * height * bytesPerPixel; i += bytesPerPixel)
    {
        pixels_prefiltered[i] = 0xff;
        pixels_prefiltered[i + 1] = 0xff;
        pixels_prefiltered[i + 2] = 0xff;
    }


    for (int64_t i = 0; i < width * height * bytesPerPixel; i += bytesPerPixel) {
        int chunk[8];
        border_t border = checkBorder(i, width, height);
        chunk[0] = (border.widthBorder != Left) ? pixels[i - bytesPerPixel] : 0;
        chunk[1] = (border.widthBorder != Right) ? pixels[i + bytesPerPixel] : 0;
        chunk[2] = (border.heightBorder != Dwn) ? pixels[i + bytesPerPixel * width] : 0;
        chunk[3] = (border.heightBorder != Up) ? pixels[i - bytesPerPixel * width] : 0;
        chunk[4] = ((border.heightBorder != Up) && (border.widthBorder != Right)) ? pixels[i - bytesPerPixel * width + bytesPerPixel] : 0;
        chunk[5] = ((border.heightBorder != Up) && (border.widthBorder != Left)) ? pixels[i - bytesPerPixel * width - bytesPerPixel] : 0;
        chunk[6] = ((border.heightBorder != Dwn) && (border.widthBorder != Right)) ? pixels[i + bytesPerPixel * width + bytesPerPixel] : 0;
        chunk[7] = ((border.heightBorder != Dwn) && (border.widthBorder != Left)) ? pixels[i + bytesPerPixel * width - bytesPerPixel] : 0;
        int64_t k = 0;

        for (int64_t j = 0; j <= 7; j++)
        {
            if (chunk[j] == 0)
            {
                pixels_prefiltered[i] = 0;
                pixels_prefiltered[i + 1] = 0;
                pixels_prefiltered[i + 2] = 0;
            }
        }

    }

    for (int64_t i = 0; i < width * height * bytesPerPixel; i += bytesPerPixel) {
        if (pixels_prefiltered[i] != 0)
        {
            for (int64_t j = i; j <= i + 2; j++)
            {
                pixels_filtered[j] = 0xff;

                pixels_filtered[j - bytesPerPixel] = 0xff;

                pixels_filtered[j + bytesPerPixel] = 0xff;

                pixels_filtered[j + bytesPerPixel * width] = 0xff;

                pixels_filtered[j - bytesPerPixel * width] = 0xff;

                pixels_filtered[j - bytesPerPixel * width + bytesPerPixel] = 0xff;

                pixels_filtered[j - bytesPerPixel * width - bytesPerPixel] = 0xff;

                pixels_filtered[j + bytesPerPixel * width + bytesPerPixel] = 0xff;

                pixels_filtered[j + bytesPerPixel * width - bytesPerPixel] = 0xff;
            }
        }
    }
    WriteImage(OUTPUT, pixels_filtered, width, height, bytesPerPixel);

    end = clock();
    double runtime = double(end - start) / double(CLOCKS_PER_SEC);


    printf("%f s\n", runtime);
    free(pixels);
}