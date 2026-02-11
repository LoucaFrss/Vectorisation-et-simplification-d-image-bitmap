#include <stdio.h>
#include "sequence_point.h"
#include "image.h"
#include "eps.h"
#include "geom2d.h"

#include "contour.h"
int main(int argc, char *argv[])
{
    int n = 0;
    Image I = lire_fichier_image(argv[1]);

    Liste_Point l = trouver_contours_multiple(I);
    Vecteur dimensions = {largeur_image(I), hauteur_image(I)};
    ecrire_eps(l, dimensions, "tests.eps", 0);

} // fin du programme
