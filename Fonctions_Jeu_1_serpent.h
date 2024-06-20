#ifndef __FONCTIONS_JEU_1_SERPENT__
#define __FONCTIONS_JEU_1_SERPENT__

#include <stdio.h>
#include <stdlib.h>
#include "Grille.h"
#include <ncurses.h>

int max(int *tab, int taille, int);
int verifier_touches(int, int);
int verifier_tete_et_fruit(Grille *, Serpent *);
void bouger_serpent(Serpent *, Direction, Case **);
int ai(Serpent *, Grille *, Case **M, int, int, int, int);
int Game(Grille *, Serpent *, Serpent **, const int, Case **, const int, const int);

#endif