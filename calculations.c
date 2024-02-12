/*STAN Andrei - 314CC*/
#include <stdio.h>

#include "data.h"

// functie care calculeaza valoarea medie
// a pixelilor rosii dintr-o zona din imagine

double avereage_red(IMAGE *pic, int x, int y, int size)
{
    int i, j;
    double s = 0;
    for (i = x; i < x + size; i++)
        for (j = y; j < y + size; j++)
            s += (double)pic->img[i][j].r;
    return ((s / (double)size) / (double)size);
}

// functie care calculeaza valoarea medie
// a pixelilor verzi dintr-o zona din imagine
double avereage_green(IMAGE *pic, int x, int y, int size)
{
    int i, j;
    double s = 0;
    for (i = x; i < x + size; i++)
        for (j = y; j < y + size; j++)
            s += (double)pic->img[i][j].g;
    return ((s / (double)size) / (double)size);
}

// functie care calculeaza valoarea medie
// a pixelilor albastrii dintr-o zona din imagine
double avereage_blue(IMAGE *pic, int x, int y, int size)
{
    int i, j;
    double s = 0;
    for (i = x; i < x + size; i++)
        for (j = y; j < y + size; j++)
            s += (double)pic->img[i][j].b;
    return ((s / (double)size) / (double)size);
}

// functie care care calculeaza valoarea medie a unei zone din imagine
// dupa formula din enunt
double calculate_mean(IMAGE *pic, int x, int y, int size)
{
    int i, j;
    double sum = 0;
    double red, green, blue;

    // calculam valoarea medie a pixelilor rosii, verzi si albastrii din poza
    red = avereage_red(pic, x, y, size);
    green = avereage_green(pic, x, y, size);
    blue = avereage_blue(pic, x, y, size);

    // calculam suma din enunt
    for (i = x; i < x + size; i++)
        for (j = y; j < y + size; j++)
        {
            sum += (red - (double)pic->img[i][j].r) * (red - (double)pic->img[i][j].r);
            sum += (green - (double)pic->img[i][j].g) * (green - (double)pic->img[i][j].g);
            sum += (blue - (double)pic->img[i][j].b) * (blue - (double)pic->img[i][j].b);
        }

    // facem impartirea si returnam rezultatul
    return (((sum / 3) / (double)size) / (double)size);
}
