COMPILE = gcc -c -Wall -pedantic -std=c99
fichier = score_save.txt

all: menu.o Case.o Liste_Section.o Liste_Mouvement.o Serpent.o Grille.o Fonctions_Jeu_1_serpent.o main.o
	gcc menu.o Case.o Liste_Section.o Liste_Mouvement.o Serpent.o Grille.o Fonctions_Jeu_1_serpent.o main.o -o game -lncurses

menu.o: menu.c menu.h
	$(COMPILE) menu.c

Case.o: Case.c Case.h
	$(COMPILE) Case.c

Liste_Section.o : Liste_Section.c Liste_Section.h
	$(COMPILE) Liste_Section.c

Liste_Mouvement.o: Liste_Mouvement.c Liste_Mouvement.h
	$(COMPILE) Liste_Mouvement.c

Serpent.o: Serpent.c Serpent.h
	$(COMPILE) Serpent.c

Grille.o: Grille.c Grille.h
	$(COMPILE) Grille.c

Fonctions_Jeu_1_serpent.o : Fonctions_Jeu_1_serpent.c Fonctions_Jeu_1_serpent.h
	$(COMPILE) Fonctions_Jeu_1_serpent.c

main.o : main.c
	$(COMPILE) main.c

clean:
	rm *.o $(fichier) game