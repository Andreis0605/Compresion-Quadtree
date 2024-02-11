/*STAN Andrei - 314CC*/
#include <stdio.h>

#include "data.h"

//functie care calculeaza valoarea medie 
//a pixelilor rosii dintr-o zona din imagine
unsigned int avereage_red(IMAGE *pic, int x, int y, int size)
{
    unsigned long long i, j, s = 0;
    for (i = x; i < x + size; i++)
        for (j = y; j < y + size; j++)
            s += pic->img[i][j].r;
    return (unsigned int)(s / (size * size));
}

//functie care calculeaza valoarea medie 
//a pixelilor verzi dintr-o zona din imagine
unsigned int avereage_green(IMAGE *pic, int x, int y, int size)
{
    unsigned long long i, j, s = 0;
    for (i = x; i < x + size; i++)
        for (j = y; j < y + size; j++)
            s += pic->img[i][j].g;
    return (unsigned int)(s / (size * size));
}

//functie care calculeaza valoarea medie 
//a pixelilor albastrii dintr-o zona din imagine
unsigned int avereage_blue(IMAGE *pic, int x, int y, int size)
{
    unsigned long long i, j, s = 0;
    for (i = x; i < x + size; i++)
        for (j = y; j < y + size; j++)
            s += pic->img[i][j].b;
    return (unsigned int)(s / (size * size));
}

//functie care care calculeaza valoarea medie a unei zone din imagine
//dupa formula din enunt
unsigned long long calculate_mean(IMAGE *pic, int x, int y, int size)
{
    int i, j;
    unsigned long long sum = 0;
    unsigned long long red, green, blue;

    //calculam valoarea medie a pixelilor rosii, verzi si albastrii din poza
    red = (unsigned long long)avereage_red(pic, x, y, size);
    green = (unsigned long long)avereage_green(pic, x, y, size);
    blue = (unsigned long long)avereage_blue(pic, x, y, size);

    //calculam suma din enunt
    for (i = x; i < x + size; i++)
        for (j = y; j < y + size; j++)
        {
            sum += (red - (unsigned long long)pic->img[i][j].r) * (red - (unsigned long long)pic->img[i][j].r);
            sum += (green - (unsigned long long)pic->img[i][j].g) * (red - (unsigned long long)pic->img[i][j].g);
            sum += (blue - (unsigned long long)pic->img[i][j].b) * (red - (unsigned long long)pic->img[i][j].b);
        }

    //facem impartirea si returnam rezultatul
    return sum / (3 * size * size);
}
