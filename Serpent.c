#include <stdlib.h>
#include <stdio.h>
#include "Serpent.h"

 /* creation du serpent */
Serpent * creer_serpent(int couleur){

    Serpent * serpent = malloc(sizeof(Serpent));//allouer l'espace memoire pour un serpent
    serpent->list_section = creer_liste_section();//creer la liste des sections du serpent
    serpent->list_cases = creer_liste_mouvement();// creer la liste du mouvement de serpent
    Section *tete = creer_section(1, couleur);//creer une section d'une case pour la tete du serpent 

    ajouter_debut_liste_section(serpent->list_section, tete);//ajoute la section du la tete a la liste des sectios du serpent

    _case_* tete_case = malloc(sizeof(_case_));//creer une case pour la tete
    tete_case->case_suivante = NULL;//inialiser le suivant de la case de la tet a null
    tete_case->cases_coord.x = 0;//inialiser les cordonnees du la tete a(0,0) dans sa case dans la liste de mouvement;
    tete_case->cases_coord.y = 0;

    serpent->tete.x = 0;//inialiser les cordonnees du la tete a(0,0)
    serpent->tete.y = 0;

    ajouter_debut_liste_mouvement(serpent->list_cases, tete_case);//ajoute la case du la tete a la liste du mouvement du serpent

    return serpent;//returner l'adresse du serpent
}

 /* desallouer le serpent */
void desallouer_serpent(Serpent **serpent){
    if(*serpent){
        desallouer_liste_section(&(*serpent)->list_section);//desalouer la liste des section du serpent
        desallouer_liste_mouvement(&(*serpent)->list_cases);//desalouer la liste du mouvement du serpent
        free(*serpent);//desallouer la structure serpent 
        *serpent = NULL;
    }
}