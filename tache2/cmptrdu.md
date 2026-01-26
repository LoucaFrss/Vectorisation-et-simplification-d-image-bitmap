# MAP401 - Compte-rendu Tâche 2

***geom2d.h***
```c
#ifndef _GEOM2D_H_
#define _GEOM2D_H_

/**
 * Structure représentant un vecteur 2D
 * Contient les coordonnées x et y du vecteur
 */
typedef struct Vecteur_
{
    double x, y;
} Vecteur;

/**
 * Structure représentant un point 2D
 * Contient les coordonnées x et y du point
 */
typedef struct Point_
{
    double x, y;
} Point;

/**
 * Crée un point avec les coordonnées spécifiées
 * @param x : coordonnée x
 * @param y : coordonnée y
 * @return Point créé
 */
Point set_point(double x, double y);

/**
 * Additionne deux points (addition vectorielle)
 * @param P1 : premier point
 * @param P2 : deuxième point
 * @return Point résultant de P1 + P2
 */
Point add_point(Point P1, Point P2);

/**
 * Multiplie un point par un scalaire
 * @param P : point à multiplier
 * @param a : scalaire
 * @return Point résultant de P * a
 */
Point mul_point(Point P, double a);

/**
 * Calcule la distance euclidienne entre deux points
 * @param P1 : premier point
 * @param P2 : deuxième point
 * @return Distance entre P1 et P2
 */
float distance(Point P1, Point P2);

/**
 * Crée un vecteur à partir de deux points
 * Calcule le vecteur allant de A vers B
 * @param A : point de départ
 * @param B : point d'arrivée
 * @return Vecteur AB
 */
Vecteur vect_bipoint(Point A, Point B);

/**
 * Multiplie un vecteur par un scalaire
 * @param V : vecteur à multiplier
 * @param a : scalaire
 * @return Vecteur résultant de V * a
 */
Vecteur mul_vect(Vecteur V, double a);

/**
 * Calcule le produit scalaire de deux vecteurs
 * @param A : premier vecteur
 * @param B : deuxième vecteur
 * @return Produit scalaire A · B
 */
double produit_scalaire(Vecteur A, Vecteur B);

/**
 * Calcule la norme (longueur) d'un vecteur
 * @param V : vecteur
 * @return Norme du vecteur
 */
float norme(Vecteur V);

#endif
```

***geom2d.c***
```c
/**
 * @file geom2d.c
 * @brief Implémentation des fonctions géométriques 2D
 *
 * Ce fichier contient l'implémentation des opérations sur les points et vecteurs 2D,
 * incluant les opérations arithmétiques et les calculs de distance/norme.
 */

#include "geom2d.h"
#include <math.h>

/**
 * Crée un point avec les coordonnées spécifiées
 * @param x : coordonnée x du point
 * @param y : coordonnée y du point
 * @return Un nouveau point (x, y)
 */
Point set_point(double x, double y)
{
    Point P = {x, y};
    return P;
}

/**
 * Additionne deux points (addition vectorielle)
 * Résultat: (P1.x + P2.x, P1.y + P2.y)
 * @param P1 : premier point
 * @param P2 : deuxième point
 * @return Point résultant de l'addition P1 + P2
 */
Point add_point(Point P1, Point P2)
{
    return set_point(P1.x + P2.x, P1.y + P2.y);
}

/**
 * Multiplie un point par un scalaire (multiplication vectorielle)
 * Résultat: (P.x * a, P.y * a)
 * @param P : point à multiplier
 * @param a : scalaire multiplicateur
 * @return Point résultant de la multiplication P * a
 */
Point mul_point(Point P, double a)
{
    return set_point(P.x * a, P.y * a);
}

/**
 * Calcule la distance euclidienne entre deux points
 * Distance = ||AB|| où AB est le vecteur allant de P1 à P2
 * @param P1 : premier point
 * @param P2 : deuxième point
 * @return Distance euclidienne entre P1 et P2
 */
float distance(Point P1, Point P2)
{
    /* Calcule le vecteur allant de P1 vers P2 */
    Vecteur v = vect_bipoint(P1, P2);
    /* Retourne la norme de ce vecteur */
    return norme(v);
}

/**
 * Crée un vecteur à partir de deux points
 * Vecteur AB = (B.x - A.x, B.y - A.y)
 * @param A : point de départ
 * @param B : point d'arrivée
 * @return Vecteur AB pointant de A vers B
 */
Vecteur vect_bipoint(Point A, Point B)
{
    Vecteur V = {B.x - A.x,
                 B.y - A.y};
    return V;
}

/**
 * Multiplie un vecteur par un scalaire
 * Résultat: (V.x * a, V.y * a)
 * @param V : vecteur à multiplier
 * @param a : scalaire multiplicateur
 * @return Vecteur résultant de la multiplication V * a
 */
Vecteur mul_vect(Vecteur V, double a)
{
    Vecteur V2 = {V.x * a, V.y * a};
    return V2;
}

/**
 * Calcule le produit scalaire de deux vecteurs
 * Produit scalaire = A.x * B.x + A.y * B.y
 * @param A : premier vecteur
 * @param B : deuxième vecteur
 * @return Produit scalaire A · B (résultat réel)
 */
double produit_scalaire(Vecteur A, Vecteur B)
{
    return A.x * B.x + A.y * B.y;
}

/**
 * Calcule la norme (longueur) d'un vecteur
 * Norme = sqrt(V.x² + V.y²)
 * @param V : vecteur
 * @return Norme (longueur) du vecteur V
 */
float norme(Vecteur V)
{
    return sqrtf(V.x * V.x + V.y * V.y);
}
```


***test_geom2d***
```c
#include <stdio.h>;
#include <stdlib.h>
#include "geom2d.h";
int main(int argc, char *argv[])
{

    if (argc < 5)
    {
        printf("geom2d A.x A.y B.x B.y a\n");
        return 1;
    }

    Point A = set_point(atoi(argv[1]), atoi(argv[2]));
    Point B = set_point(atoi(argv[3]), atoi(argv[4]));
    double a = atoi(argv[5]);

    Point C = add_point(A, B);
    printf("A + B = (%f, %f)\n", C.x, C.y);

    Point D = mul_point(A, a);
    printf("A * a = (%f, %f)\n", D.x, D.y);

    Point E = mul_point(B, a);
    printf("B * a = (%f, %f)\n", E.x, E.y);

    Vecteur V1 = {A.x, A.y};
    Vecteur V2 = {B.x, B.y};
    printf("A . B = %f\n", produit_scalaire(V1, V2));

    Vecteur V3 = vect_bipoint(A, B);
    printf("Vecteur de A a B: (%f, %f)\n", V3.x, V3.y);

    printf("distance AB = ||V3|| = %f\n", distance(A, B));
}
```

### Execution du programme de test

```bash
$ ./test_geom2d 0 1 1 0 5
A + B = (1.000000, 1.000000)
A * a = (0.000000, 5.000000)
B * a = (5.000000, 0.000000)
A . B = 0.000000
Vecteur de A a B: (1.000000, -1.000000)
distance AB = ||V3|| = 1.414214
```