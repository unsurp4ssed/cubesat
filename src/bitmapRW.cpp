//
// Created by admin on 15.10.2023.
//

#include "../include/bitmapRW.h"
#include <inttypes.h>

void ReadImage(const char *fileName, byte **pixels, int32_t *width, int32_t *height, uint32_t *bytesPerPixel)
{
    //HEADER READING
    FILE *imageFile = fopen(fileName, "rb");
    long dataOffset;

    fseek(imageFile, DATA_OFFSET_OFFSET, SEEK_SET);
    fread(&dataOffset, 4, 1, imageFile);

    fseek(imageFile, WIDTH_OFFSET, SEEK_SET);
    fread(width, 4, 1, imageFile);
    *width = abs(*width);

    fseek(imageFile, HEIGHT_OFFSET, SEEK_SET);
    fread(height, 4, 1, imageFile);
    *height = abs(*height);

    uint32_t bitsPerPixel;
    fseek(imageFile, BITS_PER_PIXEL_OFFSET, SEEK_SET);
    fread(&bitsPerPixel, 2, 1, imageFile);
    *bytesPerPixel = (bitsPerPixel) / 8;

    //reading pixel data
    uint32_t unpaddedRowSize = (*width)*(*bytesPerPixel);
    uint32_t paddedRowSize = unpaddedRowSize;
    while (paddedRowSize % 4 != 0) {
        paddedRowSize++;
    }
    uint32_t totalSize = unpaddedRowSize*(*height);
    *pixels = (byte*)malloc(totalSize);
    byte *currentRowPointer = *pixels+((*height-1)*unpaddedRowSize);
    for (int i = 0; i < *height; i++) //going from height value down to 0 bc libcamera writes from lower left corner instead og higher left
    {
        fseek(imageFile, dataOffset+(i*paddedRowSize), SEEK_SET);
        fread(currentRowPointer, 1, unpaddedRowSize, imageFile);
        currentRowPointer -= unpaddedRowSize;
    }
    fclose(imageFile);
}

void WriteImage(const char *fileName, byte *pixels, uint32_t width, uint32_t height, uint32_t bytesPerPixel)
{
    FILE *outputFile = fopen(fileName, "wb");
    //*****HEADER*******//
    const char *BM = "BM";
    fwrite(&BM[0], 1, 1, outputFile);
    fwrite(&BM[1], 1, 1, outputFile);

    uint32_t unpaddedRowSize = width*bytesPerPixel;
    uint32_t paddedRowSize = unpaddedRowSize;
    while (paddedRowSize % 4 != 0) {
        paddedRowSize++;
    }

    uint32_t fileSize = paddedRowSize*height + HEADER_SIZE + INFO_HEADER_SIZE;
    fwrite(&fileSize, 4, 1, outputFile);
    uint32_t reserved = 0x0000;
    fwrite(&reserved, 4, 1, outputFile);
    uint32_t dataOffset = HEADER_SIZE+INFO_HEADER_SIZE;
    fwrite(&dataOffset, 4, 1, outputFile);

    //*******INFO*HEADER******//
    uint32_t infoHeaderSize = INFO_HEADER_SIZE;
    fwrite(&infoHeaderSize, 4, 1, outputFile);

    fwrite(&width, 4, 1, outputFile);
    fwrite(&height, 4, 1, outputFile);

    uint16_t planes = 1; //always 1
    fwrite(&planes, 2, 1, outputFile);

    uint16_t bitsPerPixel = bytesPerPixel * 8;
    fwrite(&bitsPerPixel, 2, 1, outputFile);

    //write compression
    uint32_t compression = NO_COMPRESSION;
    fwrite(&compression, 4, 1, outputFile);

    //write image size (in bytes)
    uint32_t imageSize = width*height*bytesPerPixel;
    fwrite(&imageSize, 4, 1, outputFile);
    uint32_t resolutionX = 11811; //300 dpi
    uint32_t resolutionY = 11811; //300 dpi
    fwrite(&resolutionX, 4, 1, outputFile);
    fwrite(&resolutionY, 4, 1, outputFile);

    uint32_t colorsUsed = MAX_NUMBER_OF_COLORS;
    fwrite(&colorsUsed, 4, 1, outputFile);
    uint32_t importantColors = ALL_COLORS_REQUIRED;
    fwrite(&importantColors, 4, 1, outputFile);

    for (uint32_t i = 0; i < height; i++)
    {
        uint32_t pixelOffset = ((height - i) - 1)*unpaddedRowSize;
        fwrite(&pixels[pixelOffset], 1, paddedRowSize, outputFile);
    }
    fclose(outputFile);
}