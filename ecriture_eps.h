/****************************************************************************** 
  Interface du module ecriture_eps
******************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <string.h>
#include <stdio.h>

#include "image.h"
#include "geom2d.h"
#include "sequence.h"

#ifndef _ECRITURE_EPS_H_
#define _ECRITURE_EPS_H_
#define STROKE_MODE 0x01
#define FILL_MODE 0x02
#define OUTPUT_EPS_PATH "./FichiersEPS"
#define OUTPUT_TXT_PATH "./Fichierstxt"
#define INPUT_PATH "./IMAGES_TESTS"

void ecriture_entete(FILE *fp, Image I);

char * getFileName (char * pathname);

FILE * creation_fichier_eps(char * filename);

void ecriture_eps(int height, Cellule_Liste_Point *el, FILE * fp);

void ecriture_eps_plusieurs_contours(Ensemble_Contours Ens, Image I, char *filename);

#endif