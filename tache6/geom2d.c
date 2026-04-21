#include "geom2d.h"
#include <math.h>

Point set_point(double x, double y)
{
    Point P = {x, y};
    return P;
}

Point add_point(Point P1, Point P2)
{
    return set_point(P1.x + P2.x, P1.y + P2.y);
}

Point mul_point(Point P, double a)
{
    return set_point(P.x * a, P.y * a);
}

float distance(Point P1, Point P2)
{
    Vecteur v = vect_bipoint(P1, P2);
    return norme(v);
}

Vecteur vect_bipoint(Point A, Point B)
{
    Vecteur V = {B.x - A.x,
                 B.y - A.y};
    return V;
}

Vecteur mul_vect(Vecteur V, double a)
{

    Vecteur V2 = {V.x * a, V.y * a};
    return V2;
}

double produit_scalaire(Vecteur A, Vecteur B)
{
    return A.x * B.x + A.y * B.y;
}
float norme(Vecteur V)
{
    return sqrtf(V.x * V.x + V.y * V.y);
}

float distance_point_segment(Segment s, Point p)
{
    if ((s.a.x == s.b.x) && (s.a.y == s.b.y))
        return distance(s.a, p);

    float d;
    Vecteur vecteur_segment = vect_bipoint(s.a, s.b);
    Vecteur vecteur_de_p = vect_bipoint(s.a, p);
    double lamda = produit_scalaire(vecteur_de_p, vecteur_segment) / (produit_scalaire(vecteur_segment, vecteur_segment));
    if (lamda < 0)
    {
        d = distance(s.a, p);
    }
    else if (lamda >= 0 && lamda <= 1)
    {
        Point Q;
        Q = add_point(add_point(s.a, mul_point(s.b, lamda)), mul_point(s.a, -lamda));
        d = distance(p, Q);
    }
    else
    {
        d = distance(p, s.b);
    }
    return d;
}