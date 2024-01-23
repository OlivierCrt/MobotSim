#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include "image_process.h"
//#include "ismael.h"
//#include "solal.h"

void main_img(){
    printf("\n\x1B[1m---------------NOUVELLE IMAGE--------------\x1B[0m\n\n");
    char nomfichier[100]; //je l'utilise aussi pour le fond d'ecran turtle
    int nombre;
    do {
        printf("Entrez le nom de l'image que vous souhaitez modéliser : ");
        scanf("%s", nomfichier);
        sscanf(nomfichier, "IMG_%d.txt", &nombre);
    } while (nombre < 5389 || nombre > 5408 );

    int rayon_bleu, rayon_jaune, rayon_orange;//-1 si pas de rayon
    int *milieu_bleu, *milieu_jaune, *milieu_orange;//liste vide si existe pas
    main_it(&rayon_bleu, &rayon_jaune, &rayon_orange,&milieu_bleu, &milieu_jaune, &milieu_orange, nomfichier );

    int *coin_HD = (int*)malloc(2 * sizeof(int));
    coin_HD[0] = 300;
    coin_HD[1] = 300;

    int recentrage_x = coin_HD[0]/2;
    int recentrage_y = coin_HD[1]/2;

    coin_HD[0] -= recentrage_x;
    coin_HD[1] -= recentrage_y;
      
    milieu_bleu[0] -= recentrage_x;
    milieu_bleu[1] = -milieu_bleu[1] +recentrage_y;

    milieu_jaune[0] -= recentrage_x;
    milieu_jaune[1] = -milieu_jaune[1] +recentrage_y;
   
    milieu_orange[0] -= recentrage_x;
    milieu_orange[1] = -milieu_orange[1] +recentrage_y;
   
    while (getchar() != '\n') {         
    }

    printf("\nAppuyez sur la touche 'Entrée' pour continuer...");
    while (getchar() != '\n') {   
    }

    envPy(nomfichier, coin_HD, rayon_bleu, rayon_jaune, rayon_orange, milieu_bleu, milieu_jaune, milieu_orange);

}

void main_txt(){
    printf("\n\x1B[1m---------------NOUVELLE IMAGE--------------\x1B[0m\n\n");
    char nomfichier[100]= "IMG_5408.txt"; //je l'utilise aussi pour le fond d'ecran turtle

    int rayon_bleu =-1;int rayon_jaune=-1;int rayon_orange=-1;//-1 si pas de rayon
    int *milieu_bleu =malloc(2 * sizeof(int));int *milieu_jaune=malloc(2 * sizeof(int));int *milieu_orange= malloc(2 * sizeof(int));//liste vide si existe pas
    milieu_bleu[0] = milieu_bleu[1] = milieu_jaune[0] = milieu_jaune[1] = milieu_orange[0] = milieu_orange[1] = 0;

    char phrase[200];
    char lang[3];
    Queue myQueue = createQueue();
    char *mat[5][4];
    int mat_compt = 0;
    int i,j;
    
    int *coin_HD = (int*)malloc(2 * sizeof(int));
    coin_HD[0] = 150;
    coin_HD[1] = 150;

    int b;
    while ((b = getchar()) != '\n' && b != EOF) { }

    printf("\x1B[1m---------------TRAITEMENT DE TEXTE--------------\x1B[0m\n\n");
    printf("\x1B[4mCHOIX DE LA LANGUE:\x1B[0m\n\n");



    printf("Choisissez la langue avec laquelle gérer la phrase.\nEntrez 'es' pour espagnol et 'fr' pour français : ");
    fgets(lang, sizeof(lang), stdin); // Lee la elección del idioma, incluyendo '\n'

    // Limpia el buffer de entrada si es necesario
    if (strlen(lang) == 2 && lang[1] != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
    }

    printf("\n");
    printf("\x1B[4mPHRASE A TRAITER:\x1B[0m\n\n");
    printf("Ecrivez la phrase à traiter:\n");
    fgets(phrase, sizeof(phrase), stdin);
    phrase[strcspn(phrase, "\n")] = 0; // Remueve el salto de línea al final

    if (strcmp(lang, "es") == 0) {
        afficher_Action_es(phrase, &myQueue); // Procesa y encola las subfrases
    } else if (strcmp(lang, "fr") == 0) {
        afficher_Action_fr(phrase, &myQueue);
    }

    printf("\n");
    printf("\x1B[4mSEPARATION EN MOTS-CLES:\x1B[0m\n");
    while (!isQueueEmpty(myQueue) && mat_compt < 5) {
        ActionData action = dequeue(&myQueue);
        printf("\nAction: %s\nParametre 1: %s\nParametre 2: %s\nType de phrase: %s\n",
               action.action, action.param1, action.param2, action.type);
        mat[mat_compt][0] = strdup(action.action);
        mat[mat_compt][1] = strdup(action.param1);
        mat[mat_compt][2] = strdup(action.param2);
        mat[mat_compt][3] = strdup(action.type);
        mat_compt++;
    }
    printf("\n");

/*
    for(i = 0; i < mat_compt; i++) {
        for(j = 0; j < 4; j++) {
            printf("\t%s\t", mat[i][j]);
        }
        printf("\n");
    }   
*/

    printf("-----------------------------------------------\n\n");

    printf("Appuyez sur la touche 'Entrée' pour continuer...");
    while (getchar() != '\n') {
    }
    printf("\n");

   actionsPy(nomfichier,mat,mat_compt, coin_HD, rayon_bleu, rayon_jaune, rayon_orange, milieu_bleu, milieu_jaune, milieu_orange);

}

