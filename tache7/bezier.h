#ifndef BEZIER_H
#define BEZIER_H

#include "geom2d.h"
#include "liste.h"
typedef struct
{
    Point c0;
    Point c1;
    Point c2;
} Bezier2;

typedef struct
{
    Point c0;
    Point c1;
    Point c2;
    Point c3;
} Bezier3;
DECL_LISTE(Bezier2);
DECL_LISTE(Liste_Bezier2);
DECL_LISTE(Bezier3);
DECL_LISTE(Liste_Bezier3);

Liste_Bezier2 simplification_douglas_peucker_bezier2(Liste_Point CONT, int j1, int j2, double d);
Bezier3 Bezier2versBezier3(Bezier2 b2);
Point C3(Bezier3 b, double t);
double distance_point_bezier3(Point p, Bezier3 b, double ti);
Bezier3 approx_bezier3(Liste_Point L, int j1, int j2);
Liste_Bezier3 simplification_douglas_peucker_bezier3(Liste_Point CONT, int j1, int j2, double d);
#endif