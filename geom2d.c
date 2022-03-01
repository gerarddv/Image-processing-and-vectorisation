/******************************************************************************
  Implementation Module Geometrie en 2D
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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

/*subtraction deux points*/
Point sub_point(Point P1, Point P2)
{
    Point P;
    P.x = P1.x - P2.x;
    P.y = P1.y - P2.y;
    return P;
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
    R.x = a * P.x;
    R.y = a * P.y;
    return R;
}

/*produit vecteur par scalaire*/
Vecteur produit_vect_scalaire(Vecteur V, double a)
{
    Vecteur U;
    U.x = a * V.x;
    U.y = a * V.y;
    return U;
}

/*produit scalaire entre deux vecteurs*/
double produit_scalaire_vecteurs(Vecteur V, Vecteur U)
{
    return V.x * U.x + V.y * U.y;
}

/*norme eucledienne vecteurs*/
double norme_vecteur(Vecteur V)
{
    return sqrt(pow(V.x, 2.0) + pow(V.y, 2.0));
}

/*distance deux points*/
double distance_deux_points(Point A, Point B)
{
    return sqrt(pow((A.x - B.x), 2.0) + pow((A.y - B.y), 2));
}

/*création d'un segment avec deux points*/
Segment set_segment(Point A, Point B)
{
    Segment S;
    S.A = A;  //origine
    S.B = B;  //fin
    return S;
}

/*calcul du reel lambda*/
double calcul_lambda(Segment S, Point P)
{
    return ((produit_scalaire_vecteurs(vect_bipoint(S.A, P), vect_bipoint(S.A, S.B))) / produit_scalaire_vecteurs(vect_bipoint(S.A, S.B), vect_bipoint(S.A, S.B)));
}

/*calcul point droite*/
Point calcul_point_droite(Segment S, double reel)
{
    return add_point(S.A, produit_point_scalaire(sub_point(S.B, S.A), reel));  // Q = A + reel*(B-A)
}

/*distance point segment*/
double distance_point_segment(Point P, Segment S)
{
    double d = 0;
    double reel = calcul_lambda(S, P);
    if ((S.A.x == S.B.x) && (S.A.y == S.B.y))
    {
        d = distance_deux_points(S.A, P);
    }
    else
    {
        if ((0 <= reel) && (reel <= 1))
        {
            d = distance_deux_points(calcul_point_droite(S, reel), P); //distance de point Q au segment
        }
        else if (reel < 0)
        {
            d = distance_deux_points(S.A, P); //distance de point A au P
        }
        else if (reel > 1)
        {
            d = distance_deux_points(S.B, P); //distance de point B au P
        }
    }
    return d;
}