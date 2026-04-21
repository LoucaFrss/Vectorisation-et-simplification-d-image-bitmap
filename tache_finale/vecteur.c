#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "vecteur.h"
typedef struct
{
    int taille_element;
    int taille;
    int capacite;
    void *tab;
} vector;

vector creer_vector(int n)
{
    vector v;
    v.taille = 0;
    v.taille_element = n;
    v.capacite = 0;
    v.tab = NULL;
    return v;
}
void redimensionner(vector *v, int n)

{
    if (v->taille > n)
    {
        printf("ERREUR: redimensionnement inferieur a la taille");
        return;
    }
    if (v->capacite > n)
    {
        return;
    }
    realloc(v->tab, n * v->taille_element);
    v->capacite = n;
}
void ajouter_fin(vector *v, void *element)
{
    if (v->taille == v->capacite)
    {
        redimensionner(v, v->taille + 1);
    }
    memcpy(&v->tab[v->taille++], element, v->taille_element);
}

void concatenation(vector *v1, vector *v2)
{
    if (v1->taille_element != v2->taille_element)
    {
        printf("LES TYPES DES VECTEURS A CONCATENER NE SONT PAS LES MEME ERREUR\n");
        return;
    }
    int taille_element = v1->taille_element;
    int tmin = v1->taille + v2->taille;
    if (v1->capacite >= tmin)
    {

        memmove(v1->tab + v1->taille * taille_element, v2->tab, v2->taille * taille_element);
        v1->taille += v2->taille;
        return;
    }
    redimensionner(v1, v1->taille + v2->taille);
    memmove(&v1->tab[v1->taille], v2->tab, v2->taille * taille_element);
    free(v1->tab);
    return;
}
void supprimer_premier_element(vector *v)
{
    memcpy(&v->tab[0], &v->tab[1], (v->taille--) * v->taille_element);
}
