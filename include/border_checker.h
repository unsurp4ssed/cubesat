//
// Created by admin on 09.11.2023.
//

#ifndef CUBESAT_BORDER_CHECKER_H
#define CUBESAT_BORDER_CHECKER_H

//typedef enum borderType {
//    NoBorder, Up, Dwn, Left, Right, Up2, Dwn2, Left2, Right2
//} borderType_t;

typedef struct border {
    //borderType widthBorder;
    signed short widthBorderDistance;
    //borderType heightBorder;
    signed short heightBorderDistance;
} border_t;

border_t checkBorder(long long int i, int width, int height) {
    //borderType widthBorder = NoBorder;
    signed short widthBorderDistance = 0;
    //borderType heightBorder = NoBorder;
    signed short heightBorderDistance = 0;

    long long int pxNo = 1 + i / 3;

    //TODO auto-detect how pixel data is written
    //+1/+2 - border to the Right
    if (pxNo % width == 0)            widthBorderDistance = 1;
    else if ((pxNo + 1) % width == 0) widthBorderDistance = 2;
    else if ((pxNo + 2) % width == 0) widthBorderDistance = 3;
    //-1/-2 - border to the Left
    else if ((pxNo - 1) % width == 0)   widthBorderDistance = -1;
    else if ((pxNo - 2) % width == 0)   widthBorderDistance = -2;
    else if ((pxNo - 3) % width == 0)   widthBorderDistance = -3;

    //+1/+2 - border to the Up
    if (pxNo <= width)          heightBorderDistance = 1;
    else if (pxNo <= 2 * width) heightBorderDistance = 2;
    else if (pxNo <= 3 * width) heightBorderDistance = 3;
    //-1/-2 - border to the Down
    else if ((pxNo <= width * height) && (pxNo >= width * (height - 1)))     heightBorderDistance = -1;
    else if ((pxNo <= 2 * width * height) && (pxNo >= width * (height - 2))) heightBorderDistance = -2;
    else if ((pxNo <= 3 * width * height) && (pxNo >= width * (height - 3))) heightBorderDistance = -3;

    return {widthBorderDistance, heightBorderDistance };
}

#endif //CUBESAT_BORDER_CHECKER_H
