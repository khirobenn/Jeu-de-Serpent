#ifndef __LISTE_SECTION__
#define __LISTE_SECTION__

typedef struct Section{
    int taille;
    int couleur;
    struct Section * suivant;
}Section;

typedef struct{
    Section * premier;
    Section * dernier;
}Liste_Section;

Liste_Section * creer_liste_section();/* creer la liste des sections du serpent */
Section * creer_section(int, int);/* creer une section */
void ajouter_debut_liste_section(Liste_Section *, Section *);/* ajouter une section au debut de la liste des sections*/
void ajouter_fin_liste_section(Liste_Section *, Section *);/* ajouter une section a la fin de la liste des sections*/
Section * extraire_debut_liste_section(Liste_Section *);/* extraire une section du debut de la liste des sections */
Section * extraire_fin_liste_section(Liste_Section *);/* extraire une section du la fin de la liste des sections */
void desallouer_section(Section **);/* desallouer une section */
void desallouer_liste_section(Liste_Section **);/* desallouer une liste section */


#endif