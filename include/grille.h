/**
@file grille.h
@brief Header file for "grille.c" file of TP3
@author Marek Felsoci, Thomas Millot
@date 12th April 2015
*/

#ifndef GRILLE
#define GRILLE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "joueur.h"

typedef struct
{
    int m;
    int n;
    int **content;
} grille;

grille * alloue_grille(int n, int m);

grille * creer_grille(char filename[], joueur * j);

void suppr_grille(grille * g);

int salles_vides(grille * g);

char afficher_element(int e);

void afficher_grille(grille * g, joueur * j);

void deplacement(grille * g, joueur * j);

#endif /* end of include guard: GRILLE */
