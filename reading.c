/*STAN Andrei - 314CC*/
#include <stdio.h>
#include <stdlib.h>

#include "data.h"

//functie care citeste un pisier PPM P6
void read_ppm(IMAGE *pic, FILE *fin)
{
    int i, j;
    unsigned char aux;
    //FILE *fout;
    //fout = fopen("verif_img.txt", "wt");

    //prima data citim partea text a fisierului
    fscanf(fin, "P6\n%d %d\n%d\n", &(pic->width), &(pic->height), &(pic->max_col));
    //fgetc(fin);
    // printf("%d %d %d\n", pic->width, pic->height, pic->max_col);


    pic->img = malloc(pic->height * sizeof(PIXEL *));
    if(pic->img==NULL)
    {
        printf("Nu s-a putut aloca memorie pentru matricea care stocheaza imaginea");
        exit(1);
    }
    for (i = 0; i < pic->height; i++)
    {
        pic->img[i] = malloc(pic->width * sizeof(PIXEL));
        if(pic->img[i]==NULL)
    {
        printf("Nu s-a putut aloca memorie pentru matricea care stocheaza imaginea");
        exit(1);
    }
    }

    for (i = 0; i < pic->height; i++)
    {
        for (j = 0; j < pic->width; j++)
        {
            fread(&aux, sizeof(unsigned char), 1, fin);
            pic->img[i][j].r = aux;
            fread(&aux, sizeof(unsigned char), 1, fin);
            pic->img[i][j].g = aux;
            fread(&aux, sizeof(unsigned char), 1, fin);
            pic->img[i][j].b = aux;
        }
    }
}