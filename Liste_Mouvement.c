#include "Liste_Mouvement.h"

/* creer la liste de mouvement */
Liste_Mouvement * creer_liste_mouvement(){
    Liste_Mouvement * list = malloc(sizeof(Liste_Mouvement));
    list->dernier = NULL;
    list->premier = NULL;
    return list;
}

/*ajouter une case au debut du la liste du mouvement */
void ajouter_debut_liste_mouvement(Liste_Mouvement * liste, _case_ * ma_case){
    if(!liste->premier){liste->premier = ma_case; liste->dernier = ma_case;}
    else{ma_case->case_suivante = liste->premier; liste->premier = ma_case;}

}

/*ajouter une case a la fin du la liste du mouvement */
void ajouter_fin_liste_mouvement(Liste_Mouvement * liste, _case_ * ma_case){
    ma_case->case_suivante = NULL;
    if(!liste->premier) ajouter_debut_liste_mouvement(liste, ma_case);
    else{liste->dernier->case_suivante = ma_case; liste->dernier = ma_case;}
}

/*extraire une case du debut de la liste du mouvement */
_case_ * extraire_debut_liste_mouvement(Liste_Mouvement * liste){
    if(!liste->premier) return NULL;
    if(liste->premier == liste->dernier){
        _case_ *cas = liste->premier;
        liste->premier = NULL;
        liste->dernier = NULL;
        return cas;
    }
    _case_ * toReturn = liste->premier;
    liste->premier = liste->premier->case_suivante;
    toReturn->case_suivante = NULL;
    return toReturn;
}

/*extraire une case a la fin de la liste du mouvement */
_case_ * extraire_fin_liste_mouvement(Liste_Mouvement * liste){
    if(!liste->premier) return NULL;
    if(liste->premier == liste->dernier){
        _case_ *cas = liste->premier;
        liste->premier = NULL;
        liste->dernier = NULL;
        return cas;
    }
    _case_ * toReturn = liste->dernier;
    _case_ *tmp = liste->premier;
    while(tmp->case_suivante != toReturn){tmp = tmp->case_suivante;}
    tmp->case_suivante = NULL;
    liste->dernier = tmp;
    return toReturn;
}

/*desallouer une case */
void desallouer_case(_case_ ** ma_case){
    if(*ma_case != NULL){
        free(*ma_case);
        *ma_case = NULL;
    }
}

/*desallouer une liste du mouvement*/
void desallouer_liste_mouvement(Liste_Mouvement ** liste){
    if(*liste != NULL){
        while((*liste)->premier){
            _case_ * tmp = extraire_debut_liste_mouvement(*liste);
            desallouer_case(&tmp);
        }
    }
    free(*liste);
    *liste = NULL;
}

/*changer la direction de la case et ses cordonnees par apport a les cordonnees de la derniere case*/
void changer_direction(_case_ *dernier, _case_ *cas, Direction direction, Case **M){
    switch(direction){
        case Haut: // 'cas' il va en haut vers 'dernier' 
            cas->cases_coord.y = dernier->cases_coord.y + 1;//la case va etre au dessous de la dernier case
            cas->cases_coord.x = dernier->cases_coord.x;
        break;

        case Bas:
            cas->cases_coord.y = dernier->cases_coord.y - 1;//la case va etre au dessus de la dernier case
            cas->cases_coord.x = dernier->cases_coord.x;
        break;

        case Droite:
            cas->cases_coord.y = dernier->cases_coord.y;
            cas->cases_coord.x = dernier->cases_coord.x-1;//la case va etre a gauche de la dernier case
        break;

        case Gauche:
            cas->cases_coord.y = dernier->cases_coord.y;
            cas->cases_coord.x = dernier->cases_coord.x+1;//la case va etre a droite de la dernier case
        break;
    }
    M[cas->cases_coord.y][cas->cases_coord.x].contenu = Snake;//remplire la matrice par la nouvelle case de la liste mouvement
    cas->direction = direction;//donner la direction a la case
}

/*verifier si on peut ajouter une case par aport a la cese de cordonnees (x,y) et la direction*/
int verifier_si_on_peut_ajouter_case(int x, int y, int n, int m, Direction direction, Case **M){
    int toReturn;
    switch(direction){
        case Haut:
            toReturn = (y+1 != n) && (M[y+1][x].contenu == Vide); //si on peut ajouter au dessous
        break;

        case Bas:
            toReturn = (y-1 != -1) && (M[y-1][x].contenu == Vide);//si on peut ajouter au dessus
        break;

        case Gauche:
            toReturn = (x+1 != m) && (M[y][x+1].contenu == Vide);//si on peut ajouter a droite
        break;

        case Droite:
            toReturn = (x-1 != -1) && (M[y][x-1].contenu == Vide);//si on peut ajouter a gauche
        break;

    }
    return toReturn;
}

