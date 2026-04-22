#include "eps.h"
#include <math.h>

int ecrire_eps_simplification_segment(Liste_Liste_Segment l, Vecteur dimensions, char *fichier, int stroke)
{
    int h = dimensions.y;
    int n_segment = 0;
    // int k = 0;
    FILE *f = fopen(fichier, "w");
    if (!f)
        return -1; // Sécurité

    Tableau_Liste_Segment t = sequence_Liste_Segment_liste_vers_tableau(l);
    // printf(ta"%d")
    fprintf(f, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(f, "%%%%BoundingBox: 0 0 %d %d\n", (int)dimensions.x, (int)dimensions.y);

    if (t.taille == 0)
        return 0;

    for (int j = 0; j < t.taille; j++)
    {
        Tableau_Segment t2 = sequence_Segment_liste_vers_tableau(t.tab[j]);

        Segment s = t2.tab[0];
        fprintf(f, "%f %f moveto ", s.a.x, h - s.a.y);
        for (int i = 0; i < t2.taille; i++)
        {
            Segment s = t2.tab[i];

            // b3.c1 = mul_point(b3.c1, 1 / 100);
            // b3.c2 = mul_point(b3.c2, 1 / 100);
            fprintf(f, "%f %f lineto ", s.b.x, h - s.b.y);
            n_segment++;
        }
    }

    fprintf(f, "0 fill\n");
    if (!stroke)
    {
        // Utilise "eofill" si tu as des problèmes de trous non remplis
        fprintf(f, "\n0 fill\n");
    }
    else
    {
        // fprintf(f, "0 setlinewidth stroke\n");
        fprintf(f, "0 fill\n");
    }

    fprintf(f, "showpage\n");
    fclose(f);
    // Libérer t.tab si nécessaire selon ta gestion de mémoire
    printf("Nombre de segments: %d\n", n_segment);
    return 0;
}

int ecrire_eps_simplification_bezier3(Liste_Liste_Bezier3 l, Vecteur dimensions, char *fichier, int stroke)
{
    int h = dimensions.y;
    int n_bezier = 0;
    // int k = 0;
    FILE *f = fopen(fichier, "w");
    if (!f)
        return -1; // Sécurité

    Tableau_Liste_Bezier3 t = sequence_Liste_Bezier3_liste_vers_tableau(l);
    // printf(ta"%d")
    fprintf(f, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(f, "%%%%BoundingBox: 0 0 %d %d\n", (int)dimensions.x, (int)dimensions.y);

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
            n_bezier++;
        }
    }

    fprintf(f, "0 fill\n");
    // fprintf(f, "\n0 setlinewidth stroke\n\n");

    fprintf(f, "showpage\n");
    printf("Nombre de courbes de Bezier de degrés 3: %d\n", n_bezier);
    fclose(f);
    return 0;
}

int ecrire_eps_simplification_bezier2(Liste_Liste_Bezier2 l, Vecteur dimensions, char *fichier, int stroke)
{
    int h = dimensions.y;
    int n_bezier = 0;
    // int k = 0;
    FILE *f = fopen(fichier, "w");
    if (!f)
        return -1; // Sécurité

    Tableau_Liste_Bezier2 t = sequence_Liste_Bezier2_liste_vers_tableau(l);
    // printf(ta"%d")
    fprintf(f, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(f, "%%%%BoundingBox: 0 0 %d %d\n", (int)dimensions.x, (int)dimensions.y);

    if (t.taille == 0)
        return 0;

    for (int j = 0; j < t.taille; j++)
    {
        Tableau_Bezier2 t2 = sequence_Bezier2_liste_vers_tableau(t.tab[j]);

        Bezier2 b = t2.tab[0];
        fprintf(f, "%d %d moveto ", (int)b.c0.x, h - (int)b.c0.y);
        for (int i = 0; i < t2.taille; i++)
        {
            Bezier2 b = t2.tab[i];
            Bezier3 b3 = Bezier2versBezier3(b);

            // b3.c1 = mul_point(b3.c1, 1 / 100);
            // b3.c2 = mul_point(b3.c2, 1 / 100);
            fprintf(f, "%f %f %f %f %f %f curveto ", b3.c1.x, h - b3.c1.y, b3.c2.x, h - b3.c2.y, b3.c3.x, h - b3.c3.y);
            n_bezier++;
        }
    }

    fprintf(f, "0 fill\n");
    // fprintf(f, "\n0 setlinewidth stroke\n\n");

    fprintf(f, "showpage\n");
    printf("Nombre de courbes de Bezier de degrés 2: %d\n", n_bezier);
    fclose(f);
    return 0;
}