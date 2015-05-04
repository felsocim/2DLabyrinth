/**
@file grille.c
@brief Source code file of TP3
@author Marek Felsoci, Thomas Millot
@date 12th April 2015
*/

#include "../include/grille.h"
#define VIE_MAX 5 //maximum count of lives for a gamer

/**
@brief Allocate memory space for new element of type "grille" of specified size
@param <int n> <number of lines of "grille">
@param <int m> <number of columns of "grille">
@return <returns a new "grille" element>
*/
grille * alloue_grille(int n, int m)
{
    grille * g = (grille *) malloc(sizeof(grille));
    g -> n = n;
    g -> m = m;
    g -> content = (int **) malloc(g -> n * sizeof(int *));
    for (int i = 0; i < g -> n; i++)
        g -> content[i] = (int *) malloc(g -> m * sizeof(int));
    return g;
}

/**
@brief Loads the content of an element of type "grille" from a compatible text file,
plus loads the gamer position
@param <grille * g> <an element of type "grille" to load the file content in>
@param <char filename[]> <file name>
@return <void>
*/
grille * creer_grille(char filename[], joueur * j)
{
    FILE* fichier = NULL;
    fichier = fopen(filename, "r");
    if (fichier != NULL)
    {
        int n, m;
        fscanf(fichier,"%d %d", &n, &m);
        fgetc(fichier);
        grille * g = alloue_grille(n, m);

        fscanf(fichier, "%d %d", &j -> x, &j -> y);
        fgetc(fichier);

        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                fscanf(fichier,"%d",&g -> content[i][j]);
            }
            fgetc(fichier);
        }
        fclose(fichier);
        return g;
    }
    else {
        printf("Impossible d'ouvrir le fichier grille.txt");
        exit (1);
    }
}

/**
@brief Deallocate memory space of an element of type "grille" of specified size
@param <grille * g> <"grille" element to deallocate>
@return <void>
*/
void suppr_grille(grille * g)
{
    for (int i = 0; i < g -> m; i++) {
        free (g -> content[i]);
    }
    free(g -> content);
    free(g);
}

/**
@brief Count the number of empty rooms in an element of type "grille"
@param <grille * g> <an element of type "grille" to verify>
@return <int>
*/
int salles_vides(grille * g)
{
    int i, j, c = 0;
    for (i = 0; i < (g -> n); i++)
        for (j = 0; j < (g -> m); j++)
            if (g -> content[i][j] == 0)
                c++;
    return (((g->n)*(g->m)) - c);
}

/**
@brief Draws different elements according to a speciefied number
@param <int e>
@return <char>
*/
char afficher_element(int e)
{
    switch (e) {
        case 0 :
            return ' ';
            break;
        case 1 :
            return '#';
            break;
        case 2 :
            return '-';
            break;
        case 3 :
            return '+';
            break;
        case 8 :
            return 'O';
            break;
        default :
            return ' ';
            break;
    }
}

/**
@brief Draws a labyrinth according to data from loaded file on terminal using ncurses
@param <grille * g>
@param <joueur * j> <the gamer whose position will be loaded>
@return <void>
*/
void afficher_grille(grille * g, joueur * jr)
{
    int i,j;
    clear();
    refresh();
    for (i=0;i<(g->n);i++)
        for (j=0;j<(g->m);j++)
            mvprintw(i, j, "%c", afficher_element(g -> content[i][j]));

    mvprintw(jr -> y, jr -> x, "*");
    refresh();
}

/**
@brief Moves a gamer within an element of type "grille" when possible
@param <joueur * j> <a gamer to move>
@param <grille * g> <an element of type "grille" containing gamer j>
@return <void>
*/

/** In this function :
    Direction options are : s -> SOUTH, q -> WEST, d -> EAST, z -> NORTH
    Room types are : 1 -> contents a wall (impossible to move in)
                     2 -> contents a trap (decrease the count of lives)
                     3 -> contents a new life
                     */
void deplacement(grille * g, joueur * j)
{
    int t = getch();
    // z=122 q=113 s=115 d=100
    switch (t) {
        case 122 :
            if (j -> y == 1)
                break;
            if (g -> content[j -> y - 1][j -> x] != 1)
                (j -> y) --;
            break;
        case 115 :
            if (j -> y == g -> n - 1)
                break;
            if (g -> content[j -> y + 1][j -> x] != 1)
                (j -> y) ++;
            break;
        case 113 :
            if (g -> content[j -> y ][j -> x - 1] != 1)
                (j -> x) --;
            break;
        case 100 :
            if (g -> content[j -> y ][j -> x + 1] != 1)
                (j -> x) ++;
            break;
    }

    if ( (g->content[(j -> y)][j -> x]) == 2 )
        j -> vie--;

    if ( (g->content[(j -> y)][j -> x]) == 3 )
        if ( (j -> vie) < VIE_MAX)
        {
            j -> vie++;
            g -> content[j -> y][j -> x] = 0;
        }
}
