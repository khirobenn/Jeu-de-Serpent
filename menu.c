#include "menu.h"

// Pour afficher un menu et retourner le choix après la pression sur entrer
// Nous avons utilisé des unicodes pour afficher des symbols spéciaux, ainsi que des couleurs (trouvé sur le site partagé dans le sujet)

// pour le logo USPN
void menu(){
    printf("\33[1;35m                %s  %s %s%s%s %s%s%s %s%s%s %s               \33[1E", "\u2557","\u2554", "\u2554", "\u2550", "\u2557", "\u2554", "\u2550", "\u2557", "\u2554","\u2550", "\u2557", "\u2554");
    printf("                %s  %s %s%s%s %s%s%s %s %s %s               \33[1E", "\u2551", "\u2551", "\u255a", "\u2550", "\u2557", "\u2560", "\u2550", "\u255d", "\u2551", "\u2551", "\u2551");
    printf("                %s%s%s%s %s%s%s %s   %s %s%s%s               \33[1E\33[1E\33[00m", "\u255a", "\u2550", "\u2550", "\u255d", "\u255a", "\u2550", "\u255d", "\u255d", "\u255d", "\u255a","\u2550", "\u255d");
}

void aurevoir(){
    initscr();
    refresh();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    halfdelay(30);
    printf("\33[38;5;117mA bientôt !\33[00m\33[1E");
    fflush(stdout);
    getch();
    
    printf("\33[?25h"); // Rendre le cursor dans l'affichage
    

    endwin();
}

// Pour afficher un menu et retourner le choix après la pression sur entrer
int menu_table(int choix, int high_score){

    int key_menu;
   
    char *table_de_choix[5] = {
        "                 Jeu du serpent                ",
        "           Jeu du serpent (2 joueurs)          ",
        "       Jeu du serpent (contre ordinateur)      ",
        " Jeu du serpent (Ordinateur contre ordinateur) ",
        "                    Quitter                    ",};

    char *table_mode[5] = {
        "Mode 1 : Mode Solo (jouer tout seul)",
        "Mode 2 : Jouer contre un ami",
        "Mode 3 : Jouer contre un IA ou plusieurs",
        "Mode 4 : Faire jouer un IA ou plusieurs entre eux",
        "Quitter",
    };
    initscr();
    refresh();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    do{
        printf("\33[2J");
        printf("\33[H");
        menu();
        printf("                    %s Mode 1 \33[00m%s               \33[00m\33[1E","\u25B6",  "\u25C0");
        printf("\33[1;35m                  HighScore : %d                 \33[00m\33[1E\33[1E", high_score);
        printf("%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s MENU %s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s\33[1E","\u2554" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550"  ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2557");
        for(int i=0; i<5; i++){
            printf("%s", "\u2551");
            if(choix == i+1) printf("\33[5m\33[45m%s\33[00m", table_de_choix[i]);
            else printf("%s", table_de_choix[i]);
            printf("%s\33[1E", "\u2551");
        }
        printf("%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s\33[1E\33[1E","\u255a" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" , "\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550"  ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u2550" ,"\u255d");
        printf("Vous êtes sur le point de choisir %s \33[1;35m%s\33[00m\33[1E", "\u25B6", table_mode[choix-1]);
        printf("%s Cliquez sur 'entrer' pour confirmer votre choix.\33[1E\33[1E", "\u25B6");
        
        printf("%s Touches du premier joueur : %s, %s, %s et %s.\33[1E", "\u25B6", "\33[38;5;226m\u2B06\33[00m", "\33[38;5;226m\u2B07\33[00m", "\33[38;5;226m\u27A1\33[00m", "\33[38;5;226m\u2B05\33[00m");
        printf("%s Touches du deuxième joueur : '\33[38;5;226mZ\33[00m'(%s), '\33[38;5;226mS\33[00m'(%s), '\33[38;5;226mD\33[00m'(%s) et '\33[38;5;226mQ\33[00m'(%s).\33[1E  \33[3;33mTel que 'touche' correspend à (direction)\33[00m\33[1E", "\u25B6", "\u2B06", "\u2B07", "\u27A1", "\u2B05");
        printf("\33[?25l");

        fflush(stdout);
        key_menu = getch();
        if(key_menu == KEY_UP){choix--; if(choix == 0) choix = 5;}
        else if(key_menu == KEY_DOWN){choix++; if(choix == 6) choix = 1; }

    }while(key_menu != 10);

    endwin();
    return choix;
}