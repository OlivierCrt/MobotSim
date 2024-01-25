#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "solal.h"


void envPy(char nomfichier[],int *coin_HD, int rayon_bleu, int rayon_jaune,int rayon_orange,int *milieu_bleu,int *milieu_jaune,int *milieu_orange){

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


    // Exécuter le script Python avec le code Turtle en tant que sortie
    FILE* python_process = popen("python3 solal.py", "w");

    // Écrire le code Turtle dans le processus Python
    fprintf(python_process, "%s", res);
    fclose(python_process);
} 

void actionsPy(char nomfichier[], char *mat[5][4], int mat_compt, int *coin_HD, int rayon_bleu, int rayon_jaune,int rayon_orange,int *milieu_bleu,int *milieu_jaune, int *milieu_orange){ 
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
      
    sprintf(res + strlen(res),";tl.up()");
    sprintf(res + strlen(res),";set_robot_position(0,%d, 90)",-((coin_HD[1])-10));
    sprintf(res + strlen(res),";tl.speed(1);time.sleep(1)");
    

for (int nbaction=0;nbaction<mat_compt;nbaction++){

    if(strcmp(mat[nbaction][3], "Négative") != 0 || strcmp(mat[nbaction][3], "Negativa") != 0){
 
//Subphrase:"Avancer de [Distance] mètres"
        if(strcmp(mat[nbaction][0], "avancer") == 0 || strcmp(mat[nbaction][0], "avance") == 0 || strcmp(mat[nbaction][0], "avanzar") == 0 || strcmp(mat[nbaction][0], "avanza") == 0 || strcmp(mat[nbaction][0], "avances") == 0){
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
    }
}

// Exécuter le script Python avec le code Turtle en tant que sortie
FILE* python_process = popen("python3 solal.py", "w");

// Écrire le code Turtle dans le processus Python
fprintf(python_process, "%s", res);
fclose(python_process);
}

int main(){
    return 1;
}
