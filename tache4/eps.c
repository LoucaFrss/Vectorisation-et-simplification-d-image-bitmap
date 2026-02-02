#include "eps.h"
#include "image.h"
#include <stdio.h>
int ecrire_eps(Liste_Point l, Vecteur dimensions, char *fichier)
{

    FILE *f = fopen(fichier, "w");
    Tableau_Point t = sequence_points_liste_vers_tableau(l);

    fprintf(f, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(f, "%%%%BoundingBox: 0 0 %d %d\n", (int)dimensions.x, (int)dimensions.y);
    // fprintf(f, "0.1 0.1 scale\n");

    Point p = t.tab[0];
    fprintf(f, "%d %d moveto ", (int)p.x, (int)dimensions.y - (int)p.y);

    for (int i = 1; i < t.taille; i++)
    {
        p = t.tab[i];
        fprintf(f, "%d %d lineto ", (int)p.x, (int)dimensions.y - (int)p.y);
    }

    fprintf(f, "\n0 setlinewidth fill\n\n");
    fprintf(f, "\nshowpage\n");

    fclose(f);
}