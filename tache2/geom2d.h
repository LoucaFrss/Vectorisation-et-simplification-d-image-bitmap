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