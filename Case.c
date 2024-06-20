#include "Case.h"

Case ** creer_matrice_cases(int n, int m){
    Case ** M = malloc(sizeof(Case *)*n);
    for(int i=0; i<n; i++){
        M[i] = malloc(sizeof(Case)*m);
    }

    return M;
}

void desallouer_matrice_cases(Case ***M, int n){
    if(*M){
        for(int i = 0; i<n; i++){
            free((*M)[i]);
        }
        free(*M);
        *M = NULL;
    }
}