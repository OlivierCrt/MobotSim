#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "image_process.h"
#include <unistd.h>


/**
 * @mainpage Traitement d'image
 *
 * @section intro Introduction
 * Cette partie de code permet de detecter des pixels dans differentes plages de couleurs RGB.    
 * Elle permet aussi de savoir si ces pixels détectés forment des objets et ainsi les utiliser dans les autres partie du pfr1.
 *
 * @section usage Usage
 * - Inclure le header image_process.h dans votre projet.
 * - Utiliser les differentes fonctions de traitement.
 *
 * @section features Fonctionnalités
 * - Detection d'objets de couleurs orange,bleu ou jaune dans une image.
 * - Groupement et manipulation de pixels en utilisant la detection de couleur.
 * - Trouver le centre d'objet dans une image.
 * - Trouver le nombre d'objet dans une image.(1 par couleur)
 * - Trouver le rayon d'un objet.
 * - Ecrire dans un nouveau fichier texte les matrices des plages detectés.
 *
 * @section example Example
 * @code
 * #include <stdio.h>
 * #include <stdlib.h>
 * #include "image_process.h"
 *
 * int main() {
 *     // code
 *     return 0;
 * }
 * @endcode
 */

/**
 * @file
 * @brief Ce fichier rassemble les fonctions concernant la detection d'objet dans une image.
 * 
 * 
*/

/**
 * @defgroup Groupe_pixel
 * @{
*/
/**
 * 
 * 
 *  
 * @brief Structure d'un groupe de pixel.
 * @struct Groupe_Pixel_s
 * 
 */
struct Groupe_Pixel_s {
    int nbpixel_g ;/**<Nombre de pixels correspondant au groupe.  */
    int ** matrice_associe ;/**<Matrice de la taille de l'image de l'entrée standart, composée de 0 et de 1, 1 pour un pixel dans la plage.  */
    char* couleur ;/**<Couleur du groupe.*/
    
};

//Allocation pixel
/**
 * @brief Fonction d'allocation pour un pointeur vers un groupe de pixels.
 * @param nbp Nombre de pixel du groupe.
 * @param matrice_ass_param Tableau à deux dimensions concernant la couleur.
 * @param couleur Chaîne de caractère correspondant à la couleur du groupe.
 * @return Pointeur vers un groupe de pixel.
 * */
Groupe_Pixel_ptr alloc_Groupe_Pixel(int nbp , int** matrice_ass_param,char * couleur){
    Groupe_Pixel_ptr res = malloc(sizeof(struct Groupe_Pixel_s)) ;
    res->nbpixel_g = nbp ;
    res->matrice_associe = matrice_ass_param ;
    res->couleur = couleur ;
    return res ;
}



//Detection de plage de couleur

/**
 * @brief Fonction de detection de pixel dans la plage de couleur Jaune , utilisation de seuil RGB avec valeur min et max.
 * @param matriceR Tableau à deux dimension correspondant à la matrice initiale du Rouge.
 * @param matriceG Tableau à deux dimension correspondant à la matrice initiale du Vert.
 * @param matriceB Tableau à deux dimension correspondant à la matrice initiale du Bleu.
 * @param hauteur Hauteur de l'image iniatiale/tableau.
 * @param largeur Largeur de l'image initaiale/tableau.
 * @return Pointeur vers un groupe de pixel, on ne peut pas encore dissocier le groupe d'un objet @see isObjet()
*/

