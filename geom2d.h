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

typedef struct Segment_ {
    Point A, B; /*Coordonnees*/
} Segment;

/*creer un point de coord x et y*/
Point set_point(double x, double y);

/*somme de deux points*/
Point add_point(Point P1, Point P2);

/*subtraction deux points*/
Point sub_point(Point P1, Point P2);

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

/*création d'un segment avec deux points*/
Segment set_segment(Point A, Point B);

/*calcul du reel lambda*/
double calcul_lambda(Segment S, Point P);

/*calcul point droite*/
Point calcul_point_droite(Segment S, double reel);

/*distance point segment*/
double distance_point_segment(Point P, Segment S);

#endif