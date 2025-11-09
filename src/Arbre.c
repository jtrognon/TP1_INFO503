#include <string.h>
#include "Arbre.h"


ABS * creerABSArbre(int racine, ABS * fg, ABS * fd)
{
    /**
     * \brief Creation d'un ABS contenant un arbre.
     * \param racine Valeur de la racine.
     * \param fg Fils gauche de l'arbre.
     * \param fd Fils droit de l'arbre.
     * \return Renvoie un pointeur vers l'ABS créé ou NULL si celui-ci n'as pas de fils.
     */
    ABS * abs;
    
    if (fg != NULL || fg != NULL)
    {
        abs = (ABS *) malloc(sizeof(ABS));
        abs->type = ARBRE;
        abs->valeur.arbre = creerArbre(racine, fg, fd);
    }
    else
    {
        abs = NULL;
    }
        
    return abs;
}
ABS * creerABSFeuille(int valeur, Noeud liste)
{
    /**
     * \brief Creation d'un ABS contenant une feuille.
     * \param valeur Valeur de la feuille.
     * \param liste Liste associée à la feuille.
     * \return Renvoie le pointeur vers l'ABS créé.
     */
    ABS * abs = (ABS *) malloc(sizeof(ABS));
    abs->type = FEUILLE;
    abs->valeur.feuille = creerFeuille(valeur, liste);
    
    return abs;
}


Arbre * creerArbre(int racine, ABS * fg, ABS * fd)
{
    /**
     * \brief Creation d'un arbre.
     * \param racine Valeur de la racine.
     * \param fg Fils gauche de l'arbre.
     * \param fd Fils droit de l'arbre.
     * \return Renvoie un pointeur vers l'arbre créé ou NULL si celui-ci n'as pas de fils.
     */
    Arbre * arbre;
    if (fg != NULL || fd != NULL)
    {
        arbre = (Arbre *) malloc(sizeof(Arbre));
        arbre->racine = racine;
        arbre->fg = fg;
        arbre->fd = fd;
    }
    else
    {
        arbre = NULL;
    }

    return arbre;
}

Feuille * creerFeuille(int valeur, Noeud liste)
{
    /**
     * \brief Creation d'une feuille.
     * \param valeur Valeur de la feuille.
     * \param liste Liste associée à la feuille.
     * \return Renvoie le pointeur vers la feuille crée.
     */
    Feuille * feuille = (Feuille *) malloc(sizeof(Feuille));
    feuille->valeur = valeur;
    feuille->liste = liste;

    return feuille;
}




void afficherABS(ABS * abs, char * tabulations)
{
    /**
     * \brief Affiche l'ABS donné avec la chaine tabulation à gauche.
     * \param abs L'abs à afficher.
     * \param tabulations Tabulations à afficher à gauche de l'arbre.
     */
    if (abs != NULL)
    {
        switch (abs->type)
        {
            case ARBRE:
                afficherArbre(abs->valeur.arbre, tabulations);
                break; 
            case FEUILLE:
                afficherFeuille(abs->valeur.feuille, tabulations);
                break;
        }
    }
}
void afficherArbre(Arbre * arbre, char * tabulations)
{
    /**
     * \brief Affiche l'arbre donné avec la chaine tabulation à gauche.
     * \param arbre L'arbre à afficher.
     * \param tabulations Tabulations à afficher à gauche de l'arbre.
     */
    if (arbre != NULL)
    {
        // tab pour les fils
        char nextTab[strlen(tabulations) + sizeof("\t")];
        strcpy(nextTab, tabulations);
        strcat(nextTab, "\t");

        afficherABS(arbre->fg, nextTab);
        printf("%s%d\n\n", tabulations, arbre->racine);
        afficherABS(arbre->fd, nextTab);
    }
}
void afficherFeuille(Feuille * feuille, char * tabulations)
{
    /**
     * \brief Affiche la feuille donnée avec la chaine tabulation à gauche.
     * \param feuille La feuille à afficher.
     * \param tabulations Tabulations à afficher à gauche de l'arbre.
     */
    if (feuille != NULL)
    {
        printf("%s%d - ", tabulations, feuille->valeur);
        afficherListe(feuille->liste);
    }
}

