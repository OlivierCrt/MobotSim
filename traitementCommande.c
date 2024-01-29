// Auteur : Solal Danton Laloy

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "traitementCommande.h"

/**
 * @file
 * @brief Ce fichier rassemble les fonctions nécessaires pour le traitement de commandes.
*/

/**
 * @defgroup gtrait Traitement de commmandes
 * @brief Fonctions nécessaires pour le traitement de commandes. Transforment les informations envoyées par les traitements d'images et de textes en fonctions python qui permettent une modélisation graphique.  
 * @{
 * 
*/

/**
 * @brief Fonction qui permet de changer les coordonnées de la base de l'image vers la base de la modélisation Python Turtle
 * @param coin_HD à deux dimension correspondant à la matrice initiale du Rouge.
 * @param milieu_bleu Tableau à deux dimension correspondant à la matrice initiale du Vert.
 * @param milieu_jaune Tableau à deux dimension correspondant à la matrice initiale du Bleu.
 * @param milieu_orange Hauteur de l'image iniatiale/tableau.
*/

void changementDeBase(int* coin_HD, int* milieu_bleu, int* milieu_jaune, int* milieu_orange) {
    int recentrage_x = coin_HD[0] / 2;
    int recentrage_y = coin_HD[1] / 2;

    coin_HD[0] -= recentrage_x;
    coin_HD[1] -= recentrage_y;

    milieu_bleu[0] -= recentrage_x;
    milieu_bleu[1] = -milieu_bleu[1] + recentrage_y;

    milieu_jaune[0] -= recentrage_x;
    milieu_jaune[1] = -milieu_jaune[1] + recentrage_y;

    milieu_orange[0] -= recentrage_x;
    milieu_orange[1] = -milieu_orange[1] + recentrage_y;
}

/**
 * @brief Fonction qui prends en entrée les informations connues sur l'environnement. Puis, les transforme en appels de fonctions python qui s'éxecutent pour modéliser l'environnement.
 * @param nomfichier chemin d'accès de l'image que l'on modélise
 * @param coin_HD duo d'entiers correspondants aux coordonnées (x,y) du coin droit de l'image que l'on modélise
 * @param rayon_bleu entier correspondant à la taille de la boule bleue ; vaut -1 si il n'y en a pas
 * @param rayon_jaune entier correspondant à la taille de la boule bleue ; vaut -1 si il n'y en a pas
 * @param rayon_orange entier correspondant à la taille de la boule bleue ; vaut -1 si il n'y en a pas
 * @param milieu_bleu duo d'entiers correspondants aux coordonnées (x,y) du centre de la boule bleue ; vaut [] si il n'y en a pas
 * @param milieu_jaune duo d'entiers correspondants aux coordonnées (x,y) du centre de la boule jaune ; vaut [] si il n'y en a pas
 * @param milieu_orange duo d'entiers correspondants aux coordonnées (x,y) du centre de la boule orange ; vaut [] si il n'y en a pas
*/

void modeliserEnvironnement(char nomfichier[],int *coin_HD, int rayon_bleu, int rayon_jaune,int rayon_orange,int *milieu_bleu,int *milieu_jaune,int *milieu_orange){

    char res[1000] = "";

   sprintf(res + strlen(res),"initialisation(%d,%d,'%s')",coin_HD[0],coin_HD[1],nomfichier);
  
    if (rayon_bleu > 0){
        sprintf(res + strlen(res),";boule(%d,%d,%d,'blue')", milieu_bleu[0],milieu_bleu[1],rayon_bleu);
    }
    if (rayon_jaune >0){
        sprintf(res + strlen(res),";boule(%d,%d,%d,'yellow')", milieu_jaune[0],milieu_jaune[1],rayon_jaune);
    }
    if (rayon_orange >0){
        sprintf(res + strlen(res),";boule(%d,%d,%d,'orange')", milieu_orange[0],milieu_orange[1],rayon_orange);
    }    

    sprintf(res + strlen(res),";set_robot_position(0,%d, 90)",-((coin_HD[1])-10));


    FILE* python_process = popen("python3 modelisation.py", "w");
    fprintf(python_process, "%s", res);
    fclose(python_process);
} 

