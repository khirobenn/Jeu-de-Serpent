#ifndef __LISTE__MOUVEMENT__
#define __LISTE__MOUVEMENT__

#include <stdlib.h>
#include "Coordonnees.h"
#include "Case.h"

typedef enum {Haut, Bas, Gauche, Droite} Direction;

typedef struct _case_{
    Coordonnees cases_coord;
    Direction direction;
    struct _case_ * case_suivante;
}_case_;

typedef struct {
    _case_ *premier;
    _case_ *dernier;
}Liste_Mouvement;



Liste_Mouvement * creer_liste_mouvement();/* creer la liste de mouvement */
void ajouter_debut_liste_mouvement(Liste_Mouvement *, _case_ *);/*ajouter une case au debut du la liste du mouvement */
void ajouter_fin_liste_mouvement(Liste_Mouvement *, _case_ *);/*ajouter une case a la fin du la liste du mouvement */
_case_ * extraire_debut_liste_mouvement(Liste_Mouvement *);/*extraire une case du debut de la liste du mouvement */
_case_ * extraire_fin_liste_mouvement(Liste_Mouvement *);/*extraire une case a la fin de la liste du mouvement */
void desallouer_case(_case_ ** ma_case);/*desallouer une case */
void desallouer_liste_mouvement(Liste_Mouvement **);/*desallouer une liste du mouvement*/
void changer_direction(_case_ *, _case_ *, Direction, Case **);/*changer la direction de la case et ses cordonnees par apport a les cordonnees de la derniere case*/
int verifier_si_on_peut_ajouter_case(int, int, int, int, Direction, Case**);/*verifier si on peut ajouter une case a les cordonnees (x,y)*/
void ajouter_section_de_case_liste_mouvement(Liste_Mouvement *, int, int, int, Case **);/*ajouter les case d'une section a la liste de mouvement*/



#endif