Groupe_Pixel_ptr detecterPixelsJaune(int **matriceR, int ** matriceG, int ** matriceB,int hauteur , int largeur) {
    int ** objetDetecte = malloc(hauteur * sizeof(int * )) ;
    //allocation
    for (int i = 0 ; i<hauteur ; i++){
        objetDetecte[i] = malloc(largeur * sizeof(int));
        for (int j =0 ; j<largeur ; j++){
            objetDetecte[i][j] = 0 ;
        }
    }






    // Plages, on changes les plages en fonction des couleurs qu on veut detecter ici  r
    int seuilRougeMin = 200;
    int seuilRougeMax = 255;
    int seuilVertMin = 180;
    int seuilVertMax = 255;
    int seuilBleuMin = 0;
    int seuilBleuMax = 100;

    int nbPixelsObjet = 0;



    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            if (matriceR[i][j] >= seuilRougeMin && matriceR[i][j] <= seuilRougeMax &&
                matriceG[i][j] >= seuilVertMin && matriceG[i][j] <= seuilVertMax &&
                matriceB[i][j] >= seuilBleuMin && matriceB[i][j] <= seuilBleuMax) {
                
                objetDetecte[i][j] = 1; // Marquer le pixel
                nbPixelsObjet++;
            }
        }
    }

    // si nbpixel trop élevé dire que ce n est pas un objet mais un arriere plan sinon dfs et regroupement 
    




    return (alloc_Groupe_Pixel(nbPixelsObjet , objetDetecte,"Jaune"));
}
Groupe_Pixel_ptr detecterPixelsBleu(int **matriceR, int ** matriceG, int ** matriceB,int hauteur , int largeur) {
    int ** objetDetecte = malloc(hauteur * sizeof(int * )) ;
    //allocation
    for (int i = 0 ; i<hauteur ; i++){
        objetDetecte[i] = malloc(largeur * sizeof(int));
        for (int j =0 ; j<largeur ; j++){
            objetDetecte[i][j] = 0 ;
        }
    }
    // Plages, on changes les plages en fonction des couleurs qu on veut detecter ici  r
    int seuilRougeMin = 0;
    int seuilRougeMax = 10;
    int seuilVertMin = 21;
    int seuilVertMax = 94;
    int seuilBleuMin = 48;
    int seuilBleuMax = 255;

    int nbPixelsObjet = 0;



    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            if (matriceR[i][j] >= seuilRougeMin && matriceR[i][j] <= seuilRougeMax &&
                matriceG[i][j] >= seuilVertMin && matriceG[i][j] <= seuilVertMax &&
                matriceB[i][j] >= seuilBleuMin && matriceB[i][j] <= seuilBleuMax) {
                
                objetDetecte[i][j] = 1; // Marquer le pixel
                nbPixelsObjet++;
            }
        }
    }
    return (alloc_Groupe_Pixel(nbPixelsObjet , objetDetecte,"Bleu"));
}
Groupe_Pixel_ptr detecterPixelsOrange(int **matriceR, int ** matriceG, int ** matriceB,int hauteur , int largeur) {
    int ** objetDetecte = malloc(hauteur * sizeof(int * )) ;
    //allocation
    for (int i = 0 ; i<hauteur ; i++){
        objetDetecte[i] = malloc(largeur * sizeof(int));
        for (int j =0 ; j<largeur ; j++){
            objetDetecte[i][j] = 0 ;
        }
    }
    // Plages, on changes les plages en fonction des couleurs qu on veut detecter ici  r
    int seuilRougeMin = 136;
    int seuilRougeMax = 250;
    int seuilVertMin = 27;
    int seuilVertMax = 56;
    int seuilBleuMin = 0;
    int seuilBleuMax = 10;

    int nbPixelsObjet = 0;



    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            if (matriceR[i][j] >= seuilRougeMin && matriceR[i][j] <= seuilRougeMax &&
                matriceG[i][j] >= seuilVertMin && matriceG[i][j] <= seuilVertMax &&
                matriceB[i][j] >= seuilBleuMin && matriceB[i][j] <= seuilBleuMax) {
                
                objetDetecte[i][j] = 1; // Marquer le pixel
                nbPixelsObjet++;
            }
        }
    }
    return (alloc_Groupe_Pixel(nbPixelsObjet , objetDetecte,"Orange"));
}
/**@}*/


// Fonctions de renvoi pour l'intégration
/**
 * @defgroup Fonctions_utiles
 * @{
*/
/**
 * @brief Fonction pour trouver le milieu d'un objet, ne donne le milieu uniquement si le groupe est un objet @see isObjet().
 *
 * @param groupe Pointeur vers le groupe de pixels.
 * @param largeur Largeur de l'image.
 * @param hauteur Hauteur de l'image.
 * @return Tableau d'entiers contenant les coordonnées du milieu [hauteur, largeur].Vide si impossible.
 */
