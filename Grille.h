#ifndef __GRILLE__
#define __GRILLE__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Coordonnees.h"
#include "Serpent.h"
#include "Case.h"

typedef enum {Normal, Boost} Type_Fruit;

typedef struct {
    int n;
    int m;
    char ***tab;
    Coordonnees fruit;
    Type_Fruit type_fruit;//indique le type de fruit dans la grille
}Grille;

Grille* Grille_allouer(int, int);/*allouer la grille*/
void Grille_vider(Grille *, Case **);/*remplire toutes les case de la grille par deux espace avec une couleur poor backrougnd  */
void Grille_tirage_fruit(Grille *, Case **, int);/*tirage d'un fruit (boost/normal)*/
void Grille_remplir(Grille *, Serpent *, Case **, int);/*remplier la grille et la matrice des case par le fruit et les case de la liste mouvement*/
void Grille_desallouer(Grille **);/*desallouer une grille*/
void Grille_redessiner(Grille *);/*afficher la grille et ses bordures*/

#endif
