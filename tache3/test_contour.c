#include <stdio.h>
#include "sequence_point.h"
#include "image.h"

#include "contour.h"
int main(int argc, char *argv[])
{
    //     Contour C1, C2;

    //     /* initialiser C1 comme contour vide */
    //     C1 = creer_liste_Point_vide();
    //     printf("C1 : ");
    //     ecrire_contour(C1);

    //     /* ajouter les points (5,3),(3,1),(7,2) et (1,6) dans C1 */
    //     C1 = ajouter_element_liste_Point(C1, set_point(5, 3));
    //     C1 = ajouter_element_liste_Point(C1, set_point(3, 1));
    //     C1 = ajouter_element_liste_Point(C1, set_point(7, 2));
    //     C1 = ajouter_element_liste_Point(C1, set_point(1, 6));
    //     printf("C1 : ");
    //     ecrire_contour(C1);

    //     /* supprimer le premier point de C1, puis ajouter le point (4,1) dans C1 */
    //     C1 = supprimer_premier_element_liste_Point(C1);
    //     C1 = ajouter_element_liste_Point(C1, set_point(4, 1));
    //     printf("C1 : ");
    //     ecrire_contour(C1);

    //     /* creer le contour C2 avec les points (9,5) et (5,7) */
    //     C2 = creer_liste_Point_vide();
    //     C2 = ajouter_element_liste_Point(C2, set_point(9, 5));
    //     C2 = ajouter_element_liste_Point(C2, set_point(5, 7));
    //     printf("C2 : ");
    //     ecrire_contour(C2);

    //     /* concatener C2 a la suite de C1 */
    //     C1 = concatener_liste_Point(C1, C2);
    //     printf("C1 : ");
    //     ecrire_contour(C1);

    //     /* supprimer le contour C1 */
    //     C1 = supprimer_liste_Point(C1);
    //     printf("C1 : ");
    //     ecrire_contour(C1);
    Image I = lire_fichier_image(argv[1]);
    Liste_Point l = trouver_contour(I);

    // Tableau_Point t = sequence_points_liste_vers_tableau(l);
    // Point p = t.tab[0];

    // Point min = set_point(p.x, p.y);
    // Point max = set_point(p.x, p.y);
    // for (int i = 1; i < t.taille; i++)
    // {
    //     p = t.tab[i];
    //     min.x = p.x < min.x ? p.x : min.x;
    //     min.y = p.y < min.y ? p.y : min.y;
    //     max.x = p.x > max.x ? p.x : max.x;
    //     max.y = p.y > max.y ? p.y : max.y;
    // }

    // Point dimensions = set_point(max.x - min.x, max.y - min.y);
    ecrire_contour(l);
    printf("%s\n", argv[1]);
    printf("nb de segments: %d\n", l.taille - 1);
    printf("dimensions: (%dpx, %dpx)\n", largeur_image(I), hauteur_image(I));

} // fin du programme