int * trouver_milieu(Groupe_Pixel_ptr groupe, int largeur , int hauteur){//null si pas un objet
    int * res =malloc(2*sizeof(int));
    if (!isObjet(groupe)){
        return(res);//liste 
    }
    int imin_h=60000 ;
    int jmin_l = 60000;
    int imax_h,jmax_l ;
    for (int i =0 ; i<hauteur ; i++){
        for(int j = 0 ; j<largeur ; j++){
            if (groupe->matrice_associe[i][j] == 1 && imin_h> i){
                imin_h = i ;
            }
            if (groupe->matrice_associe[i][j] == 1){
                imax_h =i;
            }
        }
    }

    for (int j = 0 ; j<largeur ; j++){
        for(int i =0 ; i<hauteur ; i++){
            if (groupe->matrice_associe[i][j] == 1 && jmin_l> j){
                jmin_l = j ;
            }
            if (groupe->matrice_associe[i][j] == 1){
                jmax_l =j;
            }
        }
    }
    res[0] =jmin_l+(jmax_l-jmin_l)/2 ; //hauteur
    res[1] = imin_h+(imax_h-imin_h)/2 ;
    if(groupe->couleur == "Bleu"){
        printf("Le milieu de l'objet \x1B[34m%s\x1B[0m est de coordonnées : [%d,%d]\n",groupe->couleur,res[0],res[1]);

    }
    else if(groupe->couleur == "Jaune"){
        printf("Le milieu de l'objet \x1B[33m%s\x1B[0m est de coordonnées : [%d,%d]\n",groupe->couleur,res[0],res[1]);
    }
    else{
        printf("Le milieu de l'objet \x1B[38;5;208m%s\x1B[0m est de coordonnées : [%d,%d]\n",groupe->couleur,res[0],res[1]);
    }
      

    return (res);

}
/**
 * @brief Fonction de calcul de rayon d'un objet .
 * @param objet Objet de couleur.La fonction effectue un controle pour verifier que c'est bien un objet.
 * @param largeur Largeur de l'image.
 * @param hauteur Hauteur de l'image.
 * @return Entier correspondant au rayon.-1 si impossible.
*/
int  trouver_rayon(Groupe_Pixel_ptr objet, int largeur , int hauteur){
    if (!isObjet(objet)){
        return(-1);
    }
    int imin_h=60000 ;
    int jmin_l = 60000;
    int imax_h,jmax_l ;
    for (int i =0 ; i<hauteur ; i++){
        for(int j = 0 ; j<largeur ; j++){
            if (objet->matrice_associe[i][j] == 1 && imin_h> i){
                imin_h = i ;
            }
            if (objet->matrice_associe[i][j] == 1){
                imax_h =i;
            }
        }
    }
    for (int j = 0 ; j<largeur ; j++){
        for(int i =0 ; i<hauteur ; i++){
            if (objet->matrice_associe[i][j] == 1 && jmin_l> j){
                jmin_l = j ;
            }
            if (objet->matrice_associe[i][j] == 1){
                jmax_l =j;
            }
        }
    }
    int maxres = (jmax_l-jmin_l)/2 ;
    if ((imax_h-imin_h)/2>maxres){
        maxres = (imax_h-imin_h)/2 ;
    }

    if(objet->couleur == "Bleu"){
        printf("Le rayon de l'objet de couleur \x1B[34m%s\x1B[0m est : %d\n",objet->couleur,maxres);

    }
    else if (objet->couleur == "Jaune"){
        printf("Le rayon de l'objet de couleur \x1B[33m%s\x1B[0m est : %d\n",objet->couleur,maxres);

    }
    else {
        printf("Le rayon de l'objet de couleur \x1B[38;5;208m%s\x1B[0m est : %d\n",objet->couleur,maxres);
        
    }
    
    return maxres;





}
/**
 * @brief Fonction getter de la couleur d'un groupe de pixel.
 * @param groupe Groupe de pixel.
 * @return Chaîne de caractère correspondant à la couleur du groupe.
 * 
*/
char* get_couleur(Groupe_Pixel_ptr groupe){
    return(groupe->couleur);

}
/**
 * @brief Fonction pour connaitre si un groupe de pixel est un objet.
 * @return Booleen.
*/
bool isObjet (Groupe_Pixel_ptr groupe){
    return (groupe->nbpixel_g>30 );

}
/**
 * @}
*/

//Pas demandé dans le dossier mais pratique pour visualiser les plages detectées en noir et blanc
/**
 * @defgroup Hors_spec
 * @{
*/
/**
 * @brief Fonction d'écriture dans un nouveau fichier texte une image en noir et blanc correspondant à une couleur.
 * @param groupePixel Groupe de pixel de couleur.
 * @param hauteur Hauteur de l'image.
 * @param largeur Largeur de l'image.
 * @param nomfichier Nom du fichier avec extension.(.dat)
*/
void ecrireMatriceDansFichier(Groupe_Pixel_ptr groupePixel, int hauteur, int largeur,char*nomfichier) {
    FILE *fichier = fopen(nomfichier, "w"); // Ouvre un fichier en écriture
   



    if (fichier == NULL || !isObjet(groupePixel)) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    fprintf(fichier,"%d  ",hauteur);
    fprintf(fichier,"%d  ",largeur);
    fprintf(fichier,"%d\n",3);
    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            fprintf(fichier, "%d ", groupePixel->matrice_associe[i][j]); // Écrit la valeur dans le fichier
        }
        fprintf(fichier, "\n"); // Passage à la ligne suivante dans le fichier
    }

    fclose(fichier); // Ferme le fichier
}
/**
 * @brief Fonction de parcours en profondeur ( Deep First Search) récursive.
 * @param matrice_p Matrice à explorer.( Avec : matrice[hauteur][largeur]).
 * @param hauteur Hauteur de l'image/matrice.
 * @param largeur Largeur de l'image/matrice.
 * @param deb_i Indice de la hauteur du début du dfs.
 * @param deb_j Indice de la largeur du début du dfs.
 * @param visite Matrice des élements deja visité, marqués par un 1.
*/
int dfs (int ** matrice_p , int hauteur , int largeur , int deb_i , int deb_j ,int ** visite){
    if (deb_i < 0 || deb_i >= hauteur || deb_j < 0 || deb_j >= largeur || visite[deb_i][deb_j] == 1 || matrice_p[deb_i][deb_j] == 0) {
        // Conditions d'arrêt (coordonnées invalides, déjà visité, ou pixel non marqué)
        return 0;
    }
    visite[deb_i][deb_j] = 1 ;
    int taille = 1 ;

    //parcours voisins

    taille = taille +dfs(matrice_p , hauteur , largeur , deb_i +1 , deb_j , visite) ;
    taille = taille +dfs(matrice_p , hauteur , largeur , deb_i -1 , deb_j , visite);
    taille = taille +dfs(matrice_p , hauteur , largeur , deb_i , deb_j+1 , visite);
    taille = taille +dfs(matrice_p , hauteur , largeur , deb_i  , deb_j-1 , visite);
    return taille ;


}
/**
 * @brief Fonction qui repère et isole le plus gros groupe de pixel dans une image. C'est en fait une fonction d'elimination de bruit. 
 * @param matrice Tableau d'entier de 0 et de 1 correspondant à une couleur. Le traitement s'effectue sur cette matrice.
 * @param hauteur Hauteur de l'image/matrice.
 * @param largeur Largeur de l'image/matrice.
 * 
*/
void trouverLePlusGros (int ** matrice , int hauteur, int largeur){
    int ** visite = malloc(hauteur * sizeof(int * )) ;
    //allocation
    for (int i = 0 ; i<hauteur ; i++){
    
        visite[i] = malloc(largeur * sizeof(int));
        for (int j =0 ; j<largeur ; j++){
            visite[i][j] = 0 ;
        }
    }
    int taillemax = 0 ;
    int lpg_deb_i = -1 ;
    int lpg_deb_j =-1 ;


    for (int i =0 ; i<hauteur ; i++){
        for(int j =0 ; j<largeur ; j++){
            if (matrice[i][j] == 1 && visite[i][j] == 0){
                int taille_actuelle = dfs(matrice , hauteur, largeur,i , j ,visite);
                if (taille_actuelle > taillemax){
                    taillemax = taille_actuelle ;
                    lpg_deb_i = i ;
                    lpg_deb_j = j ;
                }
            }
        }
    }
    //maj de la matrice et garder lpg
    for (int i=0; i<hauteur ; i++){
        for(int j =0 ; j<largeur ; j++){
            if (matrice[i][j] == 1 && (i!= lpg_deb_i ||j!= lpg_deb_j)){
                matrice[i][j] = 0 ;
            }
        }
    }








}
/**
 *  @}
*/
void main_it(int *rayon_bleu, int *rayon_jaune, int *rayon_orange,int **milieu_bleu, int **milieu_jaune, int **milieu_orange, char* nomFichier){

int largeur,hauteur,nbcompo ;



 FILE *fichier = fopen(nomFichier, "r");

    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier.");
        return ;
    }


