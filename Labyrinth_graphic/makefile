bin/main : obj/main.o obj/grille.o obj/joueur.o
	gcc obj/main.o obj/grille.o obj/joueur.o -o main -lncurses `pkg-config --cflags --libs sdl --libs cairo --libs SDL_image --libs SDL_ttf`
	mv main bin/.

obj/grille.o : src/grille.c include/grille.h
	gcc -c src/grille.c -std=c99
	mv grille.o obj/.

obj/joueur.o : src/joueur.c include/joueur.h
	gcc -c src/joueur.c -std=c99
	mv joueur.o obj/.

obj/main.o : src/main.c include/grille.h include/joueur.h
	gcc `pkg-config --cflags --libs sdl --libs cairo --libs SDL_image --libs SDL_ttf` -c src/main.c -std=c99
	mv main.o obj/.
