#include <stdio.h>
#include "sequence_liste.h"
#include "geom2d.h"
#include "image.h"
#include "contour.h"

int ecrire_eps(Liste_Segment l, Vecteur dimensions, char *fichier, int stroke)
{
    int k = 0;
    FILE *f = fopen(fichier, "w");
    if (!f)
        return -1; // Sécurité

    Tableau_Segment t = sequence_segments_liste_vers_tableau(l);

    fprintf(f, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(f, "%%%%BoundingBox: 0 0 %d %d\n", (int)dimensions.x, (int)dimensions.y);

    if (t.taille == 0)
        return 0;

    for (int i = 0; i < t.taille; i++)
    {
        Segment s_actuel = t.tab[i];
        Point a = s_actuel.a;
        Point b = s_actuel.b;
        // printf("a: (%f, %f) b: (%f, %f)\n", a.x, a.y, b.x, b.y);
        fprintf(f, "%d %d moveto ", (int)a.x, (int)dimensions.y - (int)a.y);

        fprintf(f, "%d %d lineto ", (int)b.x, (int)dimensions.y - (int)b.y);
    }
    // printf("nombre de segments: %d\n", k);

    // if (!stroke)
    // {
    fprintf(f, "\n0 setlinewidth fill\n\n");
    // }
    // else
    // {
    fprintf(f, "0 setlinewidth stroke\n");
    // }

    fprintf(f, "showpage\n");
    fclose(f);
    return 0;
}

int main(int argc, char *argv[])
{
    Image I = lire_fichier_image(argv[1]);
    Liste_Point l = trouver_contours_multiple(I);
    Tableau_Point t2 = sequence_points_liste_vers_tableau(l);
    int indices[1000];
    int n_indices = 1;
    indices[0] = -1;
    Point pdebut = t2.tab[0];
    for (int i = 1; i < l.taille; i++)
    {
        Point p = t2.tab[i];
        if ((p.x == pdebut.x) && (p.y == pdebut.y))
        {
            // printf("/////////////////////////////////%f %f\n", p.x, p.y);

            indices[n_indices++] = i;
            i++;
            pdebut = t2.tab[i];
        }
        // printf("p: (%f, %f)\n", p.x, p.y);
    }
    // printf("%d", n_indices);
    Liste_Segment l2 = creer_liste_Segment_vide();
    // for (int i = 0; i < n_indices; i++)
    // {
    //     printf("indice: %d\n", indices[i]);
    // }
    for (int j = 0; j < n_indices - 1; j++)
    {
        // printf("premier point: %f %f\n", t2.tab[indices[j] + 1].x, t2.tab[indices[j]].y);
        // printf("dernier point: %f %f\n", t2.tab[indices[j + 1]].x, t2.tab[indices[j + 1]].y);
        Liste_Segment l3 = simplification_douglas_peucker(l, indices[j] + 1, indices[j + 1], 1);
        // printf("taille segment l3 %d;", l3.taille);

        l2 = concatener_liste_Segment(l2, l3);
    }
    // printf("taille segment l2 %d;", l2.taille);
    Vecteur dimensions = {largeur_image(I), hauteur_image(I)};
    Tableau_Segment t = sequence_segments_liste_vers_tableau(l2);
    ecrire_eps(l2, dimensions, "test.eps", 0);
}
