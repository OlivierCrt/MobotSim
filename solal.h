#ifndef SOLAL_H
#define SOLAL_H

#include <stdio.h>
#include <stdlib.h>

void changementDeBase(int* coin_HD, int* milieu_bleu, int* milieu_jaune, int* milieu_orange);
void modeliserEnvironnement(char nomfichier[],int *coin_HD, int rayon_bleu, int rayon_jaune,int rayon_orange,int *milieu_bleu,int *milieu_jaune,int *milieu_orange);
void modeliserActions(char nomfichier[], char *mat[5][4], int mat_compt, int *coin_HD, int rayon_bleu, int rayon_jaune,int rayon_orange,int *milieu_bleu,int *milieu_jaune, int *milieu_orange);

#endif 
