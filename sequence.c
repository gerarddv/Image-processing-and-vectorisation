#include <stdio.h>	/* utilisation des entr�es-sorties standard de C */
#include <stdlib.h> /* utilisation des fonctions malloc et free */

#include "geom2d.h"
#include "sequence.h"

/* cr�er une cellule de liste avec l'�l�ment v
   renvoie le pointeur sur la cellule de liste cr��e
   la fonction s'arrete si la cr�ation n'a pas pu se faire */
Cellule_Liste_Point *creer_element_liste_Point(Point v)
{
	Cellule_Liste_Point *el;
	el = (Cellule_Liste_Point *)malloc(sizeof(Cellule_Liste_Point));
	if (el == NULL)
	{
		fprintf(stderr, "creer_element_liste_Point : allocation impossible\n");
		exit(-1);
	}
	el->data = v;
	el->suiv = NULL;
	return el;
}

/* cr�er une liste vide */
Liste_Point creer_liste_Point_vide()
{
	Liste_Point L = {0, NULL, NULL};
	return L;
}

/* ajouter l'�l�ment e en fin de la liste L, renvoie la liste L modifi�e */
Liste_Point ajouter_element_liste_Point(Liste_Point L, Point e)
{
	Cellule_Liste_Point *el;

	el = creer_element_liste_Point(e);
	if (L.taille == 0)
	{
		/* premier �l�ment de la liste */
		L.first = L.last = el;
	}
	else
	{
		L.last->suiv = el;
		L.last = el;
	}
	L.taille++;
	return L;
}

/* suppression de tous les �l�ments de la liste, renvoie la liste L vide */
Liste_Point supprimer_liste_Point(Liste_Point L)
{
	Cellule_Liste_Point *el = L.first;

	while (el)
	{
		Cellule_Liste_Point *suiv = el->suiv;
		free(el);
		el = suiv;
	}
	L.first = L.last = NULL;
	L.taille = 0;
	return L;
}

/* concat�ne L2 � la suite de L1, renvoie la liste L1 modifi�e */
Liste_Point concatener_liste_Point(Liste_Point L1, Liste_Point L2)
{
	/* cas o� l'une des deux listes est vide */
	if (L1.taille == 0)
		return L2;
	if (L2.taille == 0)
		return L1;

	/* les deux listes sont non vides */
	L1.last->suiv = L2.first; /* lien entre L1.last et L2.first */
	L1.last = L2.last;		  /* le dernier �l�ment de L1 est celui de L2 */
	L1.taille += L2.taille;	  /* nouvelle taille pour L1 */
	return L1;
}

/* cr�er une s�quence de points sous forme d'un tableau de points
   � partir de la liste de points L */
Tableau_Point sequence_points_liste_vers_tableau(Liste_Point L)
{
	Tableau_Point T;
	/* taille de T = taille de L */
	T.taille = L.taille;

	/* allocation dynamique du tableau de Point */
	T.tab = malloc(sizeof(Point) * T.taille);

	if (T.tab == NULL)
	{
		/* allocation impossible : arret du programme avec un message */
		fprintf(stderr, "sequence_points_liste_vers_tableau : ");
		fprintf(stderr, " allocation impossible\n");
		exit(-1);
	}

	/* remplir le tableau de points T en parcourant la liste L */
	int k = 0;						   /* indice de l'�l�ment dans T.tab */
	Cellule_Liste_Point *el = L.first; /* pointeur sur l'�l�ment dans L */
	while (el)
	{
		T.tab[k] = el->data;
		k++;		   /* incr�menter k */
		el = el->suiv; /* passer � l'�lement suivant dans la liste chainee */
	}
	return T;
}

/* �crire le contour L � l'�cran
   cette fonction montre un exemple de conversion d'une liste de points en
   tableau de points afin de pouvoir par la suite acc�der aux �l�ments d'une
   s�quence de points par indice */
