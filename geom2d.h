/****************************************************************************** 
  Interface Module Geometrie en 2D
******************************************************************************/
#ifndef _GEOM2D_H_
#define _GEOM2D_H_

typedef struct Vecteur_ {
    double x, y; /*coord du vecteur*/
} Vecteur;

typedef struct Point_ {
    double x, y; /*coord du point*/
} Point;

/*creer un point de coord x et y*/
Point set_point(double x, double y);

/*somme de deux points*/
Point add_point(Point P1, Point P2);

/*vecteur entre deux points A et B*/
Vecteur vect_bipoint(Point A, Point B);

/*produit point par scalaire*/
Point produit_point_scalaire(Point P, double a);

/*produit vecteur par scalaire*/
Vecteur produit_vect_scalaire(Vecteur V, double a);

/*produit scalaire entre deux vecteurs*/
double produit_scalaire_vecteurs(Vecteur V, Vecteur U);

/*norme eucledienne vecteurs*/
double norme_vecteur(Vecteur V);

/*distance deux points*/
double distance_deux_points(Point A, Point B);
#endif