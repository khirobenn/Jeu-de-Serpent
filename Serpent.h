#ifndef __SERPENT__
#define __SERPENT__
#include "Coordonnees.h"
#include "Liste_Section.h"
#include "Liste_Mouvement.h"

typedef struct {
    Coordonnees tete;
    Liste_Section * list_section;
    Liste_Mouvement * list_cases;
}Serpent;

Serpent * creer_serpent(int);  /* creation du serpent */

void desallouer_serpent(Serpent **);  /* desallouer le serpent */

#endif