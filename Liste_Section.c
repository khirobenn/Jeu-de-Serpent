#include <stdio.h>
#include <stdlib.h>
#include "Liste_Section.h"

/* creer la liste des sections du serpent */
Liste_Section * creer_liste_section(){
    Liste_Section * liste = malloc(sizeof(Liste_Section));//allouer l'espace memoire pour la liste de section 
    liste->premier = NULL;
    liste->dernier = NULL;
    return liste;
}
 
/* creer une section */
Section * creer_section(int taille, int couleur){
    Section * section = malloc(sizeof(Section));//allouer l'espace memoire pour la section 
    section->suivant = NULL;
    section->taille = taille;//inialiser la taille 
    section->couleur = couleur;//inialiser la couleur
    return section;
}

/* ajouter une section au debut de la liste des sections*/
void ajouter_debut_liste_section(Liste_Section * liste, Section * section){
    if(!liste->premier) {liste->premier = section; liste->dernier = section;}
    else{section->suivant = liste->premier; liste->premier = section;}
}

/* ajouter une section a la fin de la liste des sections*/
void ajouter_fin_liste_section(Liste_Section * liste, Section * section){
    section->suivant = NULL;
    if(!liste->premier) ajouter_debut_liste_section(liste, section);
    else{liste->dernier->suivant = section; liste->dernier = section;}
}

/* extraire une section du debut de la liste des sections */
Section * extraire_debut_liste_section(Liste_Section * liste){
    if(!liste->premier) return NULL;
    Section * toReturn = liste->premier;
    liste->premier = liste->premier->suivant;
    toReturn->suivant = NULL;
    return toReturn;
}

/* extraire une section du la fin de la liste des sections */
Section * extraire_fin_liste_section(Liste_Section * liste){
    if(!liste->dernier) return extraire_debut_liste_section(liste);
    Section * toReturn = liste->dernier;
    Section *tmp = liste->premier;
    while(tmp->suivant != toReturn){tmp = tmp->suivant;}
    tmp->suivant = NULL;
    if(tmp == liste->premier) liste->dernier = NULL;
    else liste->dernier = tmp;
    return toReturn;
}

/* desallouer une section */
void desallouer_section(Section ** section){
    if(*section != NULL){
        free(*section);
        *section = NULL;
    }
}

/* desallouer une liste section */
void desallouer_liste_section(Liste_Section ** liste){
    if(*liste != NULL){
        while((*liste)->premier){
            Section * tmp = extraire_debut_liste_section(*liste);
            desallouer_section(&tmp);
        }
        free(*liste);
        *liste = NULL;
    }
}