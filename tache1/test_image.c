/**
 * @file test_image.c
 * @brief Programme de test pour appliquer un filtre négatif sur une image
 *
 * Ce programme prend en entrée le chemin d'un fichier image et applique
 * un filtre négatif en inversant les valeurs des pixels, puis affiche le résultat.
 *
 * Usage: ./test_image <chemin_image>
 */

#include "image.h"
#include <stdio.h>

in(int argc, char *argv[])
{
    /* Vérifie si un argument (le chemin de l'image) a été fourni */
    if (argc <= 1)
    {
        printf("Usage: ./test_image <chemin_image>");
        return 1;
    }

    /* Lit l'image depuis le fichier spécifié en argument */
    Image I = lire_fichier_image(argv[1]);

    /* Applique le filtre négatif à l'image */
    negatif_image(I);

    /* Écrit et affiche l'image traitée */
    ecrire_image(I);

    return 0;
}