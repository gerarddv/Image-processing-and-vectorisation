#include <stdio.h>
#include <string.h>
#include <math.h>
#include "geom2d.h"

int main(int argc, char *argv[])
{
    FILE *fp = fopen(argv[1], "r");
    float x = 0, y=0;

    fscanf(fp, "%f %f", &x, &y);
    Point A = set_point(x, y);
    printf("Point A: %f %f\n", A.x, A.y);

    fscanf(fp, "%f %f", &x, &y);
    Point B = set_point(x, y);
    printf("Point B: %f %f\n", B.x, B.y);

    fscanf(fp, "%f %f", &x, &y);
    Point P = set_point(x, y);
    printf("Point P: %f %f\n", P.x, P.y);

    double a = produit_scalaire_vecteurs(vect_bipoint(A,P), vect_bipoint(A,B));
    printf("prod vect 1: %f\n",a);
    a = produit_scalaire_vecteurs(vect_bipoint(A,B), vect_bipoint(A,B));
    printf("prod vect 2: %f\n",a);
    Segment S = set_segment(A,B);
    a = produit_scalaire_vecteurs(vect_bipoint(S.A,P), vect_bipoint(S.A,S.B));
    printf("prod vect 1 avec seg: %f\n",a);
    a = produit_scalaire_vecteurs(vect_bipoint(S.A,S.B), vect_bipoint(S.A,S.B));
    printf("prod vect 2 avec seg: %f\n",a);

    printf("Segment S: A: [%f %f] B: [%f %f]\n", S.A.x, S.A.y, S.B.x, S.B.y);
    double lambda = calcul_lambda(S, P);
    printf("Lambda: %f\n",lambda);
    Point Q = calcul_point_droite(S, lambda);
    printf("Point Q: %f %f\n", Q.x, Q.y);
    double dist = distance_point_segment(P, S);
    printf("distance: %f\n",dist);
    return 0;
}