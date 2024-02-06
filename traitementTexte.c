#include "traitementTexte.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stdbool.h"
#include "ctype.h"

double convertDouble(char *str) {
    char *temp;
    double val = strtod(str, &temp);
    return val;
}


void toLowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char) str[i]);
    }
}

Queue createQueue() {
    Queue q;
    q.front = q.rear = NULL;
    q.size = 0;
    return q;
}

void enqueue(Queue* q, ActionData data, typePhrase typeData) {
    Node* temp = (Node*) malloc(sizeof(Node));
    temp->data = data;  // Direct copy
    temp->typeData = typeData;  // Direct copy
    temp->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = temp;
        q->size = 1;
        return;
    }

    q->rear->next = temp;
    q->rear = temp;
    q->size++;
}

// Ahora dequeue devuelve un Node, para obtener tanto ActionData como typePhrase
Node dequeue(Queue* q) {
    if (q->front == NULL) {
        fprintf(stderr, "Error: Intento de desencolar de una cola vacía.\n");
        exit(EXIT_FAILURE);
    }

    Node *temp = q->front;
    Node data = *temp;  // Copy the data and typeData

    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    q->size--;

    free(temp);
    return data;
}

int isQueueEmpty(Queue q) {
    return (q.front == NULL);
}


int str_to_num_fr(char *nombre) {
    if (strcmp(nombre, "un") == 0) return 1;
    if (strcmp(nombre, "deux") == 0) return 2;
    if (strcmp(nombre, "trois") == 0) return 3;
    if (strcmp(nombre, "quatre") == 0) return 4;
    if (strcmp(nombre, "cinq") == 0) return 5;
    if (strcmp(nombre, "six") == 0) return 6;
    if (strcmp(nombre, "sept") == 0) return 7;
    if (strcmp(nombre, "huit") == 0) return 8;
    if (strcmp(nombre, "neuf") == 0) return 9;
    if (strcmp(nombre, "dix") == 0) return 10;
    if (strcmp(nombre, "onze") == 0) return 11;
    if (strcmp(nombre, "douze") == 0) return 12;
    if (strcmp(nombre, "treize") == 0) return 13;
    if (strcmp(nombre, "quatorze") == 0) return 14;
    if (strcmp(nombre, "quinze") == 0) return 15;
    if (strcmp(nombre, "seize") == 0) return 16;
    if (strcmp(nombre, "vingt") == 0) return 20;
    if (strcmp(nombre, "trente") == 0) return 30;
    if (strcmp(nombre, "quarante") == 0) return 40;
    if (strcmp(nombre, "cinquante") == 0) return 50;
    if (strcmp(nombre, "soixante") == 0) return 60;
    if (strcmp(nombre, "cent") == 0 || strcmp(nombre, "cents") == 0) return 100;
    if (strcmp(nombre, "mille") == 0 || strcmp(nombre, "milles") == 0) return 1000;
    else
        return 0;
}

int str_to_num_es(char *nombre) {
    if (strcmp(nombre, "uno") == 0 || strcmp(nombre, "un") == 0) return 1;
    if (strcmp(nombre, "dos") == 0) return 2;
    if (strcmp(nombre, "tres") == 0) return 3;
    if (strcmp(nombre, "cuatro") == 0) return 4;
    if (strcmp(nombre, "cinco") == 0) return 5;
    if (strcmp(nombre, "seis") == 0) return 6;
    if (strcmp(nombre, "siete") == 0) return 7;
    if (strcmp(nombre, "ocho") == 0) return 8;
    if (strcmp(nombre, "nueve") == 0) return 9;
    if (strcmp(nombre, "diez") == 0) return 10;
    if (strcmp(nombre, "once") == 0) return 11;
    if (strcmp(nombre, "doce") == 0) return 12;
    if (strcmp(nombre, "trece") == 0) return 13;
    if (strcmp(nombre, "catorce") == 0) return 14;
    if (strcmp(nombre, "quince") == 0) return 15;
    if (strcmp(nombre, "dieciseis") == 0) return 16;
    if (strcmp(nombre, "diecisiete") == 0) return 17;
    if (strcmp(nombre, "dieciocho") == 0) return 18;
    if (strcmp(nombre, "diecinueve") == 0) return 19;
    if (strcmp(nombre, "veinte") == 0) return 20;
    if (strcmp(nombre, "veintiun") == 0) return 21;
    if (strcmp(nombre, "veintidos") == 0) return 22;
    if (strcmp(nombre, "veintitres") == 0) return 23;
    if (strcmp(nombre, "veinticuatro") == 0) return 24;
    if (strcmp(nombre, "veinticinco") == 0) return 25;
    if (strcmp(nombre, "veintiseis") == 0) return 26;
    if (strcmp(nombre, "veintisiete") == 0) return 27;
    if (strcmp(nombre, "veintiocho") == 0) return 28;
    if (strcmp(nombre, "veintintinueve") == 0) return 29;

    if (strcmp(nombre, "treinta") == 0) return 30;
    if (strcmp(nombre, "cuarenta") == 0) return 40;
    if (strcmp(nombre, "cincuenta") == 0) return 50;
    if (strcmp(nombre, "sesenta") == 0) return 60;
    if (strcmp(nombre, "setenta") == 70) return 70;
    if (strcmp(nombre, "ochenta") == 0) return 80;
    if (strcmp(nombre, "ochenta") == 0) return 90;

    if (strcmp(nombre, "cien") == 0 || strcmp(nombre,"ciento") == 0) return 100;
    if (strcmp(nombre, "doscientos") == 0) return 200;
    if (strcmp(nombre, "trescientos") == 0) return 300;
    if (strcmp(nombre, "cuatrocientos") == 0) return 400;
    if (strcmp(nombre, "quinientos") == 0) return 500;
    if (strcmp(nombre, "seiscientos") == 0) return 600;
    if (strcmp(nombre, "setecientos") == 0) return 700;
    if (strcmp(nombre, "ochocientos") == 0) return 800;
    if (strcmp(nombre, "novecientos") == 0) return 900;

    if (strcmp(nombre, "mil") == 0) return 1000;
    else
        return 0;
}


