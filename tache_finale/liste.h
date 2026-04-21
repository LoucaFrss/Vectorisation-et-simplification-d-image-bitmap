#ifndef _LISTE_H_
#define _LISTE_H_
#include <stdlib.h>
#include <stdio.h>
#define DECL_LISTE(t)                                                               \
    typedef struct Cellule_Liste_##t##_                                             \
    {                                                                               \
        t data; /* donnee de l'element de liste */                                  \
        struct Cellule_Liste_##t##_ *suiv;                                          \
    } Cellule_Liste_##t;                                                            \
                                                                                    \
    /*---- le type liste de point ----*/                                            \
    typedef struct Liste_##t##_                                                     \
    {                                                                               \
        unsigned int taille;      /* nombre d'elements dans la liste */             \
        Cellule_Liste_##t *first; /* pointeur sur le premier element de la liste */ \
        Cellule_Liste_##t *last;  /* pointeur sur le dernier element de la liste */ \
    } Liste_##t;                                                                    \
                                                                                    \
    /*---- le type tableau de point ----*/                                          \
    typedef struct Tableau_##t##_                                                   \
    {                                                                               \
        unsigned int taille; /* nombre d'elements dans le tableau */                \
        t *tab;              /* pointeur vers le tableau des elements */            \
    } Tableau_##t;                                                                  \
                                                                                    \
    /*---- Prototypes des fonctions ----*/                                          \
                                                                                    \
    /* Créer une cellule de liste avec l'élément v */                               \
    Cellule_Liste_##t *creer_element_liste_##t(t v);                                \
                                                                                    \
    /* Créer une liste de points vide */                                            \
    Liste_##t creer_liste_##t##_vide();                                             \
                                                                                    \
    /* Ajouter l'élément e en fin de la liste L */                                  \
    Liste_##t ajouter_element_liste_##t(Liste_##t L, t e);                          \
                                                                                    \
    /* Supprimer tous les éléments de la liste L */                                 \
    Liste_##t supprimer_liste_##t(Liste_##t L);                                     \
                                                                                    \
    /* Concaténer L2 à la suite de L1 */                                            \
    Liste_##t concatener_liste_##t(Liste_##t L1, Liste_##t L2);                     \
                                                                                    \
    /* Supprimer le premier élément de la liste L */                                \
    Liste_##t supprimer_premier_element_liste_##t(Liste_##t L);                     \
                                                                                    \
    /* Convertir une liste de points L en un tableau de points */                   \
    Tableau_##t sequence_##t##_liste_vers_tableau(Liste_##t L);

