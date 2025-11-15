#include <string.h>
#include "Arbre.h"


ABS * creerABSArbre(int racine, ABS * fg, ABS * fd, ABS * pere)
{
    /**
     * \brief Creation d'un ABS contenant un arbre.
     * \param racine Valeur de la racine.
     * \param fg Fils gauche de l'arbre.
     * \param fd Fils droit de l'arbre.
     * \param pere Père de l'arbre.
     * \return Renvoie un pointeur vers l'ABS créé ou NULL si celui-ci n'as pas de fils ou si son pere est une feuille.
     */
    ABS * abs = NULL;
    
    if ((fg != NULL || fg != NULL) && (pere == NULL || pere->type == ARBRE))
    {
        abs = (ABS *) malloc(sizeof(ABS));
        abs->type = ARBRE;
        abs->valeur.arbre = creerArbre(racine, fg, fd);
        abs->pere = pere;
    }
    else
    {
        abs = NULL;
    }
        
    return abs;
}
ABS * creerABSFeuille(int valeur, Noeud liste, ABS * pere)
{
    /**
     * \brief Creation d'un ABS contenant une feuille.
     * \param valeur Valeur de la feuille.
     * \param liste Liste associée à la feuille.
     * \param pere Père de l'arbre.
     * \return Renvoie le pointeur vers l'ABS créé.
     */
    ABS * abs = NULL;
    if (pere == NULL || pere->type == ARBRE)
    {
        abs = (ABS *) malloc(sizeof(ABS));
        abs->type = FEUILLE;
        abs->valeur.feuille = creerFeuille(valeur, liste);
        abs->pere = pere;
    }
        
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


void arbreVersFeuille(ABS ** abs)
{
    /**
     * \brief Convertie un arbre sans fils en feuille avec une liste vide.
     * \param abs L'ABS à modifier.
     */
    if (abs != NULL && *abs != NULL && (*abs)->type == ARBRE && (*abs)->valeur.arbre != NULL && (*abs)->valeur.arbre->fg == NULL && (*abs)->valeur.arbre->fd == NULL)
    {
        int racine = (*abs)->valeur.arbre->racine;
        libererArbre(&(*abs)->valeur.arbre);
        (*abs)->type = FEUILLE;
        (*abs)->valeur.feuille = creerFeuille(racine, NULL);
    }
}

void changementValeurFeuille(ABS * abs)
{
    /**
     * \brief Change la valeur de la feuille avec la première valeur de la liste.
     * \param abs ABS de la feuille à modifier.
     */
    if (abs != NULL && abs->type == FEUILLE && abs->valeur.feuille != NULL && abs->valeur.feuille->liste != NULL)
    {
        int min = popPremNoeud(&abs->valeur.feuille->liste);
        abs->valeur.feuille->valeur = min;
    }
}


void afficherABS(ABS * abs, char * tabulations)
{
    /**
     * \brief Affiche l'ABS donné avec la chaine tabulation à gauche.// --------- ABS avec une feuille comme père ---------
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
    ABS * abs1 = creerABSFeuille(10, NULL, NULL);
    Test(
        abs1 != NULL &&
        abs1->type == FEUILLE && 
        abs1->valeur.feuille != NULL &&
        abs1->valeur.feuille->valeur == 10 && 
        abs1->valeur.feuille->liste == NULL, 
        "Creation d'un ABS feuille.");

    // Arbre sans fils
    ABS * abs2 = creerABSArbre(20, NULL, NULL, NULL);
    Test(
        abs2 == NULL, 
        "Creation d'un ABS arbre sans fils.");

    // Arbre avec 1 fils
    ABS * abs3 = creerABSArbre(30, abs1, NULL, NULL);
    abs1->pere = abs3;
    Test(
        abs3 !=  NULL &&
        abs3->type == ARBRE && 
        abs3->valeur.arbre != NULL && 
        abs3->valeur.arbre->racine == 30 && 
        abs3->valeur.arbre->fg != NULL &&
        abs3->valeur.arbre->fg->type == FEUILLE && 
        abs3->valeur.arbre->fg->valeur.feuille == abs1->valeur.feuille, 
        "Creation d'un ABS arbre avec 1 fils.");

    // Arbre avec 2 fils
    ABS * abs4_1 = creerABSFeuille(45, NULL, NULL);
    ABS * abs4 = creerABSArbre(40, abs3, abs4_1, NULL);
    abs4_1->pere = abs4;
    abs3->pere = abs4; 
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
        "Creation d'un ABS arbre avec 2 fils.");


    // --------- ABS avec une feuille comme père ---------

    ABS * abs7 = creerABSFeuille(70, NULL, abs1);
    Test(abs7 == NULL, "ABS avec une feuille comme père");

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

    // --------- Arbre -> Feuille ---------

    // NULL
    arbreVersFeuille(NULL);

    // Une variable a NULL
    arbreVersFeuille(&abs2);

    // Une feuille
    Feuille * feuille_abs1 = abs1->valeur.feuille;
    arbreVersFeuille(&abs1);
    Test(abs1 != NULL && abs1->type == FEUILLE && abs1->valeur.feuille == feuille_abs1, "Arbre -> Feuille avec une feuille");
    feuille_abs1 = NULL;

    // Un arbre qui vaut NULL
    ABS * abs5 = creerABSArbre(50, abs4, NULL, NULL);
    abs5->valeur.arbre->fg = NULL; // Pour ne pas liberer abs4
    libererArbre(&abs5->valeur.arbre);
    arbreVersFeuille(&abs5);

    // Un arbre avec un fils
    Arbre * arbre_abs3 = abs3->valeur.arbre; 
    arbreVersFeuille(&abs3);
    Test(abs3 != NULL && abs3->type == ARBRE && abs3->valeur.arbre == arbre_abs3, "Arbre -> Feuille avec un arbre contenant un fils");
    arbre_abs3 = NULL;

    // Un arbre sans fils
    ABS * abs6 = creerABSArbre(60, abs4, NULL, NULL);
    abs6->valeur.arbre->fg = NULL;
    arbreVersFeuille(&abs6);
    Test(abs6 != NULL && abs6->type == FEUILLE && abs6->valeur.feuille != NULL && abs6->valeur.feuille->valeur == 60 && abs6->valeur.feuille->liste == NULL , "Arbre -> Feuille avec un arbre sans fils");

    // --------- Changement de la valeur de la feuille ---------

    // ABS NULL
    changementValeurFeuille(NULL);

    // ABS arbre
    changementValeurFeuille(abs3);

    // ABS feuille avec feuille = NULL
    ABS * abs8 = creerABSFeuille(80, NULL, NULL);
    Feuille * abs8_feuille = abs8->valeur.feuille;
    abs8->valeur.feuille = NULL;
    changementValeurFeuille(abs8);

    // ABS feuille avec la liste de la feuille à NULL 
    abs8->valeur.feuille = abs8_feuille;
    changementValeurFeuille(abs8);

    // ABS feuille avec la liste de la feuille non NULL 
    Noeud l8 = NULL;
    ajouterNoeudTail(&l8, 85);
    ajouterNoeudTail(&l8, 88);
    abs8->valeur.feuille->liste = l8;
    changementValeurFeuille(abs8);
    Test(abs8->valeur.feuille->valeur == 85 && abs8->valeur.feuille->liste->valeur == 88 && abs8->valeur.feuille->liste->suivant == NULL, "Changement de valeur de la feuille avec la première valeur de la liste");
        
    // --------- Libération d'arbres ---------
    libererABS(NULL);
    libererABS(&abs2);
    libererABS(&abs4); // abs 1 et 3 liberée dans abs 4
    libererABS(&abs5);
    libererABS(&abs6);
    libererABS(&abs8);

    Test(abs2 == NULL && abs4 == NULL && abs5 == NULL && abs6 == NULL && abs8 == NULL, "Test Libération ABS (vérifier avec valgrind).");
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
    ABS * abs2 = creerABSFeuille(25, NULL, NULL); 
    Arbre * a2 = creerArbre(20, abs2, NULL);
    Test(a2 != NULL && a2->racine == 20 && a2->fg == abs2 && a2->fd == NULL, "[Arbre 2] - Test de creation d'un arbre avec 1 fils.");

    // Avec deux fils
    ABS * abs3_1 = creerABSFeuille(35, NULL, NULL); 
    ABS * abs3_2 = creerABSFeuille(38, NULL, NULL); 
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
