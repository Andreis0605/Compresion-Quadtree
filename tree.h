/*STAN Andrei - 314CC*/
#include "data.h"

void init_tree(TREE *root);
void create_tree(IMAGE *pic, NOD *root, int nivel, int x, int y, int size,
                 unsigned long long factor);
void init_coada_parcurgere(QUEUE *coada, NOD *radacina);
void parcurgere_abore_c1(QUEUE *coada, FILE *write, int size);
void parcurgere_abore_c2(QUEUE *coada, FILE *write, unsigned int size);