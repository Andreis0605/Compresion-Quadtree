/*STAN Andrei - 314CC*/
#include <stdio.h>
#include <stdlib.h>

#include "calculations.h"
#include "data.h"

// functia care initializeaza coada de parcurgere
void init_coada_parcurgere(QUEUE *coada, NOD *radacina)
{
    NOD_PARCURGERE *aux;
    aux = malloc(sizeof(NOD_PARCURGERE));
    if (aux == NULL)
    {
        printf("Nu s-a putut aloca pentru primul element din coada");
        exit(1);
    }
    aux->elem = radacina;
    aux->prev = NULL;
    aux->next = NULL;
    coada->first = aux;
    coada->last = aux;
}

// functia care initializeaza arborele de compresie
void init_tree(TREE *root)
{
    NOD *aux;
    aux = malloc(sizeof(NOD));
    root->radacina = aux;
}

void create_tree(IMAGE *pic, NOD *current, int nivel, int x, int y, int size, double factor)
{
    // calculating the mean color factor
    double mean;
    mean = calculate_mean(pic, x, y, size);

    if (mean <= factor || size == 1)
    {
        // add a new noded in the compresion tree
        current->type = 1;
        current->r = avereage_red(pic, x, y, size);
        current->g = avereage_green(pic, x, y, size);
        current->b = avereage_blue(pic, x, y, size);
        current->ur = NULL;
        current->ul = NULL;
        current->ll = NULL;
        current->lr = NULL;
        current->depth = nivel;
    }
    else
    {
        // divide the image further
        current->type = 0;
        current->depth = nivel;
        NOD *aux_ur, *aux_ul, *aux_ll, *aux_lr;

        aux_ul = malloc(sizeof(NOD));
        if (aux_ul == NULL)
        {
            printf("Failed to allocate memory");
            exit(1);
        }
        current->ul = aux_ul;

        aux_ur = malloc(sizeof(NOD));
        if (aux_ur == NULL)
        {
            printf("Failed to allocate memory");
            exit(1);
        }
        current->ur = aux_ur;

        aux_lr = malloc(sizeof(NOD));
        if (aux_lr == NULL)
        {
            printf("Failed to allocate memory");
            exit(1);
        }
        current->lr = aux_lr;

        aux_ll = malloc(sizeof(NOD));
        if (aux_ll == NULL)
        {
            printf("Failed to allocate memory");
            exit(1);
        }
        current->ll = aux_ll;

        // call the function for the new areas
        create_tree(pic, current->ul, nivel + 1, x, y, size / 2, factor);
        create_tree(pic, current->ur, nivel + 1, x + (size / 2), y, size / 2, factor);
        create_tree(pic, current->lr, nivel + 1, x + (size / 2), y + (size / 2), size / 2, factor);
        create_tree(pic, current->ll, nivel + 1, x, y + (size / 2), size / 2, factor);
    }
}

// functie care parcurge arborele si calculeaza informatiile pentru cerinta 2
// folosim o coada de parcurgere pentru a traversa arborele
void parse_tree_compresion(QUEUE *coada, FILE *write, unsigned int size)
{
    // incepem parcurgerea
    while (coada->first != NULL)
    {
        if (coada->first->elem->type == 1)
        {
            //afisam nodul de tip 1
            fwrite(&coada->first->elem->type, sizeof(unsigned char), 1, write);
            fwrite(&coada->first->elem->r, sizeof(unsigned char), 1, write);
            fwrite(&coada->first->elem->g, sizeof(unsigned char), 1, write);
            fwrite(&coada->first->elem->b, sizeof(unsigned char), 1, write);
            printf("%d %d %d %d\n", coada->first->elem->type, coada->first->elem->r, coada->first->elem->g, coada->first->elem->b);
        }
        else
        {
            NOD_PARCURGERE *aux_ul, *aux_ur, *aux_ll, *aux_lr;

            // alocam memorie pentru un nod din coada de parcurgere si
            // il adaugam la finalul cozii
            aux_ur = malloc(sizeof(NOD_PARCURGERE));
            if (aux_ur == NULL)
            {
                printf("Nu s-a putut aloca memorie pentru un nod din coada");
                printf("de parcurgere");
                exit(1);
            }
            aux_ur->elem = coada->first->elem->ur;
            aux_ur->prev = coada->last;
            aux_ur->next = NULL;
            coada->last->next = aux_ur;
            coada->last = coada->last->next;

            // alocam memorie pentru un nod din coada de parcurgere si
            // il adaugam la finalul cozii
            aux_ul = malloc(sizeof(NOD_PARCURGERE));
            if (aux_ul == NULL)
            {
                printf("Nu s-a putut aloca memorie pentru un nod din coada");
                printf("de parcurgere");
                exit(1);
            }
            aux_ul->elem = coada->first->elem->ul;
            aux_ul->prev = coada->last;
            aux_ul->next = NULL;
            coada->last->next = aux_ul;
            coada->last = coada->last->next;

            // alocam memorie pentru un nod din coada de parcurgere si
            // il adaugam la finalul cozii
            aux_ll = malloc(sizeof(NOD_PARCURGERE));
            if (aux_ll == NULL)
            {
                printf("Nu s-a putut aloca memorie pentru un nod din coada");
                printf("de parcurgere");
                exit(1);
            }
            aux_ll->elem = coada->first->elem->ll;
            aux_ll->prev = coada->last;
            aux_ll->next = NULL;
            coada->last->next = aux_ll;
            coada->last = coada->last->next;

            // alocam memorie pentru un nod din coada de parcurgere si
            // il adaugam la finalul cozii
            aux_lr = malloc(sizeof(NOD_PARCURGERE));
            if (aux_lr == NULL)
            {
                printf("Nu s-a putut aloca memorie pentru un nod din coada");
                printf("de parcurgere");
                exit(1);
            }
            aux_lr->elem = coada->first->elem->lr;
            aux_lr->prev = coada->last;
            aux_lr->next = NULL;
            coada->last->next = aux_lr;
            coada->last = coada->last->next;

            //afisam datele despre nodul de tip 0
            fwrite(&coada->first->elem->type, sizeof(unsigned char), 1, write);
        }

        //trecem la urmatorul element din coada
        coada->first = coada->first->next;
    }
}