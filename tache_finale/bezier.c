#include "bezier.h"
#include <stdio.h>
#include <stdlib.h>
IMPL_LISTE(Bezier2);
IMPL_LISTE(Liste_Bezier2);
IMPL_LISTE(Bezier3);
IMPL_LISTE(Liste_Bezier3);

Point C2(Bezier2 b, double t)
{
    return set_point(

        (1.0 - t) * (1.0 - t) * b.c0.x + 2.0 * (1 - t) * t * b.c1.x + t * t * b.c2.x,
        (1.0 - t) * (1.0 - t) * b.c0.y + 2.0 * (1 - t) * t * b.c1.y + t * t * b.c2.y

    );
}

Bezier3 Bezier2versBezier3(Bezier2 b2)
{
    Bezier3 b3;
    b3.c0 = b2.c0;
    b3.c1 = add_point(mul_point(b2.c0, 1.0 / 3.0), mul_point(b2.c1, 2.0 / 3.0));
    b3.c2 = add_point(mul_point(b2.c1, 2.0 / 3.0), mul_point(b2.c2, 1.0 / 3.0));
    b3.c3 = b2.c2;
    return b3;
}

double distance_point_bezier2(Point p, Bezier2 b, double ti)
{
    return distance(p, C2(b, ti));
}
Bezier2 approx_bezier2(Liste_Point L, int j1, int j2)
{
    Point C1;
    C1.x = 0;
    C1.y = 0;
    Tableau_Point T = sequence_Point_liste_vers_tableau(L);
    int N = (j2 - j1);
    double n = (double)(j2 - j1);
    if (N == 1)
    {
        C1 = mul_point(add_point(T.tab[j1], T.tab[j2]), 0.5);
        //     printf("milieu: %f %f", C1.x, C1.y);
        //     printf("milieu t: %f %f", T.tab[j1].x, T.tab[j1].y);
    }
    else if (N >= 2)
    {
        double alpha = 3.0 * n / (n * n - 1.0);
        double beta = (1.0 - (2.0 * n)) / (2.0 * (n + 1.0));
        // printf("alpha: %f\n", alpha);
        Point S = {0, 0};
        for (int i = 1; i <= N - 1; i++)
        {
            S = add_point(S, T.tab[j1 + i]);
        }
        C1 = add_point(mul_point(S, alpha), mul_point(add_point(T.tab[j1], T.tab[j2]), beta));
        // printf("milieu: %f %f", C1.x, C1.y);
        // printf("milieu t: j1: %f %f j2: %f %f beta: %f alpha: %f n: %d", T.tab[j1].x, T.tab[j1].y, T.tab[j2].x, T.tab[j2].y, beta, alpha, N);
    }
    Bezier2 b;
    b.c0 = T.tab[j1];
    b.c1 = C1;
    b.c2 = T.tab[j2];
    return b;
}

Liste_Bezier2 simplification_douglas_peucker_bezier2(Liste_Point CONT, int j1, int j2, double d)
{
    int n = j2 - j1;
    Bezier2 B = approx_bezier2(CONT, j1, j2);
    // printf("courbe bezier: %f %f %f %f %f %f ", B.c0.x, B.c0.y, B.c1.x, B.c1.y, B.c2.x, B.c2.y);
    double dmax = 0.0;
    int k = j1;
    Liste_Bezier2 L = creer_liste_Bezier2_vide();
    Tableau_Point T;
    T = sequence_Point_liste_vers_tableau(CONT);
    for (int j = j1 + 1; j <= j2; j++)
    {
        int i = j - j1;
        double ti = (double)i / (double)n;
        double dj = distance_point_bezier2(T.tab[j], B, ti);
        if (dmax < dj)
        {
            dmax = dj;
            k = j;
        }
    }
    // printf("DEBUG: dmax=%f, d=%f, diff=%f\n", dmax, d, dmax - d);
    if (dmax < d)
    {
        L = ajouter_element_liste_Bezier2(L, B);
    }
    else
    {
        Liste_Bezier2 L1 = simplification_douglas_peucker_bezier2(CONT, j1, k, d);
        Liste_Bezier2 L2 = simplification_douglas_peucker_bezier2(CONT, k, j2, d);
        L = concatener_liste_Bezier2(L1, L2);
    }
    return L;
}

double teta(int k, int n)
{
    double k1 = (double)k;
    double n1 = (double)n;
    double res = 6.0 * k1 * k1 * k1 * k1 - 8.0 * n1 * k1 * k1 * k1 + 6.0 * k1 * k1 - 4.0 * n1 * k1 + n1 * n1 * n1 * n1 - n1 * n1;
    return res;
}

