#include "contour.h"
Point trouver_pixel_depart(Image I)
{
    int i, j;

    for (i = 1; i <= largeur_image(I); i++)
    {
        for (j = 1; j <= hauteur_image(I) && get_pixel_image(I, i, j) == BLANC; j++)
            ;
    }

    if (i == largeur_image(I) && j == hauteur_image(I))
    {

        printf("Erreur, image vide impossible de trouver le pixel de depart");
    }
    // else
    return set_point(i, j);
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

    switch (o)
    {
    case Nord:
        p = set_point(p.x, p.y);

    case Sud:
        p = set_point(p.x + 1, p.y + 1);

    case Est:
        p = set_point(p.x + 1, p.y);

    case Ouest:
        p = set_point(p.x, p.y + 1);
    }
    get_pixel_image(I, p.x, p.y);
}
Pixel valeur_pixel_gauche(Image I, Point p, Orientation o)
{

    switch (o)
    {
    case Nord:
        p = set_point(p.x + 1, p.y);

    case Sud:
        p = set_point(p.x + 1, p.y + 1);

    case Est:
        p = set_point(p.x + 1, p.y + 1);

    case Ouest:
        p = set_point(p.x, p.y);
    }
    get_pixel_image(I, p.x, p.y);
}

Orientation nouvelle_orientation(Image I, Point p, Orientation o)
{
    Pixel pG = valeur_pixel_gauche(I, p, o);
    Pixel pD = valeur_pixel_droite(I, p, o);
    if (pG == NOIR)
    {
        o += 1;
        o %= 4;
    }
    else if (pD == BLANC)
    {
        o += 3;
        o %= 4;
    }
    return o;
}

Liste_Point trouver_contour(Image I)
{
    Liste_Point l = creer_liste_Point_vide();
    Point pixel_depart = trouver_pixel_depart(I);
    Point depart = set_point(pixel_depart.x - 1, pixel_depart.y - 1);
    Point p = set_point(depart.x, depart.y);
    Orientation o = Est;
    int boucle = 0;
    while (boucle)
    {
        ajouter_element_liste_Point(l, p);
        p = avancer(p, o);
        o = nouvelle_orientation(I, p, o);

        if (p.x == depart.y && p.y == depart.y && o == Est)
        {
            boucle = 0;
        }
    }
    ajouter_element_liste_Point(l, p);
    return l;
}