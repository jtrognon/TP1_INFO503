#ifndef ELEMENTS_H
#define ELEMENTS_H

#include <stdbool.h>

#define Test(cond, msg)\
    do{\
        if (cond) {\
            printf("[OK] %s\n", msg);\
        } else {\
            printf("[FAIL] %s (ligne %d de %s)\n", msg, __LINE__, __FILE_NAME__);\
        }\
    } while(0)

typedef struct _Noeud
{   
    int valeur;
    struct _Noeud * suivant;
} Noeud;

void ajouterNoeudTail(Noeud ** liste, int valeur);

void supprimerNoeud(Noeud **liste, int valeur);

void afficherListe(Noeud * liste);

void libererListe(Noeud ** liste);

int popPremNoeud(Noeud ** liste);

int tailleListe(const Noeud * liste);


void test_liste();

#endif