Bezier3 approx_bezier3(Liste_Point L, int j1, int j2)
{
    int n = j2 - j1;
    Bezier3 b;
    Tableau_Point T = sequence_Point_liste_vers_tableau(L);
    Point C1;
    Point C2;
    if (n < 2)
    {
        C1 = mul_point(add_point(T.tab[j2], mul_point(T.tab[j1], 2.0)), 1.0 / 3.0);
        C2 = mul_point(add_point(T.tab[j1], mul_point(T.tab[j2], 2.0)), 1.0 / 3.0);
    }
    else if (n == 2)
    {
        C1 = mul_point(add_point(mul_point(T.tab[j1 + 1], 4.0), mul_point(T.tab[j1 + 2], (-1.0))), 1.0 / 3.0);
        C2 = mul_point(add_point(mul_point(T.tab[j1 + 1], 4.0), mul_point(T.tab[j1], (-1.0))), 1.0 / 3.0);
    }
    else
    {
        double n1 = (double)n;
        double alpha = ((-15.0) * n1 * n1 * n1 + 5.0 * n1 * n1 + 2.0 * n1 + 4.0) / (3.0 * (n1 + 2.0) * (3.0 * n1 * n1 + 1.0));
        double beta = (10.0 * n1 * n1 * n1 - 15.0 * n1 * n1 + n1 + 2.0) / (3.0 * (n1 + 2.0) * (3.0 * n1 * n1 + 1.0));
        double lamda = 70.0 * n1 / (3 * (n1 * n1 - 1) * (3.0 * n1 * n1 + 1.0) * (n1 * n1 - 4.0));
        Point S;
        S.x = 0.0;
        S.y = 0.0;
        for (int i = 1; i <= n - 1; i++)
        {
            S = add_point(S, mul_point(T.tab[j1 + i], teta(i, n)));
        }
        C1 = add_point(add_point(mul_point(T.tab[j1], alpha), mul_point(S, lamda)), mul_point(T.tab[j2], beta));
        Point S1;
        S1.x = 0.0;
        S1.y = 0.0;
        for (int i = 1; i <= n - 1; i++)
        {
            S1 = add_point(S1, mul_point(T.tab[j1 + i], teta(n - i, n)));
        }
        C2 = add_point(add_point(mul_point(T.tab[j1], beta), mul_point(S1, lamda)), mul_point(T.tab[j2], alpha));
    }
    b.c0 = T.tab[j1];
    b.c1 = C1;
    b.c2 = C2;
    b.c3 = T.tab[j2];
    return b;
}

// calcule le point de la courbe de bezier
Point C3(Bezier3 b, double t)
{
    return set_point(

        (1.0 - t) * (1.0 - t) * (1.0 - t) * b.c0.x + 3.0 * (1.0 - t) * (1.0 - t) * t * b.c1.x + 3.0 * t * t * (1.0 - t) * b.c2.x + t * t * t * b.c3.x,
        (1.0 - t) * (1.0 - t) * (1.0 - t) * b.c0.y + 3.0 * (1.0 - t) * (1.0 - t) * t * b.c1.y + 3.0 * t * t * (1.0 - t) * b.c2.y + t * t * t * b.c3.y

    );
}

double distance_point_bezier3(Point p, Bezier3 b, double ti)
{
    return distance(p, C3(b, ti));
}

Liste_Bezier3 simplification_douglas_peucker_bezier3(Liste_Point CONT, int j1, int j2, double d)
{
    int n = j2 - j1;
    Bezier3 B = approx_bezier3(CONT, j1, j2);
    // printf("courbe bezier: %f %f %f %f %f %f ", B.c0.x, B.c0.y, B.c1.x, B.c1.y, B.c2.x, B.c2.y);
    double dmax = 0.0;
    int k = j1;
    Liste_Bezier3 L = creer_liste_Bezier3_vide();
    Tableau_Point T;
    T = sequence_Point_liste_vers_tableau(CONT);
    for (int j = j1 + 1; j <= j2; j++)
    {
        int i = j - j1;
        double ti = (double)i / (double)n;
        double dj = distance_point_bezier3(T.tab[j], B, ti);
        if (dmax < dj)
        {
            dmax = dj;
            k = j;
        }
    }
    // printf("DEBUG: dmax=%f, d=%f, diff=%f\n", dmax, d, dmax - d);
    if (dmax < d)
    {
        L = ajouter_element_liste_Bezier3(L, B);
    }
    else
    {
        Liste_Bezier3 L1 = simplification_douglas_peucker_bezier3(CONT, j1, k, d);
        Liste_Bezier3 L2 = simplification_douglas_peucker_bezier3(CONT, k, j2, d);
        L = concatener_liste_Bezier3(L1, L2);
    }
    return L;
}