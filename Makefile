.PHONY: all clean # .PHONY -> précise que certaines cibles ne correspondent pas à des fichiers (cible mais pas fichier)

# Cible principale
all: bin/city-manager bin/city-manager_gui

# Règle pour construire l'exécutable
bin/city-manager: main.o jeu.o libElements.a libutils.a libVille.a
	gcc $< jeu.o -Wall -I./include -L./lib -lVille -lElements -lutils -lm -o $@ 
# -I pour le chemin des '#include'


bin/city-manager_gui: main_gui.o jeu.o libElements.a libutils.a libVille.a
	gcc $< jeu.o -Wall -I./include -L./lib -lVille -lElements -lutils -lm -o $@ `pkg-config --cflags --libs gtk+-3.0`


# Ecrit ici car pas de .h donc marche par avec regle generique 
main.o: src/main.c libElements.a libutils.a libVille.a
	gcc -c $< -Wall -I./include -L./lib -lVille -lElements -lutils -lm -o $@ #-lm : librairie math

main_gui.o: src/main_gui.c libElements.a libutils.a libVille.a
	gcc -c $< -Wall -I./include -L./lib -lVille -lElements -lutils -lm -o $@ `pkg-config --cflags --libs gtk+-3.0`


# creation de la lib math
lib%.a: %.o
	ar -crs lib/$@ $<

%.o: src/%.c include/%.h
	gcc -c $< -I./include -o $@

# Regle générique pour compiler les fichiers .c en fichiers .o (marche seulement pour les lib car elles seules possedes des .h)
# %.o: %.c include/%.h 	# définition d'un motif generique
# 	gcc -c src/$< -o $@

# Cible pour nettoyer les fichiers objets et l'exécutable
clean:
	rm -f *.o ./lib/* ./bin/*