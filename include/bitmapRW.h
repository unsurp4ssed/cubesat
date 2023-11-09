//
// Created by admin on 15.10.2023.
//

#ifndef CUBESAT_BITMAPRW_H
#define CUBESAT_BITMAPRW_H

#include <iostream>

#define DATA_OFFSET_OFFSET 0x000A
#define WIDTH_OFFSET 0x0012
#define HEIGHT_OFFSET 0x0016
#define BITS_PER_PIXEL_OFFSET 0x001C
#define HEADER_SIZE 14
#define INFO_HEADER_SIZE 40
#define NO_COMPRESSION 0
#define MAX_NUMBER_OF_COLORS 0
#define ALL_COLORS_REQUIRED 0
//header offset values according to a certain bmp format we work with

typedef unsigned char byte;

typedef struct pixel {
    byte r;
    byte g;
    byte b;
} pixel_t;


void ReadImage(const char *fileName, byte **pixels, int32_t *width, int32_t *height, uint32_t *bytesPerPixel);
void WriteImage(const char *fileName, byte *pixels, uint32_t width, uint32_t height, uint32_t bytesPerPixel);

#endif