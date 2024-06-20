#ifndef __MENU__
#define __MENU__

#include <ncurses.h>

void menu();//afficher le logo USPN
void aurevoir(); // Pour afficher un message quand on quitte
int menu_table(int, int);// // Pour afficher un menu et retourner le choix après la pression sur entrer

#endif