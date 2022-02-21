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


void ecriture_entete(FILE *fp, Image I);

void ecriture_eps(Contour C, Image I, char * a);

#endif