#include "eps.h"
#include "image.h"
#include <stdio.h>

int ecrire_eps(Liste_Point l, Vecteur dimensions, char *fichier, int stroke)
{
    int k = 0;
    FILE *f = fopen(fichier, "w");
    if (!f)
        return -1; // Sécurité

    Tableau_Point t = sequence_points_liste_vers_tableau(l);

    fprintf(f, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(f, "%%%%BoundingBox: 0 0 %d %d\n", (int)dimensions.x, (int)dimensions.y);

    if (t.taille == 0)
        return 0;

    Point p_depart = t.tab[0];
    fprintf(f, "%d %d moveto ", (int)p_depart.x, (int)dimensions.y - (int)p_depart.y);

    for (int i = 1; i < t.taille; i++)
    {
        Point p_actuel = t.tab[i];

        fprintf(f, "%d %d lineto ", (int)p_actuel.x, (int)dimensions.y - (int)p_actuel.y);

        if (p_actuel.x == p_depart.x && p_actuel.y == p_depart.y)
        {
            k += 1;
            if (i + 1 < t.taille)
            {
                p_depart = t.tab[i + 1];
                fprintf(f, "%d %d moveto ", (int)p_depart.x, (int)dimensions.y - (int)p_depart.y);
                i++;
            }
        }
    }
    printf("nombre de segments: %d\n", k);

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
    return 0;
}