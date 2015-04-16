/**
@file grille.c
@brief Source code file of TP3
@author Marek Felsoci
@date 12th April 2015
*/

#include "grille.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#define LIFE_MAX 5 //maximum count of lives for a gamer
#define WIN 8 //code number assigned to the finish position of a labyrinth, when reached the gamer wins

/**
@brief Allocate memory space for new element of type "grille" of specified size
@param <int l> <number of lines of "grille">
@param <int c> <number of columns of "grille">
@return <returns a new "grille" element>
*/
grille * newGrille(int l, int c)
{
    int i;

    grille * nouveau = (grille*) malloc(sizeof(grille));

    nouveau->tab = (int**) malloc(l*sizeof(int*));

    for (i=0;i<l;i++)
    {
        nouveau->tab[i] = (int*) malloc(c*sizeof(int));
    }

    nouveau->n = l;
    nouveau->m = c;

    return(nouveau);
}

/**
@brief Deallocate memory space of an element of type "grille" of specified size
@param <grille * g> <"grille" element to deallocate>
@return <void>
*/
void desallocGrille(grille * g)
{
    int i;

    for (i=0;i<(g->n);i++)
    {
        free(g->tab[i]);
    }

    free(g->tab);

    free(g);

    return;
}

/**
@brief Initializes an element of type "grille" to 0
@param <grille * g> <"grille" element to initialize>
@return <void>
*/
void initGrille(grille * g)
{
    int i,j;

    for (i=0;i<(g->n);i++)
    {
        for (j=0;j<(g->m);j++)
        {
            g->tab[i][j] = 0;
        }
    }

    return;
}

/**
@brief Prints the content of an element of type "grille" on terminal
@param <grille * g> 
@return <void>
*/
void printGrille(grille * g)
{
    int i,j;

    clear();

    printw(" ");
    refresh();
    for (i=0;i<(g->m);i++)
    {
        printw("--");
        refresh();
    }

    printw("\n");
    refresh();

    for (i=0;i<(g->n);i++)
    {
        printw("| ");
        refresh();
        for (j=0;j<(g->m);j++)
        {
            printw("%d ",g->tab[i][j]);
            refresh();
        }
        printw("|\n");
        refresh();
    }

    printw(" ");
    refresh();
    for (i=0;i<(g->m);i++)
    {
        printw("--");
        refresh();
    }

    printw("\n");
    refresh();

    return;
}

/**
@brief Draws a labyrinth according to data from loaded file on terminal using ncurses
@param <grille * g> 
@param <gamer * jr> <the gamer whose position will be loaded>
@return <void>
*/
void drawGrille(gamer * jr, grille * g)
{
    int i,j;

    clear();

    refresh();

    for (i=0;i<(g->n);i++)
    {
        for (j=0;j<(g->m);j++)
        {
            if (g->tab[i][j] == 1)
            {
                mvprintw(i,j,"#");
                refresh();
            }

            if (g->tab[i][j] == 2)
            {
                mvprintw(i,j,"-");
                refresh();
            }

            if (g->tab[i][j] == 3)
            {
                mvprintw(i,j,"+");
                refresh();
            }
        }
    }

    mvprintw((jr->position.y),(jr->position.x),"*");
    refresh();

    return;
}


/**
@brief Loads the size of an element of type "grille" from a compatible text file
@param char filename[] file name
@return tabsize token
*/
tabsize loadGrilleSize(char filename[])
{
    char delim[2] = " ";
    char * line;
    char * column;
    char readline[10];
    tabsize token;

    FILE *sg;

    if ( ( sg = fopen(filename,"r") ) == NULL )
    {
        perror("Cannot open file!");
        exit(1);
    }

    fgets(readline,9,sg);

    fclose(sg);

    line = strtok(readline,delim);
    token.ln = (int) strtof(line,NULL);

    column = strtok(NULL,delim);
    token.col = (int) strtof(column,NULL);

    return token;
}