#define IMPL_LISTE(t)                                                             \
    Cellule_Liste_##t *creer_element_liste_##t(t v)                               \
    {                                                                             \
        Cellule_Liste_##t *el;                                                    \
        el = (Cellule_Liste_##t *)malloc(sizeof(Cellule_Liste_##t));              \
        if (el == NULL)                                                           \
        {                                                                         \
            fprintf(stderr, "creer_element_liste_##t : allocation impossible\n"); \
            exit(-1);                                                             \
        }                                                                         \
        el->data = v;                                                             \
        el->suiv = NULL;                                                          \
        return el;                                                                \
    }                                                                             \
    /* creer une liste vide */                                                    \
    Liste_##t creer_liste_##t##_vide()                                            \
    {                                                                             \
        Liste_##t L = {0, NULL, NULL};                                            \
        return L;                                                                 \
    }                                                                             \
                                                                                  \
    /* ajouter l'element e en fin de la liste L, renvoie la liste L modifiee */   \
    Liste_##t ajouter_element_liste_##t(Liste_##t L, t e)                         \
    {                                                                             \
        Cellule_Liste_##t *el;                                                    \
                                                                                  \
        el = creer_element_liste_##t(e);                                          \
        if (L.taille == 0)                                                        \
        {                                                                         \
            /* premier element de la liste */                                     \
            L.first = L.last = el;                                                \
        }                                                                         \
        else                                                                      \
        {                                                                         \
            L.last->suiv = el;                                                    \
            L.last = el;                                                          \
        }                                                                         \
        L.taille++;                                                               \
        return L;                                                                 \
    }                                                                             \
                                                                                  \
    /* supprimer tous les elements de la liste, renvoie la liste L vide */        \
    Liste_##t supprimer_liste_##t(Liste_##t L)                                    \
    {                                                                             \
        Cellule_Liste_##t *el = L.first;                                          \
                                                                                  \
        while (el)                                                                \
        {                                                                         \
            Cellule_Liste_##t *suiv = el->suiv;                                   \
            free(el);                                                             \
            el = suiv;                                                            \
        }                                                                         \
        L.first = L.last = NULL;                                                  \
        L.taille = 0;                                                             \
        return L;                                                                 \
    }                                                                             \
                                                                                  \
    /* concatener L2 a la suite de L1, renvoie la liste L1 modifiee */            \
    Liste_##t concatener_liste_##t(Liste_##t L1, Liste_##t L2)                    \
    {                                                                             \
        /* cas o� l'une des deux listes est vide */                               \
        if (L1.taille == 0)                                                       \
            return L2;                                                            \
        if (L2.taille == 0)                                                       \
            return L1;                                                            \
                                                                                  \
        /* les deux listes sont non vides */                                      \
        L1.last->suiv = L2.first; /* lien entre L1.last et L2.first */            \
        L1.last = L2.last;        /* le dernier element de L1 est celui de L2 */  \
        L1.taille += L2.taille;   /* nouvelle taille pour L1 */                   \
        return L1;                                                                \
    }                                                                             \
                                                                                  \
    /* si la liste est non vide, la fonction supprime le premier element de L     \
       si la liste est vide, la fonction ne fait rien                             \
       la fonction renvoie la liste (eventuellement) modifiee */                  \
    Liste_##t supprimer_premier_element_liste_##t(Liste_##t L)                    \
    {                                                                             \
        /* cas d'une liste L vide : ne rien faire */                              \
        if (L.taille == 0)                                                        \
            return L;                                                             \
                                                                                  \
        Cellule_Liste_##t *e1 = L.first;  /* pointeur vers le premier element  */ \
        Cellule_Liste_##t *e2 = e1->suiv; /* pointeur vers le deuxieme element */ \
                                                                                  \
        /* supprimer l'element pointe par e1 */                                   \
        free(e1);                                                                 \
                                                                                  \
        /* mettre a jour la structure L */                                        \
        L.first = e2;                                                             \
        if (e2 == NULL)    /* cas d'une liste L avec un seul element */           \
            L.last = NULL; /* --> la liste L devient une liste vide  */           \
        L.taille--;                                                               \
        return L;                                                                 \
    }                                                                             \
                                                                                  \
    /* creer une sequence de points sous forme d'un tableau de points             \
       a partir de la liste de points L */                                        \
    Tableau_##t sequence_##t##_liste_vers_tableau(Liste_##t L)                    \
    {                                                                             \
        Tableau_##t T;                                                            \
                                                                                  \
        /* taille de T = taille de L */                                           \
        T.taille = L.taille;                                                      \
                                                                                  \
        /* allocation dynamique du tableau de ##t */                              \
        T.tab = malloc(sizeof(t) * T.taille);                                     \
        if (T.tab == NULL)                                                        \
        {                                                                         \
            /* allocation impossible : arret du programme avec un message */      \
            fprintf(stderr, "sequence_points_liste_vers_tableau : ");             \
            fprintf(stderr, " allocation impossible\n");                          \
            exit(-1);                                                             \
        }                                                                         \
                                                                                  \
        /* remplir le tableau de points T en parcourant la liste L */             \
        int k = 0;                       /* indice de l'element dans T.tab */     \
        Cellule_Liste_##t *el = L.first; /* pointeur sur l'element dans L */      \
        while (el)                                                                \
        {                                                                         \
            T.tab[k] = el->data;                                                  \
            k++;           /* incrementer k */                                    \
            el = el->suiv; /* passer a l'element suivant dans la liste chainee */ \
        }                                                                         \
                                                                                  \
        return T;                                                                 \
    }

DECL_LISTE(int);

#endif