void libererABS(ABS ** abs)
{
    /**
     * \brief Libère la mémoire de l'ABS.
     * \param abs L'ABS à libérer.  
     */
    if (abs != NULL && (*abs) != NULL)
    {
        switch ((*abs)->type)
        {
            case ARBRE:
                if ((*abs)->valeur.arbre != NULL)
                {
                    libererArbre(&(*abs)->valeur.arbre);
                }
                break;
            case FEUILLE:
                if ((*abs)->valeur.feuille != NULL)
                {
                    libererFeuille(&(*abs)->valeur.feuille);
                }
                break;
        }

        free(*abs);
        *abs = NULL;
    }
}
void libererArbre(Arbre ** arbre)
{
    /**
     * \brief Libère la mémoire de l'arbre.
     * \param arbre L'arbre à libérer.  
     */
    if (arbre != NULL && *arbre != NULL)
    {
        libererABS(&(*arbre)->fg);
        libererABS(&(*arbre)->fd);
        free(*arbre);
        *arbre = NULL;
    }
}
void libererFeuille(Feuille ** feuille)
{
    /**
     * \brief Libère la mémoire de la feuille.
     * \param feuille La feuille à libérer.  
     */
    if (feuille != NULL && *feuille != NULL)
    {
        libererListe(&(*feuille)->liste);
        free(*feuille);
        *feuille = NULL;
    }
}


