#Auteur : Solal Danton Laloy

import turtle as tl
import time
import sys

sc = tl.Screen() 
tl.speed(2)


def initialisation(x_HD, y_HD,nom):
    """
    Initialise l'environnement : Donne u titre, place le fond, créé un contour et affiche les coordonnées. 

    :param x_HD: Coordonnée X du coin supérieur droit.
    :type x_HD: int
    :param y_HD: Coordonnée Y du coin supérieur droit.
    :type y_HD: int
    :param nom: Position de l'image.
    :type nom: str
    """ 
    # Titre
    nomtitre = nom
    sc.title("MODELISATION: " + nomtitre.split("/")[-1]) 

    #Place le fond d'écran après remplacé l'extension par .gif
    indice_txt = nom.find("txt") 
    newnom = nom[:indice_txt] + "gif" 
    newnom+= newnom[indice_txt + 3:]
    sc.bgpic(newnom)

    sc.setup(2*x_HD + 50,2*y_HD + 50) 

    tl.up()
    tl.right(90)
    longueur_cote = x_HD * 2 +10 
    tl.goto(x_HD+5, y_HD+5)

    # Traçage du contour
    tl.width(20)                 
    tl.color('DarkGreen')          
    tl.down()                   
    for i in range(4):
        tl.forward(longueur_cote)
        tl.right(90)

    # Affichage des coordonnées
    tl.width(1) 
    tl.up()
    tl.color('red')
    cox,coy= -x_HD-5, -y_HD-10
    while cox < x_HD:
        tl.goto(cox,coy)    
        tl.write(cox+5, font=("Calibri", 8, "bold"),align='center')
        cox+=50
    cox,coy= -x_HD-2.5, -y_HD+45
    while coy < y_HD:
        tl.goto(cox,coy)
        tl.write(coy+5, font=("Calibri", 8, "bold"),align='center')
        coy+=50
    tl.down()



# Fonction pour setup le robot
def set_robot_position(x, y, angle):
    """
    Place le robot dans la position d'où est prise la photo, puis configure son apparence et l'apparence de son tracé.

    :param x: Coordonnée X du centre du robot.
    :type x: int
    :param y: Coordonnée Y du centre du robot.
    :type y: int
    :param angle_degrees: Orientation initiale du robot en degrés.
    :type angle_degrees: int
    """
    tl.up()
    tl.goto(x, y)
    tl.shape()
    tl.shapesize(2, 2)
    tl.fillcolor("aqua")
    tl.setheading(angle)
    tl.down()
    tl.width(1) 
    tl.color("aqua")      



def avancer(d):
    '''
    Permet au robot d'avancer sans sortir de l'image.

    :param d: Distance à parcourir.
    :type d: int
    '''
    #Fais avancer le robot tant qu'il est dans la zone de l'image.
    while d > 0:
        if ((d>=95)and(-50<tl.xcor()<50) and (-50<tl.ycor()<50)):
            tl.forward(90)
            d-=95
        elif ((d>=9)and(-140<tl.xcor()<140) and (-140<tl.ycor()<140)):
            tl.forward(9)
            d-=9 
        elif ((d>=1)and(-150.1<tl.xcor()<150.1) and (-150.1<tl.ycor()<150.1)):
            tl.forward(1)
            d-=1          
        else:
            d=0 
    #Dans le cas où le robot serait sorti de la zone de quelques millimètres, il est replacé dedans.
    if tl.xcor()>150:
        tl.setx(150)
    if tl.xcor()<-150:
        tl.setx(-150)
    if tl.ycor()>150:
        tl.sety(150)
    if tl.ycor()<-150:
        tl.sety(-150)
        


def reculer(d):
    '''
    Permet au robot de reculer sans sortir de l'image. Même fonction qu'au dessus mais pour reculer.

    :param d: Distance à parcourir.
    :type d: int
    '''   
    while d > 0:
        if ((d>=95)and(-50<tl.xcor()<50) and (-50<tl.ycor()<50)):
            tl.backward(90)
            d-=95
        elif ((d>=9)and(-140<tl.xcor()<140) and (-140<tl.ycor()<140)):
            tl.backward(9)
            d-=9 
        elif ((d>=1)and(-151<tl.xcor()<151) and (-151<tl.ycor()<151)):
            tl.backward(1)
            d-=1
        else:
            d=0
    if tl.xcor()>150:
        tl.setx(150)
    if tl.xcor()<-150:
        tl.setx(-150)
    if tl.ycor()>150:
        tl.sety(150)
    if tl.ycor()<-150:
        tl.sety(-150)



def boule(x, y, r, coul):
    '''
    Dessine une boule de couleur "coul" de centre (x,y) et de rayon r.

    :param x: Coordonnée X du centre de la boule.
    :type x: int
    :param y: Coordonnée Y du centre de la boule.
    :type y: int
    :param r: Rayon de la boule.
    :type r: int
    :param coul: Couleur de la boule.
    :type c
    '''
    
    tl.up()
    tl.goto(x-r,y)
    tl.color(coul)
    tl.down()
    tl.fillcolor(coul)
    tl.begin_fill()
    tl.circle(r)
    tl.end_fill()



def gobj(couleur): 
    """
    Déplace le robot vers le point le plus proche de la boule en paramètre.

    :param couleur: Liste représentant l'objet [x, y, r, coul].
    :type couleur: list
    """
    #trouve l'angle entre le centre de la boule et le robot
    angle = tl.towards(couleur[0], couleur[1]) 
    #place le robot dans cette direction
    tl.setheading(angle) 
    #calcul la distance entre le robot et le point le plus proche de la boule
    distance = tl.distance(couleur[0], couleur[1]) - couleur[2] 
    #fait avancer le robot jusqu'à ce point
    tl.forward(distance) 



def contobj(x,y,r,coul,sens):
    """
    Fais avancer le robot jusqu'à l'objet spécifié puis le contourne. Par la droite si sens =1 et par la gauche si sens = -1

    :param x: Coordonnée X du centre de l'objet.
    :type x: int
    :param y: Coordonnée Y du centre de l'objet.
    :type y: int
    :param r: Rayon de l'objet.
    :type r: int
    :param coul: Couleur de l'objet.
    :type coul: str
    :param sens: Direction de rotation (1 pour horaire, -1 pour anti-horaire).
    :type sens: int
    """
    gobj([x,y,r,coul])
    tl.right(sens*90)
    tl.forward(r)
    tl.left(sens*90)
    tl.forward(2*r)
    tl.left(sens*90)
    tl.forward(r)
    tl.right(sens*90)
   
          

#Ne s'exécute que si ce code est exécuté en tant que code principal
if __name__ == "__main__":
    #Assure que le robot est bien en mode standard.
    tl.mode("standard")
    #Lis les fonctions envoyé par le .c
    code_turtle = sys.stdin.read() 
    #Exécute ces fonctions
    exec(code_turtle)

#Attend 3 secondes que le robot ait terminé.
time.sleep(3)
#La fenêtre se ferme en cliquant dessus.
sc.exitonclick()

