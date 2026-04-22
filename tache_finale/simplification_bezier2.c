#include "image.h"
#include "liste.h"
#include "contour.h"
#include "bezier.h"
#include "eps.h"

int main(int argc, char *argv[])
{
    Image I = lire_fichier_image(argv[1]);
    double d = atof(argv[2]);
    Liste_Liste_Point l = trouver_contours_multiple(I);
    printf("Nombre de contours: %d\n", l.taille);
    Tableau_Liste_Point t = sequence_Liste_Point_liste_vers_tableau(l);
    Liste_Liste_Bezier2 b = creer_liste_Liste_Bezier2_vide();

    printf("d: %f\n", d);
    for (int i = 0; i < l.taille; i++)
    {
        Liste_Point l2 = t.tab[i];
        Liste_Bezier2 b2 = simplification_douglas_peucker_bezier2(l2, 0, l2.taille - 1, d);

        b = ajouter_element_liste_Liste_Bezier2(b, b2);
    }
    Vecteur dim;
    dim.x = largeur_image(I);
    dim.y = hauteur_image(I);
    ecrire_eps_simplification_bezier2(b, dim, "test.eps", 1);
}
