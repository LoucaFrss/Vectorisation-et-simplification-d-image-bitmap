#include "contour.h"
#include <stdio.h>
#include <unistd.h>

/**
 * Parcourt l'image pour trouver le premier pixel NOIR.
 * qu'on utilisera comme point de départ pour l'extraction d'un contour.
 */
Point trouver_pixel_depart(Image I)
{
    double i, j;

    for (j = 1; j <= hauteur_image(I); j++)
    {
        for (i = 1; (i <= largeur_image(I)); i++)
        {
            // Si on arrive au bout de l'image sans trouver de pixel noir
            if (i == largeur_image(I) && j == hauteur_image(I))
            {
                return set_point(largeur_image(I), hauteur_image(I));
            }
            // Premier pixel noir trouvé (bord supérieur du contour)
            if (get_pixel_image(I, i, j) == NOIR)
            {
                return set_point(i, j);
            }
        }
    }
    return set_point(0, 0); // Sécurité pour le compilateur
}

/**
 fait avancer le robot d'une case devant lui et cela selon son orientation
 */
Point avancer(Point p, Orientation o)
{
    switch (o)
    {
    case Nord:
        return (set_point(p.x, p.y - 1));
    case Sud:
        return (set_point(p.x, p.y + 1));
    case Est:
        return (set_point(p.x + 1, p.y));
    case Ouest:
        return (set_point(p.x - 1, p.y));
    default:
        return p;
    }
}

/**
 * Récupére la valeur du pixel à gauche du robot (Soit BLANC Soit NOIR)
 */
Pixel valeur_pixel_gauche(Image I, Point p, Orientation o)
{
    Point p2;
    switch (o)
    {
    case Nord:
        p2 = set_point(p.x, p.y);
        break;
    case Sud:
        p2 = set_point(p.x + 1, p.y + 1);
        break;
    case Est:
        p2 = set_point(p.x + 1, p.y);
        break;
    case Ouest:
        p2 = set_point(p.x, p.y + 1);
        break;
    }
    return get_pixel_image(I, (int)p2.x, (int)p2.y);
}

/**
 * Récupére la valeur du pixel à droite du robot (Soit BLANC Soit NOIR).
 */
Pixel valeur_pixel_droite(Image I, Point p, Orientation o)
{
    Point p2;
    switch (o)
    {
    case Nord:
        p2 = set_point(p.x + 1, p.y);
        break;
    case Sud:
        p2 = set_point(p.x, p.y + 1);
        break;
    case Est:
        p2 = set_point(p.x + 1, p.y + 1);
        break;
    case Ouest:
        p2 = set_point(p.x, p.y);
        break;
    }
    return get_pixel_image(I, (int)p2.x, (int)p2.y);
}

/**
 * nouvelle orientation du robot selon les conditions suivantes:
 * Si pixel gauche est noir -> tourner à gauche (+1 mod 4).
 * Sinon si pixel droit est blanc -> tourner à droite (+3 mod 4).
 * Sinon -> continuer tout droit.
 */
Orientation nouvelle_orientation(Image I, Point p, Orientation o)
{
    Pixel pG = valeur_pixel_gauche(I, p, o);
    Pixel pD = valeur_pixel_droite(I, p, o);

    if (pG == NOIR)
    {
        o = (o + 1) % 4; // Tourner à gauche (sens trigo)
    }
    else if (pD == BLANC)
    {
        o = (o + 3) % 4; // Tourner à droite
    }
    return o;
}

/**
 * Extrait UN contour complet à partir d'un pixel de départ.
 * Marque les pixels traités dans le 'masque' pour éviter de boucler à l'infini
 * dans le cas ou il y a contours multiples.
 */
Liste_Point trouver_contour(Image I, Image masque, Point pixel_depart, Liste_Point l)
{
    // Position initiale du robot (coin supérieur gauche du pixel de départ)
    Point depart = set_point(pixel_depart.x - 1, pixel_depart.y - 1);
    Point p = set_point(depart.x, depart.y);
    Orientation o = Est;

    l = ajouter_element_liste_Point(l, p);

    int boucle = 1;
    while (boucle)
    {
        if (o == Est)
        {
            set_pixel_image(masque, p.x + 1, p.y + 1, BLANC);
        }

        p = avancer(p, o);
        o = nouvelle_orientation(I, p, o);
        l = ajouter_element_liste_Point(l, p);

        // Condition d'arrêt : retour au point de départ avec l'orientation initiale
        if (p.x == depart.x && p.y == depart.y && o == Est)
        {
            boucle = 0;
        }
    }
    return l;
}

/**
 *  Extrait tous les contours de l'image.
 */
Liste_Liste_Point trouver_contours_multiple(Image I)
{
    Image masque = image_masque(I); // Masque des "bords supérieurs"
    Point p = trouver_pixel_depart(masque);
    Liste_Liste_Point l = creer_liste_Liste_Point_vide();

    // Tant qu'il reste des pixels noirs dans le masque, il reste des contours
    while (p.x != largeur_image(I) || p.y != hauteur_image(I))
    {
        l = ajouter_element_liste_Liste_Point(l, trouver_contour(I, masque, p, creer_liste_Point_vide()));
        p = trouver_pixel_depart(masque);
    }

    return l;
}

/**
 * Crée une image "masque" contenant uniquement les pixels noirs
 * ayant un pixel blanc au-dessus.
 */
Image image_masque(Image I)
{
    Image masque = creer_image(largeur_image(I), hauteur_image(I));

    for (int j = 1; j <= hauteur_image(I); j++)
    {
        for (int i = 1; i <= largeur_image(I); i++)
        {
            // Un pixel est un départ de contour s'il est NOIR et que celui au dessus est BLANC
            if (get_pixel_image(I, i, j) == NOIR && get_pixel_image(I, i, j - 1) == BLANC)
                set_pixel_image(masque, i, j, NOIR);
        }
    }
    return masque;
}