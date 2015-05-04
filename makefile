bin/main : obj/main.o obj/grille.o obj/joueur.o
	gcc -o main obj/main.o obj/grille.o obj/joueur.o -lncurses
	mv main bin/.

obj/grille.o : src/grille.c include/grille.h
	gcc -c src/grille.c
	mv grille.o obj/.

obj/joueur.o : src/joueur.c include/joueur.h
	gcc -c src/joueur.c
	mv joueur.o obj/.

obj/main.o : src/main.c include/grille.h include/joueur.h
	gcc -c src/main.c
	mv main.o obj/.