/*ajouter les case d'une section a la liste de mouvement*/
void ajouter_section_de_case_liste_mouvement(Liste_Mouvement * list_cases, int aleaTaille, int n, int m, Case **M){
    for(int i=0; i<aleaTaille; i++){ // creer et ajouter "aleataille(taille de la section)" cases pour la liste de mouvement
        _case_ * cas = malloc(sizeof(_case_));//allouer une case
        cas->case_suivante = NULL;
        switch(list_cases->dernier->direction){//switch la direction de la dernier cas dans la liste mouvement
            case Haut:
                if(verifier_si_on_peut_ajouter_case(list_cases->dernier->cases_coord.x, list_cases->dernier->cases_coord.y, n, m, Haut, M))//verifier si on peut ajouter la case en bas de la dernier cas
                    changer_direction(list_cases->dernier, cas, Haut, M); //changer la direction de la case et ses cordonnees par apport a les cordonnees de la derniere case pour qu'elle soit en bas de cette derniere
                
                else if(verifier_si_on_peut_ajouter_case(list_cases->dernier->cases_coord.x, list_cases->dernier->cases_coord.y, n, m, Gauche, M))//verifier si on peut ajouter la case a droite de la dernier cas
                    changer_direction(list_cases->dernier, cas, Gauche, M);//changer la direction de la case et ses cordonnees par apport a les cordonnees de la derniere case pour qu'elle soit a droite de cette derniere
                
                else if(verifier_si_on_peut_ajouter_case(list_cases->dernier->cases_coord.x, list_cases->dernier->cases_coord.y, n, m, Droite, M))//verifier si on peut ajouter la case a gauche de la dernier cas
                    changer_direction(list_cases->dernier, cas, Droite, M);//changer la direction de la case et ses cordonnees par apport a les cordonnees de la derniere case pour qu'elle soit a gauche de cette derniere
            break;

            case Bas:
                if(verifier_si_on_peut_ajouter_case(list_cases->dernier->cases_coord.x, list_cases->dernier->cases_coord.y, n, m, Bas, M))//verifier si on peut ajouter la case en haut de la dernier cas
                    changer_direction(list_cases->dernier, cas, Bas, M);//changer la direction de la case et ses cordonnees par apport a les cordonnees de la derniere case pour qu'elle soit en haut de cette derniere
                
                else if(verifier_si_on_peut_ajouter_case(list_cases->dernier->cases_coord.x, list_cases->dernier->cases_coord.y, n, m, Gauche, M))//verifier si on peut ajouter la case a droite de la dernier cas
                    changer_direction(list_cases->dernier, cas, Gauche, M);//changer la direction de la case et ses cordonnees par apport a les cordonnees de la derniere case pour qu'elle soit a droite de cette derniere
                
                else if(verifier_si_on_peut_ajouter_case(list_cases->dernier->cases_coord.x, list_cases->dernier->cases_coord.y, n, m, Droite, M))//verifier si on peut ajouter la case a gauche de la dernier cas
                    changer_direction(list_cases->dernier, cas, Droite, M);//changer la direction de la case et ses cordonnees par apport a les cordonnees de la derniere case pour qu'elle soit a gauche de cette derniere
            break;

            case Droite:
                if(verifier_si_on_peut_ajouter_case(list_cases->dernier->cases_coord.x, list_cases->dernier->cases_coord.y, n, m, Droite, M))//verifier si on peut ajouter la case a gauche de la dernier cas
                    changer_direction(list_cases->dernier, cas, Droite, M);//changer la direction de la case et ses cordonnees par apport a les cordonnees de la derniere case pour qu'elle soit a gauche de cette derniere
                
                else if(verifier_si_on_peut_ajouter_case(list_cases->dernier->cases_coord.x, list_cases->dernier->cases_coord.y, n, m, Haut, M))//verifier si on peut ajouter la case en bas de la dernier cas
                    changer_direction(list_cases->dernier, cas, Haut, M);//changer la direction de la case et ses cordonnees par apport a les cordonnees de la derniere case pour qu'elle soit en bas de cette derniere
               
                else if(verifier_si_on_peut_ajouter_case(list_cases->dernier->cases_coord.x, list_cases->dernier->cases_coord.y, n, m, Bas, M))//verifier si on peut ajouter la case en haut de la dernier cas
                    changer_direction(list_cases->dernier, cas, Bas, M);//changer la direction de la case et ses cordonnees par apport a les cordonnees de la derniere case pour qu'elle soit en haut de cette derniere
            break;

            case Gauche:
                if(verifier_si_on_peut_ajouter_case(list_cases->dernier->cases_coord.x, list_cases->dernier->cases_coord.y, n, m, Gauche, M))//verifier si on peut ajouter la case a droite de la dernier cas
                    changer_direction(list_cases->dernier, cas, Gauche, M);//changer la direction de la case et ses cordonnees par apport a les cordonnees de la derniere case pour qu'elle soit a droite de cette derniere
               
                else if(verifier_si_on_peut_ajouter_case(list_cases->dernier->cases_coord.x, list_cases->dernier->cases_coord.y, n, m, Haut, M))//verifier si on peut ajouter la case en bas de la dernier cas
                    changer_direction(list_cases->dernier, cas, Haut, M); //changer la direction de la case et ses cordonnees par apport a les cordonnees de la derniere case pour qu'elle soit en bas de cette derniere
               
                else if(verifier_si_on_peut_ajouter_case(list_cases->dernier->cases_coord.x, list_cases->dernier->cases_coord.y, n, m, Bas, M))//verifier si on peut ajouter la case en haut de la dernier cas
                    changer_direction(list_cases->dernier, cas, Bas, M);  //changer la direction de la case et ses cordonnees par apport a les cordonnees de la derniere case pour qu'elle soit en haut de cette derniere
            break;
        }
        ajouter_fin_liste_mouvement(list_cases, cas);//ajouter la case a la liste de mouvement
    }
}