int num_to_chiffre_tot_fr(char *str) {
    char *mot;
    char ponctuation[] = " ',.-";
    int total = 0, temp = 0;

    mot = strtok(str, ponctuation);
    while (mot != NULL) {
        int num = str_to_num_fr(mot);
        if (num == 1000 || num == 100 || num == 20) {
            temp = (temp == 0 ? 1 : temp) * num;
            total += temp;
            temp = 0;
        } else {
            temp += num;
        }
        mot = strtok(NULL, ponctuation);
    }
    total += temp; // Añadir cualquier valor restante
    return total;
}

int num_to_chiffre_tot_es(char *str) {
    char *mot;
    char ponctuation[] = " ',.-";
    int total = 0, temp = 0;

    mot = strtok(str, ponctuation);
    while (mot != NULL) {
        int num = str_to_num_es(mot);
        if (num == 1000 || num == 100) {
            temp = (temp == 0 ? 1 : temp) * num;
            total += temp;
            temp = 0;
        } else {
            temp += num;
        }
        mot = strtok(NULL, ponctuation);
    }
    total += temp; // Añadir cualquier valor restante
    return total;
}


bool detect_chiffre_fr(const char *word) {
    const char *nombre_mot[] = {
            "un", "deux", "trois", "quatre", "cinq", "six", "sept", "huit", "neuf",
            "dix", "onze", "douze", "treize", "quatorze", "quinze", "seize",
            "vingt", "trente", "quarante", "cinquante", "soixante", "quatre vingts",
            "cent","cents", "mille","milles", NULL
    };

    for (int i = 0; nombre_mot[i] != NULL; i++) {
        if (strcmp(word, nombre_mot[i]) == 0) {
            return true;
        }
    }
    return false;
}

bool detect_chiffre_es(const char *word) {
    const char *nombre_mot[] = {
            "uno","un", "dos", "tres", "cuatro", "cinco", "seis", "siete", "ocho", "nueve",
            "diez", "once", "doce", "trece", "catorce", "quince", "dieciseis","diecisiete","dieciocho","diecinueve",
            "veinte","veintiun","veintidos","veintitres","veinticuatro","veinticinco","veintiseis","veintisiete","veintiocho","veintinueve",
            "treinta", "cuarenta", "cincuenta", "sesenta", "setenta","ochenta", "noventa",
            "cien", "doscientos", "trescientos", "cuatrocientos", "quinientos", "seiscientos", "setecientos", "ochocientos", "novecientos",
            "mil", NULL
    };

    for (int i = 0; nombre_mot[i] != NULL; i++) {
        if (strcmp(word, nombre_mot[i]) == 0) {
            return true;
        }
    }
    return false;
}

