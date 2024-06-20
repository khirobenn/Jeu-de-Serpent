#include "Fonctions_Jeu_1_serpent.h"
#include "menu.h"
#define chemin_fichier_score "score_save.txt"

/*  Réalisé par :
        BENMEZIANE KHIREDDINE               n° étudiant : 12308874
            &
        MOUSSAOUI IMENE                     n° étudiant : 12309982

    Groupe : DL

    Année universitaire : 2023/2024

    Supervisé par : DUPONT-BOUILLARD ALEXANDRE

    NB : Les fichiers doivent être compilés sous un système Linux (nous avons pas vérifié sur windows),
         et le fichier executable est nommé 'game'
*/

int main(int argc, char *argv[]){
    if(argc < 4){
        printf("Nombre d'arguments insiffusants!\nIl faut 3 arguments : 'nombres de lignes', 'nombres de colonnes' et la 'vitesse du jeu'\n");
        return 1;
    }
    srand(time(NULL));//inialiser le generateur de nombres pseudo-aleatoirs
    const int n = strtol(argv[1], NULL, 10); // on récupère le nombre de lignes
    const int m = strtol(argv[2], NULL, 10); // on récupère le nombre de colonnes
    const int delay = strtol(argv[3], NULL, 10); // on récupère la vitesse

    int choix = 1; // Utilisé pour le menu

    int new_score = 0; // On récupère là dans le score du jeu 

    int high_score = 0; // On récupère là dans le HighScore

    FILE * f = fopen(chemin_fichier_score, "r");
    if(f){ // si le fichier existe, on récupère le HighScore de la dérnière fois qu'on a joué
        fscanf(f, "%d", &high_score);
        fclose(f);
    }

    
    Serpent *serpent = NULL; // Ce serpent existe toujours (c'est notre serpent principal)
    Serpent **serpent_tab = NULL;//pour les autres serpents
    int taille;
    
    
    
               
    do{
        Grille *g = Grille_allouer(n,m); // On crée une grille n*M
        Case ** M = creer_matrice_cases(n, m); // On crée une matrice de case n*m
        choix = menu_table(choix, high_score); // On affiche le menu et on  récupère le choix
        switch(choix)
        {
            case 1: // Jeu du serpent
                
                serpent = creer_serpent(41); // On crée un serpent (couleur de la tete 41)
                new_score = Game(g, serpent, NULL, delay, M, choix, 0); // On appelle la fonction Game qui retourne le score
                if(new_score > high_score) high_score = new_score; // Si le nouveau score est plus grand que le HighScore, on met à jour ce dernier
            break;

            case 2:
               
                serpent = creer_serpent(41); // On crée un serpent principale
                serpent_tab = malloc(sizeof(Serpent*));// On crée un tableau de serpent d'un seul élement qui est considéré comme le deuxième serpent
                serpent_tab[0] = creer_serpent(46);// On crée le deuxieme serpent 
                serpent_tab[0]->tete.y = n-1;// on change les cordonnees de la tete de deuxieme serpent
                serpent_tab[0]->list_cases->premier->cases_coord.y = n-1;//on change les cordonnees de la tete de deuxieme serpent dans la liste de mouvement
                new_score = Game(g, serpent, serpent_tab, delay, M, choix, 1);//On appelle la fonction Game
            break;

            case 3:
            case 4:
                do{
                    printf("\33[2J");// effacer l'ecran 
                    printf("\33[H");// effacer l'ecran 
                    if(choix == 3)
                        printf("Contre combien de joueurs voulez-vous jouer ? (à ne pas dépasser 6)\n--> "); // On peut pas dépasser 6 à cause des couleurs des serpents
                    else
                        printf("Combien d'IA voulez-vous faire jouer ? (à ne pas dépasser 7)\n--> "); // On peut pas dépasser 7 à cause des couleurs des serpents
                    scanf("%d", &taille); // lire le nombre de serpent 
                }while(((taille > 7 || taille <= 0) && choix == 4) || ((taille > 6 || taille <= 0) && choix == 3));

                if(choix == 4) taille--;// meme le serpent principale on concederent comme un IA
                serpent_tab = malloc(sizeof(Serpent *)*taille);// creer le tableaux des serpent 
                for(int i=0; i<taille; i++){
                    int couleur = 42+i;// donner la couleur de la tete pour chaque serpent (chaque serpent doit avoir une couleur differente )
                    serpent_tab[i] = creer_serpent(couleur);// creer chaque serpent
                    serpent_tab[i]->tete.y = n-i*n/taille - 1;//fixer les cordonnees de la tete
                    serpent_tab[i]->tete.x = m-i*m/taille - 1;//fixer les cordonnees de la tete
                    serpent_tab[i]->list_cases->premier->cases_coord.y = n-i*n/taille - 1;//fixer les cordonnees de la tete dans la liste de mouvement 
                    serpent_tab[i]->list_cases->premier->cases_coord.x = m-i*m/taille - 1;//fixer les cordonnees de la tete dans la liste de mouvement 
                }  
                
                serpent = creer_serpent(41); // On crée le serpent principale
                new_score = Game(g, serpent, serpent_tab, delay, M, choix, taille);//On appelle la fonction Game qui retourne le score
            break;


        }



    }while(choix != 5);


    // On met à jour le HighScore dans le fichier, pour le récupérer une prochaine fois qu'on joue
    f = fopen(chemin_fichier_score, "w");
    fprintf(f, "%d", high_score);
    fclose(f);

    aurevoir();
    return 0;
}