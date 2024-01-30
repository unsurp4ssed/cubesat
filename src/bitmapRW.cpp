//
// Created by admin on 15.10.2023.
//

#include "../include/bitmapRW.h"

void ReadImage(const char *fileName, byte **pixels, uint32_t *width, uint32_t *height, uint32_t *bytesPerPixel) {
    FILE *imageFile = fopen(fileName, "rb");

    uint32_t dataOffset;
    fseek(imageFile, OFFSET_DATAOFFSET, SEEK_SET);
    fread(&dataOffset, 4, 1, imageFile);

    fseek(imageFile, OFFSET_WIDTH, SEEK_SET);
    fread(width, 4, 1, imageFile);
    //*width = abs(*width);

    fseek(imageFile, OFFSET_HEIGHT, SEEK_SET);
    fread(height, 4, 1, imageFile);
    //*height = abs(*height);

    uint16_t bitsPerPixel;
    fseek(imageFile, OFFSET_BITS_PER_PIXEL, SEEK_SET);
    fread(&bitsPerPixel, 2, 1, imageFile);
    *bytesPerPixel = (uint32_t) (bitsPerPixel) / 8;

    uint32_t unpaddedRowSize = (*width)*(*bytesPerPixel);
    uint32_t paddedRowSize = unpaddedRowSize;
    while (paddedRowSize % 4 != 0) {
        paddedRowSize++;
    }

    uint64_t totalSize = (*width)*(*height)*(*bytesPerPixel);

    *pixels = (byte*)malloc(totalSize);
    if (*pixels == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    byte *currentRowPointer = *pixels+((*height-1)*unpaddedRowSize);

    for (int i = 0; i < *height; i++)
    {
        fseek(imageFile, dataOffset+(i*paddedRowSize), SEEK_SET);
        fread(currentRowPointer, 1, unpaddedRowSize, imageFile);
        currentRowPointer -= unpaddedRowSize;
    }
    fclose(imageFile);
}

void WriteImage(const char *fileName, byte *pixels, uint32_t width, uint32_t height, uint32_t bytesPerPixel) {
    FILE *outputFile = fopen(fileName, "wb");
    fseek(outputFile, OFFSET_SIGNATURE, 0);
    const char *BM = "BM";
    fwrite(&BM[0], 1, 1, outputFile);
    fwrite(&BM[1], 1, 1, outputFile);

    uint32_t unpaddedRowSize = width*bytesPerPixel;
    uint32_t paddedRowSize = unpaddedRowSize;
    while (paddedRowSize % 4 != 0) {
        paddedRowSize++;
    }

    uint32_t fileSize = paddedRowSize*height + HEADER_SIZE + INFO_HEADER_SIZE;
    fseek(outputFile, OFFSET_FILESIZE, 0);
    fwrite(&fileSize, 4, 1, outputFile);

    uint32_t reserved = 0x0000;
    fseek(outputFile, OFFSET_RESERVED, 0);
    fwrite(&reserved, 4, 1, outputFile);

    uint32_t dataOffset = HEADER_SIZE+INFO_HEADER_SIZE;
    fseek(outputFile, OFFSET_DATAOFFSET, 0);
    fwrite(&dataOffset, 4, 1, outputFile);


    uint32_t infoHeaderSize = INFO_HEADER_SIZE;
    fseek(outputFile, OFFSET_HEADERSIZE, 0);
    fwrite(&infoHeaderSize, 4, 1, outputFile);

    fseek(outputFile, OFFSET_WIDTH, 0);
    fwrite(&width, 4, 1, outputFile);
    fseek(outputFile, OFFSET_HEIGHT, 0);
    fwrite(&height, 4, 1, outputFile);

    uint16_t planes = 1; //always 1
    fseek(outputFile, OFFSET_PLANES, 0);
    fwrite(&planes, 2, 1, outputFile);

    uint16_t bitsPerPixel = bytesPerPixel * 8;
    fseek(outputFile, OFFSET_BITS_PER_PIXEL, 0);
    fwrite(&bitsPerPixel, 2, 1, outputFile);

    //write compression
    uint32_t compression = NO_COMPRESSION;
    fseek(outputFile, OFFSET_COMPRESSION, 0);
    fwrite(&compression, 4, 1, outputFile);


    //write image size (in bytes)
    uint32_t imageSize = width*height*bytesPerPixel;
    fseek(outputFile, OFFSET_IMGSIZE, 0);
    fwrite(&imageSize, 4, 1, outputFile);

    uint32_t resolutionX = 11811; //300 dpi
    uint32_t resolutionY = 11811; //300 dpi
    fseek(outputFile, OFFSET_DPIX, 0);
    fwrite(&resolutionX, 4, 1, outputFile);
    fseek(outputFile, OFFSET_DPIY, 0);
    fwrite(&resolutionY, 4, 1, outputFile);

    uint32_t colorsUsed = 1;
    for (uint16_t i = 0; i < bitsPerPixel; i++) {
        colorsUsed *= colorsUsed;
    }
    fseek(outputFile, OFFSET_COLORS, 0);
    fwrite(&colorsUsed, 4, 1, outputFile);

    uint32_t importantColors = ALL_COLORS_REQUIRED;
    fseek(outputFile, OFFSET_IMPORTANT_COLORS, 0);
    fwrite(&importantColors, 4, 1, outputFile);

    for (uint32_t i = 0; i < height; i++)
    {
        uint32_t pixelOffset = ((height - i) - 1)*unpaddedRowSize;
        fwrite(&pixels[pixelOffset], 1, paddedRowSize, outputFile);
    }
    fclose(outputFile);

}