/**
@file joueur.c
@brief Source code file of TP3
@author Marek Felsoci, Thomas Millot
@date 12th April 2015
*/

#include "../include/joueur.h"

joueur * alloue_joueur()
{
    joueur * j = (joueur *) malloc(sizeof(joueur));
    j -> inventaire = (char **) malloc(25 * sizeof(char *));
    for (int i = 0; i < 25; i++)
        j -> inventaire[i] = (char *) malloc(20 * sizeof(char));
    j -> vie = 5;
    j -> defence = 1;
    j -> attaque = 2;
    return j;
}

void suppr_joueur(joueur * j)
{
    for (int i = 0; i < 25; i++) {
        free (j -> inventaire[i]);
    }
    free(j -> inventaire);
    free(j);
}
