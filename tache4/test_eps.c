#include "eps.h"
#include "image.h"
#include "geom2d.h"
#include "contour.h"
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    Image I = lire_fichier_image(argv[1]);
    Liste_Point l = trouver_contour(I);
    Vecteur dimensions = {largeur_image(I), hauteur_image(I)};

    ecrire_eps(l, dimensions, "tests.eps", atoi(argv[2]));

    return 0;
}