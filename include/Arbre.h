#include "ListeElements.h"

typedef struct _Feuille
{   
    int valeur;
    struct _Feuille * suivant;
} Feuille;

// typedef struct Arbre;

typedef union _ABS
{
    Feuille feuille;
    Arbre arbre;
} ABS;

typedef struct _Arbre
{   
    int racine;
    ABS * fg;
    ABS * fd;
} Arbre;


Arbre ** creerArbre(int racine, ABS fg, ABS fd);

Feuille ** creerFeuille(int valeur, Noeud liste);


void ajouterFg(Arbre ** arbre, ABS fg);

void ajouterFd(Arbre ** arbre, ABS fg);

void afficherABS(ABS * abs);
void afficherArbre(Arbre * arbre);
void afficherFeuille(Feuille * feuille);

void libererABS(ABS ** abs);
void libererArbre(Arbre ** arbre);
void libererFeuille(Feuille ** feuille);

void test_ABS();
void test_Arbre();
void test_Feuille();