/**
@brief Gets the information about initial gamer position from a compatible text file
@param <char filename[]> <file name>
@return <gposit token>
*/
gposit getGamerPositFromFile(char filename[])
{
    char line[10]; int cnt=0;

    char delim[2] = " ";
    char * px;
    char * py;
    gposit token;

    FILE *fd;

    if ((fd = fopen(filename,"r"))==NULL)
    {
        perror("Cannot open file!");
        exit(1);
    }

    while ((!feof(fd)) && (cnt <= 2))
    {
        cnt++;
        fgets(line,10,fd);

        if (cnt == 2)
        {
            px = strtok(line,delim);
            token.x = (int) strtof(px,NULL);

            py = strtok(NULL,delim);
            token.y = (int) strtof(py,NULL);
        }
    }
    fclose(fd);

    return token;
}

/**
@brief Loads the content of an element of type "grille" from a compatible text file
@param <grille * g> <an element of type "grille" to load the file content in>
@param <char filename[]> <file name>
@return <void>
*/
void loadGrilleFromFile(grille * g, char filename[])
{
    char line[1000]; int cnt=0;

    char delim[2] = " ";
    char * x;

    int j;

    FILE *tl;

    if ((tl = fopen(filename,"r"))==NULL)
    {
        perror("Cannot open file!");
        exit(1);
    }

    while (cnt <= (g->n + 1))
    {
        cnt++;
        fgets(line,1000,tl);

        if (cnt > 2)
        {
            x = strtok(line,delim);

            g->tab[cnt-3][0] = (int) strtof(x,NULL);

            for (j=1;j<(g->m);j++)
            {
                x = strtok(NULL,delim);
                g->tab[cnt-3][j] = (int) strtof(x,NULL);
            }
        }
    }
    fclose(tl);

    return;
}

/**
@brief Count the number of empty rooms in an element of type "grille"
@param <grille * g> <an element of type "grille" to verify>
@return <int>
*/
int notEmpty(grille * g)
{
    int i,j,c;

    for (i=0;i<(g->n);i++)
    {
        for (j=0;j<(g->m);j++)
        {
            if (g->tab[i][j] == 0)
            {
                c++;
            }
        }
    }
    return (((g->n)*(g->m)) - c);
}

/**
@brief Moves a gamer within an element of type "grille" when possible
@param <int dir> <integer indicating the direction to move in>
@param <gamer j> <a gamer to move>
@param <grille * g> <an element of type "grille" containing gamer j>
@return <void>
*/

/** In this function :
    Direction options are : s -> SOUTH, a -> WEST, d -> EAST, w -> NORTH
    Room types are : 1 -> contents a wall (impossible to move in)
                     2 -> contents a trap (decrease the count of lives)
                     3 -> contents a new life
                     */
void moveGamer(int dir, gamer * jr, grille * g)
{
    int w,s,a,d;
    switch (dir)
    {
        case 119: //MOVE ABOVE - KEY "w"
        {
            w = (g->tab[(jr->position.y) - 1][jr->position.x]);
            if ((w == 0) || (w == 2) || (w == 3) || (w == WIN))
            {
                jr->position.y--;
                if ( (g->tab[(jr->position.y)][jr->position.x]) == 2 )
                {
                    jr->life--;
                }

                if ( (g->tab[(jr->position.y)][jr->position.x]) == 3 )
                {
                    if ( (jr->life) < LIFE_MAX )
                    {
                        jr->life++;
                        g->tab[jr->position.y][jr->position.x] = 0;
                    }
                }
            }
        } break;
        case 115: //MOVE BELOW - KEY "s"
        {
            s = (g->tab[(jr->position.y) + 1][jr->position.x]);
            if ((s == 0) || (s == 2) || (s == 3) || (s == WIN))
            {
                jr->position.y++;
                if ( (g->tab[(jr->position.y)][jr->position.x]) == 2 )
                {
                    jr->life--;
                }

                if ( (g->tab[(jr->position.y)][jr->position.x]) == 3 )
                {
                    if ( (jr->life) < LIFE_MAX )
                    {
                        jr->life++;
                        g->tab[jr->position.y][jr->position.x] = 0;
                    }
                }
            }
        } break;
        case 97: //MOVE LEFT - KEY "a"
        {
            a = (g->tab[jr->position.y][jr->position.x - 1]);
            if ((a == 0) || (a == 2) || (a == 3) || (a == WIN))
            {
                jr->position.x--;
                if ( (g->tab[jr->position.y][jr->position.x]) == 2 )
                {
                    jr->life--;
                }
                if ( (g->tab[jr->position.y][jr->position.x]) == 3 )
                {
                    if ( (jr->life) < LIFE_MAX )
                    {
                        jr->life++;
                        g->tab[jr->position.y][jr->position.x] = 0;
                    }
                }
            }
        } break;
        case 100: //MOVE RIGHT - KEY "d"
        {
            d = (g->tab[jr->position.y][jr->position.x + 1]);
            if ((d == 0) || (d == 2) || (d == 3) || (d == WIN))
            {
                jr->position.x++;
                if ( (g->tab[jr->position.y][jr->position.x]) == 2 )
                {
                    jr->life--;
                }
                if ( (g->tab[jr->position.y][jr->position.x]) == 3 )
                {
                    if ( (jr->life) < LIFE_MAX )
                    {
                        jr->life++;
                        g->tab[jr->position.y][jr->position.x] = 0;
                    }
                }
            }
        } break;
        default: { jr->position.x = jr->position.x; jr->position.y = jr->position.y; }
    }
}

