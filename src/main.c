/**
@file main.c
@brief Source code file of TP3
@author Marek Felsoci, Thomas Millot
@date 12th April 2015
*/

#include "../include/grille.h"
#include "../include/joueur.h"

/**
@brief Main function gets involved all the functions above excepting "printGrille" which has been replaced by "drawGrille"
*/
int main()
{
    char filename[256] = "data/grille.txt";
    joueur * j = alloue_joueur();
    int choice;

    initscr();
    mvprintw(2,2,"LABYRINTH GAME v.1");
    refresh();
    mvprintw(4,2,"-- Make your choice --");
    refresh();
    mvprintw(6,3,"Press 'N' to start a new game (labyrinth chosen by default)");
    mvprintw(7,3,"Press 'L' to load a game from a file (choose the labyrinth from a file)");
    mvprintw(8,3,"Press 'Q' to quit\n");
    refresh();
    choice = getch();
    clear();

    if ((choice == 110) || (choice == 78) || (choice == 108) || (choice == 76))
    {
        if ((choice == 108) || (choice == 76))
        {
            printw("Enter the path of a saved game file: ");
            scanw("%s",filename);
        }

        grille * g = creer_grille(filename, j);
        afficher_grille(g, j);

        while (j -> vie > 0)
        {
            afficher_grille(g, j);
            mvprintw(g -> n + 3,1,"X: %d, Y: %d, REMAINING LIVES: %d",j -> x, j -> y,j -> vie);
            deplacement(g, j);

            if (g -> content[j -> y][j -> x] == 8)
            {
                mvprintw(g -> n + 4,1,"YOU WON --> Press any key to quit!");
                refresh();
                getch();
                endwin();
                exit(0);
            }
        }

        if (j -> vie <= 0)
        {
            mvprintw(g -> n + 4,1,"GAME OVER --> Press any key to quit!");
            refresh();
            getch();
            endwin();
            exit(0);
        }
        suppr_grille(g);
    }

    else if ( (choice == 113) || (choice == 81) )
    {
        endwin();
        exit(0);
    }

    suppr_joueur(j);
    return 0;
}
