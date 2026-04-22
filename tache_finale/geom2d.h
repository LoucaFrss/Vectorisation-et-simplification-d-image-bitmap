#ifndef _GEOM2D_H_
#define _GEOM2D_H_
#include "liste.h"
typedef struct Vecteur_
{
    double x, y;
} Vecteur;

typedef struct Point_
{
    double x, y;
} Point;
DECL_LISTE(Point);
DECL_LISTE(Liste_Point);

Point set_point(double x, double y);

Point add_point(Point P1, Point P2);
Point sub_point(Point P1, Point P2);

Point mul_point(Point P, double a);

double distance(Point P1, Point P2);

Vecteur vect_bipoint(Point A, Point B);

Vecteur mul_vect(Vecteur V, double a);

double produit_scalaire(Vecteur A, Vecteur B);
double norme(Vecteur V);
typedef struct
{
    Point a;
    Point b;

} Segment;

double distance_point_segment(Segment s, Point p);
#endif
