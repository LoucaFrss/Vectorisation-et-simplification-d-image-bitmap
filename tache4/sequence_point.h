#ifndef _SEQUENCE_POINT_H_
#define _SEQUENCE_POINT_H_

#include "geom2d.h"

/*---- le type cellule de liste de point ----*/
typedef struct Cellule_Liste_Point_
{
    Point data;                        /* donnee de l'element de liste */
    struct Cellule_Liste_Point_ *suiv; /* pointeur sur l'element suivant */
} Cellule_Liste_Point;

/*---- le type liste de point ----*/
typedef struct Liste_Point_
{
    unsigned int taille;        /* nombre d'elements dans la liste */
    Cellule_Liste_Point *first; /* pointeur sur le premier element de la liste */
    Cellule_Liste_Point *last;  /* pointeur sur le dernier element de la liste */
} Liste_Point;

/* type Contour = type Liste_Point */
typedef Liste_Point Contour;

/*---- le type tableau de point ----*/
typedef struct Tableau_Point_
{
    unsigned int taille; /* nombre d'elements dans le tableau */
    Point *tab;          /* pointeur vers le tableau des elements */
} Tableau_Point;

/*---- Prototypes des fonctions ----*/

/* Créer une cellule de liste avec l'élément v */
Cellule_Liste_Point *creer_element_liste_Point(Point v);

/* Créer une liste de points vide */
Liste_Point creer_liste_Point_vide();

/* Ajouter l'élément e en fin de la liste L */
Liste_Point ajouter_element_liste_Point(Liste_Point L, Point e);

/* Supprimer tous les éléments de la liste L */
Liste_Point supprimer_liste_Point(Liste_Point L);

/* Concaténer L2 à la suite de L1 */
Liste_Point concatener_liste_Point(Liste_Point L1, Liste_Point L2);

/* Supprimer le premier élément de la liste L */
Liste_Point supprimer_premier_element_liste_Point(Liste_Point L);

/* Convertir une liste de points L en un tableau de points */
Tableau_Point sequence_points_liste_vers_tableau(Liste_Point L);

/* Afficher le contour à l'écran */
void ecrire_contour(Liste_Point L);

#endif