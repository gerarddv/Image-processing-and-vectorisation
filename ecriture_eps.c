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

void ecriture_entete(FILE *fp, Image I)
{
    fprintf(fp, "%%!PS-Adobe-3.0 EPSF-3.0\n"); // création entete
    fprintf(fp, "%%%%BoundingBox: %d %d %d %d\n", 0, 0, I.L, I.H);
}

void ecriture_eps(Contour C, Image I, char *a)
{
    char name[50];
    strcpy(name, a);
    strcat(name, ".eps");
    FILE *fp = fopen(name, "w");
    ecriture_entete(fp, I);
    int mode;
    Cellule_Liste_Point *el;
    el = C.first;
    printf("Donnez une valeur, 1 pour stoke et 2 pour fill:");
    scanf("%d", &mode);
    if (mode == 1)
    {
        fprintf(fp, "newpath\n");
        fprintf(fp, "%f %f moveto\n", (el->data.x), (I.H - (el->data.y)));
        while (!(el->suiv == NULL))
        {
            el = el->suiv;
            fprintf(fp, "%f %f lineto\n", (el->data.x), (I.H - (el->data.y)));
        }
        fprintf(fp, "stroke\n");
    }
    else if (mode == 2)
    {
        fprintf(fp, "newpath\n");
        fprintf(fp, "%f %f moveto\n", (el->data.x), (I.H - (el->data.y)));
        while (!(el->suiv == NULL))
        {
            el = el->suiv;
            fprintf(fp, "%f %f lineto\n", (el->data.x), (I.H - (el->data.y)));
        }
        fprintf(fp, "fill\n");
    }
    fprintf(fp, "showpage\n");
}

void ecriture_eps_plusieurs_contours(Ensemble_Contours Ens, Image I, char *a)
{
    char name[50];
    strcpy(name, a);
    strcat(name, ".eps");
    FILE *fp = fopen(name, "w");
    ecriture_entete(fp, I);
    int mode;
    Contour_List_Element *cell;
    cell = Ens.first;
    Cellule_Liste_Point *el;
    el = cell->C.first;
    printf("Donnez une valeur, 1 pour stoke et 2 pour fill:");
    scanf("%d", &mode);
    while (cell)    //while cell!=NULL
    {
        el = cell->C.first;
        if (mode == 1)
        {
            fprintf(fp, "newpath\n");
            fprintf(fp, "%f %f moveto\n", (el->data.x), (I.H - (el->data.y)));
            while (!(el->suiv == NULL))
            {
                el = el->suiv;
                fprintf(fp, "%f %f lineto\n", (el->data.x), (I.H - (el->data.y)));
            }
            fprintf(fp, "stroke\n");
        }
        else if (mode == 2)
        {
            fprintf(fp, "newpath\n");
            fprintf(fp, "%f %f moveto\n", (el->data.x), (I.H - (el->data.y)));
            while (!(el->suiv == NULL))
            {
                el = el->suiv;
                fprintf(fp, "%f %f lineto\n", (el->data.x), (I.H - (el->data.y)));
            }
            fprintf(fp, "fill\n");
        }
        printf("n\n");
        cell = cell->next;
    }
    fprintf(fp, "showpage\n");
}