void afficher_Action_fr(char *phrase, Queue* q){
    char subphrases[5][200];
    char *mots[20];
    int compt = 0;
    char Avant_chiffre[100] = "", Chiffre_mots[100] = "", Apres_chiffre[100] = "";
    int chiffre;
    char ponctuation_chiffre[] = " ";
    char *mot;
    char ponctuation[] = " ',.!?";
    bool nombre_trouve = false;
    char *action;
    char ponctuation_sub[] = " ',.!?";
    char *mot_sub;
    int i, j;
    double result;
    int entre_flag = 0;
    int ou_flag=0;
    char *mots_sub[50];
    int compt_sub = 0;
    int subphr_compt = 0;
    ActionData resultData;
    typePhrase resultPhrase;


    for (i = 0; i < 5; i++) {
        subphrases[i][0] = '\0';
    }

    toLowercase(phrase);

    mot = strtok(phrase, ponctuation);
    while (mot != NULL && compt < 20) {
        mots[compt++] = mot;
        mot = strtok(NULL, ponctuation);
    }


// Dividir en subfrases y concatenarlas
    for (i = 0; i < compt; i++) {
        if (strcmp(mots[i], "puis") == 0) {
            subphr_compt++;
        } else {
            strcat(subphrases[subphr_compt], mots[i]);
            strcat(subphrases[subphr_compt], " ");
        }
    }

    for (i = 0; i <= subphr_compt; i++) {
        printf("\nSubphrase %d: %s\n", i + 1, subphrases[i]);

        // Resetear las variables para la subfrase actual
        nombre_trouve = false;
        strcpy(Avant_chiffre, "");
        strcpy(Chiffre_mots, "");
        strcpy(Apres_chiffre, "");

        mot = strtok(subphrases[i], ponctuation_chiffre);
        while (mot != NULL) {
            if (detect_chiffre_fr(mot)) {
                nombre_trouve = true;
                strcat(Chiffre_mots, mot);
                strcat(Chiffre_mots, " ");
            } else {
                if (!nombre_trouve) {
                    strcat(Avant_chiffre, mot);
                    strcat(Avant_chiffre, " ");
                } else {
                    strcat(Apres_chiffre, mot);
                    strcat(Apres_chiffre, " ");
                }
            }
            mot = strtok(NULL, ponctuation_chiffre);
        }

        // Procesar el número y reconstruir la subfrase
        chiffre = num_to_chiffre_tot_fr(Chiffre_mots);
        sprintf(subphrases[i], "%s%d %s", Avant_chiffre, chiffre, Apres_chiffre);
        //printf("Processed Subphrase: %s\n", subphrases[i]);
    }

    //printf("Nb ss-phrases : %d\n",subphr_compt+1);

    // Imprimir las subfrases
    for (i = 0; i <= subphr_compt; i++) {           //On utilise i et après j pcq ça em donnait erreur

        compt_sub = 0;
        entre_flag = 0;

        char param1[20] = "";
        char param2[20] = "";
        char type[20] = "";


        mot_sub = strtok(subphrases[i], ponctuation_sub);
        while (mot_sub != NULL && compt_sub < 20) {
            mots_sub[compt_sub++] = mot_sub;
            mot_sub = strtok(NULL, ponctuation_sub);
        }

        //for (j = 0; j < compt_sub; j++) {
        //    printf("mot[%d]=%s\n", j, mots_sub[j]);
        //}


        for (j = 0; j < compt_sub; j++) {
            if(strcmp(mots_sub[0], "ne") == 0 || strcmp(mots_sub[0], "n") == 0)
                sprintf(type, "Négative");
            else
                sprintf(type, "Affirmative");

            if (strcmp(mots_sub[j], "avancer") == 0 || strcmp(mots_sub[j], "avance") == 0 ||
                strcmp(mots_sub[j], "reculer") == 0 || strcmp(mots_sub[j], "recule") == 0 ||
                strcmp(mots_sub[j], "tourner") == 0 || strcmp(mots_sub[j], "tourne") == 0 ||
                strcmp(mots_sub[j], "localiser") == 0 || strcmp(mots_sub[j], "localise") == 0 ||
                strcmp(mots_sub[j], "trouver") == 0 || strcmp(mots_sub[j], "trouve") == 0 ||
                strcmp(mots_sub[j], "contourner") == 0 || strcmp(mots_sub[j], "contourne") == 0 ||
                strcmp(mots_sub[j], "passer") == 0 || strcmp(mots_sub[j], "passe") == 0 ||
                strcmp(mots_sub[j], "compter") == 0 || strcmp(mots_sub[j], "compte") == 0) {
                action = mots_sub[j];
            }


            //PHRASE DU TYPE "CONTOURNER PAR LA [DIRECTION] L'[OBJET]"
            //PHRASE DU TYPE "CONTOURNER L'[OBJET] PAR LA [DIRECTION]"
            if(strcmp(action, "contourner") == 0 || strcmp(action, "contourne") == 0) {

                if(strcmp(mots_sub[j], "droite") == 0 || strcmp(mots_sub[j], "gauche") == 0)
                    sprintf(param1, "%s", mots_sub[j]);

                if (strcmp(mots_sub[j], "cube") == 0 || strcmp(mots_sub[j], "carré") == 0 ||
                    strcmp(mots_sub[j], "balle") == 0 || strcmp(mots_sub[j], "boule") == 0 ||
                    strcmp(mots_sub[j], "objet") == 0 || strcmp(mots_sub[j], "obstacle") == 0) {
                    if (j + 1 < compt_sub && (strcmp(mots_sub[j + 1], "rouge") == 0 || strcmp(mots_sub[j + 1], "bleu") == 0 || strcmp(mots_sub[j + 1], "bleue") == 0 ||
                                              strcmp(mots_sub[j + 1], "jaune") == 0 || strcmp(mots_sub[j + 1], "orange") == 0)) {
                        sprintf(param2, "%s %s", mots_sub[j], mots_sub[j + 1]);
                    } else {
                        sprintf(param2, "%s", mots_sub[j]);
                    }
                }
            }


                //PHRASE DU TYPE "PASSER ENTRE [OBJET] ET [OBJET]"
            else if (strcmp(action, "passer") == 0 || strcmp(action, "passe") == 0) {

                if(strcmp(mots_sub[j], "entre") == 0) {
                    entre_flag = 1;                                         // Mot "entre" trouvé
                    continue;
                }

                // Procesar objetos y colores después de "entre"
                if (entre_flag == 1 && strcmp(mots_sub[j], "et") == 0){
                    entre_flag = 0;                                         // On remet le flag de "entre" a 0
                    continue;
                }

                if (entre_flag == 1) {
                    if (strcmp(mots_sub[j], "cube") == 0 || strcmp(mots_sub[j], "carré") == 0 ||
                        strcmp(mots_sub[j], "balle") == 0 || strcmp(mots_sub[j], "boule") == 0 ||
                        strcmp(mots_sub[j], "objet") == 0 || strcmp(mots_sub[j], "obstacle") == 0) {
                        if (j + 1 < compt_sub && (strcmp(mots_sub[j + 1], "rouge") == 0 || strcmp(mots_sub[j + 1], "bleu") == 0 || strcmp(mots_sub[j + 1], "bleue") == 0 ||
                                                  strcmp(mots_sub[j + 1], "jaune") == 0 || strcmp(mots_sub[j + 1], "orange") == 0)) {
                            sprintf(param1, "%s %s", mots_sub[j], mots_sub[j + 1]);
                        } else {
                            sprintf(param1, "%s", mots_sub[j]);
                        }
                    }
                } else {
                    if (strcmp(mots_sub[j], "cube") == 0 || strcmp(mots_sub[j], "carré") == 0 ||
                        strcmp(mots_sub[j], "balle") == 0 || strcmp(mots_sub[j], "boule") == 0 ||
                        strcmp(mots_sub[j], "objet") == 0 || strcmp(mots_sub[j], "obstacle") == 0) {
                        if (j + 1 < compt_sub && (strcmp(mots_sub[j + 1], "rouge") == 0 || strcmp(mots_sub[j + 1], "bleu") == 0 || strcmp(mots_sub[j + 1], "bleue") == 0 ||
                                                  strcmp(mots_sub[j + 1], "jaune") == 0 || strcmp(mots_sub[j + 1], "orange") == 0)) {
                            sprintf(param2, "%s %s", mots_sub[j], mots_sub[j + 1]);
                        } else {
                            sprintf(param2, "%s", mots_sub[j]);
                        }
                    }
                }
            }

            else if(strcmp(action, "localiser") == 0 || strcmp(action, "localise") == 0 ||
                    strcmp(action, "trouver") == 0 || strcmp(action, "trouve") == 0) {

                // Procesar objetos y colores después de "entre"
                if (ou_flag == 0 && strcmp(mots_sub[j], "ou") == 0){
                    ou_flag = 1;                                         // On remet le flag de "ou" a 1
                    continue;
                }

                if (ou_flag == 0) {
                    if(strcmp(mots_sub[j], "droite") == 0 || strcmp(mots_sub[j], "gauche") == 0)
                        sprintf(param1, "%s", mots_sub[j]);
                    if (strcmp(mots_sub[j], "cube") == 0 || strcmp(mots_sub[j], "carré") == 0 ||
                        strcmp(mots_sub[j], "balle") == 0 || strcmp(mots_sub[j], "boule") == 0 ||
                        strcmp(mots_sub[j], "objet") == 0 || strcmp(mots_sub[j], "obstacle") == 0) {
                        if (j + 1 < compt_sub && (strcmp(mots_sub[j + 1], "rouge") == 0 || strcmp(mots_sub[j + 1], "bleu") == 0 || strcmp(mots_sub[j + 1], "bleue") == 0 ||
                                                  strcmp(mots_sub[j + 1], "jaune") == 0 || strcmp(mots_sub[j + 1], "orange") == 0)) {
                            sprintf(param1, "%s %s", mots_sub[j], mots_sub[j + 1]);
                        } else {
                            sprintf(param1, "%s", mots_sub[j]);
                        }
                    }
                } else {
                    if(strcmp(mots_sub[j], "droite") == 0 || strcmp(mots_sub[j], "gauche") == 0)
                        sprintf(param1, "%s", mots_sub[j]);
                    if (strcmp(mots_sub[j], "cube") == 0 || strcmp(mots_sub[j], "carré") == 0 ||
                        strcmp(mots_sub[j], "balle") == 0 || strcmp(mots_sub[j], "boule") == 0 ||
                        strcmp(mots_sub[j], "objet") == 0 || strcmp(mots_sub[j], "obstacle") == 0) {
                        if (j + 1 < compt_sub && (strcmp(mots_sub[j + 1], "rouge") == 0 || strcmp(mots_sub[j + 1], "bleu") == 0 || strcmp(mots_sub[j + 1], "bleue") == 0 ||
                                                  strcmp(mots_sub[j + 1], "jaune") == 0 || strcmp(mots_sub[j + 1], "orange") == 0)) {
                            sprintf(param2, "%s %s", mots_sub[j], mots_sub[j + 1]);
                        } else {
                            sprintf(param2, "%s", mots_sub[j]);
                        }
                    }
                }
            }

            else if(strcmp(action, "compter") == 0 || strcmp(action, "compte") == 0) {
                if (strcmp(mots_sub[j], "cubes") == 0 || strcmp(mots_sub[j], "carrés") == 0 ||
                    strcmp(mots_sub[j], "balles") == 0 || strcmp(mots_sub[j], "boules") == 0 ||
                    strcmp(mots_sub[j], "objets") == 0 || strcmp(mots_sub[j], "obstacles") == 0) {
                    if (j + 1 < compt_sub && (strcmp(mots_sub[j + 1], "rouges") == 0 || strcmp(mots_sub[j + 1], "bleus") == 0 || strcmp(mots_sub[j + 1], "bleues") == 0 ||
                                              strcmp(mots_sub[j + 1], "jaunes") == 0 || strcmp(mots_sub[j + 1], "oranges") == 0)) {
                        sprintf(param2, "%s %s", mots_sub[j], mots_sub[j + 1]);
                    } else {
                        sprintf(param2, "%s", mots_sub[j]);
                    }
                }
            }

            else{

                //PHRASE DU TYPE "AVANCER DE [DISTANCE]"
                if (strcmp(mots_sub[j], "mètres") == 0 || strcmp(mots_sub[j], "mètre") == 0 || strcmp(mots_sub[j], "centimètres") == 0 || strcmp(mots_sub[j], "millimètres") == 0) {
                    if(strcmp(mots_sub[j-1], "et") == 0) {
                        result = convertDouble(mots_sub[j - 2]);
                    }else{
                        result = convertDouble(mots_sub[j - 1]);
                    }
                    if (strcmp(mots_sub[j], "centimètres") == 0) {
                        result *= 0.01;
                    } else if (strcmp(mots_sub[j], "millimètres") == 0) {
                        result *= 0.001;
                    }
                    sprintf(param2, "%.3f mètres ", result);                     // On converti le résultat en chaine et on les met ensemble
                }

                //PHRASE DU TYPE "AVANCER JUSQU'À L'[OBJET]"
                //PHRASE DU TYPE "TOURNER JUSQU'À LOCALISER L'[OBJET]"
                //PHRASE DU TYPE "TOURNER À [DIRECTION] JUSQU'À LOCALISER L'[OBJET]"
                if (strcmp(mots_sub[j], "boule") == 0 || strcmp(mots_sub[j], "balle") == 0 ||
                    strcmp(mots_sub[j], "carré") == 0 || strcmp(mots_sub[j], "cube") == 0) {
                    // Vérifier s'il y a un mot suivant pour la couleur.
                    if (j + 1 < compt_sub && (strcmp(mots_sub[j + 1], "rouge") == 0 || strcmp(mots_sub[j + 1], "bleu") == 0 || strcmp(mots_sub[j + 1], "bleue") == 0 ||
                                              strcmp(mots_sub[j + 1], "jaune") == 0 || strcmp(mots_sub[j + 1], "orange") == 0)) {
                        sprintf(param2, "%s %s ", mots_sub[j], mots_sub[j + 1]);         // On converti le résultat en chaine et on les met ensemble
                    } else {
                        sprintf(param2, "%s ", mots_sub[j]);
                    }
                }

                //PHRASE DU TYPE "TOURNER DE [VAL] DEGRÉS"
                //PHRASE DU TYPE "TOURNER À [DIRECTION] DE [VAL] DEGRÉS"
                if(strcmp(mots_sub[j], "droite") == 0 || strcmp(mots_sub[j], "gauche") == 0)
                    sprintf(param1, "%s", mots_sub[j]);

                if(strcmp(mots_sub[j], "degrés") == 0 || strcmp(mots_sub[j], "degré") == 0) {
                    if(strcmp(mots_sub[j-1], "et") == 0) {
                        result = convertDouble(mots_sub[j - 2]);
                    }else{
                        result = convertDouble(mots_sub[j - 1]);
                    }
                    sprintf(param2, "%.0f %s", result, mots_sub[j]);                 // On converti le résultat en chaine et on les met ensemble
                }
            }
        }
        strncpy(resultData.action, action, 20 - 1);
        // Asumiendo que param1 y param2 se llenan correctamente en el procesamiento
        strncpy(resultData.param1, param1, 20 - 1);
        strncpy(resultData.param2, param2, 20 - 1);
        strncpy(resultPhrase.type, type, 20 - 1);


        enqueue(q, resultData,resultPhrase); // Enqueue cada subfrase procesada
    }

}

