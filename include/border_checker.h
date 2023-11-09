//
// Created by admin on 09.11.2023.
//

#ifndef CUBESAT_BORDER_CHECKER_H
#define CUBESAT_BORDER_CHECKER_H

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

#endif //CUBESAT_BORDER_CHECKER_H
