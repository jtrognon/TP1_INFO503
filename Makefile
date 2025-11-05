.PHONY: all clean # .PHONY -> précise que certaines cibles ne correspondent pas à des fichiers (cible mais pas fichier)

# Cible principale
all: bin/city-manager bin/city-manager_gui

# Règle pour construire l'exécutable
bin/TP1_INFO503_JULIEN-DODSWORTH_TROGNON: main.o libListeElements.a libArbre.a
	gcc $< -Wall -Wextra -I./include -L./lib -lListeElements -lArbre -o $@ 
# -I pour le chemin des '#include'

# Ecrit ici car pas de .h donc marche par avec regle generique 
main.o: src/main.c libListeElements.a libArbre.a
	gcc -c $< -Wall -Wextra -I./include -L./lib -lListeElements -lArbre -o $@

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