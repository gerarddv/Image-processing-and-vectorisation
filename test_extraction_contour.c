/****************************************************************************** 
  Module test_extrac_contour
******************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "image.h"
#include "extraction_contour.h"
#include "sequence.h"
#include "geom2d.h"
#include "ecriture_eps.h"

int main(int argc, char * argv[])
{
    Image I;
    I = lire_fichier_image(argv[1]);
    Ensemble_Contours Ens1 = creer_ensemble_contours_vide();
    Ens1 = parcours_vers_contours(I);
    // ecrire_contour(Ens1.first->C);
    // ecrire_contour(Ens1.first->next->C);
    // ecrire_contour(Ens1.last->C);
    // printf("C.first = Inici=%p, Final=%p, tamany=%d \n", C.first, C.last, C.taille);
    // ecrire_contour(Ens.first->C);
    // ecrire_contour(Ens.first->next->C);
    // ecrire_contour(Ens.last->C);
    // //ecrire_contour(Ens.last->C);
    // // ecrire_contour(Ens.first->next->C);
    // //printf("Ens.first.c = Inici=%p, Final=%p, tamany=%d \n", Ens.first, Ens.last, Ens.nombre_contours);
    // //printf("Ens.first.c = Inici=%p, Final=%p, tamany=%d \n", Ens.first->C.first, Ens.first->C.last, Ens.first->C.taille);
    //ecrire_contour(Ens.first->C);
    printf("B\n");
    ecrire_ensemble_contours(Ens1);
    ecriture_eps_plusieurs_contours(Ens1, I, argv[1]);
    ecrire_file_recapitulatif_contours(Ens1, I,  argv[1]);
    //ecrire_many_contour_file(Ens1, argv[1]);
    printf("final prog\n");
    //ecrire_contour(*lc.first);
    //ecrire_plusieurs_contours(lc);
    //ecriture_eps(C, I, argv[1]);
    return 1;
}