void test_ABS()
{
    /**
     * \brief Teste les fonctions associées à ABS.
     */
    // Liste testee dans le fichier ListeElements.c
    test_Feuille();
    test_Arbre();

    printf("--------- TESTS ABS ---------\n");

    // --------- Creation d'arbres ---------
    // Feuille
    ABS * abs1 = creerABSFeuille(10, NULL);
    Test(
        abs1 != NULL &&
        abs1->type == FEUILLE && 
        abs1->valeur.feuille != NULL &&
        abs1->valeur.feuille->valeur == 10 && 
        abs1->valeur.feuille->liste == NULL, 
        "[ABS 1] Creation d'un ABS feuille.");

    // Arbre sans fils
    ABS * abs2 = creerABSArbre(20, NULL, NULL);
    Test(
        abs2 == NULL, 
        "[ABS 2] Creation d'un ABS arbre sans fils.");

    // Arbre avec 1 fils
    ABS * abs3 = creerABSArbre(30, abs1, NULL);
    Test(
        abs3 !=  NULL &&
        abs3->type == ARBRE && 
        abs3->valeur.arbre != NULL && 
        abs3->valeur.arbre->racine == 30 && 
        abs3->valeur.arbre->fg != NULL &&
        abs3->valeur.arbre->fg->type == FEUILLE && 
        abs3->valeur.arbre->fg->valeur.feuille == abs1->valeur.feuille, 
        "[ABS 3] Creation d'un ABS arbre avec 1 fils.");

    // Arbre avec 2 fils
    ABS * abs4_1 = creerABSFeuille(45, NULL);
    ABS * abs4 = creerABSArbre(40, abs3, abs4_1);
    Test(
        abs4 !=  NULL &&
        abs4->type == ARBRE && 
        abs4->valeur.arbre != NULL &&
        abs4->valeur.arbre->racine == 40 && 
        abs4->valeur.arbre->fg != NULL && 
        abs4->valeur.arbre->fg->type == ARBRE && 
        abs4->valeur.arbre->fg->valeur.arbre == abs3->valeur.arbre && 
        abs4->valeur.arbre->fd != NULL && 
        abs4->valeur.arbre->fd->type == FEUILLE && 
        abs4->valeur.arbre->fd->valeur.feuille == abs4_1->valeur.feuille, 
        "[ABS 3] Creation d'un ABS arbre avec 2 fils.");


    // --------- Affichage d'ABS ---------
    // ABS vide
    afficherABS(NULL, "");

    // Sans fils donc NULL
    printf("ABS Feuille.\n");
    afficherABS(abs1, "");
    
    // Sans fils - donc vide
    printf("ABS Arbre sans fils.\n");
    afficherABS(abs2, "");

    // Avec un fils
    printf("ABS Arbre avec un fils.\n");
    afficherABS(abs3, "");

    // Avec deux fils
    printf("ABS Arbre avec deux fils.\n");
    afficherABS(abs4, "");

    // --------- Libération d'arbres ---------
    libererABS(NULL);
    libererABS(&abs2);
    libererABS(&abs4); // abs 1 et 3 liberée dans

    Test(abs2 == NULL && abs4 == NULL, "[ABS 5] Test Libération ABS (vérifier avec valgrind).");
}
void test_Arbre()
{
    /**
     * \brief Teste les fonctions associées à Arbre.
    */

    printf("--------- TESTS ARBRE ---------\n");

    // --------- Creation d'arbres ---------
    // Sans fils
    Arbre * a1 = creerArbre(10, NULL, NULL);
    Test(a1 == NULL, "[Arbre 1] - Test de creation d'un arbre sans fils (renvoie NULL).");

    // Avec un fils
    ABS * abs2 = creerABSFeuille(25, NULL); 
    Arbre * a2 = creerArbre(20, abs2, NULL);
    Test(a2 != NULL && a2->racine == 20 && a2->fg == abs2 && a2->fd == NULL, "[Arbre 2] - Test de creation d'un arbre avec 1 fils.");

    // Avec deux fils
    ABS * abs3_1 = creerABSFeuille(35, NULL); 
    ABS * abs3_2 = creerABSFeuille(38, NULL); 
    Arbre * a3 = creerArbre(30, abs3_1, abs3_2);
    Test(a3 != NULL && a3->racine == 30 && a3->fg == abs3_1 && a3->fd == abs3_2, "[Arbre 3] - Test de creation d'un arbre avec 2 fils.");


    // --------- Affichage d'arbres ---------
    // Arbre inexistant
    afficherArbre(NULL, "");

    // Sans fils donc NULL
    afficherArbre(a1, "");
    
    // Avec un fils
    printf("Arbre avec un fils.\n");
    afficherArbre(a2, "");

    // Avec deux fils
    printf("Arbre avec deux fils.\n");
    afficherArbre(a3, "");

    // --------- Libération d'arbres ---------
    // Arbre inexistant
    libererArbre(NULL);

    // Sans fils - donc NULL
    libererArbre(&a1);

    // Avec un fils
    libererArbre(&a2);

    // Avec deux fils
    libererArbre(&a3);

    Test(a1 == NULL && a2 == NULL && a3 == NULL, "[Arbre 4] Libération des arbres (vérifier avec valgrind).");
}
void test_Feuille()
{
    /**
     * \brief Teste les fonctions associées à Feuille.
     */
    printf("--------- TESTS FEUILLE ---------\n");

    // --------- Creation de feuilles ---------
    // Avec liste vide
    Feuille * f1 = creerFeuille(10, NULL);
    Test(f1 != NULL && f1->valeur == 10 && f1->liste == NULL, "[Feuille - 1] Test de la création d'une feuille avec une liste vide.");

    // Avec liste non vide
    Noeud l2 = NULL;
    ajouterNoeudTail(&l2, 15);
    Feuille * f2 = creerFeuille(5, l2);
    Test(f2 != NULL && f2->valeur == 5 && f2->liste == l2, "[Feuille - 2] Test de la création d'une feuille avec une liste non vide.");


    // --------- Affichage de feuilles ---------
    // Feuille inexistante
    afficherFeuille(NULL, "");
    // Avec liste vide
    afficherFeuille(f1, "");
    // Avec liste non vide
    afficherFeuille(f2, "");


    // --------- Liberation de feuilles ---------
    libererFeuille(NULL);
    libererFeuille(&f1);
    libererFeuille(&f2);
    Test(f1 == NULL && f2 == NULL, "[Feuille - 3] Test de la libération des feuille (vérifier avec 'valgrind --leak-check=full ./bin/TP1_INFO503_JULIEN-DODSWORTH_TROGNON')");
}
