#include <stdio.h>
#include <stdlib.h>

typedef struct Groupe_Pixel_s * Groupe_Pixel_ptr ;
Groupe_Pixel_ptr detecterPixelsJaune(int **matriceR, int ** matriceG, int ** matriceB,int hauteur , int largeur);
int * trouver_milieu(Groupe_Pixel_ptr objet, int largeur , int hauteur) ;
char* get_couleur(Groupe_Pixel_ptr objet);
Groupe_Pixel_ptr detecterPixelsBleu(int **matriceR, int ** matriceG, int ** matriceB,int hauteur , int largeur);
Groupe_Pixel_ptr alloc_Groupe_Pixel(int nbp , int** matrice_ass_param,char * couleur) ;
Groupe_Pixel_ptr detecterPixelsOrange(int **matriceR, int ** matriceG, int ** matriceB,int hauteur , int largeur);
bool isObjet(Groupe_Pixel_ptr groupe);
void ecrireMatriceDansFichier(Groupe_Pixel_ptr groupePixel, int hauteur, int largeur,char*nomfichier);
int dfs (int ** matrice_p , int hauteur , int largeur , int deb_i , int deb_j ,int ** visite);
void trouverLePlusGros (int ** matrice , int hauteur, int largeur);
int  trouver_rayon(Groupe_Pixel_ptr objet, int largeur , int hauteur);