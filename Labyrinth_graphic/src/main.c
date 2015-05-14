/**
@file main.c
@brief Source code file of TP3
@author Marek Felsoci, Thomas Millot
@date 12th April 2015
*/

#include "../include/grille.h"
#include "../include/joueur.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <cairo.h>

#define SCREEN_WIDTH  576
#define SCREEN_HEIGHT 640
#define SPRITE_SIZE    32
#define STEP_SIZE 32

void drawRectCairo(SDL_Surface *screen) {
	/* Creation d'une surface Cairo a partir de la surface SDL */
	cairo_surface_t *cairosurf = cairo_image_surface_create_for_data (screen->pixels, CAIRO_FORMAT_RGB24,
    	screen->w, screen->h, screen->pitch);
    /* Creation d'une contexte graphique cairo a partir de la surface cairo */
    cairo_t* cr = cairo_create(cairosurf);
    /* Choix de la couleur du dessin */
    cairo_set_source_rgb(cr, 0, 0, 0);
  	/* Epaisseur du trait du dessin en nombre de pixel */
  	cairo_set_line_width(cr, 5);
  	/* Preparer le dessin du rectangle (x, y, longueur, largueur) */
	cairo_rectangle(cr, 0, SCREEN_HEIGHT - 32, 480, 32);
	/* Dessiner le rectangle (cairo_stroke_preserve pour dessiner plusieurs elements successifs sans reinitialiser le chemin) */
	//cairo_stroke(cr);
  	cairo_fill(cr);
}

/**
@brief Main function gets involved all the functions above excepting "printGrille" which has been replaced by "drawGrille"
*/

