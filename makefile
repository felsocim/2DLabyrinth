CC = gcc
LIBS = `pkg-config --cflags --libs sdl --libs cairo --libs SDL_image --libs SDL_ttf`
STD = -std=c99
CFLAGS = -Wall -g

all : bin/main1 bin/main2

bin/main1 : obj/main1.o obj/grille.o obj/joueur.o
	$(CC) $(CFLAGS) -o main1 obj/main1.o obj/grille.o obj/joueur.o -lncurses $(STD)
	mv main1 bin/.

bin/main2 : obj/main2.o obj/grille.o obj/joueur.o
	$(CC) $(CFLAGS) obj/main2.o obj/grille.o obj/joueur.o -o main2 -lncurses $(LIBS)
	mv main2 bin/.

obj/grille.o : src/grille.c include/grille.h
	$(CC) $(CFLAGS) -c src/grille.c $(STD)
	mv grille.o obj/.

obj/joueur.o : src/joueur.c include/joueur.h
	$(CC) $(CFLAGS) -c src/joueur.c $(STD)
	mv joueur.o obj/.

obj/main1.o : src/main1.c include/grille.h include/joueur.h
	$(CC) $(CFLAGS) -c src/main1.c $(STD)
	mv main1.o obj/.

obj/main2.o : src/main2.c include/grille.h include/joueur.h
	$(CC) $(CFLAGS) -c src/main2.c $(STD) $(LIBS)
	mv main2.o obj/.

clean :
	rm obj/* bin/*
