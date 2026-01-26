#include "image.h"
#include "geom2d.h"
#include "sequence_point.h"

typedef enum
{
    Nord,
    Ouest,
    Sud,
    Est,
} Orientation;

Point trouver_pixel_depart(Image I);

Liste_Point trouver_contour(Image I);