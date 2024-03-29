//
// Created by admin on 09.11.2023.
//

#ifndef CUBESAT_BORDER_CHECKER_H
#define CUBESAT_BORDER_CHECKER_H

typedef enum borderType {
    NoBorder, Up, Dwn, Left, Right, Up2, Dwn2, Left2, Right2
} borderType_t;

typedef struct border {
    borderType widthBorder;
    borderType heightBorder;
} border_t;

border_t checkBorder(long long int i, int width, int height) {
    borderType widthBorder = NoBorder;
    borderType heightBorder = NoBorder;

    long long int pxNo = i / 3;

    //keeping in mind that bmp is written from down-right corner to up-left corner
    //TODO auto-detect how pixel data is written (UL to DR or DR to UL)
    if (pxNo % width == 0) widthBorder = Right;
    else if (pxNo %  2*width == 0) widthBorder = Right2;
    else if (pxNo -  width == 0) widthBorder = Left;
    else if (pxNo -  width == 1) widthBorder = Left2;

    if (pxNo <= width) heightBorder = Up;
    else if (pxNo <=2* width) heightBorder = Up2;
    else if ((pxNo <= width * height) && (pxNo >= width * (height - 1))) heightBorder = Dwn;
    else if ((pxNo <= 2 * width * height) && (pxNo >= width * (height - 2))) heightBorder = Dwn2;

    return { widthBorder, heightBorder };
}

#endif //CUBESAT_BORDER_CHECKER_H
