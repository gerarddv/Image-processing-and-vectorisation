/****************************************************************************** 
  Interface extraction module
******************************************************************************/

#ifndef _EXTRACTION_CONTOUR_H_
#define _EXTRACTION_CONTOUR_H_
#include "image.h"
#include "geom2d.h"
#include "sequence.h"

typedef enum {Nord = 'N', Est = 'E', Sud = 'S', Ouest = 'O'} Orientation;

typedef struct Robot_
{
    double x, y;
    Orientation o;
} Robot;

int est_candidat(int x, int y, Image I);

Point pixel_candidat(Image I);

Image masque_pixel_candidat(Image I);

Robot tourner_droite(Robot r);

Robot tourner_gauche(Robot r);

Robot avancer(Robot r);

Pixel pixel_droite(Robot r, Image I);

Pixel pixel_gauche(Robot r, Image I);

Robot nouvelle_orientation(Robot r, Image I);

void parcours_contour(Image I);

Contour parcours_contour_vers_sequence(Image I);

Ensemble_Contours parcours_vers_contours(Image I);

void ecrire_contour_file(Contour C, char * a);

void ecrire_file_recapitulatif(Contour C, Image I, char * a);

#endif