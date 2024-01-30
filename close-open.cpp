#include <iostream>
#include <algorithm>
#include "include/bitmapRW.h"
#include "border_checker.h"

#define INPUT "../data/img3.bmp"
#define OUTPUT "../data/img20.bmp"

int main(int argc, char *argv[])
{
    byte* pixels; //array for data to be read from image
    byte* pixels_filtered; //array for data to be written to
    byte* pixels_prefiltered;
    uint32_t width;
    uint32_t height;
    uint32_t bytesPerPixel;

    char* input = argv[1];
    char* output = argv[2];

    clock_t start, end;

    start = clock();

    ReadImage(input, &pixels, &width, &height, &bytesPerPixel);

    pixels_filtered = (byte*)malloc(width * height * bytesPerPixel);
    pixels_prefiltered = (byte*)malloc(width * height * bytesPerPixel);

    for (int64_t i = 0; i < width * height * bytesPerPixel; i += bytesPerPixel)
    {
        pixels_filtered[i] = 0;
        pixels_filtered[i + 1] = 0;
        pixels_filtered[i + 2] = 0;
    }

    for (int64_t i = 0; i < width * height * bytesPerPixel; i += bytesPerPixel)
    {
        pixels_prefiltered[i] = 0xff;
        pixels_prefiltered[i + 1] = 0xff;
        pixels_prefiltered[i + 2] = 0xff;
    }

    for (int64_t i = 0; i < width * height * bytesPerPixel; i += bytesPerPixel) {
        int chunk[24];
        border_t border = checkBorder(i, width, height);
        //LR
        chunk[0] = (border.widthBorder != Left) ? pixels[i - bytesPerPixel] : 0;
        chunk[1] = (border.widthBorder != Left2) ? pixels[i - 2*bytesPerPixel] : 0;
        chunk[2] = (border.widthBorder != Right) ? pixels[i + bytesPerPixel] : 0;
        chunk[3] = (border.widthBorder != Right2) ? pixels[i + 2*bytesPerPixel] : 0;
        //UD
        chunk[4] = (border.heightBorder != Dwn) ? pixels[i + bytesPerPixel * width] : 0;
        chunk[5] = (border.heightBorder != Up) ? pixels[i - bytesPerPixel * width] : 0;
        chunk[6] = (border.heightBorder != Dwn2) && (border.heightBorder != Dwn) ? pixels[i+ 2 * bytesPerPixel * width] : 0;
        chunk[7] = (border.heightBorder != Up2) && (border.heightBorder != Up) ? pixels[i - 2 * bytesPerPixel * width] : 0;

        chunk[8] = ((border.heightBorder != Up2) && (border.heightBorder != Up) && (border.widthBorder != Right2)) ? pixels[i - bytesPerPixel * width + bytesPerPixel] : 0;
        chunk[9] = ((border.heightBorder != Up2) && (border.heightBorder != Up) && (border.widthBorder != Right2)) ? pixels[i - bytesPerPixel * 2*width + 2*bytesPerPixel] : 0;
        chunk[10] = ((border.heightBorder != Up2) && (border.heightBorder != Up) && (border.widthBorder != Right2)) ? pixels[i - bytesPerPixel * 2 * width +  bytesPerPixel] : 0;
        chunk[11] = ((border.heightBorder != Up2) && (border.heightBorder != Up) && (border.widthBorder != Right2)) ? pixels[i - bytesPerPixel * width + 2*bytesPerPixel] : 0;

        chunk[12] = ((border.heightBorder != Up2) && (border.heightBorder != Up) && (border.widthBorder != Left2)) ? pixels[i - bytesPerPixel * width - bytesPerPixel] : 0;
        chunk[13] = ((border.heightBorder != Up2) && (border.heightBorder != Up) && (border.widthBorder != Left2)) ? pixels[i - bytesPerPixel * width -2* bytesPerPixel] : 0;
        chunk[14] = ((border.heightBorder != Up2) && (border.heightBorder != Up) && (border.widthBorder != Left2)) ? pixels[i - 2*bytesPerPixel * width - bytesPerPixel] : 0;
        chunk[15] = ((border.heightBorder != Up2) && (border.heightBorder != Up) && (border.widthBorder != Left2)) ? pixels[i - 2*bytesPerPixel * width - 2*bytesPerPixel] : 0;

        chunk[16] = ((border.heightBorder != Dwn2) && (border.heightBorder != Dwn) && (border.widthBorder != Right2)) ? pixels[i + bytesPerPixel * width + bytesPerPixel] : 0;
        chunk[17] = ((border.heightBorder != Dwn2) && (border.heightBorder != Dwn) && (border.widthBorder != Right2)) ? pixels[i + bytesPerPixel * width + 2*bytesPerPixel] : 0;
        chunk[18] = ((border.heightBorder != Dwn2) && (border.heightBorder != Dwn) && (border.widthBorder != Right2)) ? pixels[i + 2*bytesPerPixel * width + bytesPerPixel] : 0;
        chunk[19] = ((border.heightBorder != Dwn2) && (border.heightBorder != Dwn) && (border.widthBorder != Right2)) ? pixels[i + 2*bytesPerPixel * width + 2*bytesPerPixel] : 0;

        chunk[20] = ((border.heightBorder != Dwn2) && (border.heightBorder != Dwn) && (border.widthBorder != Left2)) ? pixels[i + bytesPerPixel * width - bytesPerPixel] : 0;
        chunk[21] = ((border.heightBorder != Dwn2) && (border.heightBorder != Dwn) && (border.widthBorder != Left2)) ? pixels[i + bytesPerPixel * width - 2*bytesPerPixel] : 0;
        chunk[22] = ((border.heightBorder != Dwn2) && (border.heightBorder != Dwn) && (border.widthBorder != Left2)) ? pixels[i + 2*bytesPerPixel * width - bytesPerPixel] : 0;
        chunk[23] = ((border.heightBorder != Dwn2) && (border.heightBorder != Dwn) && (border.widthBorder != Left2)) ? pixels[i + 2*bytesPerPixel * width - 2*bytesPerPixel] : 0;

        for (int64_t j = 0; j <= 23; j++)
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
                pixels_filtered[j - 2 * bytesPerPixel] = 0xff;
                pixels_filtered[j + bytesPerPixel] = 0xff;
                pixels_filtered[j + 2*bytesPerPixel] = 0xff;


                pixels_filtered[j + bytesPerPixel * width] = 0xff;
                pixels_filtered[j - bytesPerPixel * width] = 0xff;
                pixels_filtered[j + 2*bytesPerPixel * width] = 0xff;
                pixels_filtered[j - 2*bytesPerPixel * width] = 0xff;

                pixels_filtered[j - bytesPerPixel * width + bytesPerPixel] = 0xff;
                pixels_filtered[j - bytesPerPixel * width + 2*bytesPerPixel] = 0xff;
                pixels_filtered[j - 2*bytesPerPixel * width + bytesPerPixel] = 0xff;
                pixels_filtered[j - 2*bytesPerPixel * width + 2*bytesPerPixel] = 0xff;

                pixels_filtered[j - bytesPerPixel * width - bytesPerPixel] = 0xff;
                pixels_filtered[j - bytesPerPixel * width - 2*bytesPerPixel] = 0xff;
                pixels_filtered[j - 2*bytesPerPixel * width - bytesPerPixel] = 0xff;
                pixels_filtered[j - 2*bytesPerPixel * width - 2*bytesPerPixel] = 0xff;

                pixels_filtered[j + bytesPerPixel * width + bytesPerPixel] = 0xff;
                pixels_filtered[j + bytesPerPixel * width + 2*bytesPerPixel] = 0xff;
                pixels_filtered[j + 2*bytesPerPixel * width + bytesPerPixel] = 0xff;
                pixels_filtered[j + 2*bytesPerPixel * width + 2*bytesPerPixel] = 0xff;

                pixels_filtered[j + bytesPerPixel * width - bytesPerPixel] = 0xff;
                pixels_filtered[j + bytesPerPixel * width - 2*bytesPerPixel] = 0xff;
                pixels_filtered[j + 2*bytesPerPixel * width - bytesPerPixel] = 0xff;
                pixels_filtered[j + 2*bytesPerPixel * width - 2*bytesPerPixel] = 0xff;
            }
        }
    }

    WriteImage(output, pixels_filtered, width, height, bytesPerPixel);

    end = clock();
    double runtime = double(end - start) / double(CLOCKS_PER_SEC);

    printf("%f\n", runtime);

    
//Даня, это тебе
    byte* pixel_data_bin;
    pixel_data_bin = (byte*) malloc(width * height);
    int64_t j = 0;
    int64_t i = 0;
    while (i < width*height*bytesPerPixel){
        pixel_data_bin[j] = pixels_filtered[i] 
        i+=bytesPerPixel;
        j++;
    }
    //теперь в pixel_data_bin хранятся последовательно пиксели (из правого нижнего угла в левый верхний (sic!))
    //его можно использовать дальше или записать в любой файл ("wb")
    
    free(pixel_data_bin);

    free(pixels_filtered);
    free(pixels_prefiltered);
    free(pixels);
}