int main()
{
    char filename[106] = "data/grille.txt";
    int choice;
	char buffer[500];
	char buffer2[300];

    SDL_Surface *screen, *temp, *sprite, *backbg, *monster, *wall, *trap, *life, *sword, *armor, *door, *text, *defatt;
	SDL_Rect rcSprite, rcGrass, rcMonster, rcWall, rcTrap, rcLife, rcSword, rcArmor, rcDoor, rcText, rcDefatt;
	SDL_Event event;
	TTF_Font *font;
	SDL_Color white = {255, 255, 255};
	Uint8 *keystate;
	int colorkey, gameover = 0;

	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	SDL_WM_SetCaption("Lab", "Lab");

	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

	temp   = IMG_Load("data/perso.bmp");
	sprite = SDL_DisplayFormat(temp);


	temp   = IMG_Load("data/monstre.bmp");
	monster = SDL_DisplayFormat(temp);


	colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
	SDL_SetColorKey(sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);

	font = TTF_OpenFont("data/a.ttf", 14);

	temp  = SDL_LoadBMP("data/sol.bmp");
	backbg = SDL_DisplayFormat(temp);


	temp  = SDL_LoadBMP("data/mur.bmp");
	wall = SDL_DisplayFormat(temp);


    temp  = SDL_LoadBMP("data/piege.bmp");
	trap = SDL_DisplayFormat(temp);


	temp  = SDL_LoadBMP("data/potion.bmp");
	life = SDL_DisplayFormat(temp);


	temp  = SDL_LoadBMP("data/epee.bmp");
	sword = SDL_DisplayFormat(temp);


	temp  = SDL_LoadBMP("data/armure.bmp");
	armor = SDL_DisplayFormat(temp);


	temp  = SDL_LoadBMP("data/porte.bmp");
	door = SDL_DisplayFormat(temp);


    joueur * j = alloue_joueur();
    grille * g = creer_grille(filename, j);
    monstre * m = creer_monstre(g);

	rcSprite.x = j->x*SPRITE_SIZE;
	rcSprite.y = j->y*SPRITE_SIZE;

	rcMonster.x = m->x*SPRITE_SIZE;
	rcMonster.y = m->y*SPRITE_SIZE;

	rcText.x = 32;
	rcText.y = SCREEN_HEIGHT - 32;

	rcDefatt.x = 32;
	rcDefatt.y = SCREEN_HEIGHT - 16;

    while ((gameover != 1))
    {

	 if (SDL_PollEvent(&event))
	 {
		switch (event.type)
		{
			case SDL_QUIT:
				gameover = 1;
            break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
                        gameover = 1;
					case SDLK_q:
						gameover = 1;
						break;
                    default:
                        break;
				}
            break;
		}




        keystate = SDL_GetKeyState(NULL);
		if ((keystate[SDLK_LEFT]) && (gameover != 2) ) {
		    deplacement(g,j,113);

			sprintf(buffer, "Remaining lives: %d", j->vie);
			text = TTF_RenderText_Solid(font, buffer, white);

			if (g->content[j->y][j->x] == 8)
            {
                sprintf(buffer, "You won! Press Q or ESC to quit");
                text = TTF_RenderText_Solid(font, buffer, white);

            }
		    if (m -> vie > 0)
                deplacement_monstre(g, j, m);
            if (j->vie <=0 )
            {
                sprintf(buffer, "You lost! Press Q or ESC to quit");
                text = TTF_RenderText_Solid(font, buffer, white);
                gameover = 2;
            }
			rcSprite.x = (j->x)*STEP_SIZE;
			rcMonster.x = (m->x)*STEP_SIZE;
			sprintf(buffer2, "Points of attack: %d Points of defense: %d", j->attaque, j->defense);
			defatt = TTF_RenderText_Solid(font, buffer2, white);
		}
		if (keystate[SDLK_RIGHT] && (gameover != 2) ) {
			deplacement(g,j,100);
			sprintf(buffer, "Remaining lives: %d", j->vie);
			text = TTF_RenderText_Solid(font, buffer, white);
			if (g->content[j->y][j->x] == 8)
            {
                sprintf(buffer, "You won! Press Q or ESC to quit");
                text = TTF_RenderText_Solid(font, buffer, white);
                gameover = 2;
            }
			if (m -> vie > 0)
                deplacement_monstre(g, j, m);
            if (j->vie <=0 )
            {
                sprintf(buffer, "You lost! Press Q or ESC to quit");
                text = TTF_RenderText_Solid(font, buffer, white);
                gameover = 2;
            }
			rcSprite.x = (j->x)*STEP_SIZE;
			rcMonster.x = (m->x)*STEP_SIZE;
			sprintf(buffer2, "Points of attack: %d Points of defense: %d", j->attaque, j->defense);
			defatt = TTF_RenderText_Solid(font, buffer2, white);
		}
		if (keystate[SDLK_UP] && (gameover != 2) ) {
			deplacement(g,j,122);
			sprintf(buffer, "Remaining lives: %d", j->vie);
			text = TTF_RenderText_Solid(font, buffer, white);
			if (g->content[j->y][j->x] == 8)
            {
                sprintf(buffer, "You won! Press Q or ESC to quit");
                text = TTF_RenderText_Solid(font, buffer, white);
                gameover = 2;
            }
			if (m -> vie > 0)
                deplacement_monstre(g, j, m);
            if (j->vie <=0 )
            {
                sprintf(buffer, "You lost! Press Q or ESC to quit");
                text = TTF_RenderText_Solid(font, buffer, white);
                gameover = 2;
            }
			rcSprite.y = (j->y)*STEP_SIZE;
			rcMonster.y = (m->y)*STEP_SIZE;
			sprintf(buffer2, "Points of attack: %d Points of defense: %d", j->attaque, j->defense);
			defatt = TTF_RenderText_Solid(font, buffer2, white);
		}
		if (keystate[SDLK_DOWN] && (gameover != 2) ) {
			deplacement(g,j,115);
			sprintf(buffer, "Remaining lives: %d", j->vie);
			text = TTF_RenderText_Solid(font, buffer, white);
			if (g->content[j->y][j->x] == 8)
            {
                sprintf(buffer, "You won! Press Q or ESC to quit");
                text = TTF_RenderText_Solid(font, buffer, white);
                gameover = 2;
            }
			if (m -> vie > 0)
                deplacement_monstre(g, j, m);
            if (j->vie <=0 )
            {
                sprintf(buffer, "You lost! Press Q or ESC to quit");
                text = TTF_RenderText_Solid(font, buffer, white);
                gameover = 2;
            }
			rcSprite.y = (j->y)*STEP_SIZE;
			rcMonster.y = (m->y)*STEP_SIZE;
			sprintf(buffer2, "Points of attack: %d Points of defense: %d", j->attaque, j->defense);
			defatt = TTF_RenderText_Solid(font, buffer2, white);
		}


		if ( rcSprite.x < 0 ) {
			rcSprite.x = 0;
		}
		else if ( rcSprite.x > SCREEN_WIDTH-SPRITE_SIZE ) {
			rcSprite.x = SCREEN_WIDTH-SPRITE_SIZE;
		}
		if ( rcSprite.y < 0 ) {
			rcSprite.y = 0;
		}
		else if ( rcSprite.y > SCREEN_HEIGHT-SPRITE_SIZE ) {
			rcSprite.y = SCREEN_HEIGHT-SPRITE_SIZE;
		}



		for (int i = 0; i < (g -> n); i++)
		{
            for (int j = 0; j < (g -> m); j++)
            {
				switch (g->content[i][j])
				{
                    case 0 :
                        rcGrass.x = j * SPRITE_SIZE;
                        rcGrass.y = i * SPRITE_SIZE;
                        SDL_BlitSurface(backbg, NULL, screen, &rcGrass);
                    break;
                    case 1 :
                        rcWall.x = j * SPRITE_SIZE;
                        rcWall.y = i * SPRITE_SIZE;
                        SDL_BlitSurface(wall, NULL, screen, &rcWall);
                    break;
                    case 2 :
                        rcTrap.x = j * SPRITE_SIZE;
                        rcTrap.y = i * SPRITE_SIZE;
                        SDL_BlitSurface(trap, NULL, screen, &rcTrap);
                    break;
                    case 3 :
                        rcLife.x = j * SPRITE_SIZE;
                        rcLife.y = i * SPRITE_SIZE;
                        SDL_BlitSurface(life, NULL, screen, &rcLife);
                    break;
                    case 6 :
                        rcArmor.x = j * SPRITE_SIZE;
                        rcArmor.y = i * SPRITE_SIZE;
                        SDL_BlitSurface(armor, NULL, screen, &rcArmor);
                    break;
                    case 7 :
                        rcSword.x = j * SPRITE_SIZE;
                        rcSword.y = i * SPRITE_SIZE;
                        SDL_BlitSurface(sword, NULL, screen, &rcSword);
                    break;
                    case 8 :
                        rcDoor.x = j * SPRITE_SIZE;
                        rcDoor.y = i * SPRITE_SIZE;
                        SDL_BlitSurface(door, NULL, screen, &rcDoor);
                    break;
                    default :
                        rcGrass.x = j * SPRITE_SIZE;
                        rcGrass.y = i * SPRITE_SIZE;
                        SDL_BlitSurface(backbg, NULL, screen, &rcGrass);
                    break;
                }

			}
		}

        drawRectCairo(screen);

		SDL_BlitSurface(sprite, NULL, screen, &rcSprite);

		SDL_BlitSurface(monster, NULL, screen, &rcMonster);

		SDL_BlitSurface(text, NULL, screen, &rcText);

		SDL_BlitSurface(defatt, NULL, screen, &rcDefatt);

		SDL_UpdateRect(screen,0,0,0,0);
		}
    }

    TTF_CloseFont(font);
	TTF_Quit();

    SDL_FreeSurface(sprite);
    SDL_FreeSurface(backbg);
    SDL_FreeSurface(monster);
    SDL_FreeSurface(wall);
    SDL_FreeSurface(trap);
    SDL_FreeSurface(life);
    SDL_FreeSurface(sword);
    SDL_FreeSurface(armor);
    SDL_FreeSurface(door);
	SDL_FreeSurface(text);
	SDL_FreeSurface(defatt);
	SDL_FreeSurface(temp);
	SDL_FreeSurface(screen);

    suppr_grille(g);
    suppr_joueur(j);
    suppr_monstre(m);

    SDL_Quit();



    return 0;
}
