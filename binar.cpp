#include "include/bitmapRW.h"
#include <iostream>

#define MIN_BRIGHTNESS 50
#define INPUT "../data/stars.bmp"
#define OUTPUT "../data/img2.bmp"

//TODO rewrite otsu properly

// Определение порога методом Оцу
int otsuThreshold(byte *pixels_read, int size)
{
    // Проверки на NULL и проч. опустим, чтобы сконцетрироваться
    // на работе метода

    // Посчитаем минимальную и максимальную яркость всех пикселей
    int min = pixels_read[0];
    int max = pixels_read[0];

    for (int i = 1; i < size; i+=3)
    {
        int value = pixels_read[i];

        if (value < min)
            min = value;

        if (value > max)
            max = value;
    }

    // Гистограмма будет ограничена снизу и сверху значениями min и max,
    // поэтому нет смысла создавать гистограмму размером 256 бинов
    int histSize = max - min + 1;
    int* hist = new int[histSize];

    // Заполним гистограмму нулями
    for (int t = 0; t < histSize; t++)
        hist[t] = 0;

    // И вычислим высоту бинов
    for (int i = 0; i < size; i+=3)
        hist[pixels_read[i] - min]++;

    // Введем два вспомогательных числа:
    int m = 0; // m - сумма высот всех бинов, домноженных на положение их середины
    int n = 0; // n - сумма высот всех бинов
    for (int t = 0; t <= max - min; t++)
    {
        m += t * hist[t];
        n += hist[t];
    }

    float maxSigma = -1; // Максимальное значение межклассовой дисперсии
    int threshold = 0; // Порог, соответствующий maxSigma

    int alpha1 = 0; // Сумма высот всех бинов для класса 1
    int beta1 = 0; // Сумма высот всех бинов для класса 1, домноженных на положение их середины

    // Переменная alpha2 не нужна, т.к. она равна m - alpha1
    // Переменная beta2 не нужна, т.к. она равна n - alpha1

    // t пробегается по всем возможным значениям порога
    for (int t = 0; t < max - min; t++)
    {
        alpha1 += t * hist[t];
        beta1 += hist[t];

        // Считаем вероятность класса 1.
        float w1 = (float)beta1 / n;
        // Нетрудно догадаться, что w2 тоже не нужна, т.к. она равна 1 - w1

        // a = a1 - a2, где a1, a2 - средние арифметические для классов 1 и 2
        float a = (float)alpha1 / beta1 - (float)(m - alpha1) / (n - beta1);

        // Наконец, считаем sigma
        float sigma = w1 * (1 - w1) * a * a;

        // Если sigma больше текущей максимальной, то обновляем maxSigma и порог
        if (sigma > maxSigma)
        {
            maxSigma = sigma;
            threshold = t;
        }
    }

    // Не забудем, что порог отсчитывался от min, а не от нуля
    threshold += min;

    // Все, порог посчитан, возвращаем его наверх :)
    return threshold;
}


int main(int argc, char *argv[]) {
    byte *pixels_read;
    byte *pixels_filtered;
    uint32_t width;
    uint32_t height;
    uint32_t bytesPerPixel;

    clock_t start, end;

    start = clock();

    char* input = argv[1];
    char* output = argv[2];

    ReadImage(input, &pixels_read, &width, &height, &bytesPerPixel);

    pixels_filtered = (byte*) malloc(width * height * 1);

    byte threshold = otsuThreshold(pixels_read, width*height);
    //printf("%d\n", threshold);

    for (int64_t i = 0; i < width*height*bytesPerPixel; i+=bytesPerPixel) {
        byte r, g, b;
        b = pixels_read[i];
        g = pixels_read[i+1];
        r = pixels_read[i+2];
        double brightness = (0.2989*r+0.5870*g+0.1140*b);
        //int brightness = r+g+b;
        //if (brightness < 64)
        if (brightness < threshold*3)
        {
            pixels_filtered[i] = 0;
        }
        else {
            pixels_filtered[i] = 1;

        }
    }

    WriteImage(output, pixels_read, width, height, 1);

    end = clock();
    double runtime = double(end - start) / double(CLOCKS_PER_SEC);

    printf("%f\n", runtime);
    free(pixels_read);
}
