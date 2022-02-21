/****************************************************************************** 
  Implementation Module Geometrie en 2D
******************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "geom2d.h"
/*dernière modification 25/01/2022 */
/*creer un point de coord x et y*/
Point set_point(double x, double y)
{
    Point P;
    P.x = x; 
    P.y = y;
    return P;
}

/*somme de deux points*/
Point add_point(Point P1, Point P2)
{
    Point P3;
    P3.x = P1.x + P2.x;
    P3.y = P1.y + P2.y;
    return P3;
}

/*vecteur entre deux points A et B, càd A->B*/
Vecteur vect_bipoint(Point A, Point B)
{
    Vecteur V;
    V.x = (B.x - A.x);
    V.y = (B.y - A.y);
    return V;
}

/*produit point par scalaire*/
Point produit_point_scalaire(Point P, double a)
{
    Point R;
    R.x = a*P.x;
    R.y = a*P.y;
    return R;
}

/*produit vecteur par scalaire*/
Vecteur produit_vect_scalaire(Vecteur V, double a)
{
    Vecteur U;
    U.x = a*V.x;
    U.y = a*V.y;
    return U;
}

/*produit scalaire entre deux vecteurs*/
double produit_scalaire_vecteurs(Vecteur V, Vecteur U)
{
    return V.x*U.x + V.y*U.y;
}

/*norme eucledienne vecteurs*/
double norme_vecteur(Vecteur V)
{
    return sqrt(pow(V.x, 2.0)+pow(V.y, 2.0));
}

/*distance deux points*/
double distance_deux_points(Point A, Point B){
    return sqrt(pow((A.x-B.x),2.0)+pow((A.y-B.y),2));
}