fscanf(fichier,"%d",&largeur) ;
fscanf(fichier,"%d",&hauteur) ;
fscanf(fichier,"%d", &nbcompo) ;
printf("\n\n");
printf("\x1B[1m---------------TRAITEMENT D'IMAGE--------------\x1B[0m\n\n");
printf("\x1B[4mCARACTERISTIQUES IMAGE:\x1B[0m\n\n");
printf("Largeur : %d\n",largeur);
printf("Hauteur : %d\n",hauteur);
printf("Nbcompo : %d\n",nbcompo);
printf("\n");
//Matrice initiales
int ** matrice_init_red =malloc(hauteur*sizeof(int*));
int ** matrice_init_green =malloc(hauteur*sizeof(int*));
int ** matrice_init_blue =malloc(hauteur*sizeof(int*));
//Allocations
for (int p = 0; p < hauteur; p++) {
        matrice_init_red[p] = malloc(largeur * sizeof(int));
        matrice_init_green[p] = malloc(largeur * sizeof(int));
        matrice_init_blue[p] = malloc(largeur * sizeof(int));
    }
//R
for (int i=0 ;i<hauteur ; i++){
    for(int j=0 ; j<largeur ; j++){
        fscanf(fichier,"%d",&matrice_init_red[i][j]);
    }
}
//G
int x,y ;
for (x=0 ;x<hauteur ; x++){
    for(y=0 ; y<largeur ; y++){
        fscanf(fichier,"%d",&matrice_init_green[x][y]);
    }
}
//B
int a,b ;
for (a=0 ;a<hauteur ; a++){
    for(b=0 ; b<largeur ; b++){
        fscanf(fichier,"%d",&matrice_init_blue[a][b]);
    }
}
Groupe_Pixel_ptr objet_poss_bleu = detecterPixelsBleu(matrice_init_red , matrice_init_green , matrice_init_blue , hauteur , largeur);
Groupe_Pixel_ptr objet_poss_jaune = detecterPixelsJaune(matrice_init_red , matrice_init_green , matrice_init_blue , hauteur , largeur);
Groupe_Pixel_ptr objet_poss_Orange = detecterPixelsOrange(matrice_init_red , matrice_init_green , matrice_init_blue , hauteur , largeur);
//dfs et lpg
//trouverLePlusGros(objet_poss_Orange->matrice_associe ,hauteur , largeur );
//dETECTION
printf("\x1B[4mDETECTIONS DES OBJETS :\x1B[0m\n\n");
if(isObjet(objet_poss_bleu)){printf("Objet de couleur \x1B[34mBleu\x1B[0m détecté!\n");}
if(isObjet(objet_poss_jaune)){printf("Objet de couleur \x1B[33mJaune\x1B[0m détecté!\n");}
if(isObjet(objet_poss_Orange)){printf("Objet de couleur \x1B[38;5;208mOrange\x1B[0m détecté!\n");}
if(!isObjet(objet_poss_bleu) && !isObjet(objet_poss_jaune) && !isObjet(objet_poss_Orange)){
    printf("\x1B[31m\x1B[1mAucun objet détecté!\x1B[0m\n");
}
//Milieux
printf("\n\x1B[4mCALCULS DES MILIEUX :\x1B[0m\n\n");
*milieu_bleu = trouver_milieu(objet_poss_bleu, largeur, hauteur);
*milieu_jaune = trouver_milieu(objet_poss_jaune, largeur, hauteur);
*milieu_orange = trouver_milieu(objet_poss_Orange, largeur, hauteur);
if(!isObjet(objet_poss_bleu) && !isObjet(objet_poss_jaune) && !isObjet(objet_poss_Orange)){
    printf("\x1B[31m\x1B[1mCalcul des milieux impossible il n'y a pas d'objet!\x1B[0m\n");
}
printf("\n\x1B[4mRAYON DES OBJETS\x1B[0m\n\n");
//rayons
*rayon_bleu = trouver_rayon(objet_poss_bleu, largeur, hauteur);
*rayon_jaune = trouver_rayon(objet_poss_jaune, largeur, hauteur);
*rayon_orange = trouver_rayon(objet_poss_Orange, largeur, hauteur);
if(!isObjet(objet_poss_bleu) && !isObjet(objet_poss_jaune) && !isObjet(objet_poss_Orange)){
    printf("\x1B[31m\x1B[1mCalcul des rayons impossible il n'y a pas d'objet!\x1B[0m\n");
}
printf("-----------------------------------------------\n\n");
//Fichier txt avec les matrices des plages de la forme vue en TP, j'utilise le script de M.Ferrané afin de les visualiser par la suite
//if (isObjet(objet_poss_bleu))  { ecrireMatriceDansFichier(objet_poss_bleu,hauteur,largeur,"obj_bleu.dat"); };

