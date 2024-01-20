import turtle as tl
import time
import sys

sc = tl.Screen() 
tl.speed(2)

def initialisation(x_HD, y_HD,nom):
    
    sc.title("MODELISATION: " + nom)
    indice_txt = nom.find("txt")
    newnom = nom[:indice_txt] + "gif" 
    newnom+= newnom[indice_txt + 3:]
    sc.bgpic(newnom)

    sc.setup(350,350) 
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

def avancer(d):
    
    while d > 0:
        if (-50<tl.xcor()<50) and (-50<tl.ycor()<50):
            tl.forward(90)
            d-=95
        elif (-140<tl.xcor()<140) and (-140<tl.ycor()<140):
            tl.forward(9)
            d-=9 
        elif (-150.1<tl.xcor()<150.1) and (-150.1<tl.ycor()<150.1):
            tl.forward(1)
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
        

def reculer(d):
    
    while d > 0:
        if (-50<tl.xcor()<50) and (-50<tl.ycor()<50):
            tl.backward(90)
            d-=95
        elif (-140<tl.xcor()<140) and (-140<tl.ycor()<140):
            tl.backward(9)
            d-=9 
        elif (-150.1<tl.xcor()<150.1) and (-150.1<tl.ycor()<150.1):
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



# Fonction pour créer une boule

def boule(x, y, r, coul):
    
    tl.up()
    tl.goto(x-r,y)
    tl.color(coul)
    tl.down()
    tl.fillcolor(coul)
    tl.begin_fill()
    tl.circle(r)
    tl.end_fill()

def gobj(couleur): 
    angle = tl.towards(couleur[0], couleur[1])
    tl.setheading(angle)
    distance = tl.distance(couleur[0], couleur[1]) - couleur[2]
    tl.forward(distance)
   
   
# Fonction pour setup le robot
def set_robot_position(x, y, angle_degrees):
    tl.up()
    tl.goto(x, y)
    tl.shape()
    tl.shapesize(2, 2)
    tl.fillcolor("aqua")
    tl.setheading(angle_degrees)
    tl.down()
    tl.width(1) 
    tl.color("aqua")                

if __name__ == "__main__":
    # peut etre placer random le robot ???
    x = 0
    y = -140
    angle_degrees = 90 
    tl.mode("standard")
    code_turtle = sys.stdin.read() 
    exec(code_turtle)

time.sleep(3)
sc.exitonclick()
