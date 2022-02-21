/****************************************************************************** 
  Interface du module sequence
******************************************************************************/

#ifndef _SEQUENCE_H_
#define _SEQUENCE_H_

/*---- le type cellule de liste de point ----*/
typedef struct Cellule_Liste_Point_
{
	Point data;    /* donn�e de l'�l�ment de liste */
	struct Cellule_Liste_Point_* suiv; /* pointeur sur l'�l�ment suivant */
} Cellule_Liste_Point;

/*---- le type liste de point ----*/
typedef struct Liste_Point_
{
	unsigned int taille;        /* nombre d'�l�ments dans la liste */
	Cellule_Liste_Point *first; /* pointeur sur le premier �l�ment de la liste */
	Cellule_Liste_Point *last;  /* pointeur sur le dernier �l�ment de la liste */
	                       /* first = last = NULL et taille = 0 <=> liste vide */
} Liste_Point;

typedef Liste_Point Contour; /* type Contour = type Liste_Point */

typedef struct Contour_List_Element_
{
	Contour C;				/*Type COntour*/
	struct Contour_List_Element_ * next;  /*Pointeur sur le suivant*/
} Contour_List_Element;

/*---- le type liste de contours---*/
typedef struct Ensemble_Contours_
{
	unsigned int nombre_contours;        /* nombre d'�l�ments dans la liste */
	Contour_List_Element *first; /* pointeur sur le premier �l�ment de la liste */
	Contour_List_Element *last;  /* pointeur sur le dernier �l�ment de la liste */
	                       /* first = last = NULL et taille = 0 <=> liste vide */
} Ensemble_Contours;

/*---- le type tableau de point ----*/
typedef struct Tableau_Point_
{
	unsigned int taille; /* nombre d'�l�ments dans le tableau */
	Point *tab;          /* (pointeur vers) le tableau des �l�ments */
} Tableau_Point;


Cellule_Liste_Point *creer_element_liste_Point(Point v);

Liste_Point creer_liste_Point_vide();

Liste_Point ajouter_element_liste_Point(Liste_Point L, Point e);

Liste_Point supprimer_liste_Point(Liste_Point L);

Liste_Point concatener_liste_Point(Liste_Point L1, Liste_Point L2);

Tableau_Point sequence_points_liste_vers_tableau(Liste_Point L);

void ecrire_contour(Liste_Point L);

Contour_List_Element *creer_element_liste_Contours(Contour C);

Ensemble_Contours creer_ensemble_contours_vide();

Ensemble_Contours ajouter_element_Ensemble_Contours(Ensemble_Contours Ens, Contour C);

Ensemble_Contours supprimer_ensemble_Contours(Ensemble_Contours Ens);

Ensemble_Contours ajouter_element_Ensemble_Contours(Ensemble_Contours Ens, Contour C);

Ensemble_Contours supprimer_ensemble_Contours(Ensemble_Contours Ens);

void ecrire_ensemble_contours(Ensemble_Contours Ens);

#endif
