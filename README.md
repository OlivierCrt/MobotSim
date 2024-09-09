#  MoBot - Mobile Robot Simulation

This project is designed to simulate a mobile robot, providing functionalities for image analysis, text command processing, and robot movement simulation in a virtual environment.

> **Note**: This is the first phase of a larger project, with the ultimate goal of implementing these functions on a real robot by the end of the year.

---

##  Overview

MoBot aims to help analyze the robot's environment and respond to user text commands, while simulating its movements. We use an image database provided in the specifications. The program need an image .png and a convert of this image in .txt (1 pixel = 1value between  and 256, special header, check images folder)

###  Key Features

MoBot offers three core functionalities:

1. **Image Processing**
   - Detects a ball in the image and returns:
     - The coordinates of its center
     - Its color
     - Its diameter
     - Its area

2. **Text Processing**
   - Interprets user text commands and deduces the corresponding actions to be performed by the robot.
      -  Languages : French, Spanish

3. **Robot Movement Simulation**
   - Simulates robot movements in a virtual environment based on the image and text input data.

---

## 🛠️ Installation

To get started with MoBot, follow these steps:

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/OlivierCrt/mobot.git
   cd mobot
2. **Install Python Libraries**: Make sure you have Python 3.x installed. Turtle is a base lib for theses versions.

---

##  Usage

1. **Compile and run the executable**:
   ```bash
   make
   ./main
   
---
##  Documentation

For more technical informations, please refer to the [documentation folder](https://github.com/OlivierCrt/MobotSim/blob/main/Documentation_G4.zip)
 in this repository. Just exctract and open index.html.

---

## Some results
1.**Image processing**: We have grouped all the tests together in a single photo [photo](images/Modélisations.png.JPG) 
All balls are detected regardless of number, null cases are functional. Diameters are also pretty good, except in a few photos. To go further, the use of deep learning libraries would allow us to greatly adjust the results, but in the project specifications we can only use base C for image processing.

2.**Text processing**:

3.**Simulation**:


