#include "image.h"
#include "liste.h"
#include "contour.h"
#include "bezier.h"
#include "eps.h"

int main()
{
    Image I = lire_fichier_image("./image_poly_tache6.pbm");
    Liste_Liste_Point l = trouver_contours_multiple(I);
    Tableau_Liste_Point t = sequence_Liste_Point_liste_vers_tableau(l);
    printf("taille l:%d\n", l.taille);
    Liste_Liste_Bezier3 b = creer_liste_Liste_Bezier3_vide();

    for (int i = 0; i < l.taille; i++)
    {
        Liste_Point l2 = t.tab[i];
        printf("taille l2: %d\n", l2.taille);
        Liste_Bezier3 b2 = simplification_douglas_peucker_bezier3(l2, 0, l2.taille - 1, 3);
        printf("\ntaille b2: %d\n", b2.taille);

        b = ajouter_element_liste_Liste_Bezier3(b, b2);
    }
    printf("taille b:%d\n", b.taille);
    Vecteur dim;
    dim.x = largeur_image(I);
    dim.y = hauteur_image(I);
    ecrire_eps(b, dim, "test.eps", 1);
}