void afficher_Action_es(char *phrase, Queue* q){
    char subphrases[5][200];
    char *mots[20];
    int compt = 0;
    char Avant_chiffre[100] = "", Chiffre_mots[100] = "", Apres_chiffre[100] = "";
    int chiffre;
    char ponctuation_chiffre[] = " ";
    char *mot;
    char ponctuation[] = " ',.!?";
    bool nombre_trouve = false;
    char *action;
    char ponctuation_sub[] = " ',.!?";
    char *mot_sub;
    int i, j;
    double result;
    int entre_flag = 0;
    int ou_flag=0;
    char *mots_sub[50];
    int compt_sub = 0;
    int subphr_compt = 0;
    ActionData resultData;
    typePhrase resultPhrase;


    for (i = 0; i < 5; i++) {
        subphrases[i][0] = '\0';
    }

    toLowercase(phrase);

    mot = strtok(phrase, ponctuation);
    while (mot != NULL && compt < 20) {
        mots[compt++] = mot;
        mot = strtok(NULL, ponctuation);
    }


// Dividir en subfrases y concatenarlas
    for (i = 0; i < compt; i++) {
        if (strcmp(mots[i], "luego") == 0) {
            subphr_compt++;
        } else {
            strcat(subphrases[subphr_compt], mots[i]);
            strcat(subphrases[subphr_compt], " ");
        }
    }

    for (i = 0; i <= subphr_compt; i++) {
        //printf("\nSubphrase %d: %s\n", i + 1, subphrases[i]);
        // Resetear las variables para la subfrase actual
        nombre_trouve = false;
        strcpy(Avant_chiffre, "");
        strcpy(Chiffre_mots, "");
        strcpy(Apres_chiffre, "");

        mot = strtok(subphrases[i], ponctuation_chiffre);
        while (mot != NULL) {
            if (detect_chiffre_es(mot)) {
                nombre_trouve = true;
                strcat(Chiffre_mots, mot);
                strcat(Chiffre_mots, " ");
            } else {
                if (!nombre_trouve) {
                    strcat(Avant_chiffre, mot);
                    strcat(Avant_chiffre, " ");
                } else {
                    strcat(Apres_chiffre, mot);
                    strcat(Apres_chiffre, " ");
                }
            }
            mot = strtok(NULL, ponctuation_chiffre);
        }

        // Procesar el número y reconstruir la subfrase
        chiffre = num_to_chiffre_tot_es(Chiffre_mots);
        sprintf(subphrases[i], "%s%d %s", Avant_chiffre, chiffre, Apres_chiffre);
    }

    // Imprimir las subfrases
    for (i = 0; i <= subphr_compt; i++) {
        //printf("\nSubphrase %d: %s\n", i + 1, subphrases[i]);

        compt_sub = 0;
        entre_flag = 0;

        char param1[20]="";
        char param2[20]="";
        char type[20]="";

        compt_sub = 0;
        mot_sub = strtok(subphrases[i], ponctuation_sub);
        while (mot_sub != NULL && compt_sub < 20) {
            mots_sub[compt_sub++] = mot_sub;
            mot_sub = strtok(NULL, ponctuation_sub);
        }

        //for (j = 0; j < compt_sub; j++) {
        //    printf("mot[%d]=%s\n", j, mots_sub[j]);
        //}
        for (j = 0; j < compt_sub; j++) {

            if(strcmp(mots_sub[0], "no") == 0)
                sprintf(type, "Negativa");
            else
                sprintf(type, "Afirmativa");

            if (strcmp(mots_sub[j], "avanzar") == 0 || strcmp(mots_sub[j], "avanza") == 0 || strcmp(mots_sub[j], "avances") == 0 ||
                strcmp(mots_sub[j], "retroceder") == 0 || strcmp(mots_sub[j], "retrocede") == 0 || strcmp(mots_sub[j], "retrocedas") == 0 ||
                strcmp(mots_sub[j], "girar") == 0 || strcmp(mots_sub[j], "gira") == 0 || strcmp(mots_sub[j], "gires") == 0 ||
                strcmp(mots_sub[j], "localizar") == 0 || strcmp(mots_sub[j], "localiza") == 0 || strcmp(mots_sub[j], "localices") == 0 ||
                strcmp(mots_sub[j], "encontrar") == 0 || strcmp(mots_sub[j], "encuentra") == 0 || strcmp(mots_sub[j], "encuentres") == 0 ||
                strcmp(mots_sub[j], "rodear") == 0 || strcmp(mots_sub[j], "rodea") == 0 || strcmp(mots_sub[j], "rodées") == 0 ||
                strcmp(mots_sub[j], "pasar") == 0 || strcmp(mots_sub[j], "pasa") == 0 || strcmp(mots_sub[j], "pases") == 0 ||
                strcmp(mots_sub[j], "contar") == 0 || strcmp(mots_sub[j], "cuenta") == 0 || strcmp(mots_sub[j], "cuentes") == 0) {
                action = mots_sub[j];
            }

            //PHRASE DU TYPE "CONTOURNER PAR LA [DIRECTION] L'[OBJET]"
            //PHRASE DU TYPE "CONTOURNER L'[OBJET] PAR LA [DIRECTION]"
            if(strcmp(action, "rodear") == 0 || strcmp(action, "rodea") == 0 || strcmp(mots_sub[j], "rodées") == 0) {

                if(strcmp(mots_sub[j], "derecha") == 0 || strcmp(mots_sub[j], "izquierda") == 0)
                    sprintf(param1, "%s", mots_sub[j]);

                if (strcmp(mots_sub[j], "cubo") == 0 || strcmp(mots_sub[j], "cuadrado") == 0 ||
                    strcmp(mots_sub[j], "bola") == 0 || strcmp(mots_sub[j], "pelota") == 0 ||
                    strcmp(mots_sub[j], "objeto") == 0 || strcmp(mots_sub[j], "obstaculo") == 0) {
                    if (j + 1 < compt_sub && (strcmp(mots_sub[j + 1], "rojo") == 0 || strcmp(mots_sub[j + 1], "roja") == 0 || strcmp(mots_sub[j + 1], "azul") == 0 ||
                                              strcmp(mots_sub[j + 1], "amarillo") == 0 || strcmp(mots_sub[j + 1], "amarilla") == 0 || strcmp(mots_sub[j + 1], "naranja") == 0)) {
                        sprintf(param2, "%s %s", mots_sub[j], mots_sub[j + 1]);
                    } else {
                        sprintf(param2, "%s", mots_sub[j]);
                    }
                }
            }

                //PHRASE DU TYPE "PASSER ENTRE [OBJET] ET [OBJET]"
                //PHRASE DU TYPE "PASSER À [DIRECTION] DE L'[OBJET]"
            else if (strcmp(action, "pasar") == 0 || strcmp(action, "pasa") == 0 || strcmp(mots_sub[j], "pases") == 0) {

                if(strcmp(mots_sub[j], "entre") == 0) {
                    entre_flag = 1;                                         // Mot "entre" trouvé
                    continue;
                }

                // Procesar objetos y colores después de "entre"
                if (entre_flag == 1 && strcmp(mots_sub[j], "y") == 0){
                    entre_flag = 0;                                         // On remet le flag de "entre" a 0
                    continue;
                }

                if (entre_flag == 1) {
                    if (strcmp(mots_sub[j], "cubo") == 0 || strcmp(mots_sub[j], "cuadrado") == 0 ||
                        strcmp(mots_sub[j], "bola") == 0 || strcmp(mots_sub[j], "pelota") == 0 ||
                        strcmp(mots_sub[j], "objeto") == 0 || strcmp(mots_sub[j], "obstaculo") == 0) {
                        if (j + 1 < compt_sub && (strcmp(mots_sub[j + 1], "rojo") == 0 || strcmp(mots_sub[j + 1], "roja") == 0 || strcmp(mots_sub[j + 1], "azul") == 0 ||
                                                  strcmp(mots_sub[j + 1], "amarillo") == 0 || strcmp(mots_sub[j + 1], "amarilla") == 0 || strcmp(mots_sub[j + 1], "naranja") == 0)) {
                            sprintf(param1, "%s %s", mots_sub[j], mots_sub[j + 1]);
                        } else {
                            sprintf(param1, "%s", mots_sub[j]);
                        }
                    }
                } else {
                    if (strcmp(mots_sub[j], "cubo") == 0 || strcmp(mots_sub[j], "cuadrado") == 0 ||
                        strcmp(mots_sub[j], "bola") == 0 || strcmp(mots_sub[j], "pelota") == 0 ||
                        strcmp(mots_sub[j], "objeto") == 0 || strcmp(mots_sub[j], "obstaculo") == 0) {
                        if (j + 1 < compt_sub && (strcmp(mots_sub[j + 1], "rojo") == 0 || strcmp(mots_sub[j + 1], "roja") == 0 || strcmp(mots_sub[j + 1], "azul") == 0 ||
                                                  strcmp(mots_sub[j + 1], "amarillo") == 0 || strcmp(mots_sub[j + 1], "amarilla") == 0 || strcmp(mots_sub[j + 1], "naranja") == 0)) {
                            sprintf(param2, "%s %s", mots_sub[j], mots_sub[j + 1]);
                        } else {
                            sprintf(param2, "%s", mots_sub[j]);
                        }
                    }
                }
            }

            else if(strcmp(action, "localizar") == 0 || strcmp(action, "localiza") == 0 || strcmp(action, "localices") == 0 ||
                    strcmp(action, "encontrar") == 0 || strcmp(action, "encuentra") == 0 || strcmp(action, "encuentres") == 0) {

                // Procesar objetos y colores después de "entre"
                if (ou_flag == 0 && strcmp(mots_sub[j], "o") == 0){
                    ou_flag = 1;                                         // On remet le flag de "ou" a 1
                    continue;
                }

                if (ou_flag == 0) {
                    if (strcmp(mots_sub[j], "cubo") == 0 || strcmp(mots_sub[j], "cuadrado") == 0 ||
                        strcmp(mots_sub[j], "bola") == 0 || strcmp(mots_sub[j], "pelota") == 0 ||
                        strcmp(mots_sub[j], "objeto") == 0 || strcmp(mots_sub[j], "obstaculo") == 0) {
                        if (j + 1 < compt_sub && (strcmp(mots_sub[j + 1], "rojo") == 0 || strcmp(mots_sub[j + 1], "roja") == 0 || strcmp(mots_sub[j + 1], "azul") == 0 ||
                                                  strcmp(mots_sub[j + 1], "amarillo") == 0 || strcmp(mots_sub[j + 1], "amarilla") == 0 || strcmp(mots_sub[j + 1], "naranja") == 0)) {
                            sprintf(param1, "%s %s", mots_sub[j], mots_sub[j + 1]);
                        } else {
                            sprintf(param1, "%s", mots_sub[j]);
                        }
                    }
                } else {
                    if (strcmp(mots_sub[j], "cubo") == 0 || strcmp(mots_sub[j], "cuadrado") == 0 ||
                        strcmp(mots_sub[j], "bola") == 0 || strcmp(mots_sub[j], "pelota") == 0 ||
                        strcmp(mots_sub[j], "objeto") == 0 || strcmp(mots_sub[j], "obstaculo") == 0) {
                        if (j + 1 < compt_sub && (strcmp(mots_sub[j + 1], "rojo") == 0 || strcmp(mots_sub[j + 1], "roja") == 0 || strcmp(mots_sub[j + 1], "azul") == 0 ||
                                                  strcmp(mots_sub[j + 1], "amarillo") == 0 || strcmp(mots_sub[j + 1], "amarilla") == 0 || strcmp(mots_sub[j + 1], "naranja") == 0)) {
                            sprintf(param2, "%s %s", mots_sub[j], mots_sub[j + 1]);
                        } else {
                            sprintf(param2, "%s", mots_sub[j]);
                        }
                    }
                }
            }

            else if(strcmp(action, "contar") == 0 || strcmp(action, "cuenta") == 0 || strcmp(action, "cuentes") == 0) {
                if (strcmp(mots_sub[j], "cubos") == 0 || strcmp(mots_sub[j], "cuadrados") == 0 ||
                    strcmp(mots_sub[j], "bolas") == 0 || strcmp(mots_sub[j], "pelotas") == 0 ||
                    strcmp(mots_sub[j], "objetos") == 0 || strcmp(mots_sub[j], "obstaculos") == 0) {
                    if (j + 1 < compt_sub && (strcmp(mots_sub[j + 1], "rojos") == 0 || strcmp(mots_sub[j + 1], "rojas") == 0 || strcmp(mots_sub[j + 1], "azules") == 0 ||
                                              strcmp(mots_sub[j + 1], "amarillos") == 0 || strcmp(mots_sub[j + 1], "amarillas") == 0 || strcmp(mots_sub[j + 1], "naranjas") == 0)) {
                        sprintf(param2, "%s %s", mots_sub[j], mots_sub[j + 1]);
                    } else {
                        sprintf(param2, "%s", mots_sub[j]);
                    }
                }
            }

            else{

                //PHRASE DU TYPE "AVANCER DE [DISTANCE]"
                if (strcmp(mots_sub[j], "metros") == 0 || strcmp(mots_sub[j], "metro") == 0 || strcmp(mots_sub[j], "centimetros") == 0 || strcmp(mots_sub[j], "milimetros") == 0) {
                    if(strcmp(mots_sub[j-1], "y") == 0) {
                        result = convertDouble(mots_sub[j - 2]);
                    }else{
                        result = convertDouble(mots_sub[j - 1]);
                    }
                    if (strcmp(mots_sub[j], "centimetros") == 0) {
                        result *= 0.01;
                    } else if (strcmp(mots_sub[j], "milimetros") == 0) {
                        result *= 0.001;
                    }
                    sprintf(param2, "%.3f metros ", result);                     // On converti le résultat en chaine et on les met ensemble
                }

                //PHRASE DU TYPE "AVANCER JUSQU'À L'[OBJET]"
                //PHRASE DU TYPE "TOURNER JUSQU'À LOCALISER L'[OBJET]"
                //PHRASE DU TYPE "TOURNER À [DIRECTION] JUSQU'À LOCALISER L'[OBJET]"
                if (strcmp(mots_sub[j], "bola") == 0 || strcmp(mots_sub[j], "pelota") == 0 ||
                    strcmp(mots_sub[j], "cuadrado") == 0 || strcmp(mots_sub[j], "cubo") == 0) {
                    // Vérifier s'il y a un mot suivant pour la couleur.
                    if (j + 1 < compt_sub && (strcmp(mots_sub[j + 1], "rojo") == 0 || strcmp(mots_sub[j + 1], "roja") == 0 || strcmp(mots_sub[j + 1], "azul") == 0 ||
                                              strcmp(mots_sub[j + 1], "amarillo") == 0 || strcmp(mots_sub[j + 1], "amarilla") == 0 || strcmp(mots_sub[j + 1], "naranja") == 0)) {
                        sprintf(param2, "%s %s ", mots_sub[j], mots_sub[j + 1]);         // On converti le résultat en chaine et on les met ensemble
                    } else {
                        sprintf(param2, "%s ", mots_sub[j]);
                    }
                }


                //PHRASE DU TYPE "TOURNER DE [VAL] DEGRÉS"
                //PHRASE DU TYPE "TOURNER À [DIRECTION] DE [VAL] DEGRÉS"
                if(strcmp(mots_sub[j], "derecha") == 0 || strcmp(mots_sub[j], "izquierda") == 0)
                    sprintf(param1, "%s", mots_sub[j]);

                if(strcmp(mots_sub[j], "grados") == 0 || strcmp(mots_sub[j], "grado") == 0) {
                    if(strcmp(mots_sub[j-1], "y") == 0) {
                        result = convertDouble(mots_sub[j - 2]);
                    }else{
                        result = convertDouble(mots_sub[j - 1]);
                    }
                    sprintf(param2, "%.0f %s", result, mots_sub[j]);                 // On converti le résultat en chaine et on les met ensemble
                }
            }
        }
        strncpy(resultData.action, action, 20 - 1);
        // Asumiendo que param1 y param2 se llenan correctamente en el procesamiento
        strncpy(resultData.param1, param1, 20 - 1);
        strncpy(resultData.param2, param2, 20 - 1);
        strncpy(resultPhrase.type, type, 20 - 1);


        enqueue(q, resultData,resultPhrase); // Enqueue cada subfrase procesada
    }
}
