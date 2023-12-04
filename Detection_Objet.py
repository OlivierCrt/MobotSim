import cv2
import numpy as np

image = cv2.imread('salle_photo.jpg')
if image is None:
    print("L'image n'a pas pu être chargée.")
    exit()

#  RGB en HSV
hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)

lower_blue = np.array([90, 50, 50])  # Valeurs HSV pour la couleur bleue (exemple)
upper_blue = np.array([130, 255, 255])

# filtre/masque
mask = cv2.inRange(hsv, lower_blue, upper_blue)

#contours
contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

#contours
for contour in contours:
    # delta plage de detection , on enleve les trucs trop petit
    if cv2.contourArea(contour) > 1000:
        x, y, w, h = cv2.boundingRect(contour)
        cv2.rectangle(image, (x, y), (x + w, y + h), (0, 255, 0), 2)

# Sauvegarder l'image
cv2.imwrite('resultat_detection.jpg', image)
