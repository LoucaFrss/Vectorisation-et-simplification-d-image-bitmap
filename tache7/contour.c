#include "contour.h"
#include <stdio.h>
#include <unistd.h>

Point trouver_pixel_depart(Image I)
{
    double i, j;

    for (j = 1; j <= hauteur_image(I); j++)
    {
        for (i = 1; (i <= largeur_image(I)); i++)
        {
            if (i == largeur_image(I) && j == hauteur_image(I))
            {
                // printf("Erreur, image vide impossible de trouver le pixel de depart");
                return set_point(largeur_image(I), hauteur_image(I));
            }
            if (get_pixel_image(I, i, j) == NOIR)
            {

                // else
                return set_point(i, j);
            }
        }
    }
}

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
    }
}

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

Orientation nouvelle_orientation(Image I, Point p, Orientation o)
{
    // printf("orientation: %d\n", o);
    Pixel pG = valeur_pixel_gauche(I, p, o);
    Pixel pD = valeur_pixel_droite(I, p, o);
    if (pG == NOIR)
    {
        o += 1;
        o %= 4;
    }
    else if (pD == BLANC)
    {
        // printf("test\n");
        o += 3;
        o %= 4;
    }
    // printf("orientation fin : %d\n", o);

    return o;
}
Liste_Point trouver_contour(Image I, Image masque, Point pixel_depart, Liste_Point l)
{
    Point depart = set_point(pixel_depart.x - 1, pixel_depart.y - 1);
    Point p = set_point(depart.x, depart.y);
    Orientation o = Est;
    Pixel interieur = valeur_pixel_gauche(I, p, o);
    // if ((interieur) == BLANC)
    // {
    //     o = Ouest;
    // }

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

        // if (o2 == o)

        //     *nb_segment++;

        // o = o2;
        // ecrire_contour(l);
        // sleep(1);
        if (p.x == depart.x && p.y == depart.y && o == Est)
        {
            boucle = 0;
        }
    }
    return l;
}
Liste_Liste_Point trouver_contours_multiple(Image I)
{
    Image masque = image_masque(I);

    Point p = trouver_pixel_depart(masque);
    Liste_Liste_Point l = creer_liste_Liste_Point_vide();

    while (p.x != largeur_image(I) || p.y != hauteur_image(I))
    {
        // ecrire_image(masque);
        // l_indices[i] = l.taille;
        l = ajouter_element_liste_Liste_Point(l, trouver_contour(I, masque, p, creer_liste_Point_vide()));

        p = trouver_pixel_depart(masque);
        // ecrire_contour(l);
    }
    ecrire_image(masque);

    return l;
}

// Liste_Point trouver_contour(Image I, Image masque)
// {
//     Liste_Point l = creer_liste_Point_vide();
//     Point pixel_depart = trouver_pixel_depart(I);
//     // printf("point de depart: %f %f\n", pixel_depart.x, pixel_depart.y);
//     Point depart = set_point(pixel_depart.x - 1, pixel_depart.y - 1);
//     Point p = set_point(depart.x, depart.y);
//     Orientation o = Est;
//     int boucle = 1;
//     while (boucle)
//     {
//         if (o == Est)
//         {
//             set_pixel_image(I, p.x + 1, p.y + 1, BLANC);
//         }
//         l = ajouter_element_liste_Point(l, p);
//         p = avancer(p, o);
//         o = nouvelle_orientation(I, p, o);

//         // if (o2 == o)

//         //     *nb_segment++;

//         // o = o2;
//         // ecrire_contour(l);
//         // sleep(1);
//         if (p.x == depart.x && p.y == depart.y && o == Est)
//         {
//             boucle = 0;
//         }
//     }
//     return ajouter_element_liste_Point(l, p);
// }

Image image_masque(Image I)
{
    Image masque =
        creer_image(largeur_image(I), hauteur_image(I));

    for (int j = 1; j <= hauteur_image(I); j++)
    {
        for (int i = 1; i <= largeur_image(I); i++)
        {
            if (get_pixel_image(I, i, j) == NOIR && get_pixel_image(I, i, j - 1) == BLANC)
                set_pixel_image(masque, i, j, NOIR);
        }
    }
    return masque;
}