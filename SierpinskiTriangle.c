// Colby Jeffries & Matt King-Smith
// SierpinskiTriangle.c
// Originally written in Fall 2015, updated in Spring 2018.

// Libraries
#include "ppmturtle.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
This program uses the ppmturtle functions to create a sierpinski gasket
with random colors. The program will prompt the user for the amount of
levels to be drawn.
*/

// Function Prototypes
void sierpinski(int len, int levels, Turtle *turtle);
int randomColor();
void changeColor(Turtle *turtle);


int main() {
  /*
  Main driver.
  :return: 0.
  */
  int levels;
  srand(time(NULL));
  printf("How many levels to be drawn? > ");
  scanf("%d", &levels);
  Turtle *pete = createTurtle(0, 200, 200, 0, 2000, 2000, 3);
  sierpinski(1600, levels, pete);
  imgGenerate(pete, "Sierpinski.ppm");
  return 0;
}


int randomColor() {
  /*
  Generates a random color value.
  :return: An integer from 0-254.
  */
  return (rand()%255);
}


void changeColor(Turtle *turtle) {
  /*
  Sets a random color for the turtle.
  :param: The turtle to change the color of.
  :return: Nothing.
  */
  turtle->colorR = randomColor();
  turtle->colorG = randomColor();
  turtle->colorB = randomColor();
}


void sierpinski(int len, int levels, Turtle *turtle) {
  /*
  Draws a sierpinski gasket with side length len and with levels levels.
  :param: len: The outer side length of the gasket.
  :param: levels: The levels of the gasket (0 being just a triangle).
  :param: turtle: The turtle to draw with.
  :return: Nothing.
  */
  if(levels == 0) {
    ppmPenDown(turtle);
    changeColor(turtle);
    ppmLeftTurn(turtle, 60);
    ppmForward(turtle, len);
    changeColor(turtle);
    ppmRightTurn(turtle, 120);
    ppmForward(turtle, len);
    changeColor(turtle);
    ppmRightTurn(turtle, 120);
    ppmForward(turtle, len);
    ppmRightTurn(turtle, 180);
    ppmPenUp(turtle);
  }
  else {
    sierpinski(len/2, levels-1, turtle);
    ppmForward(turtle, len/2);
    sierpinski(len/2, levels-1, turtle);
    ppmBackward(turtle, len/2);
    ppmLeftTurn(turtle, 60);
    ppmForward(turtle, len/2);
    ppmRightTurn(turtle, 60);
    sierpinski(len/2, levels-1, turtle);
    ppmLeftTurn(turtle, 60);
    ppmBackward(turtle, len/2);
    ppmRightTurn(turtle, 60);
  }
}
