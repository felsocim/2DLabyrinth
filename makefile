CC = gcc
LDFLAGS = `pkg-config --cflags --libs sdl --libs cairo --libs SDL_image --libs SDL_ttf`
STD = -std=c99
CFLAGS = -Wall -g -no-pie

all : 2DLabCLI 2DLabGUI

2DLabCLI : cli
	$(CC) $(CFLAGS) obj/2DLabCLI.o obj/grille.o obj/joueur.o -o 2DLabCLI -lncurses $(STD)

2DLabGUI : gui
	$(CC) $(CFLAGS) obj/2DLabGUI.o obj/grille.o obj/joueur.o -o 2DLabGUI -lncurses $(LDFLAGS)

grille : obj src/grille.c include/grille.h
	$(CC) $(CFLAGS) -c src/grille.c $(STD) -o obj/grille.o

joueur : obj src/joueur.c include/joueur.h
	$(CC) $(CFLAGS) -c src/joueur.c $(STD) -o obj/joueur.o

cli : grille joueur src/main1.c
	$(CC) $(CFLAGS) -c src/main1.c $(STD) -o obj/2DLabCLI.o

gui : grille joueur src/main2.c
	$(CC) $(CFLAGS) -c src/main2.c $(STD) -o obj/2DLabGUI.o $(LDFLAGS)

obj :
	test -d obj || mkdir obj

clean :
	rm -rf obj 2DLabCLI 2DLabGUI
