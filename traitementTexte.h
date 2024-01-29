// Auteur Ismael Monge Rouchdi

/**
 * @file
 * @brief Ce fichier contient les déclarations des fonctions de la bibliothèque traitementTexte.h
 * Il fournit des fonctions pour le traitement de texte
 * 
 * @author Ismaël
 * @date 29 janvier 2024
 */

#ifndef TRAITEMENTTEXTE_H
#define TRAITEMENTTEXTE_H

#include "string.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"

typedef struct {
    char action[20];
    char param1[20];
    char param2[20];
    char type[20];
}ActionData;

typedef struct node {
    ActionData data;
    struct node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
    int size;
} Queue;

double convertDouble(char *str);
void toLowercase(char *str);

Queue createQueue();
void enqueue(Queue* q, ActionData data);
ActionData dequeue(Queue* q);
int isQueueEmpty(Queue q);

int str_to_num_fr(char *nombre);
int str_to_num_es(char *nombre);

int num_to_chiffre_tot_fr(char *str);
int num_to_chiffre_tot_es(char *str);

bool detect_chiffre_fr(const char *word);
bool detect_chiffre_es(const char *word);

void afficher_Action_fr(char *phrase, Queue* q);
void afficher_Action_es(char *phrase, Queue* q);
#endif
