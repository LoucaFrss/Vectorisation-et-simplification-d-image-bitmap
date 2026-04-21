#include "image.h"
#include "geom2d.h"
#include "liste.h"
#include <stdlib.h>

typedef enum
{
    Nord,
    Ouest,
    Sud,
    Est,
} Orientation;

Point trouver_pixel_depart(Image I);

Liste_Liste_Point trouver_contours_multiple(Image I);

Image image_masque(Image I);