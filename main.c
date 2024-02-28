/*STAN Andrei - 314CC*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"
#include "reading.h"
#include "calculations.h"
#include "tree.h"

int main(int argc, char **argv)
{
    // deciding what we want to do
    if (strstr(argv[1], "-c"))
    {
        // reading the compression factor for the image
        unsigned long long factor;
        factor = atoll(argv[2]);

        // opening the files for input and output
        FILE *fin, *fout;
        fin = fopen(argv[3], "rb");
        if (fin == NULL)
        {
            printf("Nu s-a putu deschide fisierul de intrare");
            exit(1);
        }
        fout = fopen(argv[4], "wb");
        if (fout == NULL)
        {
            printf("Nu s-a putu deschide fisierul de iesire");
            exit(1);
        }

        // reading the image form the PPM P6 file
        IMAGE picture;
        read_ppm(&picture, fin);

        // writing the size of the image in the binary file
        fwrite(&picture.height, sizeof(unsigned int), 1, fout);
        // printf("%d\n", picture.height);
        //printf("%lf", calculate_mean(&picture,picture.height/2,0,picture.height/2));

        // initializam si construim arborele de compresie
        TREE arbore;
        init_tree(&arbore);
        create_tree(&picture, arbore.radacina, 0, 0, 0, picture.height, factor);

        // initializam coada de parcurgere si parcurgem arborele de compresie
        QUEUE coada;
        init_coada_parcurgere(&coada, arbore.radacina);
        parse_tree_compresion(&coada, fout, picture.height);

        // inchidem fisierele
        fclose(fin);
        fclose(fout);
    }
    if (strstr(argv[1], "-d"))
    {
        printf("BUN");
    }

    return 0;
}