void ecrire_contour(Liste_Point L)
{
	//printf("Init\n");
	Tableau_Point TP = sequence_points_liste_vers_tableau(L);
	int k;
	int nP = TP.taille;
	printf("-------------------------------------------------------------------------------------------------------------\n");
	printf("%d points : [", nP);
	for (k = 0; k < nP; k++)
	{
		Point P = TP.tab[k]; /* r�cup�rer le point d'indice k */
		printf(" (%5.1f,%5.1f)", P.x, P.y);
	}
	printf("]\n");
	printf("-------------------------------------------------------------------------------------------------------------\n");
	free(TP.tab); /* supprimer le tableau de point TP */
}

/*créer cellule de la liste de contour*/
Contour_List_Element *creer_element_liste_Contours(Contour C)
{
	Contour_List_Element *el;
	el = (Contour_List_Element *)malloc(sizeof(Contour_List_Element));
	if (el == NULL)
	{
		fprintf(stderr, "creer_element_liste_Point : allocation impossible\n");
		exit(-1);
	}
	el->C = C;
	el->next = NULL;
	return el;
}

/* cr�er une liste vide */
Ensemble_Contours creer_ensemble_contours_vide()
{
	Ensemble_Contours Ens = {0, NULL, NULL};
	return Ens;
}

/* ajouter l'�l�ment e en fin de la liste L, renvoie la liste L modifi�e */
Ensemble_Contours ajouter_element_Ensemble_Contours(Ensemble_Contours Ens, Contour C)
{
	Contour_List_Element *el;
	el = creer_element_liste_Contours(C);
	//printf("el->C: pointer el first: %p pointer el last: %p sizeof el contour: %d\n", el->C.first, el->C.last, el->C.taille);
	//printf("Capsule adress: %p\n", el);
	if (Ens.nombre_contours == 0)
	{
		/* premier �l�ment de la liste */
		Ens.first = Ens.last = el;
	}
	else
	{
		Ens.last->next = el;
		Ens.last = el;
	}
	Ens.nombre_contours++;
	return Ens;
}

/* suppression de tous les �l�ments de la liste, renvoie la liste L vide */
Ensemble_Contours supprimer_ensemble_Contours(Ensemble_Contours Ens)
{
	Contour_List_Element *el = Ens.first;

	while (el)
	{
		Contour_List_Element *next = el->next;
		free(el);
		el = next;
	}
	Ens.first = Ens.last = NULL;
	Ens.nombre_contours = 0;
	return Ens;
}

void ecrire_ensemble_contours(Ensemble_Contours Ens)
{
	int i = 1;
	Contour_List_Element *el = Ens.first;
	while (el)
	{
		printf("Contour %d: ", i);
		ecrire_contour(el->C);
		el = el->next;
		i++;
	}
}

// int main()
// {
// 	Contour C1,C2;

// 	/* initialiser C1 comme contour vide */
// 	C1 = creer_liste_Point_vide();
// 	printf("C1 : "); ecrire_contour(C1);

// 	/* ajouter les points (5,3),(3,1),(7,2) et (1,6) dans C1 */
// 	C1 = ajouter_element_liste_Point(C1, set_point(5,3));
// 	C1 = ajouter_element_liste_Point(C1, set_point(3,1));
// 	C1 = ajouter_element_liste_Point(C1, set_point(7,2));
// 	C1 = ajouter_element_liste_Point(C1, set_point(1,6));
// 	printf("C1 : "); ecrire_contour(C1);

// 	/* ajouter le point (4,1) dans C1 */
// 	C1 = ajouter_element_liste_Point(C1, set_point(4,1));
// 	printf("C1 : "); ecrire_contour(C1);

// 	/* cr�er le contour C2 avec les points (9,5) et (5,7) */
// 	C2 = creer_liste_Point_vide();
// 	C2 = ajouter_element_liste_Point(C2, set_point(9,5));
// 	C2 = ajouter_element_liste_Point(C2, set_point(5,7));
// 	printf("C2 : "); ecrire_contour(C2);

// 	/* concat�ner C2 � la suite de C1 */
// 	C1 = concatener_liste_Point(C1,C2);
// 	printf("C1 : "); ecrire_contour(C1);

// 	/* supprimer le contour C1 */
// 	C1 = supprimer_liste_Point(C1);
// 	printf("C1 : "); ecrire_contour(C1);
// } // fin du programme
