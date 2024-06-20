#include "Fonctions_Jeu_1_serpent.h"

// Dans la suite du programme, on considérera que l'indice du serpent principal est -1 et son 'numero_serpent' est -1
// donc l'indice des autres serpent commence par 0 et leur numero_serpent commence par 0

#define indice_serpent_principal -1
#define indice_egalite -4 // On utilisera -4 comme indice si y'a égalité des scores

#define stopMin 'o' // touche pour quitter en miniscule
#define stopMaj 'O' // touche pour quitter en majuscule
#define WAIT 20 // 2 secondes

// Utilisé pour retourner l'indice du serpent qui a le plus grand score dans le tableau des serpents
int max(int *tab, int taille, int score_serpent_principal){
    int different = 0; // Pour vérifier si les scores sont differents
    int max_indice = 0;
    for(int i=1; i<taille; i++){
        if(tab[i] > tab[max_indice]){max_indice = i; different = 1;}
        else if (tab[i] < tab[max_indice]) different = 1;
    }

    if(!different){
        if(tab[0] == score_serpent_principal) return indice_egalite;
        else if(tab[0] < score_serpent_principal) return indice_serpent_principal;
        return 0;
    }
    else{
        if(tab[max_indice] > score_serpent_principal) return max_indice;
        else return indice_serpent_principal;
    }
}// pour calculer le score maximum des serpent du tableaux


/*
    Cette fonction est utilisé pour que si on prend une direction précise, on peut pas prendre la direction opposée,
    par exemple si on clique sur droite (ça veut dire on est dans la direction droite) alors quand on clique sur gauche,
    il se passe rien du tout (car c'est l'opposée de droite).
*/
int verifier_touches(int keyTmp, int key){
    return ((keyTmp == KEY_LEFT || keyTmp == 'q' || keyTmp == 'Q') && (key == KEY_RIGHT || key == 'd' || key == 'D')) 
    || ((key == KEY_LEFT || key == 'q' || key == 'Q') && (keyTmp == KEY_RIGHT || keyTmp == 'd' || keyTmp == 'D'))
    || ((keyTmp == KEY_UP || keyTmp == 'z' || keyTmp == 'Z') && (key == KEY_DOWN || key == 's' || key == 'S'))
    || ((key == KEY_UP || key == 'z' || key == 'Z') && (keyTmp == KEY_DOWN || keyTmp == 's' || keyTmp == 'S'));
}


// Elle vérifie si le serpent a mangé le fruit
int verifier_tete_et_fruit(Grille *grille, Serpent *serpent){
    return grille->fruit.x == serpent->tete.x && grille->fruit.y == serpent->tete.y;// verif si les cordonnees de la tete de seprent sont les meme cordonees du fruit
}


/* 
    Pour bouger le serpent, on extrait la dernière case dans la liste des cases, on l'ajoute au début de 
    la liste des cases en modifiant ses coordonnées vers la nouvelle tête
    (Avant cela on change la direction de l'ancienne tête vers la direction qu'on est entrain de prendre,
    on fait pareil avec la nouvelle tête)
*/
void bouger_serpent(Serpent *serpent, Direction direction, Case **M){
    serpent->list_cases->premier->direction = direction;
    ajouter_debut_liste_mouvement(serpent->list_cases, extraire_fin_liste_mouvement(serpent->list_cases));
    serpent->list_cases->premier->cases_coord.x = serpent->tete.x;//les coordonnees sont deja changer par apport a la direction de la touche
    serpent->list_cases->premier->cases_coord.y = serpent->tete.y;
    serpent->list_cases->premier->direction = direction;
}

