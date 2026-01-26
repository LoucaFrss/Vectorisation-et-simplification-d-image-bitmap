
#include <stdio.h>
#include <stdlib.h>
#include "geom2d.h"
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