/**
@brief Main function gets involved all the functions above excepting "printGrille" which has been replaced by "drawGrille"
*/
int main()
{
    char filename[256] = "grille.txt"; grille * nouvelle; tabsize current; int choice; int sx,sy; gamer * jr; int dir;

    jr = (gamer*) malloc(sizeof(gamer));

    jr->life = 5;

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

    if ( (choice == 110) || (choice == 78) )
    {
        current = loadGrilleSize(filename);
        nouvelle = newGrille(current.ln,current.col);

        initGrille(nouvelle);

        jr->position = getGamerPositFromFile(filename);

        loadGrilleFromFile(nouvelle,filename);

        drawGrille(jr,nouvelle);

        while (jr->life > 0)
        {
            dir = getch();

            moveGamer(dir,jr,nouvelle);

            clear();

            drawGrille(jr,nouvelle);

            mvprintw(nouvelle->n + 3,1,"X: %d, Y: %d, REMAINING LIVES: %d",jr->position.x,jr->position.y,jr->life);

            if (nouvelle->tab[jr->position.y][jr->position.x] == WIN)
            {
                mvprintw(nouvelle->n + 4,1,"YOU WON --> Press any key to quit!");
                refresh();

                getch();
                endwin();
                exit(0);
            }
        }

        if (jr->life <= 0)
        {
            mvprintw(nouvelle->n + 4,1,"GAME OVER --> Press any key to quit!");
            refresh();

            getch();
            endwin();
            exit(0);
        }
    }
    else if ( (choice == 108) || (choice == 76) )
    {
        printw("Enter the path of a saved game file: ");
        scanw("%s",filename);

        current = loadGrilleSize(filename);
        nouvelle = newGrille(current.ln,current.col);

        initGrille(nouvelle);

        jr->position = getGamerPositFromFile(filename);

        loadGrilleFromFile(nouvelle,filename);

        drawGrille(jr,nouvelle);

        while (jr->life > 0)
        {
            dir = getch();

            moveGamer(dir,jr,nouvelle);

            clear();

            drawGrille(jr,nouvelle);

            mvprintw(nouvelle->n + 3,1,"X: %d, Y: %d, REMAINING LIVES: %d",jr->position.x,jr->position.y,jr->life);

            if (nouvelle->tab[jr->position.y][jr->position.x] == WIN)
            {
                mvprintw(nouvelle->n + 4,1,"YOU WON --> Press any key to quit!");
                refresh();

                getch();
                endwin();
                exit(0);
            }
        }
        if (jr->life <= 0)
        {
            mvprintw(nouvelle->n + 4,1,"GAME OVER --> Press any key to quit!");
            refresh();

            getch();
            endwin();
            exit(0);
        }
    }
    else if ( (choice == 113) || (choice == 81) )
    {
        endwin();
        exit(0);
    }

    desallocGrille(nouvelle);
    free(jr);

    return 0;
}
