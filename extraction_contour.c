/******************************************************************************
  Impl�mentation du module extraction_contour
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <stdio.h>

#include "image.h"
#include "extraction_contour.h"
#include "sequence.h"
#include "geom2d.h"
#include "ecriture_eps.h"

int est_candidat(int x, int y, Image I)
{
    if ((get_pixel_image(I, x, y) == NOIR) && ((get_pixel_image(I, x, y - 1) == BLANC) || (y - 1 <= 0)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

Point pixel_candidat(Image I)
{
    int x, y, cond = 0;
    Point P; // = set_point(-10, -10);
    while (cond == 0)
    {
        for (y = 1; y <= I.H; y++)
        {
            for (x = 1; x <= I.L; x++)
            {
                if (est_candidat(x, y, I))
                {
                    P.x = x - 1;
                    P.y = y - 1;
                    return P;
                }
            }
        }
    }
    fprintf(stderr, "Point pixel_candidat : Pixel candidat inexistant\n");
    exit(0);
}

Image masque_pixel_candidat(Image I)
{
    Image M = creer_image(I.L, I.H);
    int x, y;
    for (y = 1; y <= I.H; y++)
    {
        for (x = 1; x <= I.L; x++)
        {
            if (est_candidat(x, y, I))
            {
                set_pixel_image(M, x, y, get_pixel_image(I, x, y)); // on recopie le pixel candidat de I dans le masque M
            }
        }
    }
    return M;
}

Robot tourner_droite(Robot r)
{
    switch (r.o)
    {
    case Nord:
        r.o = Est;
        return r;
    case Est:
        r.o = Sud;
        return r;
    case Sud:
        r.o = Ouest;
        return r;
    case Ouest:
        r.o = Nord;
        return r;
    }
}

Robot tourner_gauche(Robot r)
{
    switch (r.o)
    {
    case Nord:
        r.o = Ouest;
        return r;
    case Ouest:
        r.o = Sud;
        return r;
    case Sud:
        r.o = Est;
        return r;
    case Est:
        r.o = Nord;
        return r;
    }
    return r;
}

Robot avancer(Robot r)
{
    switch (r.o)
    {
    case Nord:
        r.y = r.y - 1;
        return r;
    case Ouest:
        r.x = r.x - 1;
        return r;
    case Sud:
        r.y = r.y + 1;
        return r;
    case Est:
        r.x = r.x + 1;
        return r;
    }
}

Pixel pixel_droite(Robot r, Image I)
{
    Pixel P;
    switch (r.o)
    {
    case Nord:
        P = get_pixel_image(I, r.x + 1, r.y);
        return P;
    case Ouest:
        P = get_pixel_image(I, r.x, r.y);
        return P;
    case Sud:
        P = get_pixel_image(I, r.x, r.y + 1);
        return P;
    case Est:
        P = get_pixel_image(I, r.x + 1, r.y + 1);
        return P;
    }
}

Pixel pixel_gauche(Robot r, Image I)
{
    Pixel P;
    switch (r.o)
    {
    case Nord:
        P = get_pixel_image(I, r.x, r.y);
        return P;
    case Ouest:
        P = get_pixel_image(I, r.x, r.y + 1);
        return P;
    case Sud:
        P = get_pixel_image(I, r.x + 1, r.y + 1);
        return P;
    case Est:
        P = get_pixel_image(I, r.x + 1, r.y);
        return P;
    }
}

Robot nouvelle_orientation(Robot r, Image I)
{
    Pixel PG = pixel_gauche(r, I);
    Pixel PD = pixel_droite(r, I);
    if (PG == NOIR)
    {
        r = tourner_gauche(r);
    }
    else if (PD == BLANC)
    {
        r = tourner_droite(r);
    }
    else
    {
        r.o = r.o;
    }
    return r;
}

void parcours_contour(Image I)
{
    Robot r;
    double x, y;
    int cond = 1, nbpoints = 1;
    Point P = pixel_candidat(I);
    r.x = P.x;
    r.y = P.y;
    r.o = Est;
    x = r.x;
    y = r.y;
    printf("pixel candidat/position depart: %f %f\n", P.x, P.y);
    printf("points du contour: \n");
    printf("(%f,%f)", r.x, r.y);
    while (cond == 1)
    {
        r = avancer(r);
        printf("(%f,%f)", r.x, r.y);
        r = nouvelle_orientation(r, I);
        if (((x == r.x) && (y == r.y)) && (r.o == Est))
        {
            cond = 0;
        }
        nbpoints++;
    }
    printf("\n");
    printf(" 1 contour avec %d segments\n", nbpoints - 1);
}

Contour parcours_contour_vers_sequence(Image I)
{
    Robot r;
    Point e, P = pixel_candidat(I);
    Contour C = creer_liste_Point_vide();
    int cond = 1;
    r.x = P.x;
    r.y = P.y;
    r.o = Est;
    e = set_point(r.x, r.y);
    C = ajouter_element_liste_Point(C, e);
    while (cond == 1)
    {
        r = avancer(r);
        e = set_point(r.x, r.y);
        C = ajouter_element_liste_Point(C, e);
        r = nouvelle_orientation(r, I);
        if (((C.first->data.x == r.x) && (C.first->data.y == r.y)) && (r.o == Est))
        {
            cond = 0;
        }
    }
    printf("\n");
    printf(" 1 contour avec %d segments\n", C.taille - 1);
    return C;
}

Ensemble_Contours parcours_vers_contours(Image I)
{
    Image M = masque_pixel_candidat(I);
    Ensemble_Contours Ens = creer_ensemble_contours_vide();
    int points = 0;
    while (est_vide(M) == 0)
    {
        Robot r;
        Point e, P = pixel_candidat(M);
        Contour C = creer_liste_Point_vide();
        // C = supprimer_liste_Point(C);
        int cond = 1;
        r.x = P.x;
        r.y = P.y;
        r.o = Est;
        e = set_point(r.x, r.y);
        C = ajouter_element_liste_Point(C, e);
        while (cond == 1)
        {
            if (r.o == Est)
            {
                set_pixel_image(M, r.x + 1, r.y + 1, BLANC);
            }
            r = avancer(r);
            e = set_point(r.x, r.y);
            C = ajouter_element_liste_Point(C, e);
            r = nouvelle_orientation(r, I);
            if (((C.first->data.x == r.x) && (C.first->data.y == r.y)) && (r.o == Est))
            {
                cond = 0;
            }
        }
        printf("\n");
        printf(" 1 contour avec %d segments\n", C.taille - 1);
        points += C.taille;
        ecrire_contour(C);
        Ens = ajouter_element_Ensemble_Contours(Ens, C);
        // ecrire_contour(Ens.first->C);
        // ecrire_ensemble_contours(Ens);
        // C = supprimer_liste_Point(C);
    }
    printf(" %d contours avec %d segments\n", Ens.nombre_contours, points - Ens.nombre_contours);
    return Ens;
}

FILE *creation_fichier_txt(char *filename)
{
    char name[50] = "";
    // strcpy(name, filename);
    // strcat(name, ".eps");
    sprintf(name,"%s/%s.txt", OUTPUT_TXT_PATH, getFileName(filename));
    printf("name is :%s\n",name);
    return fopen(name, "w");
}

void ecrire_contour_file(Cellule_Liste_Point *el, FILE * f)
{
    while (el)
    {
        fprintf(f, "%f %f\n", el->data.x, el->data.y);
        el = el->suiv;
    }
}

void ecrire_many_contour_file(Ensemble_Contours Ens, char * filename)
{
    int points = 0;
    FILE *f = creation_fichier_txt(filename);
    Contour_List_Element *el = Ens.first;
    fprintf(f, "Contours : %d\n\n", Ens.nombre_contours);
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    while(el)
    {
        points += el->C.taille; //somme des points pour chaque contour
        ecrire_contour_file(el->C.first, f);
        fprintf(f, "\n");
        el = el->next;
    }
    fprintf(f, "Segments: %d\nPoints: %d\n", points - Ens.nombre_contours, points);
    fclose(f);
}

void ecrire_file_recapitulatif(Contour C, Image I, char *a)
{
    FILE *fp = fopen("resultats-tache3-2.txt", "a");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    int contours = 1;
    fprintf(fp, "File: %s Largeur: %d Hauteur: %d Segments: %d\n", a, I.L, I.H, C.taille - contours);
    fclose(fp);
}

void ecrire_file_recapitulatif_contours(Ensemble_Contours Ens, Image I, char *a)
{
    FILE *fp = fopen("resultats-tache5-1.txt", "a");
    int points = 0;
    Contour_List_Element *el = Ens.first;
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    while(el)
    {
        points += el->C.taille; //somme des points pour chaque contour
        el = el->next;
    }
    fprintf(fp, "PBM Filename: [%s] (X lenght, Y lenght): (%d, %d) Contours: (%d) Segments: (%d)\n", a, I.L, I.H, Ens.nombre_contours, points - Ens.nombre_contours);
    fclose(fp);
}