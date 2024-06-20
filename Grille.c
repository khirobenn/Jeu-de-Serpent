#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Grille.h"
/*allouer la grille*/
Grille* Grille_allouer(int n, int m){
    Grille* grille = malloc(sizeof(Grille));//allouer la grille
    grille->n = n;//inialiser nombre de lignes
    grille->m = m;//inialiser nombre de colones
    grille->tab = malloc(sizeof(char **)*n);//allouer un tableau des pointeur vers chaine de caracteres
    for(int i=0; i<n; i++){
        grille->tab[i] = malloc(sizeof(char *)*m);//allouer chaque tableaux dans les cases sont des chaines de caracteres
        for (int  j = 0; j < m; j++){
            grille->tab[i][j]=malloc(sizeof(char)*8);//allouer chaque case(chaine de caractere de taille 8)
        }
    }
    return grille;
}

/*remplire toutes les case de la grille par deux espace avec une couleur poor backrougnd  */
void Grille_vider(Grille *grille, Case ** M){
    for(int i=0; i<grille->n;i++){
        for (int  j = 0; j < grille->m; j++){
            M[i][j].contenu = Vide;//indique dans la matrice des case que la case est vide
            M[i][j].numero_serpent = -3; // car les indices des serpents commence de -1 et plus
            strcpy(grille->tab[i][j], "\33[00m  ");//copier la chaine dans la case 
        } 
    }
}

/*tirage d'un fruit (boost/normal)*/
void Grille_tirage_fruit(Grille *grille, Case ** M, int secondes_boost){
    do{
        grille->fruit.x = rand() % grille->m;//inialiser aleatoirement les cordonnees de fruit
        grille->fruit.y = rand() % grille->n;
    }while(M[grille->fruit.y][grille->fruit.x].contenu != Vide); //tanque la case n'est pas vide
    if(!secondes_boost){//le serpent n'est pas dans l'effet boost
        if(!(rand()%5))
            grille->type_fruit = Boost;//si le nombre alatoire == 0 donc on tire un fruit boost
        else
            grille->type_fruit = Normal;//sinon un fruit normal
    }
    else grille->type_fruit = Normal;//le serpent est dans l'effet boost du coup on tire un fruit normal
}

/*remplier la grille et la matrice des case par le fruit et les case de la liste mouvement*/
void Grille_remplir(Grille *grille, Serpent *serpent, Case ** M, int numero_serpent){
    switch(grille->type_fruit){
        case Normal:
            grille->tab[grille->fruit.y][grille->fruit.x][2] = '4';// on remplit le fruit
            grille->tab[grille->fruit.y][grille->fruit.x][3] = '3';// on remplit le fruit
        break;

        case Boost:
            grille->tab[grille->fruit.y][grille->fruit.x][2] = '4';// on remplit le fruit Boost
            grille->tab[grille->fruit.y][grille->fruit.x][3] = '5';// on remplit le fruit Boost
        break;
    }
    M[grille->fruit.y][grille->fruit.x].contenu = Fruit;//remplier la matrice par fruit

    Section *tmp = serpent->list_section->premier;// pour parcourir la liste section
    _case_ *caseTmp = serpent->list_cases->premier;// pour parcourir la liste mouvement

    while(tmp){//parcourir la liste section
        for(int i = 0; i<tmp->taille; i++){//parcourir la liste mouvement
            grille->tab[caseTmp->cases_coord.y][caseTmp->cases_coord.x][2] = (char)(tmp->couleur/10) + '0';//remplier la case da la grille
            grille->tab[caseTmp->cases_coord.y][caseTmp->cases_coord.x][3] = (char)(tmp->couleur%10) + '0';
            M[caseTmp->cases_coord.y][caseTmp->cases_coord.x].contenu = Snake;//remplire la matrice
            M[caseTmp->cases_coord.y][caseTmp->cases_coord.x].numero_serpent = numero_serpent;
            caseTmp = caseTmp->case_suivante;
        }
        tmp = tmp->suivant;
    }
}

/*desallouer une grille*/
void Grille_desallouer(Grille **g){
    if(*g){
        for(int i=0; i<(*g)->n; i++){
            for (int  j = 0; j < (*g)->m; j++){
                free((*g)->tab[i][j]);
            }
            free((*g)->tab[i]);
        }
        free(*g);
        *g = NULL;
    }
}

/*afficher la grille et ses bordures*/
void Grille_redessiner(Grille *grille){
    for(int i=-1; i<grille->n+1;i++){
        for(int j=-1; j<grille->m+1; j++){
            if(i == -1 || j == -1 || i == grille->n || j == grille->m)
                printf("\33[48;5;63m  ");//dessiner les bordures
            else
                printf("\33[00m%s", grille->tab[i][j]);//dessiner la grille
        }
        printf("\33[00m\33[1E");
    }
}