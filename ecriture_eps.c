/******************************************************************************
  Impl�mentation du module extraction_contour
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <stdio.h>

#include "image.h"
#include "geom2d.h"
#include "sequence.h"
#include "ecriture_eps.h"

void ecriture_entete(FILE *fp, Image I)
{
    fprintf(fp, "%%!PS-Adobe-3.0 EPSF-3.0\n"); // création entete
    fprintf(fp, "%%%%BoundingBox: %d %d %d %d\n", 0, 0, I.L, I.H);
}

char * getFileName ( char * pathname ) {
    return (strrchr(pathname, '/')+1);
}

FILE *creation_fichier_eps(char *filename)
{
    char name[50] = "";
    // strcpy(name, filename);
    // strcat(name, ".eps");
    sprintf(name,"%s/%s.eps", OUTPUT_EPS_PATH, getFileName(filename));
    printf("name is :%s\n",name);
    return fopen(name, "w");
}

void ecriture_eps(int height, Cellule_Liste_Point *el, FILE *fp)
{
    fprintf(fp, "%f %f moveto\n", (el->data.x), (height - (el->data.y)));
    while (!(el->suiv == NULL))
    {
        el = el->suiv;
        fprintf(fp, "%f %f lineto\n", (el->data.x), (height - (el->data.y)));
    }
}

void ecriture_eps_plusieurs_contours(Ensemble_Contours Ens, Image I, char *filename)
{
    int mode;
    Contour_List_Element *cell = Ens.first;
    Cellule_Liste_Point *el = cell->C.first;
    FILE *fp = creation_fichier_eps(filename);

    ecriture_entete(fp, I);
    printf("Donnez une valeur, 1 pour stoke et 2 pour fill:");
    scanf("%d", &mode);
    while (cell) // while cell!=NULL
    {
        el = cell->C.first;
        ecriture_eps(I.H, el, fp);
        fprintf(fp, "\n");
        cell = cell->next;
    }
    if (mode == STROKE_MODE)
    {
        fprintf(fp, "stroke\n");
    }
    if (mode == FILL_MODE)
    {
        fprintf(fp, "fill\n");
    }
    fprintf(fp, "showpage\n");
    printf("n\n");
}