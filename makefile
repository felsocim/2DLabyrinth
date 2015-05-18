all : bin/main1 bin/main2

bin/main1 : obj/main1.o obj/grille.o obj/joueur.o
	gcc -o main1 obj/main1.o obj/grille.o obj/joueur.o -lncurses -std=c99
	mv main1 bin/.

bin/main2 : obj/main2.o obj/grille.o obj/joueur.o
	gcc obj/main2.o obj/grille.o obj/joueur.o -o main2 -lncurses `pkg-config --cflags --libs sdl --libs cairo --libs SDL_image --libs SDL_ttf`
	mv main2 bin/.

obj/grille.o : src/grille.c include/grille.h
	gcc -c src/grille.c -std=c99
	mv grille.o obj/.

obj/joueur.o : src/joueur.c include/joueur.h
	gcc -c src/joueur.c -std=c99
	mv joueur.o obj/.

obj/main1.o : src/main1.c include/grille.h include/joueur.h
	gcc -c src/main1.c -std=c99
	mv main1.o obj/.

obj/main2.o : src/main2.c include/grille.h include/joueur.h
	gcc `pkg-config --cflags --libs sdl --libs cairo --libs SDL_image --libs SDL_ttf` -c src/main2.c -std=c99
	mv main2.o obj/.

clean :
	rm obj/* bin/*