//if (isObjet(objet_poss_jaune))  { ecrireMatriceDansFichier(objet_poss_jaune,hauteur,largeur,"obj_jaune.dat"); };

//if (isObjet(objet_poss_Orange))  { ecrireMatriceDansFichier(objet_poss_Orange,hauteur,largeur,"obj_orange.dat"); };
  

return;
}




double convertDouble(char *str) {    //Fonction pour transformer des str en double.
    char *temp;
    double val = strtod(str, &temp);
    return val;
}

void toLowercase(char *str) {    //Fonction pour passer n'importe quelle chaine en minuscule.
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char) str[i]);
    }
}

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

Queue createQueue() {    //Initialise et renvoie une nouvelle file vide.
    Queue q;
    q.front = q.rear = NULL;
    q.size = 0;
    return q;
}

void enqueue(Queue* q, ActionData data) {    //Rajoute un élément à la file.
    Node* temp = (Node*) malloc(sizeof(Node));
    temp->data = data;
    temp->next = NULL;

    if (q->rear == NULL) {    //Si la file est vide, le nouvel élément devient à la fois le premier et le dernier élément.
        q->front = q->rear = temp;
        q->size = 1;
        return;
    }

    q->rear->next = temp;    //Sinon, il est rajouté à la fin et devient le nouvel élément rear.
    q->rear = temp;
    q->size++;    //Incrémente la taille de la file.
}

ActionData dequeue(Queue* q) {    //Dégage un élément à la file.
    if (q->front == NULL) {    //Si la file est deja vide on affichera une erreur.
        fprintf(stderr, "Erreur: La file est deja vide.\n");
        exit(EXIT_FAILURE);
    }

    Node *temp = q->front;    //Un pointeur temporaire temp est créé pour conserver le pointeur vers le noeud de tête actuel, qui sera retiré.
    ActionData data = temp->data;  //On copie tous les parametres de data.

    q->front = q->front->next;    //Le pointeur front de la file est déplacé vers le nœud suivant, car le nœud de tête actuel est sur le point d'être supprimé.
    if (q->front == NULL) {    //Si après cette opération, q->front devient NULL, cela signifie que la file est maintenant vide.
        q->rear = NULL;    //Par conséquent, q->rear est également mis à NULL.
    }
    q->size--;    //Et on met a jour la taille de la file.

    free(temp);    //On libere de la mémoire.
    return data;    //La focntion retourne finalement les parametres de data qui viennent d'étre enlevés.
}

int isQueueEmpty(Queue q) {    //Fonction qui nous indiquera simplement si la file est vide ou pas et renvoie 1 pour un front NULL.
    return (q.front == NULL);
}

int str_to_num_fr(char *nombre) {    //Retournera un entier en fonction du str qui lui correspond.
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
}


int num_to_chiffre_tot_fr(char *str) {    //Utilisera les chiffres obtenus séparement pour les traiter après et obtenir le chiffre total.
    char *mot;
    char ponctuation[] = " ',.-";
    int total = 0, temp = 0;

    mot = strtok(str, ponctuation);    //Sépare les mots de la phrase (str) pour chaque ponctuation qu'on a déjà defini.
    while (mot != NULL) {
        int num = str_to_num_fr(mot);    //Traitement des chiffres (somme ou multiplication, dépendant de leurs utilisation dans une phrase.
        if (num == 1000 || num == 100 || num == 20) {
            temp = (temp == 0 ? 1 : temp) * num;
            total += temp;
            temp = 0;
        } else {
            temp += num;
        }
        mot = strtok(NULL, ponctuation);    //Appel au mot defini.
    }
    total += temp;    //On rajoute les valeurs réstants.
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
    total += temp;
    return total;
}


