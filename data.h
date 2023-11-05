/*STAN Andrei - 314CC*/
#ifndef DATA_H
#define DATA_H

// structura care va retine pixelii din imagine
typedef struct pixel
{
    unsigned char r, g, b;
} PIXEL;

// structura care va retine toate datele despre imaginea data
typedef struct image
{
    int height, width, max_col;
    PIXEL **img;
} IMAGE;

// structura folosita ca nod in arborele de compresie
typedef struct nod
{
    unsigned char type;
    int depth;
    unsigned char r, g, b;
    struct nod *ul, *ur, *lr, *ll;
} NOD;

// structura care retine radacina arborelui de compresie
typedef struct arbore
{
    NOD *radacina;
} TREE;

// structura care este folosita pentru un nod din coada de parcurgere
typedef struct nod_coada
{
    NOD *elem;
    struct nod_coada *next, *prev;
} NOD_PARCURGERE;

// structura care retine coada de parcurgere
typedef struct coada
{
    NOD_PARCURGERE *first, *last;
} QUEUE;

#endif