#include "bezier.h"
#include "liste.h"
#include "segment.h"

#include <stdio.h>

int ecrire_eps_simplification_bezier3(Liste_Liste_Bezier3 l, Vecteur dimensions, char *fichier, int stroke);
int ecrire_eps_simplification_segment(Liste_Liste_Segment l, Vecteur dimensions, char *fichier, int stroke);
int ecrire_eps_simplification_bezier2(Liste_Liste_Bezier2 l, Vecteur dimensions, char *fichier, int stroke);