//Auteur : Solal Danton Laloy

/**
 * @file
 * @brief Ce fichier contient les déclarations des fonctions de la bibliothèque traitementCommande.h
 * Il fournit des fonctions pour le traitement de commandes qui permettent
 * la modélisation graphique à l'aide de Python Turtle.
 *
 * @author Solal
 * @date 29 janvier 2024
 */

#ifndef TRAITEMENTCOMMANDE_H
#define TRAITEMENTCOMMANDE_H

#include <stdio.h>
#include <stdlib.h>

void changementDeBase(int* coin_HD, int* milieu_bleu, int* milieu_jaune, int* milieu_orange);
void modeliserEnvironnement(char nomfichier[],int *coin_HD, int rayon_bleu, int rayon_jaune,int rayon_orange,int *milieu_bleu,int *milieu_jaune,int *milieu_orange);
void modeliserActions(char nomfichier[], char *mat[5][4], int mat_compt, int *coin_HD, int rayon_bleu, int rayon_jaune,int rayon_orange,int *milieu_bleu,int *milieu_jaune, int *milieu_orange);

#endif 
