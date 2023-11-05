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
    //decidem ce cerinta va fi efectuata de program
    if (strstr(argv[1], "-c1"))
    {
        //citim argumentele din linia de comanada
        unsigned long long factor;
        factor = atoll(argv[2]);
        //printf("%lld", factor);

        //deschidem fisierele si verificam ca acestea se deschid corect
        FILE *fin, *fout;
        fin = fopen(argv[3], "rb");
        if(fin==NULL)
        {
            printf("Nu s-a putu deschide fisierul de intrare");
            exit(1);
        }
        fout = fopen(argv[4], "wt");
        if(fout==NULL)
        {
            printf("Nu s-a putu deschide fisierul de iesire");
            exit(1);
        }

        //citim imaginea din fisierul PPM
        IMAGE picture;
        read_ppm(&picture, fin);

        //initializam si construim arborele de compresie
        TREE arbore;
        init_tree(&arbore);
        create_tree(&picture, arbore.radacina, 0, 0, 0, picture.height, factor);

        //initializam coada de parcurgere si parcurgem arborele de compresie
        QUEUE coada;
        init_coada_parcurgere(&coada, arbore.radacina);
        parcurgere_abore_c1(&coada, fout, picture.height);

        //inchidem fisierele
        fclose(fin);
        fclose(fout);
    }
    if (strstr(argv[1], "-c2"))
    {
        //citim argumentele din linia de comanada
        unsigned long long factor;
        factor = atoll(argv[2]);

        //deschidem fisierele si verificam ca acestea se deschid corect
        FILE *fin, *fout;
        fin = fopen(argv[3], "rb");
        if(fin==NULL)
        {
            printf("Nu s-a putu deschide fisierul de intrare");
            exit(1);
        }
        fout = fopen(argv[4], "wb");
        if(fout==NULL)
        {
            printf("Nu s-a putu deschide fisierul de iesire");
            exit(1);
        }

        //citim imaginea din fisierul PPM
        IMAGE picture;
        read_ppm(&picture, fin);
        
        //scriem in fisierul de iesire dimensiunea imaginii
        fwrite(&picture.height, sizeof(unsigned int), 1, fout);

        //initializam si construim arborele de compresie
        TREE arbore;
        init_tree(&arbore);
        create_tree(&picture, arbore.radacina, 0, 0, 0, picture.height, factor);

        //initializam coada de parcurgere si parcurgem arborele de compresie
        QUEUE coada;
        init_coada_parcurgere(&coada, arbore.radacina);
        parcurgere_abore_c2(&coada, fout,picture.height);
        //init_coada_parcurgere(&coada, arbore.radacina);

        //inchidem fisierele
        fclose(fin);
        fclose(fout);
    }
    if (strstr(argv[1], "-d"))
    {
        printf("BUN");
    }

    return 0;
}