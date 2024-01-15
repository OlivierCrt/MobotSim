# Import des bibliothèques nécessaires
import numpy as np               # Gestion des tableaux de type array
import matplotlib.pyplot as plt  # Tracé des figures
import os                        # Fonctionnalités dépendantes du système d'exploitation (OS)

# Récupération du chemin vers le dossier contenant les données à traiter
# Ici, on utilise le répertoire courant où se trouve ce script comme référence
PATH = os.getcwd()  # Le répertoire courant

# Saisie du nom du fichier .dat à traiter (assumes qu'il est dans le répertoire courant)
nom_fichier = input('Nom du fichier .dat à traiter : ')

# Récupération du nom sans l'extension
nom_seul, ext = os.path.splitext(nom_fichier)

# Ouverture du fichier .dat (fichier texte) et conversion en array
with open(os.path.join(PATH, nom_fichier), "r") as fichier:
    # Lecture de la première ligne contenant la hauteur et la largeur de la matrice
    ligne_dim = fichier.readline()
    liste_dim = ligne_dim.split()
    val_dim = [int(val) for val in liste_dim]
    hauteur = val_dim[0]
    largeur = val_dim[1]

    # Définition d'une matrice d'entiers à la bonne dimension
    image_lue = np.zeros((hauteur, largeur), dtype=int)

    # Chargement ligne par ligne de la matrice à partir du fichier texte
    for i in range(hauteur):
        ligne_fichier = fichier.readline()
        liste_valeur = ligne_fichier.split()
        image_lue[i] = [int(val) for val in liste_valeur]

# Affichage du contenu de la matrice
print(image_lue)

# Affichage de la matrice comme une image en niveaux de gris
plt.imshow(image_lue, cmap='gray')

# Sauvegarde au format jpg dans le répertoire courant
plt.savefig(os.path.join(PATH, nom_seul + '.jpg'))
print('Image sauvegardée au format jpg :', os.path.join(PATH, nom_seul + '.jpg'))
