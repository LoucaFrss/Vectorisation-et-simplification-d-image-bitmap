#include <stdio.h>
#include "liste.h"
#include "geom2d.h"
#include "image.h"
#include "contour.h"
#include "eps.h"
#include "segment.h"

int main(int argc, char *argv[])
{
    Image I = lire_fichier_image(argv[1]);
    Liste_Liste_Point l = trouver_contours_multiple(I);
    printf("Nombre de contours: %d\n", l.taille);

    Liste_Liste_Segment l2 = creer_liste_Liste_Segment_vide();

    Tableau_Liste_Point t = sequence_Liste_Point_liste_vers_tableau(l);

    for (int i = 0; i < t.taille; i++)
    {
        l2 = ajouter_element_liste_Liste_Segment(
            l2,
            simplification_douglas_peucker(t.tab[i], 0, t.tab[i].taille - 1, 3));
    }

    Vecteur dimensions = {largeur_image(I), hauteur_image(I)};

    ecrire_eps_simplification_segment(l2, dimensions, "test.eps", 0);
}
