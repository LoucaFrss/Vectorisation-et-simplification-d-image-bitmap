#include "eps.h"
#include "math.h"
int ecrire_eps(Liste_Liste_Bezier3 l, Vecteur dimensions, char *fichier, int stroke)
{
    int h = dimensions.y;
    // int k = 0;
    FILE *f = fopen(fichier, "w");
    if (!f)
        return -1; // Sécurité

    Tableau_Liste_Bezier3 t = sequence_Liste_Bezier3_liste_vers_tableau(l);
    // printf(ta"%d")
    fprintf(f, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(f, "%%%%BoundingBox: 0 0 %d %d\n", (int)dimensions.x, (int)dimensions.y);

    printf("taille: %d\n", t.taille);
    if (t.taille == 0)
        return 0;

    for (int j = 0; j < t.taille; j++)
    {
        Tableau_Bezier3 t2 = sequence_Bezier3_liste_vers_tableau(t.tab[j]);

        Bezier3 b = t2.tab[0];
        fprintf(f, "%d %d moveto ", (int)b.c0.x, h - (int)b.c0.y);
        for (int i = 0; i < t2.taille; i++)
        {
            Bezier3 b = t2.tab[i];

            // b3.c1 = mul_point(b3.c1, 1 / 100);
            // b3.c2 = mul_point(b3.c2, 1 / 100);
            fprintf(f, "%f %f %f %f %f %f curveto ", b.c1.x, h - b.c1.y, b.c2.x, h - b.c2.y, b.c3.x, h - b.c3.y);
        }
    }
    fprintf(f, "\n");

    fprintf(f, "0 fill\n");
    // fprintf(f, "\n0 setlinewidth stroke\n\n");

    fprintf(f, "showpage\n");
    fclose(f);
    return 0;
}