/**
 * @brief Fonction qui prends en entrée les informations connues sur l'environnement et les mots-clés extraits de la phrase entrée par l'utilisateur. Puis, les transforme en appels de fonctions python  qui s'éxecutent pour modéliser l'environnement et les actions du robots.
 * @param nomfichier chemin d'accès de l'image que l'on modélise
 * @param mat matrice contenant tous les mots-clés extraits de la phrase entrée par l'utilisateur : jusqu'à 5 éléments de type[[action],[param1],[param2]]
 * @param mat_compt entier correspondant au nombre d'éléments dans "mat"
 * @param coin_HD duo d'entiers correspondants aux coordonnées (x,y) du coin droit de l'image que l'on modélise
 * @param rayon_bleu entier correspondant à la taille de la boule bleue ; vaut -1 si il n'y en a pas
 * @param rayon_jaune entier correspondant à la taille de la boule bleue ; vaut -1 si il n'y en a pas
 * @param rayon_orange entier correspondant à la taille de la boule bleue ; vaut -1 si il n'y en a pas
 * @param milieu_bleu duo d'entiers correspondants aux coordonnées (x,y) du centre de la boule bleue ; vaut [] si il n'y en a pas
 * @param milieu_jaune duo d'entiers correspondants aux coordonnées (x,y) du centre de la boule jaune ; vaut [] si il n'y en a pas
 * @param milieu_orange duo d'entiers correspondants aux coordonnées (x,y) du centre de la boule orange ; vaut [] si il n'y en a pas
*/