void main_imgtxt(){

    printf("\n\x1B[1m---------------NOUVELLE IMAGE--------------\x1B[0m\n\n");
    
    char nomfichier[100]; //je l'utilise aussi pour le fond d'ecran turtle
    int nombre;

    do {
        printf("Entrez le nom de l'image que vous souhaitez modéliser : ");
        scanf("%s", nomfichier);
        sscanf(nomfichier, "IMG_%d.txt", &nombre);
    } while (nombre < 5389 || nombre > 5408 );

    int rayon_bleu, rayon_jaune, rayon_orange;//-1 si pas de rayon
    int *milieu_bleu, *milieu_jaune, *milieu_orange;//liste vide si existe pas
    main_it(&rayon_bleu, &rayon_jaune, &rayon_orange,&milieu_bleu, &milieu_jaune, &milieu_orange, nomfichier );

    char phrase[200];
    char lang[3];
    Queue myQueue = createQueue();
    char *mat[5][4];
    int mat_compt = 0;
    int i,j;
    char boucle ='\0';

    int *coin_HD = (int*)malloc(2 * sizeof(int));
    coin_HD[0] = 300;
    coin_HD[1] = 300;

    int recentrage_x = coin_HD[0]/2;
    int recentrage_y = coin_HD[1]/2;

    coin_HD[0] -= recentrage_x;
    coin_HD[1] -= recentrage_y;
      
    milieu_bleu[0] -= recentrage_x;
    milieu_bleu[1] = -milieu_bleu[1] +recentrage_y;

    milieu_jaune[0] -= recentrage_x;
    milieu_jaune[1] = -milieu_jaune[1] +recentrage_y;
   
    milieu_orange[0] -= recentrage_x;
    milieu_orange[1] = -milieu_orange[1] +recentrage_y;
   
    while (getchar() != '\n') {         
    }

    printf("\nAppuyez sur la touche 'Entrée' pour continuer...");
    while (getchar() != '\n') {   
    }


    envPy(nomfichier, coin_HD, rayon_bleu, rayon_jaune, rayon_orange, milieu_bleu, milieu_jaune, milieu_orange);

     printf("\n\n");

    printf("\x1B[1m---------------TRAITEMENT DE TEXTE--------------\x1B[0m\n\n");
    printf("\x1B[4mCHOIX DE LA LANGUE:\x1B[0m\n\n");



   printf("Choisissez la langue avec laquelle gérer la phrase.\nEntrez 'es' pour espagnol et 'fr' pour français : ");
    fgets(lang, sizeof(lang), stdin); // Lee la elección del idioma, incluyendo '\n'

    // Limpia el buffer de entrada si es necesario
    if (strlen(lang) == 2 && lang[1] != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
    }

    printf("\n");
    printf("\x1B[4mPHRASE A TRAITER:\x1B[0m\n\n");
    printf("Ecrivez la phrase à traiter:\n");
    fgets(phrase, sizeof(phrase), stdin);
    phrase[strcspn(phrase, "\n")] = 0; // Remueve el salto de línea al final

    if (strcmp(lang, "es") == 0) {
        afficher_Action_es(phrase, &myQueue); // Procesa y encola las subfrases
    } else if (strcmp(lang, "fr") == 0) {
        afficher_Action_fr(phrase, &myQueue);
    }

    printf("\n");
    printf("\x1B[4mSEPARATION EN MOTS-CLES:\x1B[0m\n");
    while (!isQueueEmpty(myQueue) && mat_compt < 5) {
        ActionData action = dequeue(&myQueue);
        printf("\nAction: %s\nParametre 1: %s\nParametre 2: %s\nType de phrase: %s\n",
               action.action, action.param1, action.param2, action.type);
        mat[mat_compt][0] = strdup(action.action);
        mat[mat_compt][1] = strdup(action.param1);
        mat[mat_compt][2] = strdup(action.param2);
        mat[mat_compt][3] = strdup(action.type);
        mat_compt++;
    }
    printf("\n");

/*
    for(i = 0; i < mat_compt; i++) {
        for(j = 0; j < 4; j++) {
            printf("\t%s\t", mat[i][j]);
        }
        printf("\n");
    }   
*/

    printf("-----------------------------------------------\n\n");

    printf("Appuyez sur la touche 'Entrée' pour continuer...");
    while (getchar() != '\n') {
    }
    printf("\n");

   actionsPy(nomfichier,mat,mat_compt, coin_HD, rayon_bleu, rayon_jaune, rayon_orange, milieu_bleu, milieu_jaune, milieu_orange);

}


int main() {
    char choix;

    do {
        printf("Veuillez entrer un chiffre entre 1 et 4\n\n1- Modéliser une image.\n2- Se déplacer dans une pièce vide.\n3- Modéliser une image puis se déplacer dedans.\n4- Quitter ce programme.\n");
        scanf(" %c", &choix);

        switch (choix) {
            case '1':
                main_img();
                break;
            case '2':
                main_txt();
                break;
            case '3':
                main_imgtxt();
                break;
            case '4':
                return 0;
            default:
                printf("Choix non valide.\n");
        }
    } while (choix < '1' || choix > '4');

    main();
}



/*
IMG_5402.txt
exemples de phrase pour tester

avancer de 1000 mètres puis tourner de 70 degrés puis reculer de 150 mètres puis tourner de 50 degrés
avance jusqua la boule jaune puis avance jusqua la boule orange puis avance jusqua la boule bleue
contourne la balle bleue par la droite

compter le nb de boul


mettre un menu avec 1 faire la modélisation ; 2 faire les instruction ; 3 faire les 2 l'un apres l'autre ; 4 quitter 
*/
