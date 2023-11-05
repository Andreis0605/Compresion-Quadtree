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

// functie care creeaza arborele de compresie
void create_tree(IMAGE *pic, NOD *root, int nivel, int x, int y, int size, unsigned long long factor)
{
    unsigned long long mean;

    // calculam media zonei din matrice la care suntem
    mean = calculate_mean(pic, x, y, size);
    // printf("%lld ", mean);
    // if (root != NULL)
    //{

    if (mean <= factor || size == 1)
    {
        // daca media unei zone este mai mica decat factorul primit ca argument
        // sau daca zona are dimensiunea 1, tunci adaugam un nod de tip 1
        root->type = 1;
        root->r = avereage_red(pic, x, y, size);
        root->g = avereage_green(pic, x, y, size);
        root->b = avereage_blue(pic, x, y, size);
        root->ur = NULL;
        root->ul = NULL;
        root->ll = NULL;
        root->lr = NULL;
        root->depth = nivel;
    }
    else
    {
        // daca nu se intampla nici o conditie din cele de mai sus
        // adaugam un nod de tip 0, divizand zona curenta in 4 zone egale
        root->type = 0;
        root->depth = nivel;
        NOD *aux_ur, *aux_ul, *aux_ll, *aux_lr;

        // alocam memorie pentru un nod care va retine zona din stanga sus
        aux_ul = malloc(sizeof(NOD));
        if (aux_ul == NULL)
        {
            printf("Nu s-a putut aloca pentru un nod din arbore");
            exit(1);
        }
        root->ul = aux_ul;

        // apelam functia pentru zona din stanga sus
        create_tree(pic, root->ul, nivel + 1, x, y, size / 2, factor);

        // alocam memorie pentru un nod care va retine zona din dreapta sus
        aux_ur = malloc(sizeof(NOD));
        if (aux_ur == NULL)
        {
            printf("Nu s-a putut aloca pentru un nod din arbore");
            exit(1);
        }
        root->ur = aux_ur;

        // apelam functia pentru zona din dreapta sus
        create_tree(pic, root->ur, nivel + 1, x + (size / 2), y,
                    size / 2, factor);

        // alocam memorie pentru un nod care va retine zona din dreapta jos
        aux_lr = malloc(sizeof(NOD));
        if (aux_lr == NULL)
        {
            printf("Nu s-a putut aloca pentru un nod din arbore");
            exit(1);
        }
        root->lr = aux_lr;

        // apelam functia pentru zona din dreapta jos
        create_tree(pic, root->lr, nivel + 1, x + (size / 2), y + (size / 2),
                    size / 2, factor);

        // alocam memorie pentru un nod care va retine zona din dreapta jos
        aux_ll = malloc(sizeof(NOD));
        if (aux_ll == NULL)
        {
            printf("Nu s-a putut aloca pentru un nod din arbore");
            exit(1);
        }
        root->ll = aux_ll;

        // apelam functia pentru zona din stanga jos
        create_tree(pic, root->ll, nivel + 1, x, y + (size / 2),
                    size / 2, factor);
    }
}

// functie care parcurge arborele si calculeaza informatiile pentru cerinta 1
// folosim o coada de parcurgere in care retinem un pointer catre nodul
// pentru care calculam la un moment dat
void parcurgere_abore_c1(QUEUE *coada, FILE *write, int size)
{
    // initializam variabilelel in care calculam informatiile
    int max_depth = -1, max_area = -1, nr_area = 0;

    // incepem parcurgerea
    while (coada->first != NULL)
    {
        if (coada->first->elem->type == 1)
        {
            // daca nodul este de tip 1, atunci calculam date despre arbore
            if (coada->first->elem != NULL)
                nr_area++;
            if (coada->first->elem->depth > max_depth)
                max_depth = coada->first->elem->depth;
            if (max_area == -1)
                max_area = coada->first->elem->depth;
        }
        else
        {
            // daca nodul este de tip 0, atunci adaugam in coada
            // nodurile de pe nivelul urmator
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
        }
        //trecem la urmatorul element din coada
        coada->first = coada->first->next;
    }

    //generam puterea lui 2 pentru a afla cea mai mare zona nedivizata
    int two_pow = 1;
    two_pow = two_pow << (max_area);

    //afisam informatiile
    fprintf(write, "%d\n%d\n%d\n", max_depth + 1, nr_area, size / two_pow);
}

// functie care parcurge arborele si calculeaza informatiile pentru cerinta 2
// folosim o coada de parcurgere pentru a traversa arborele
void parcurgere_abore_c2(QUEUE *coada, FILE *write, unsigned int size)
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