int ai(Serpent *serpent, Grille *grille, Case **M, int VERS_HAUT, int VERS_DROITE, int VERS_GAUCHE, int VERS_BAS){
    int x = grille->fruit.x - serpent->tete.x;//pour voir l'emplacement du fruit par apport au serpent
    int y = grille->fruit.y - serpent->tete.y;

    if(x > 0 && y < 0){
        if(serpent->tete.y-1 != -1 && M[serpent->tete.y-1][serpent->tete.x].contenu != Snake) return VERS_HAUT;
        if(serpent->tete.x+1 != grille->m && M[serpent->tete.y][serpent->tete.x+1].contenu != Snake) return VERS_DROITE;
        if(serpent->tete.x-1 != -1 && M[serpent->tete.y][serpent->tete.x-1].contenu != Snake) return VERS_GAUCHE;
        if(serpent->tete.y+1 != grille->n && M[serpent->tete.y+1][serpent->tete.x].contenu != Snake) return VERS_BAS;
    } 

    if(x < 0 && y < 0){
        if(serpent->tete.y-1 != -1 && M[serpent->tete.y-1][serpent->tete.x].contenu != Snake) return VERS_HAUT;
        if(serpent->tete.x-1 != -1 && M[serpent->tete.y][serpent->tete.x-1].contenu != Snake) return VERS_GAUCHE;
        if(serpent->tete.x+1 != grille->m && M[serpent->tete.y][serpent->tete.x+1].contenu != Snake) return VERS_DROITE;
        if(serpent->tete.y+1 != grille->n && M[serpent->tete.y+1][serpent->tete.x].contenu != Snake) return VERS_BAS;
    }

    if(x > 0 && y > 0){
        if(serpent->tete.y+1 != grille->n && M[serpent->tete.y+1][serpent->tete.x].contenu != Snake) return VERS_BAS;
        if(serpent->tete.x+1 != grille->m && M[serpent->tete.y][serpent->tete.x+1].contenu != Snake) return VERS_DROITE;
        if(serpent->tete.y-1 != -1 && M[serpent->tete.y-1][serpent->tete.x].contenu != Snake) return VERS_HAUT;
        if(serpent->tete.x-1 != -1 && M[serpent->tete.y][serpent->tete.x-1].contenu != Snake) return VERS_GAUCHE;
    }

    if(x < 0 && y > 0){
        if(serpent->tete.y+1 != grille->n && M[serpent->tete.y+1][serpent->tete.x].contenu != Snake) return VERS_BAS;
        if(serpent->tete.x-1 != -1 && M[serpent->tete.y][serpent->tete.x-1].contenu != Snake) return VERS_GAUCHE;
        if(serpent->tete.y-1 != -1 && M[serpent->tete.y-1][serpent->tete.x].contenu != Snake) return VERS_HAUT;
        if(serpent->tete.x+1 != grille->m && M[serpent->tete.y][serpent->tete.x+1].contenu != Snake) return VERS_DROITE;
    }

    if(!x && y < 0){
        if(serpent->tete.y-1 != -1 && M[serpent->tete.y-1][serpent->tete.x].contenu != Snake) return VERS_HAUT;
        if(serpent->tete.x+1 != grille->m && M[serpent->tete.y][serpent->tete.x+1].contenu != Snake) return VERS_DROITE;
        if(serpent->tete.x-1 != -1 && M[serpent->tete.y][serpent->tete.x-1].contenu != Snake) return VERS_GAUCHE;
        if(serpent->tete.y+1 != grille->n && M[serpent->tete.y+1][serpent->tete.x].contenu != Snake) return VERS_BAS;
    }
    if(!x && y > 0){
        if(serpent->tete.y+1 != grille->n && M[serpent->tete.y+1][serpent->tete.x].contenu != Snake) return VERS_BAS;
        if(serpent->tete.x+1 != grille->m && M[serpent->tete.y][serpent->tete.x+1].contenu != Snake) return VERS_DROITE;
        if(serpent->tete.x-1 != -1 && M[serpent->tete.y][serpent->tete.x-1].contenu != Snake) return VERS_GAUCHE;
        if(serpent->tete.y-1 != -1 && M[serpent->tete.y-1][serpent->tete.x].contenu != Snake) return VERS_HAUT;
    }

    if(x > 0 && !y){
        if(serpent->tete.x+1 != grille->m && M[serpent->tete.y][serpent->tete.x+1].contenu != Snake) return VERS_DROITE;
        if(serpent->tete.y-1 != -1 && M[serpent->tete.y-1][serpent->tete.x].contenu != Snake) return VERS_HAUT;
        if(serpent->tete.y+1 != grille->n && M[serpent->tete.y+1][serpent->tete.x].contenu != Snake) return VERS_BAS;
        if(serpent->tete.x-1 != -1 && M[serpent->tete.y][serpent->tete.x-1].contenu != Snake) return VERS_GAUCHE;
    }

    if(x < 0 && !y){
        if(serpent->tete.x-1 != -1 && M[serpent->tete.y][serpent->tete.x-1].contenu != Snake) return VERS_GAUCHE;
        if(serpent->tete.y-1 != -1 && M[serpent->tete.y-1][serpent->tete.x].contenu != Snake) return VERS_HAUT;
        if(serpent->tete.y+1 != grille->n && M[serpent->tete.y+1][serpent->tete.x].contenu != Snake) return VERS_BAS;
        if(serpent->tete.x+1 != grille->m && M[serpent->tete.y][serpent->tete.x+1].contenu != Snake) return VERS_DROITE;
    }

    return -1;
}

