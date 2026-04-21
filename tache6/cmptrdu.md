# MAP401 - TACHE6
### Fonction de calcul de la distance point-segment
```c

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
```
### Programme de test
```c
int main(int argc, char *argv[])
{
    Point P = set_point(atoi(argv[1]), atoi(argv[2]));
    Point A = set_point(atoi(argv[3]), atoi(argv[4]));
    Point B = set_point(atoi(argv[5]), atoi(argv[6]));
    Segment S = {A, B};

    printf("Distance : %f\n", distance_point_segment(S, P));
    return 0;
}
```


### Jeu de test

```c
Segment s1 = {{0, 0}, {3, 0}};
Segment s2 = {{0, 0}, {3, 3}};
Point a = set_point(0, 1);
Point b = set_point(1, 1);
Point c = set_point(2, 1);
Point d = set_point(3, 1);
Point e = set_point(4, 1);
Point f = set_point(-1, 1);
printf("%f\n", distance_point_segment(s1, a)); // 1.0
printf("%f\n", distance_point_segment(s1, b)); // 1.0
printf("%f\n", distance_point_segment(s1, c)); // 1.0
printf("%f\n", distance_point_segment(s1, d)); // 1.0
printf("%f\n", distance_point_segment(s1, e)); // 1.41.. (racine de 2)
printf("%f\n", distance_point_segment(s1, f)); // 1.41.. (racine de 2)
printf("%f\n", distance_point_segment(s2, a)); // 0.707.. ((racine de 2)/2)
printf("%f\n", distance_point_segment(s2, b)); // 0.0
printf("%f\n", distance_point_segment(s2, c)); // 0.707.. ((racine de 2)/2)
printf("%f\n", distance_point_segment(s2, d)); // 1.41.. (racine de 2)
printf("%f\n", distance_point_segment(s2, e)); // 2.12.. ((racine de 2 * 3/2))
printf("%f\n", distance_point_segment(s2, f)); // 1.41.. (racine de 2)
printf("%f\n", distance_point_segment(s3, a)); // 1
printf("%f\n", distance_point_segment(s3, b)); // 1.41.. (racine de 2)
printf("%f\n", distance_point_segment(s3, f)); // 1.41.. (racine de 2)
```

execution:
```
1.000000
1.000000
1.000000
1.000000
1.414214
1.414214
0.707107
0.000000
0.707107
1.414214
2.121320
1.414214
1.000000
1.414214
1.414214
```
