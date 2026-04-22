#ifndef _SEGMENT_H_
#define _SEGMENT_H_

#include "liste.h"
#include "geom2d.h"
DECL_LISTE(Segment);
DECL_LISTE(Liste_Segment);
Liste_Segment simplification_douglas_peucker(Liste_Point CONT, int j1, int j2, float d);

#endif