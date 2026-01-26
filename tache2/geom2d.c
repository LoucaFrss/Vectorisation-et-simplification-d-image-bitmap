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