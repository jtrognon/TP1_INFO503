#include "ListeElements.h"

void ajouterNoeudTail(Noeud *liste, int valeur)
{
    if(*liste== NULL){
        *liste = malloc(sizeof(struct _Noeud));
        


        (*liste)->valeur = valeur;
        (*liste)->suivant = NULL;

    }
    else{
        Noeud pt = *liste;
        
        while(pt->suivant != NULL){
            pt = pt->suivant;
        }
        Noeud lst = malloc(sizeof(struct _Noeud));

        lst->valeur = valeur;
        




        lst->suivant = NULL;
        pt->suivant = lst;
        
        
    }
};

void supprimerNoeud(Noeud *liste, int valeur)
{
    Noeud pt = *liste;
    Noeud precedent = NULL;
    bool trouve = false;

    
    while(pt != NULL && !trouve){
        
        if(pt->valeur == valeur){
            trouve = true;
        }
        else{
            precedent = pt;
            pt = pt->suivant;
        }
        
    }

    if(trouve){
        //Cas d'un élément en début de liste
        if(precedent == NULL){
            *liste = pt->suivant;
        }

        else{

            precedent->suivant = pt->suivant;

        }
        free(pt);

    };
}

void afficherListe(Noeud liste)
{
    if(liste == NULL){
        printf("La liste est vide\n");
    }
    else{
        while(liste){
            printf(" %d |",liste->valeur);
            liste = liste->suivant;
        
        }
    }   
    printf("\n");
}

void libererListe(Noeud *liste)
{
    Noeud pt;
    
   
    while (*liste != NULL)
    {
        pt = *liste;
        *liste = pt->suivant;
        
        free(pt);
    }
    
    *liste = NULL;


}

int popPremNoeud(Noeud *liste)
{
    Noeud pt = *liste;
    int res = (*liste)->valeur;

    *liste = pt->suivant;
    
    free(pt);
    
    return res;

}

int tailleListe(Noeud *liste)
{
    Noeud pt = *liste;
    int compteur = 0;
    while(pt != NULL){
        compteur++;
        pt = pt->suivant;

    }

    return compteur;
}

void test_liste()
{
    Noeud test = NULL;

    ajouterNoeudTail(&test,1);
    ajouterNoeudTail(&test,2);
    ajouterNoeudTail(&test,3);
    ajouterNoeudTail(&test,4);


    afficherListe(test);

    printf("Taille de la liste : %d\n",tailleListe(&test));

    int res = popPremNoeud(&test);

    printf("Premier noeud : %d\n",res);

    afficherListe(test);

    supprimerNoeud(&test,3);

    afficherListe(test);


    libererListe(&test);




}
