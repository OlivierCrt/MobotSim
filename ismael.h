#ifndef IMAGE_PROCESS_H
#define IMAGE_PROCESS_H

#include <stdio.h>
#include <stdlib.h>


double convertDouble(char *str);    //Fonction pour transformer des str en double.

void toLowercase(char *str);    //Fonction pour passer n'importe quelle chaine en minuscule.
    

typedef struct{    //Structure definissant les parametres qu'on cherche a obtenir a la fin du traitement de la phrase.
    char action[20];
    char param1[20];
    char param2[20];
    char type[20];
} ActionData;

//**Definition du FIFO des parametres**//

typedef struct node {    //Un noeud pour la file d'attente, contenant une donnée de type ActionData et un pointeur vers le noeud suivant.
    ActionData data;
    struct node* next;
} Node;

typedef struct {    //Une structure représentant un ordre de positionnement dans une file avec des pointeurs vers le premier (front) et le dernier élément (rear), ainsi qu'un entier pour stocker la taille de la file.
    Node* front;
    Node* rear;
    int size;
} Queue;

Queue createQueue(); //Initialise et renvoie une nouvelle file vide.
void enqueue(Queue* q, ActionData data); //Rajoute un élément à la file.
ActionData dequeue(Queue* q);   //Dégage un élément à la file.
int isQueueEmpty(Queue q);   //Fonction qui nous indiquera simplement si la file est vide ou pas et renvoie 1 pour un front NULL.

int str_to_num_fr(char *nombre);    //Retournera un entier en fonction du str qui lui correspond.
int str_to_num_es(char *nombre);  

int num_to_chiffre_tot_fr(char *str);   //Utilisera les chiffres obtenus séparement pour les traiter après et obtenir le chiffre total.
int num_to_chiffre_tot_es(char *str);

bool detect_chiffre_fr(const char *word);    //Fonction ayant le role de détecter si le str introduit corréspond à un chiffre. 
bool detect_chiffre_es(const char *word);

void afficher_Action_fr(char *phrase, Queue* q);
void afficher_Action_es(char *phrase, Queue* q);

#endif
    
