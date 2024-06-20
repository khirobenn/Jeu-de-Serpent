#ifndef __CASE__
#define __CASE__ 

#include <stdlib.h>

typedef enum {Vide, Fruit, Snake} Contenu;

typedef struct {
    Contenu contenu;
    int numero_serpent;
}Case;

Case ** creer_matrice_cases(int, int);
void desallouer_matrice_cases(Case ***, int);

#endif