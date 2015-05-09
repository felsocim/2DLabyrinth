/**
@file joueur.h
@brief Header file for "joueur.c" file of TP3
@author Marek Felsoci, Thomas Millot
@date 12th April 2015
*/

#ifndef JOUEUR
#define JOUEUR

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int x;
    int y;
    int vie;
    int attaque;
    int defence;
    char **inventaire;
} joueur;

typedef struct
{
    int x;
    int y;
    int vie;
    int attaque;
    int defence;
} monstre;

joueur * alloue_joueur();

void suppr_joueur(joueur * j);

#endif /* end of include guard: JOUEUR */