void modeliserActions(char nomfichier[], char *mat[5][4], int mat_compt, int *coin_HD, int rayon_bleu, int rayon_jaune,int rayon_orange,int *milieu_bleu,int *milieu_jaune, int *milieu_orange){ 
    char res[1000] = "";

    sprintf(res + strlen(res),"tl.speed(0)");
    sprintf(res + strlen(res),";initialisation(%d,%d,'%s')",coin_HD[0],coin_HD[1],nomfichier);

    if (rayon_bleu >0){
        sprintf(res + strlen(res),";boule(%d,%d,%d,'blue')", milieu_bleu[0],milieu_bleu[1],rayon_bleu);
    }
    if (rayon_jaune >0){
        sprintf(res + strlen(res),";boule(%d,%d,%d,'yellow')", milieu_jaune[0],milieu_jaune[1],rayon_jaune);
    }
    if (rayon_orange >0){
        sprintf(res + strlen(res),";boule(%d,%d,%d,'orange')", milieu_orange[0],milieu_orange[1],rayon_orange);
    }
      
    sprintf(res + strlen(res),";set_robot_position(0,%d, 90)",-((coin_HD[1])-10));
    sprintf(res + strlen(res),";tl.speed(1);time.sleep(1)");
    

for (int nbaction=0;nbaction<mat_compt;nbaction++){

    if(strcmp(mat[nbaction][3], "Négative") != 0 || strcmp(mat[nbaction][3], "Negativa") != 0){
 
//Subphrase:"Avancer de [Distance] mètres" ou bien "Avancer de [Distance] mètres à [Direction]"
        if(strcmp(mat[nbaction][0], "avancer") == 0 || strcmp(mat[nbaction][0], "avance") == 0 || strcmp(mat[nbaction][0], "avanzar") == 0 || strcmp(mat[nbaction][0], "avanza") == 0 || strcmp(mat[nbaction][0], "avances") == 0){
            if (strcmp(mat[nbaction][1], "gauche") == 0 || strcmp(mat[nbaction][1], "izquierda") == 0) {
                    sprintf(res + strlen(res),";tl.left(90)");
            }
            if (strcmp(mat[nbaction][1], "droite") == 0 || strcmp(mat[nbaction][1], "derecha") == 0) {
                    sprintf(res + strlen(res),";tl.right(90)");
            }
            if (strstr(mat[nbaction][2], "mètres") != NULL){
                char *substring = "mètres";
                char *ptr = strstr(mat[nbaction][2], substring);
                strcpy(ptr, ptr + strlen(substring));
                sprintf(res + strlen(res),";avancer(%s)", mat[nbaction][2]); 
            }
            else if (strstr(mat[nbaction][2], "metros") != NULL){
                char *substring = "metros";
                char *ptr = strstr(mat[nbaction][2], substring);
                strcpy(ptr, ptr + strlen(substring));
                sprintf(res + strlen(res),";avancer(%s)", mat[nbaction][2]);            
            }
        }   
//Subphrase:"Reculer de [Distance] mètres"
        if(strcmp(mat[nbaction][0], "reculer") == 0 || strcmp(mat[nbaction][0], "recule") == 0 || strcmp(mat[nbaction][0], "retroceder") == 0 || strcmp(mat[nbaction][0], "retrocede") == 0 || strcmp(mat[nbaction][0], "retrocedas") == 0 ){
            if (strstr(mat[nbaction][2], "mètres") != NULL){
                char *substring = "mètres";
                char *ptr = strstr(mat[nbaction][2], substring);
                strcpy(ptr, ptr + strlen(substring));
                sprintf(res + strlen(res),";reculer(%s)", mat[nbaction][2]);
            }
            else if (strstr(mat[nbaction][2], "metros") != NULL){
                char *substring = "metros";
                char *ptr = strstr(mat[nbaction][2], substring);
                strcpy(ptr, ptr + strlen(substring));
                sprintf(res + strlen(res),";reculer(%s)", mat[nbaction][2]);           
            }
        }
//Subphrase:"Tourner de [Val] degrés" ; Subphrase:"TOURNER À [DIRECTION] DE [VAL] DEGRÉS"
        if(strcmp(mat[nbaction][0], "tourner") == 0 || strcmp(mat[nbaction][0], "tourne") == 0 || strcmp(mat[nbaction][0], "girar") == 0 || strcmp(mat[nbaction][0], "gira") == 0 || strcmp(mat[nbaction][0], "gires") == 0){
            if (strstr(mat[nbaction][2], "degrés") != NULL){
                char *substring = "degrés";
                char *ptr = strstr(mat[nbaction][2], substring);
                strcpy(ptr, ptr + strlen(substring));
            }
            else if (strstr(mat[nbaction][2], "degré") != NULL){
                char *substring = "degré";
                char *ptr = strstr(mat[nbaction][2], substring);
                strcpy(ptr, ptr + strlen(substring));
            }
            else if (strstr(mat[nbaction][2], "grados") != NULL){
                char *substring = "grados";
                char *ptr = strstr(mat[nbaction][2], substring);
                strcpy(ptr, ptr + strlen(substring));
            }
            else if (strstr(mat[nbaction][2], "grado") != NULL){
                char *substring = "grado";
                char *ptr = strstr(mat[nbaction][2], substring);
                strcpy(ptr, ptr + strlen(substring));        
            }
            if (strcmp(mat[nbaction][1], "gauche") == 0 || strcmp(mat[nbaction][1], "izquierda") == 0) {
                    sprintf(res + strlen(res),";tl.left(%s)", mat[nbaction][2]);
            }
            else{
                sprintf(res + strlen(res),";tl.right(%s)", mat[nbaction][2]);
            } 
        }

//Subphrase:"AVANCER JUSQU'À L'[OBJET]"
        if(strcmp(mat[nbaction][0], "avancer") == 0 || strcmp(mat[nbaction][0], "avance") == 0 || strcmp(mat[nbaction][0], "avanzar") == 0 || strcmp(mat[nbaction][0], "avanza") == 0 || strcmp(mat[nbaction][0], "avances") == 0){

            if ((strstr(mat[nbaction][2], "jaune") != NULL) || (strstr(mat[nbaction][2], "amarillo") != NULL) || (strstr(mat[nbaction][2], "amarilla") != NULL)){
                if (rayon_jaune >0){
                sprintf(res + strlen(res),";gobj([%d,%d,%d,'yellow'])", milieu_jaune[0],milieu_jaune[1],rayon_jaune);  
                }
            }
            else if ((strstr(mat[nbaction][2], "bleu") != NULL)||(strstr(mat[nbaction][2], "bleue") != NULL)||(strstr(mat[nbaction][2], "azul") != NULL)){
                if (rayon_bleu >0){
                sprintf(res + strlen(res),";gobj([%d,%d,%d,'blue'])", milieu_bleu[0],milieu_bleu[1],rayon_bleu); 
                }            
            }
            else if ((strstr(mat[nbaction][2], "orange") != NULL)||(strstr(mat[nbaction][2], "naranja") != NULL)){
                if (rayon_orange >0){
                sprintf(res + strlen(res),";gobj([%d,%d,%d,'orange'])", milieu_orange[0],milieu_orange[1],rayon_orange);      
                }
            }
        } 

//Subphrase:"CONTOURNER PAR LA [DIRECTION] L'[OBJET]" ou bien "CONTOURNER L'[OBJET] PAR LA [DIRECTION]"
        if(strcmp(mat[nbaction][0], "contourner") == 0 || strcmp(mat[nbaction][0], "contourne") == 0 || strcmp(mat[nbaction][0], "rodear") == 0 || strcmp(mat[nbaction][0], "rodea") == 0 || strcmp(mat[nbaction][0], "rodées") == 0){
            if ((strstr(mat[nbaction][2], "jaune") != NULL) || (strstr(mat[nbaction][2], "amarillo") != NULL) || (strstr(mat[nbaction][2], "amarilla") != NULL)){
                if (rayon_jaune >0){
                    if ((strstr(mat[nbaction][1], "gauche") != NULL) || (strstr(mat[nbaction][1], "izquierda") != NULL)){
                        sprintf(res + strlen(res),";contobj(%d,%d,%d,'yellow',-1)", milieu_jaune[0],milieu_jaune[1],rayon_jaune);  
                    }
                    else{
                        sprintf(res + strlen(res),";contobj(%d,%d,%d,'yellow',1)", milieu_jaune[0],milieu_jaune[1],rayon_jaune);
                    }
                }                 
            }
            else if ((strstr(mat[nbaction][2], "bleu") != NULL)||(strstr(mat[nbaction][2], "bleue") != NULL)||(strstr(mat[nbaction][2], "azul") != NULL)){
                if (rayon_bleu >0){
                    if ((strstr(mat[nbaction][1], "gauche") != NULL) || (strstr(mat[nbaction][1], "izquierda") != NULL)){
                        sprintf(res + strlen(res),";contobj(%d,%d,%d,'blue',-1)", milieu_bleu[0],milieu_bleu[1],rayon_bleu);             
                    }
                    else{
                        sprintf(res + strlen(res),";contobj(%d,%d,%d,'blue',1)", milieu_bleu[0],milieu_bleu[1],rayon_bleu);
                    }
                }
            }
            else if ((strstr(mat[nbaction][2], "orange") != NULL)||(strstr(mat[nbaction][2], "naranja") != NULL)){
                if (rayon_orange >0){
                    if ((strstr(mat[nbaction][1], "gauche") != NULL) || (strstr(mat[nbaction][1], "izquierda") != NULL)){             
                        sprintf(res + strlen(res),";contobj(%d,%d,%d,'orange',-1)", milieu_orange[0],milieu_orange[1],rayon_orange);      
                    }
                    else{
                        sprintf(res + strlen(res),";contobj(%d,%d,%d,'orange',1)", milieu_orange[0],milieu_orange[1],rayon_orange);  
                    }
                }    
            }
        }

//Subphrase:"COMPTER LE NOMBRE D'[OBJET]"
        if(strcmp(mat[nbaction][0], "compter") == 0 || strcmp(mat[nbaction][0], "compte") == 0 || strcmp(mat[nbaction][0], "contar") == 0 || strcmp(mat[nbaction][0], "cuenta") == 0 || strcmp(mat[nbaction][0], "cuentes") == 0){
            if ((strstr(mat[nbaction][2], "balles") != NULL) || (strstr(mat[nbaction][2], "boules") != NULL) || (strstr(mat[nbaction][2], "bolas") != NULL)|| (strstr(mat[nbaction][2], "pelotas") != NULL)){                
                if ((strstr(mat[nbaction][2], "jaune") != NULL) || (strstr(mat[nbaction][2], "amarillo") != NULL) || (strstr(mat[nbaction][2], "amarilla") != NULL)){
                    sprintf(res + strlen(res),";print('---> IL Y A %d BOULE JAUNE.')",((rayon_jaune > 0) ? 1 : 0)); 
                }                
                else if ((strstr(mat[nbaction][2], "bleu") != NULL)||(strstr(mat[nbaction][2], "bleue") != NULL)||(strstr(mat[nbaction][2], "azul") != NULL)){
                    sprintf(res + strlen(res),";print('---> IL Y A %d BOULE BLEUE.')",((rayon_bleu > 0) ? 1 : 0));
                }
                else if ((strstr(mat[nbaction][2], "orange") != NULL)||(strstr(mat[nbaction][2], "naranja") != NULL)){
                    sprintf(res + strlen(res),";print('---> IL Y A %d BOULE ORANGE.')",((rayon_orange > 0) ? 1 : 0));
                }    
                else{
                    int nb_boules = 0;
                    if (rayon_jaune >0){nb_boules+=1;}
                    if (rayon_bleu >0){nb_boules+=1;}
                    if (rayon_orange >0){nb_boules+=1;}
                    sprintf(res + strlen(res),";print('---> IL Y A %d BOULES(S)).')",nb_boules);
                }
            }
            else{
                sprintf(res + strlen(res),";print('---> OBJET INEXISTANT.')");
            }
        }      
    }
}

FILE* python_process = popen("python3 modelisation.py", "w");
fprintf(python_process, "%s", res);
fclose(python_process);
}

/**
 * @}
 * 
*/
