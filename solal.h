#ifndef IMAGE_PROCESS_H
#define IMAGE_PROCESS_H

#include <stdio.h>
#include <stdlib.h>

void actionsPy(char nomfichier[], char *mat[5][4], int mat_compt, int *coin_HD, int rayon_bleu, int rayon_jaune,int rayon_orange,int *milieu_bleu,int *milieu_jaune, int *milieu_orange);
void envPy(char nomfichier[],int *coin_HD, int rayon_bleu, int rayon_jaune,int rayon_orange,int *milieu_bleu,int *milieu_jaune,int *milieu_orange);

#endif 