// La fonction Game qui retourne le score du jeu (on utilisera le score retourné seulement dans le mode 1)
int Game(Grille *grille, Serpent *serpent, Serpent **serpent_tab, const int delay, Case ** M, const int mode, const int taille){

    initscr();
    refresh();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    int *keys = NULL; // Tableau utilisé pour piloter les serpents si on est dans le mode 3 ou 4, sinon si on est dans le mode 2 on l'utilisera pour le 2eme joueur
    int *scores = NULL; // Tableau des scores de chaque serpent

    if(taille != 0){
        keys = malloc(sizeof(int)*taille);
        scores = calloc(taille, sizeof(int)); 
    }

    int mangeur_de_fruit_boost = -2; // 

    
    int key = 'c'; 

    int keyTmp;

    int score = 0; // Le score du joueur
    int perdu = 0; // Si le joueur touche un mûr on donnera 1 à cette variable pour sortir de la boucle while
    int pause = 0; // Utilisée pour mettre le jeu on pause quand on clique sur Espace
    int stop = 0; // Utilisée pour quitter le jeu
    int attente_seconde = 0; // Utilisée pour le temps d'apparition du fruit Boost
    int secondes_boost = 0; // Utilisée pour le temps d'effet Boost

    int indice_gagnant = -2;
    
    Grille_tirage_fruit(grille, M, secondes_boost); // Tirage au sort des coordonnées du Fruit

    halfdelay(delay);
    do{

        printf("\33[2J");
        printf("\33[H");

        if(serpent_tab){//si on a plusieur serpent on affiche tous les scores
            printf("Score Joueur 1 \33[%c%cm  \33[00m : %d\33[1E", serpent->list_section->premier->couleur/10 + '0',serpent->list_section->premier->couleur%10 + '0', score);
            for(int i=0; i<taille; i++){
                printf("Score Joueur %d \33[%c%cm  \33[00m : %d\33[1E", 2+i, serpent_tab[i]->list_section->premier->couleur/10 + '0', serpent_tab[i]->list_section->premier->couleur%10 + '0', scores[i]);
            }
        }
        else//si on a un seul serpent
            printf("Score : %d\33[1E", score);

        printf("\33[43m  \33[00m\33[33m : Fruit Normal\33[00m || \33[45m  \33[00m\33[35m : Fruit Boost X3\33[00m\33[1E\33[1E");//afiche les couleur des fruits

        Grille_vider(grille, M);
        Grille_remplir(grille, serpent, M, indice_serpent_principal);//remlir le serpent pricipale
        for(int i=0; i<taille;i++){
            if(serpent_tab && serpent_tab[i]) Grille_remplir(grille, serpent_tab[i], M, i);//remplire les autres serpent
        }
        Grille_redessiner(grille);//dessiner la grille

        printf("%s Appuyer ur '\33[38;5;226m%c\33[00m' pour quitter.\33[1E", "\u25B6", stopMaj);
        if(!pause)
            printf("%s Appuyer sur 'Espace' pour mettre le jeu en pause.\33[1E", "\u25B6");
        else{
            printf("PAUSE : \33[1E");
            printf("%s Appuyer sur 'Espace' pour continuer le jeu.\33[1E", "\u25B6");
        }

        printf("\33[?25l"); // Supprimer le cursor dans l'affichage

        /* Dans ce bloc du if else qui suit, on est en train de vérifier si je suis dans le mode boost ou non;*/
        if(!secondes_boost){ // secondes_boost est zéro, ça veut dire je suis pas dans le mode boost
            
            if(grille->type_fruit == Boost && attente_seconde != 50){
                // Si le fruit affiché est le fruit boost et attentes n'est pas égale à 50 (tq 50 représente 5 secondes) alors on incrémente l'attente
                attente_seconde += delay;
                printf("\33[35m%d secondes pour la disparition du fruit \"Boost X3\"!\33[00m", 5 - attente_seconde/10);
            }
            else if (attente_seconde == 50){ // Si l'attente est arrivée à 5 secondes, on fait disparaitre le fruit boost, et on remet l'attente à 0 et on tire un autre fruit
                Grille_tirage_fruit(grille, M, secondes_boost);
                attente_seconde = 0;
            }
            else // sinon on remet l'attente à 0 toujours
                attente_seconde = 0;
        }
        else
        { // ici, ça veut dire je suis dans le mode boost, donc j'affiche combiens de secondes me reste en ce mode
            printf("\33[35m%d secondes restantes pour le mode \"Boost X3\"*\33[00m", secondes_boost/10 + 1);
        }

        fflush(stdout);

        keyTmp = getch();

        if(keyTmp == ' ') // Si la touche touchée est espace, je mets le jeu en pause
            pause = !pause;
        else if(keyTmp == stopMin || keyTmp == stopMaj){ // Si la touche touchée est 'o' ou 'O', je quitte le jeu
            stop = 1; 
        }
        // Sinon si je suis pas dans le mode 4, ça veut dire le serpent principal c'est moi qui le controle, je rentre
        else if(mode != 4 && (keyTmp == KEY_UP || keyTmp == KEY_DOWN || keyTmp == KEY_LEFT || keyTmp == KEY_RIGHT)){
            // ( Si le jeu n'est pas en pause, ou la touche cliquée est la touche de quitter) et (le serpent contient que la tête ou la direction qu'on veut prendre n'est pas l'opposée de la direction prise avant) alors on met à jour 'key'
            if((!pause || keyTmp == stopMaj || keyTmp == stopMin) && (serpent->list_section->premier->suivant == NULL || !verifier_touches(keyTmp, key)))
                key = keyTmp; 
        }
        // Ici, si on est dans le mode 2 et la touche touchée est 'z' ou 'q' ou 'd' ou 's', ça veut dire on est en train de piloter le premier serpent dans le tableau qui est le serpent du deuxième joueur.
        else if(mode == 2 && (keyTmp == 'z' || keyTmp == 's' || keyTmp == 'q' || keyTmp == 'd' || keyTmp == 'Z' || keyTmp == 'S' || keyTmp == 'Q' || keyTmp == 'D')){
            // ( Si le jeu n'est pas en pause, ou la touche cliquée est la touche de quitter) et (le serpent contient que la tête ou la direction qu'on veut prendre n'est pas l'opposée de la direction prise avant) alors on met à jour 'key'
            if(!pause && serpent_tab && serpent_tab[0] && (serpent_tab[0]->list_section->premier->suivant == NULL || !verifier_touches(keyTmp, keys[0])))
                keys[0] = keyTmp;
        }
        // Ici on est dans le mode 4, ça veut dire même le serpent principal, on va le piloter par un IA
        else if(mode == 4){key = ai(serpent, grille, M, KEY_UP, KEY_RIGHT, KEY_LEFT, KEY_DOWN); if(key == -1) perdu = 1;}

        if(!pause){ // Si le jeu n'est pas en pause on rentre là-dans

            // On récupère les coordonnées de la dernière case dans ces deux variables
            int x_derniere_case = serpent->list_cases->dernier->cases_coord.x;
            int y_derniere_case = serpent->list_cases->dernier->cases_coord.y;

            switch(key){ 

                case KEY_UP:
                    // Si la touche est Haut
                    serpent->tete.y--; // Le y de la nouvelle tête du serpent change
                    bouger_serpent(serpent, Haut, M); // On bouge le serpent vers Haut
                break;

                case KEY_DOWN:
                    serpent->tete.y++;
                    bouger_serpent(serpent, Bas, M);
                break;

                case KEY_LEFT:
                    serpent->tete.x--;
                    bouger_serpent(serpent, Gauche, M);
                break;

                case KEY_RIGHT:
                    serpent->tete.x++;
                    bouger_serpent(serpent, Droite, M);
                break;
            }

            if(key == KEY_UP || key == KEY_DOWN || key == KEY_LEFT || key == KEY_RIGHT){
                // On vérifie si la tête n'a pas touché la grille ou n'a pas touché une case du serpent lui même
                if(serpent->tete.y == grille->n || serpent->tete.y == -1 || serpent->tete.x == -1 || serpent->tete.x == grille->m || (M[serpent->tete.y][serpent->tete.x].contenu == Snake && M[serpent->tete.y][serpent->tete.x].numero_serpent == indice_serpent_principal)) perdu = 1;

                // On vérifie si le serpent n'a pas touché un autre serpent
                else if(M[serpent->tete.y][serpent->tete.x].contenu == Snake && M[serpent->tete.y][serpent->tete.x].numero_serpent != indice_serpent_principal) indice_gagnant = indice_serpent_principal;

                // On met la case de la nouvelle tête dans la matrice des cases à la valeur Snake avec le numéro du serpent
                else{M[serpent->tete.y][serpent->tete.x].contenu = Snake; M[serpent->tete.y][serpent->tete.x].numero_serpent = indice_serpent_principal;}
            }
                

            M[y_derniere_case][x_derniere_case].contenu = Vide; // On met la case de l'ancienne dernière dernière case du serpent à Vide dans la matrice des cases

            if(verifier_tete_et_fruit(grille, serpent)){ // On verifie si la nouvelle tête a mangé un fruit
                if(secondes_boost > 0 && mangeur_de_fruit_boost == indice_serpent_principal) // Si on est dans le mode boost, le score augmente de 3
                    score+=3;
                else
                    score++; // sinon de 1

                if(grille->type_fruit == Boost){
                    // Si le fruit mangé est le fruit Boost, on donne 10 secondes en mode Boost
                    secondes_boost = 100;
                    mangeur_de_fruit_boost = indice_serpent_principal; // On considére l'indice du serpent principal est -1
                } 

                int aleaTaille = rand() % 5 + 1; // On met une valeur aléatoire entre 1 et 5
                Section *section = creer_section(aleaTaille, (rand() % 7) + 41); // On crée une section avec une taille aleaTaille et une couleur aléatoire aussi

                ajouter_fin_liste_section(serpent->list_section, section); // On ajoute la section à la fin de la liste des sections du serpent
                ajouter_section_de_case_liste_mouvement(serpent->list_cases, aleaTaille, grille->n, grille->m, M); // Cette fonction ajoute 't' cases pour la liste des cases du serpent, tq: 't' est la taille de la dernière section ajoutée au serpent.
                Grille_tirage_fruit(grille, M, secondes_boost); // On fait un tirage au sort pour les coordonnées du fruit
            }

            if(serpent_tab){

                for(int i=0; i<taille; i++){

                    if(serpent_tab[i] && !perdu && indice_gagnant == -2){
                        // Si on est dans le mode 3 ou 4, chaque serpent du tableau on le pilote par un IA
                        if(mode == 3 || mode == 4){keys[i] = ai(serpent_tab[i], grille, M, 'z', 'd', 'q', 's'); if(keys[i] == -1) perdu = 1;}
                        int x2_derniere_case = serpent_tab[i]->list_cases->dernier->cases_coord.x;
                        int y2_derniere_case = serpent_tab[i]->list_cases->dernier->cases_coord.y;

                        switch(keys[i]){

                            case 'z':
                            case 'Z':
                                // Si la touche est 'z' ou 'Z'
                                serpent_tab[i]->tete.y--; // Le y de la nouvelle tête du serpent[i] change
                                bouger_serpent(serpent_tab[i], Haut, M); // On bouge le serpent[i] vers Haut
                            break;

                            case 's':
                            case 'S':
                                serpent_tab[i]->tete.y++;
                                bouger_serpent(serpent_tab[i], Bas, M);
                            break;

                            case 'q':
                            case 'Q':
                                serpent_tab[i]->tete.x--;
                                bouger_serpent(serpent_tab[i], Gauche, M);
                            break;

                            case 'd':
                            case 'D':
                                serpent_tab[i]->tete.x++;
                                bouger_serpent(serpent_tab[i], Droite, M);
                            break;
                        }

                        if(keys[i] == 'z' || keys[i] == 'Z' || keys[i] == 'q' || keys[i] == 'Q' || keys[i] == 's' || keys[i] == 'S' || keys[i] == 'd' || keys[i] == 'D'){
                            if(serpent_tab[i]->tete.y == -1 || serpent_tab[i]->tete.y == grille->n || serpent_tab[i]->tete.x == -1 || serpent_tab[i]->tete.x == grille->m || (M[serpent_tab[i]->tete.y][serpent_tab[i]->tete.x].contenu == Snake && M[serpent_tab[i]->tete.y][serpent_tab[i]->tete.x].numero_serpent == i)) perdu = 1;
                            else if(M[serpent_tab[i]->tete.y][serpent_tab[i]->tete.x].contenu == Snake && M[serpent_tab[i]->tete.y][serpent_tab[i]->tete.x].numero_serpent != i) indice_gagnant = i; // On vérifie si le serpent_2 ne s'est pas heurté lui même ou n'a pas touch)é les bords
                            else{M[serpent_tab[i]->tete.y][serpent_tab[i]->tete.x].contenu = Snake; M[serpent_tab[i]->tete.y][serpent_tab[i]->tete.x].numero_serpent = i;} // On met la case de la nouvelle tête dans la matrice des cases à la valeur Snake}
                        }

                        M[y2_derniere_case][x2_derniere_case].contenu = Vide; // On met la case de l'ancienne dernière dernière case du serpent[i] à Vide dans la matrice des cases

                        if(verifier_tete_et_fruit(grille, serpent_tab[i])){ // On verifie si la nouvelle tête a mangé un fruit
                            if(secondes_boost > 0 && i == mangeur_de_fruit_boost) // Si on est dans le mode boost, le score augmente de 3
                                scores[i]+=3;
                            else
                                scores[i]++; // sinon de 1

                            if(grille->type_fruit == Boost){
                                // Si le fruit mangé est le fruit Boost, on donne 10 secondes en mode Boost
                                secondes_boost = 100;
                                mangeur_de_fruit_boost = i; // On garde l'indice de celui qui a mangé le fruit
                            }
                            int aleaTaille = rand() % 5 + 1; // On met une valeur aléatoire entre 1 et 5
                            
                            Section *section = creer_section(aleaTaille, (rand() % 7) + 41); // On crée une section avec une taille aleaTaille et une couleur aléatoire aussi

                            ajouter_fin_liste_section(serpent_tab[i]->list_section, section); // On ajoute la section à la fin de la liste des sections du serpent[i]
                            ajouter_section_de_case_liste_mouvement(serpent_tab[i]->list_cases, aleaTaille, grille->n, grille->m, M); // Cette fonction ajoute 't' cases pour la liste des cases du serpent[i], tq: 't' est la taille de la dernière section ajoutée au serpent[i].
                            Grille_tirage_fruit(grille, M, secondes_boost); // On fait un tirage au sort pour les coordonnées du fruit
                        }
                    }
                }

            }

            if(secondes_boost > 0) // Si on est dans le mode Boost, on décremente le nombre de secondes qu'il nous reste en ce mode
                secondes_boost -= delay;
 
        }

    }while(!stop && !perdu && indice_gagnant == -2); 
    // Toute cette boucle se déroulera tant qu'on a pas quitter le jeu ( stop == 0 ) 
    // && personne n'a perdu (perdu == 0) 
    // && personne n'a gagné (indice_gagnant == -2)

    // Si on a perdu ou gagné on rentre ici
    if(perdu || indice_gagnant != -2){
        if(!serpent_tab){ // dans le cas ou y'a un seul joueur on affiche ça
            printf("\33[2J");
            printf("\33[H");
            printf("\33[31mPerdu ! :(\33[37m\33[1E");
            printf("Ton score est : %d\33[1E", score);
            fflush(stdout);
            halfdelay(WAIT);
            getch();
            getch();
        }
        else{ // Si y'a plusieurs joueurs, soit on prend le score max, soit on prend le joueur qui a mangé un autre, et ça on le saura selon l'indice
            if(indice_gagnant == -2){ 
                // Si l'indice est toujours -2, ça veut dire personne n'a mangé l'autre, donc on prend le score max
                indice_gagnant = max(scores, taille, score);
            }
            // On affiche le gagnant ici
            printf("\33[2J");
            printf("\33[H");
            if(serpent_tab){
                printf("Score Joueur 1 \33[%c%cm  \33[00m : %d\33[1E", serpent->list_section->premier->couleur/10 + '0',serpent->list_section->premier->couleur%10 + '0', score);
                for(int i=0; i<taille; i++){
                    printf("Score Joueur %d \33[%c%cm  \33[00m : %d\33[1E", 2+i, serpent_tab[i]->list_section->premier->couleur/10 + '0', serpent_tab[i]->list_section->premier->couleur%10 + '0', scores[i]);
                }
            }
            if(indice_gagnant == indice_egalite){
                printf("Egalité !!\33[1E");
            }
            else if(indice_gagnant != indice_serpent_principal)
                printf("La couleur \33[%c%cm  \33[00m a gagné\33[1E", serpent_tab[indice_gagnant]->list_section->premier->couleur/10 + '0', serpent_tab[indice_gagnant]->list_section->premier->couleur%10 + '0');
            else
                printf("La couleur \33[%c%cm  \33[00m a gagné\33[1E", serpent->list_section->premier->couleur/10 + '0', serpent->list_section->premier->couleur%10 + '0');

            fflush(stdout);
            halfdelay(WAIT);
            getch();
            getch();
        }
    }
    else if(stop){ // Ici ça veut dire on a quitté
        printf("\33[2J");
        printf("\33[H");
        printf("\33[31mOops ! Vous avez quitté :(\33[00m\33[1E");
        fflush(stdout);
        halfdelay(WAIT);
        getch();
        getch();
    }

    // On désalloue tout ici
    desallouer_matrice_cases(&M, grille->n);
    Grille_desallouer(&grille);
    desallouer_serpent(&serpent);
    if(serpent_tab){
        for(int i=0; i<taille; i++){
            desallouer_serpent(&serpent_tab[i]);
        }
    }

    free(scores);
    free(keys);

    // Fin de ncurses
    endwin();
    if(!stop) return score; // Si on a pas quitté, on retourne le score du premier joueur (qu'on utilisera dans le mode 1 seulement)
    else return 0; // Comme on a quitté c'est comme si on a annulé notre partie, donc on retourne 0
}