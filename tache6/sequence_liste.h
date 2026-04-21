#ifndef _SEQUENCE_LISTE_H_
#define _SEQUENCE_LISTE_H_

#include "geom2d.h"
#include "sequence_point.h"

/*---- le type cellule de liste de segment ----*/
typedef struct Cellule_Liste_Segment_
{
    Segment data;                        /* donnee de l'element de liste */
    struct Cellule_Liste_Segment_ *suiv; /* pointeur sur l'element suivant */
} Cellule_Liste_Segment;

/*---- le type liste de segment ----*/
typedef struct Liste_Segment_
{
    unsigned int taille;          /* nombre d'elements dans la liste */
    Cellule_Liste_Segment *first; /* pointeur sur le premier element */
    Cellule_Liste_Segment *last;  /* pointeur sur le dernier element */
} Liste_Segment;

typedef Liste_Segment;

/*---- le type tableau de segment ----*/
typedef struct Tableau_Segment_
{
    unsigned int taille; /* nombre d'elements dans le tableau */
    Segment *tab;        /* pointeur vers le tableau des elements */
} Tableau_Segment;

/*---- Prototypes des fonctions ----*/

/* Créer une cellule de liste avec l'élément v */
Cellule_Liste_Segment *creer_element_liste_Segment(Segment v);

/* Créer une liste de segments vide */
Liste_Segment creer_liste_Segment_vide();

/* Ajouter l'élément e en fin de la liste L */
Liste_Segment ajouter_element_liste_Segment(Liste_Segment L, Segment e);

/* Supprimer tous les éléments de la liste L */
Liste_Segment supprimer_liste_Segment(Liste_Segment L);

/* Concaténer L2 à la suite de L1 */
Liste_Segment concatener_liste_Segment(Liste_Segment L1, Liste_Segment L2);

/* Supprimer le premier élément de la liste L */
Liste_Segment supprimer_premier_element_liste_Segment(Liste_Segment L);

/* Convertir une liste de segments L en un tableau de segments */
Tableau_Segment sequence_segments_liste_vers_tableau(Liste_Segment L);

Liste_Segment simplification_douglas_peucker(Liste_Point CONT, int j1, int j2, float d);

#endif