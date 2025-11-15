#ifndef ARBRE_H
#define ARBRE_H

#include <stdlib.h>
#include "ListeElements.h"


typedef struct _Feuille
{   
    int valeur;
    Noeud liste;
} Feuille;


typedef struct _Arbre Arbre;

typedef enum _TypeABS {FEUILLE, ARBRE} TypeABS;

typedef union _UnionABS {
    Feuille * feuille;
    Arbre * arbre;
} UnionABS;

typedef struct _ABS {
    TypeABS type;
    UnionABS valeur;
    struct _ABS * pere;
} ABS;


typedef struct _Arbre
{   
    int racine;
    ABS * fg;
    ABS * fd;
} Arbre;


// Creation
ABS * creerABSArbre(int racine, ABS * fg, ABS * fd, ABS * pere);
ABS * creerABSFeuille(int valeur, Noeud liste, ABS * pere);
Arbre * creerArbre(int racine, ABS * fg, ABS * fd);
Feuille * creerFeuille(int valeur, Noeud liste);

// Modification
void arbreVersFeuille(ABS ** abs);
void changementValeurFeuille(ABS * abs);

// Affichage
void afficherABS(ABS * abs, char * tabulations);
void afficherArbre(Arbre * arbre, char * tabulations);
void afficherFeuille(Feuille * feuille, char * tabulations);

// Liberation
void libererABS(ABS ** abs);
void libererArbre(Arbre ** arbre);
void libererFeuille(Feuille ** feuille);

// Tests
void test_ABS();
void test_Arbre();
void test_Feuille();


#endif