/**
@file grille.h
@brief Header file for "grille.c" file of TP3
@author Marek Felsoci
@date 12th April 2015
*/

typedef struct { int direction; int type; }room;
typedef struct { int**tab; int n; int m; }grille;
typedef struct { int ln; int col; }tabsize;
typedef struct { int x; int y; }gposit;
typedef struct { gposit position; int life; int attack; int defense; char * invent; }gamer;

grille * newGrille(int l, int c);

void desallocGrille(grille * g);

void initGrille(grille * g);

void printGrille(grille * g);

void drawGrille(gamer * jr, grille * g);

tabsize loadGrilleSize(char filename[]);

gposit getGamerPositFromFile(char filename[]);

void loadGrilleFromFile(grille * g, char filename[]);

int notEmpty(grille * g);

void moveGamer(int dir, gamer * j, grille * g);