bool detect_chiffre_fr(const char *word) {    //Fonction ayant le role de détecter si le str introduit corréspond à un chiffre. 
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


    for (i = 0; i < 5; i++) {    //Initialise toutes les sous-phrases à vide.
        subphrases[i][0] = '\0';
    }

    toLowercase(phrase);


    mot = strtok(phrase, ponctuation);
    while (mot != NULL && compt < 20) {
        mots[compt++] = mot;
        mot = strtok(NULL, ponctuation);
    }

    //On divise les sous-phrases à chaque fois qu'on trouve un "puis" et on passe a la prochaine sous-phrase, si non on garde la phrase traité diréctement comme une sous-phrase.
    for (i = 0; i < compt; i++) {
        if (strcmp(mots[i], "puis") == 0) {
            subphr_compt++;
        } else {
            strcat(subphrases[subphr_compt], mots[i]);
            strcat(subphrases[subphr_compt], " ");
        }
    }

    for (i = 0; i <= subphr_compt; i++) {
        //printf("\nSubphrase %d: %s\n", i + 1, subphrases[i]);

        //On réinitialise les variables suivantes à chaque itération pour ne pas avoir des problèmes en mémoire.
        nombre_trouve = false;
        strcpy(Avant_chiffre, "");
        strcpy(Chiffre_mots, "");
        strcpy(Apres_chiffre, "");

        mot = strtok(subphrases[i], ponctuation_chiffre);    //On diférentie les parties de la sous-phrase qui definissent les chiffres ou pas.
        while (mot != NULL) {
            if (detect_chiffre_fr(mot)) {    //Si on détecte un mot corréspondant à un chiffre on les garde comme "Chiffre_mots".
                nombre_trouve = true;
                strcat(Chiffre_mots, mot);
                strcat(Chiffre_mots, " ");
            } else {
                if (!nombre_trouve) {    //Si les mots se trouvent avant la détection des mots corréspondant aux chiffres on les garde comme "Avant_chiffre".
                    strcat(Avant_chiffre, mot);
                    strcat(Avant_chiffre, " ");
                } else {    //Si les mots se trouvent après la détection des mots corréspondant aux chiffres on les garde comme "Apres_chiffre".
                    strcat(Apres_chiffre, mot);
                    strcat(Apres_chiffre, " ");
                }
            }
            mot = strtok(NULL, ponctuation_chiffre);
        }

        //On transforme "Chiffre_mots" en chiffre puis on réconstruit la sous-phrase initiale en charactéres et chiffres
        chiffre = num_to_chiffre_tot_fr(Chiffre_mots);
        sprintf(subphrases[i], "%s%d %s", Avant_chiffre, chiffre, Apres_chiffre);
        //printf("Subphrase traité: %s\n", subphrases[i]);
    }

    //printf("Nb ss-phrases : %d\n",subphr_compt+1);

    // Imprimir las subfrases
    for (i = 0; i <= subphr_compt; i++) {           //On utilise i et après j pcq ça nous donne erreur sinon

        //On réinitialise les variables suivantes à chaque itération pour ne pas avoir des problèmes en mémoire.
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
        if (action != NULL && action[0] != '\0') {
            strncpy(resultData.action, action, 20 - 1);
        }
        // Asumiendo que param1 y param2 se llenan correctamente en el procesamiento
        strcpy(resultData.param1, param1);
        strcpy(resultData.param2, param2);
        strcpy(resultData.type, type);


        enqueue(q, resultData); // Enqueue cada subfrase procesada
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
        if (action != NULL && action[0] != '\0') {
            strncpy(resultData.action, action, 20 - 1);
        }
        // Asumiendo que param1 y param2 se llenan correctamente en el procesamiento
        strcpy(resultData.param1, param1);
        strcpy(resultData.param2, param2);
        strcpy(resultData.type, type);

        enqueue(q, resultData); // Enqueue cada subfrase procesada
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------
// MES FONCTIONS -------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------


void envPy(char nomfichier[],int *coin_HD, int rayon_bleu, int rayon_jaune,int rayon_orange,int *milieu_bleu,int *milieu_jaune,int *milieu_orange){//-1 si pas de rayon ; liste vide si existe pas

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

    sprintf(res + strlen(res),";tl.up()");

    sprintf(res + strlen(res),";set_robot_position(x, y, angle_degrees)"); // peut etre modifier en fonction de la taille de l'image
    
    sprintf(res + strlen(res),";tl.up()");


    // Exécuter le script Python avec le code Turtle en tant que sortie
    FILE* python_process = popen("python3 propre.py", "w");

    // Écrire le code Turtle dans le processus Python
    fprintf(python_process, "%s", res);
    fclose(python_process);
} 

void actionsPy(char nomfichier[], char *mat[5][4], int mat_compt, int *coin_HD, int rayon_bleu, int rayon_jaune,int rayon_orange,int *milieu_bleu,int *milieu_jaune, int *milieu_orange){ //+ info olivier
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
    sprintf(res + strlen(res),";set_robot_position(x, y, angle_degrees)"); // peut etre modifier apres avoir eu la taille de l'image
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
                sprintf(res + strlen(res),";gobj([%d,%d,%d,'yellow'])", milieu_jaune[0],milieu_jaune[1],rayon_jaune);  
            }
            else if ((strstr(mat[nbaction][2], "bleu") != NULL)||(strstr(mat[nbaction][2], "bleue") != NULL)||(strstr(mat[nbaction][2], "azul") != NULL)){
                sprintf(res + strlen(res),";gobj([%d,%d,%d,'blue'])", milieu_bleu[0],milieu_bleu[1],rayon_bleu);             
            }
            else if ((strstr(mat[nbaction][2], "orange") != NULL)||(strstr(mat[nbaction][2], "naranja") != NULL)){
                sprintf(res + strlen(res),";gobj([%d,%d,%d,'orange'])", milieu_orange[0],milieu_orange[1],rayon_orange);      
            }
        } 
//Subphrase:"CONTOURNER PAR LA [DIRECTION] L'[OBJET]" ou bien "CONTOURNER L'[OBJET] PAR LA [DIRECTION]"
        if(strcmp(mat[nbaction][0], "contourner") == 0 || strcmp(mat[nbaction][0], "contourne") == 0 || strcmp(mat[nbaction][0], "rodear") == 0 || strcmp(mat[nbaction][0], "rodea") == 0 || strcmp(mat[nbaction][0], "rodées") == 0){
            if ((strstr(mat[nbaction][2], "jaune") != NULL) || (strstr(mat[nbaction][2], "amarillo") != NULL) || (strstr(mat[nbaction][2], "amarilla") != NULL)){
                if ((strstr(mat[nbaction][1], "gauche") != NULL) || (strstr(mat[nbaction][1], "izquierda") != NULL)){
                    sprintf(res + strlen(res),";contobj(%d,%d,%d,'yellow',-1)", milieu_jaune[0],milieu_jaune[1],rayon_jaune);  
                }
                else{
                    sprintf(res + strlen(res),";contobj(%d,%d,%d,'yellow',1)", milieu_jaune[0],milieu_jaune[1],rayon_jaune);
                }                 
            }
            else if ((strstr(mat[nbaction][2], "bleu") != NULL)||(strstr(mat[nbaction][2], "bleue") != NULL)||(strstr(mat[nbaction][2], "azul") != NULL)){
                if ((strstr(mat[nbaction][1], "gauche") != NULL) || (strstr(mat[nbaction][1], "izquierda") != NULL)){
                    sprintf(res + strlen(res),";contobj(%d,%d,%d,'blue',-1)", milieu_bleu[0],milieu_bleu[1],rayon_bleu);             
                }
                else{
                    sprintf(res + strlen(res),";contobj(%d,%d,%d,'blue',1)", milieu_bleu[0],milieu_bleu[1],rayon_bleu);
                }
            }
            else if ((strstr(mat[nbaction][2], "orange") != NULL)||(strstr(mat[nbaction][2], "naranja") != NULL)){
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

    // Exécuter le script Python avec le code Turtle en tant que sortie
    FILE* python_process = popen("python3 propre.py", "w");

    // Écrire le code Turtle dans le processus Python
    fprintf(python_process, "%s", res);
    fclose(python_process);
}


int main() {


    printf("\n\x1B[1m---------------NOUVELLE IMAGE--------------\x1B[0m\n\n");
    char nomfichier[100]; //je l'utilise aussi pour le fond d'ecran turtle

    printf("Veuillez entrer le nom de l'image que vous souhaitez utiliser : ");
    scanf("%s", nomfichier);
    printf("%s",nomfichier);

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


    printf("Pour Recommencer avec une nouvelle image, appuyez sur 'R', pour Quitter appuyez sur 'Q' : \n");
    boucle = getchar(); 


    while (1) {
        if (boucle == 'r' || boucle == 'R') {
            printf("\n\n");
            main();
        } else if (boucle == 'q' || boucle == 'Q') {
            return 0; 
        }
        getchar(); 
        printf("Pour Recommencer avec une nouvelle image, appuyez sur 'R', pour Quitter appuyez sur 'Q' : \n");
        boucle = getchar(); 
    }


}
/*
IMG_5402.txt
exemples de phrase pour tester

avancer de 1000 mètres puis tourner de 70 degrés puis reculer de 150 mètres puis tourner de 50 degrés
avance jusqua la boule jaune puis avance jusqua la boule orange puis avance jusqua la boule bleue
contourne la balle bleue par la droite
*/
