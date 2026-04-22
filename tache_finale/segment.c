
#include "segment.h"
IMPL_LISTE(Segment);
IMPL_LISTE(Liste_Segment);

Liste_Segment simplification_douglas_peucker(Liste_Point CONT, int j1, int j2, float d)
{
    Liste_Segment L = creer_liste_Segment_vide();
    Segment s;
    Tableau_Point T;

    T = sequence_Point_liste_vers_tableau(CONT);

    s.a = T.tab[j1];
    s.b = T.tab[j2];

    float dmax = 0;
    int k = j1;

    for (int j = j1 + 1; j < j2; j++)
    {
        float dj = distance_point_segment(s, T.tab[j]);
        if (dmax < dj)
        {
            dmax = dj;
            k = j;
        }
    }

    if (dmax <= d)
    {
        L = ajouter_element_liste_Segment(L, s);
    }
    else
    {
        Liste_Segment L1 = simplification_douglas_peucker(CONT, j1, k, d);
        Liste_Segment L2 = simplification_douglas_peucker(CONT, k, j2, d);
        L = concatener_liste_Segment(L1, L2);
    }

    free(T.tab);

    return L;
}