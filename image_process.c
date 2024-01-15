#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "image_process.h"


//Structure de resultat
struct Groupe_Pixel_s {
    int nbpixel_g ;
    int ** matrice_associe ;
    char* couleur ;
    
};

//Allocation pixel
Groupe_Pixel_ptr alloc_Groupe_Pixel(int nbp , int** matrice_ass_param,char * couleur){
    Groupe_Pixel_ptr res = malloc(sizeof(struct Groupe_Pixel_s)) ;
    res->nbpixel_g = nbp ;
    res->matrice_associe = matrice_ass_param ;
    res->couleur = couleur ;
    return res ;
}

//Detection de plage
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

//Dfs pour les groupe de 1
//Elimination des petit groupes
//Pour aller plus loin, beta, pas demandé dans le dossier de spec

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


//Fonctions de renvoie pour l'integration
int * trouver_milieu(Groupe_Pixel_ptr objet, int largeur , int hauteur){
    int * res =malloc(2*sizeof(int));
    if (!isObjet(objet)){
        printf("Pas d'objet de couleur %s\n",objet->couleur);
        return(res);
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
    res[0] =jmin_l+(jmax_l-jmin_l)/2 ; //hauteur
    res[1] = imin_h+(imax_h-imin_h)/2 ;
    printf("Objet de couleur %s trouvé! Son milieu est de coordonnées : [%d,%d]\n",objet->couleur,res[0],res[1]);
    return (res);

}
int  trouver_rayon(Groupe_Pixel_ptr objet, int largeur , int hauteur){
    
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
    int maxres = jmax_l-jmin_l ;
    if ((imax_h-imin_h)>maxres){
        maxres = imax_h-imin_h ;
    }
    return maxres;





}
char* get_couleur(Groupe_Pixel_ptr objet){
    return(objet->couleur);

}

bool isObjet (Groupe_Pixel_ptr groupe){
    return (groupe->nbpixel_g>30 );

}


//Pas demandé dans le dossier mais pratique pour visualiser les plages detectées en noir et blanc
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




int main(){
//Entrées scannées de l'entrée standart
int largeur,hauteur,nbcompo ;
scanf("%d",&largeur) ;
scanf("%d",&hauteur) ;
scanf ("%d", &nbcompo) ;
printf("Largeur : %d\n",largeur);
printf("Hauteur : %d\n",hauteur);
printf("Nbcompo : %d\n\n\n",nbcompo);
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
int i,j ;
for (i=0 ;i<hauteur ; i++){
    for(j=0 ; j<largeur ; j++){
        scanf("%d",&matrice_init_red[i][j]);
    }
}
//G
int x,y ;
for (x=0 ;x<hauteur ; x++){
    for(y=0 ; y<largeur ; y++){
        scanf("%d",&matrice_init_green[x][y]);
    }
}
//B
int a,b ;
for (a=0 ;a<hauteur ; a++){
    for(b=0 ; b<largeur ; b++){
        scanf("%d",&matrice_init_blue[a][b]);
    }
}
Groupe_Pixel_ptr objet_poss_bleu = detecterPixelsBleu(matrice_init_red , matrice_init_green , matrice_init_blue , hauteur , largeur);
Groupe_Pixel_ptr objet_poss_jaune = detecterPixelsJaune(matrice_init_red , matrice_init_green , matrice_init_blue , hauteur , largeur);
Groupe_Pixel_ptr objet_poss_Orange = detecterPixelsOrange(matrice_init_red , matrice_init_green , matrice_init_blue , hauteur , largeur);
//dfs et lpg
//trouverLePlusGros(objet_poss_Orange->matrice_associe ,hauteur , largeur );
//Milieux
int * obj_bleu = trouver_milieu(objet_poss_bleu ,largeur, hauteur);
int * obj_jaune = trouver_milieu(objet_poss_jaune ,largeur, hauteur);
int * obj_orange = trouver_milieu(objet_poss_Orange ,largeur, hauteur);
//Fichier txt avec les matrices des plages de la forme vue en TP, j'utilise le script de M.Ferrané afin de les visualiser par la suite
if (isObjet(objet_poss_bleu))  { ecrireMatriceDansFichier(objet_poss_bleu,hauteur,largeur,"obj_bleu.dat"); };

if (isObjet(objet_poss_jaune))  { ecrireMatriceDansFichier(objet_poss_jaune,hauteur,largeur,"obj_jaune.dat"); };

if (isObjet(objet_poss_Orange))  { ecrireMatriceDansFichier(objet_poss_Orange,hauteur,largeur,"obj_orange.dat"); };

return 0;
}