#include <string.h>
#include "Arbre.h"


ABS creerABSVide()
{
    ABS absVide;
    absVide.type = VIDE;

    return absVide;
} 

Arbre * creerArbre(int racine, ABS fg, ABS fd)
{
    Arbre * arbre = (Arbre *) malloc(sizeof(Arbre));
    arbre->racine = racine;
    arbre->fg = fg;
    arbre->fd = fd;

    return arbre;
}

Feuille * creerFeuille(int valeur, Noeud * liste)
{
    Feuille * feuille = (Feuille *) malloc(sizeof(Feuille));
    feuille->valeur = valeur;
    feuille->liste = liste;

    return feuille;
}




void afficherABS(ABS abs, char * tabulations)
{
    switch (abs.type)
    {
    case ARBRE:
        afficherArbre(abs.valeur.arbre, tabulations);
        break;
    case FEUILLE:
        afficherFeuille(abs.valeur.feuille, tabulations);
        break;
    default:
        break;
    }
}
void afficherArbre(Arbre * arbre, char * tabulations)
{
    if (arbre != NULL)
    {
        afficherABS(arbre->fg, strcat(tabulations, "\t"));
        printf("%s%d\n\n", tabulations, arbre->racine);
        afficherABS(arbre->fd, strcat(tabulations, "\t"));
    }
}
void afficherFeuille(Feuille * feuille, char * tabulations)
{
    if (feuille != NULL)
    {
        printf("%s%d - ", tabulations, feuille->valeur);
        afficherListe(feuille->liste);
    }
}

void libererABS(ABS abs)
{
    switch (abs.type)
    {
    case ARBRE:
        libererArbre(&abs.valeur.arbre);
        break;

    case FEUILLE:
        libererFeuille(&abs.valeur.feuille);
        break;

    default:
        break;
    }
}
void libererArbre(Arbre ** arbre)
{
    if (arbre != NULL && *arbre != NULL)
    {
        libererABS((*arbre)->fg);
        libererABS((*arbre)->fd);
        free(*arbre);
        *arbre = NULL;
    }
}
void libererFeuille(Feuille ** feuille)
{
    if (feuille != NULL && *feuille != NULL)
    {
        libererListe((*feuille)->liste);
        free(*feuille);
        *feuille = NULL;
    }
}


void test_ABS()
{
    test_Feuille();
    test_Arbre();

    const ABS ABS_VIDE = creerABSVide();

    /**
     * \brief Test la structure ABS
     */
    Feuille * feuille = creerFeuille(5, NULL);

    Arbre * arbre = creerArbre(10, ABS_VIDE, ABS_VIDE);
}
void test_Arbre()
{

}
void test_Feuille()
{
    
}
