#ifndef _GEOM2D_H_
#define _GEOM2D_H_

typedef struct Vecteur_
{
    double x, y;
} Vecteur;

typedef struct Point_
{
    double x, y;
} Point;

Point set_point(double x, double y);

Point add_point(Point P1, Point P2);

Point mul_point(Point P, double a);

float distance(Point P1, Point P2);

Vecteur vect_bipoint(Point A, Point B);

Vecteur mul_vect(Vecteur V, double a);

double produit_scalaire(Vecteur A, Vecteur B);
float norme(Vecteur V);
typedef struct
{
    Point a;
    Point b;

} Segment;

#endif
float distance_point_segment(Segment s, Point p);
