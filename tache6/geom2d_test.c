#include "geom2d.h"
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    //     Point P = set_point(atoi(argv[1]), atoi(argv[2]));
    //     Point A = set_point(atoi(argv[3]), atoi(argv[4]));
    //     Point B = set_point(atoi(argv[5]), atoi(argv[6]));
    //     Segment S = {A,
    //                  B};

    //     printf("Distance : %f\n", distance_point_segment(S, P));
    //     return 0;

    Segment s1 = {{0, 0}, {3, 0}};
    Segment s2 = {{0, 0}, {3, 3}};
    Segment s3 = {{0, 0}, {0, 0}};
    Point a = set_point(0, 1);
    Point b = set_point(1, 1);
    Point c = set_point(2, 1);
    Point d = set_point(3, 1);
    Point e = set_point(4, 1);
    Point f = set_point(-1, 1);
    printf("%f\n", distance_point_segment(s1, a));
    printf("%f\n", distance_point_segment(s1, b));
    printf("%f\n", distance_point_segment(s1, c));
    printf("%f\n", distance_point_segment(s1, d));
    printf("%f\n", distance_point_segment(s1, e));
    printf("%f\n", distance_point_segment(s1, f));

    printf("%f\n", distance_point_segment(s2, a));
    printf("%f\n", distance_point_segment(s2, b));
    printf("%f\n", distance_point_segment(s2, c));
    printf("%f\n", distance_point_segment(s2, d));
    printf("%f\n", distance_point_segment(s2, e));
    printf("%f\n", distance_point_segment(s2, f));
    printf("%f\n", distance_point_segment(s3, a));
    printf("%f\n", distance_point_segment(s3, b));
    printf("%f\n", distance_point_segment(s3, f));
}