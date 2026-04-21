#include <stdio.h>  /* utilisation des entrees-sorties standard de C */
#include <stdlib.h> /* utilisation des fonctions malloc et free */
#include "geom2d.h"
#include "sequence_liste.h"
#include "sequence_point.h"

Cellule_Liste_Segment *creer_element_liste_Segment(Segment v)
{
    Cellule_Liste_Segment *el;
    el = (Cellule_Liste_Segment *)malloc(sizeof(Cellule_Liste_Segment));
    if (el == NULL)
    {
        fprintf(stderr, "creer_element_liste_Segment : allocation impossible\n");
        exit(-1);
    }
    el->data = v;
    el->suiv = NULL;
    return el;
}

Liste_Segment creer_liste_Segment_vide()
{
    Liste_Segment L = {0, NULL, NULL};
    return L;
}

Liste_Segment ajouter_element_liste_Segment(Liste_Segment L, Segment e)
{
    Cellule_Liste_Segment *el;

    el = creer_element_liste_Segment(e);

    if (L.taille == 0)
    {
        L.first = L.last = el;
    }
    else
    {
        L.last->suiv = el;
        L.last = el;
    }

    L.taille++;
    return L;
}

Liste_Segment supprimer_liste_Segment(Liste_Segment L)
{
    Cellule_Liste_Segment *el = L.first;

    while (el)
    {
        Cellule_Liste_Segment *suiv = el->suiv;
        free(el);
        el = suiv;
    }
    L.first = L.last = NULL;
    L.taille = 0;
    return L;
}

Liste_Segment concatener_liste_Segment(Liste_Segment L1, Liste_Segment L2)
{
    if (L1.taille == 0)
        return L2;

    if (L2.taille == 0)
        return L1;

    L1.last->suiv = L2.first;
    L1.last = L2.last;
    L1.taille += L2.taille;

    return L1;
}

Liste_Segment supprimer_premier_element_liste_Segment(Liste_Segment L)
{
    if (L.taille == 0)
        return L;

    Cellule_Liste_Segment *e1 = L.first;
    Cellule_Liste_Segment *e2 = e1->suiv;

    free(e1);

    L.first = e2;

    if (e2 == NULL)
        L.last = NULL;

    L.taille--;

    return L;
}

Tableau_Segment sequence_segments_liste_vers_tableau(Liste_Segment L)
{
    Tableau_Segment T;

    T.taille = L.taille;

    T.tab = malloc(sizeof(Segment) * T.taille);
    if (T.tab == NULL)
    {
        fprintf(stderr, "sequence_segments_liste_vers_tableau : ");
        fprintf(stderr, "allocation impossible\n");
        exit(-1);
    }

    int k = 0;
    Cellule_Liste_Segment *el = L.first;

    while (el)
    {
        T.tab[k] = el->data;
        k++;
        el = el->suiv;
    }

    return T;
}

Liste_Segment simplification_douglas_peucker(Liste_Point CONT, int j1, int j2, float d)
{
    Liste_Segment L = creer_liste_Segment_vide();
    Segment s;
    Tableau_Point T;

    T = sequence_points_liste_vers_tableau(CONT);

    s.a = T.tab[j1];
    s.b = T.tab[j2];

    float dmax = 0;
    int k = j1;

    for (int j = j1 + 1; j < j2; j++)
    {
        float dj = distance_point_segment(s, T.tab[j]);
        if (dmax < dj)
        {
            dmax = dj;
            k = j;
        }
    }

    if (dmax <= d)
    {
        L = ajouter_element_liste_Segment(L, s);
    }
    else
    {
        Liste_Segment L1 = simplification_douglas_peucker(CONT, j1, k, d);
        Liste_Segment L2 = simplification_douglas_peucker(CONT, k, j2, d);
        L = concatener_liste_Segment(L1, L2);
    }

    free(T.tab);

    return L;
}