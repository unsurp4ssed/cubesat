//
// Created by admin on 15.10.2023.
//

#ifndef CUBESAT_BITMAPRW_H
#define CUBESAT_BITMAPRW_H

#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>

#define OFFSET_SIGNATURE 0x00
#define OFFSET_FILESIZE 0x02
#define OFFSET_RESERVED 0x06
#define OFFSET_DATAOFFSET 0x0A
#define OFFSET_HEADERSIZE 0x0E
#define OFFSET_WIDTH 0x12
#define OFFSET_HEIGHT 0x16
#define OFFSET_PLANES 0x1A
#define OFFSET_BITS_PER_PIXEL 0x1C
#define OFFSET_COMPRESSION 0x1E
#define OFFSET_IMGSIZE 0x22
#define OFFSET_DPIX 0x26
#define OFFSET_DPIY 0x2A
#define OFFSET_COLORS 0x2E
#define OFFSET_IMPORTANT_COLORS 0x32

#define HEADER_SIZE 14
#define INFO_HEADER_SIZE 40
#define NO_COMPRESSION 0
#define MAX_NUMBER_OF_COLORS 0
#define ALL_COLORS_REQUIRED 0

typedef uint8_t byte;

void ReadImage(const char *fileName, byte **pixels, uint32_t *width, uint32_t *height, uint32_t *bytesPerPixel);
void WriteImage(const char *fileName, byte *pixels, uint32_t width, uint32_t height, uint32_t bytesPerPixel);

#endif