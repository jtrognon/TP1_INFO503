#ifndef ARBRE_H
#define ARBRE_H

#include <stdlib.h>
#include "ListeElements.h"


typedef struct _Feuille
{   
    int valeur;
    Noeud * liste;
} Feuille;


typedef struct _Arbre Arbre;

typedef enum _TypeABS {VIDE, FEUILLE, ARBRE} TypeABS;

typedef union _UnionABS {
    Feuille * feuille;
    Arbre * arbre;
} UnionABS;

typedef struct ABS {
    TypeABS type;
    UnionABS valeur;
} ABS;


typedef struct _Arbre
{   
    int racine;
    ABS fg;
    ABS fd;
} Arbre;


ABS creerABSVide();

Arbre * creerArbre(int racine, ABS fg, ABS fd);

Feuille * creerFeuille(int valeur, Noeud * liste);

void afficherABS(ABS abs, char * tabulations);
void afficherArbre(Arbre * arbre, char * tabulations);
void afficherFeuille(Feuille * feuille, char * tabulations);

void libererABS(ABS abs);
void libererArbre(Arbre ** arbre);
void libererFeuille(Feuille ** feuille);

void estArbre(ABS abs);
void estFeuille(ABS abs);

void test_ABS();
void test_Arbre();
void test_Feuille();


#endif