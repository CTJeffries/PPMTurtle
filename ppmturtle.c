// Colby Jeffries & Matt King-Smith
// ppmturtle.c
// Originally written in Fall 2015, updated in Spring 2018.

/*
This library provides functions to generate a .ppm output
of a "turtle" similar Python turtles. It replicates much of the turtle
functionality. This is mean for neat visualizations and educational
purposes.
*/

// Libraries
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "ppmturtle.h"

// Global Constants
#define MAX_COLOR 255
#define POINTS_PER_LINE 10000
#define DEGREES_MULTIPLIER (M_PI/180.0)


Turtle *createTurtle(float heading, float x, float y, int pen, int height,
                     int width, int thickness) {
  /*
  This function initializes a turtle structure. This includes all of the
  information about the turtle, and along with its image environment.
  :param: heading: The initial heading of the turtle.
  :param: x: Initial x position of the turtle.
  :param: y: Initial y position of the turtle.
  :param: pen: Whether or not turtle's pen is initially active.
  :param: height: The height of the turtle's image.
  :param: width: The width of the turtle's image.
  :param: thickness: The initial thickness of the turtle in degrees.
  :return: An initialized turtle structure.
  */
  Turtle *turtle = (Turtle *) malloc(sizeof(Turtle));
  turtle->x = x;
  turtle->y = y;
  turtle->pen = pen;
  turtle->heading = heading;
  turtle->thickness = thickness;
  turtle->colorR = 0;
  turtle->colorG = 0;
  turtle->colorB = 0;
  turtle->height = height;
  turtle->width = width;
  turtle->data = createImgData(height, width);
  return turtle;
}


void imgGenerate(Turtle *turtle, char *filename) {
  /*
  This function is used to write the image from a turtle structure.
  :param: *turtle: The turtle structure to write the image from.
  :param: *filename: The name of the file to write to.
  :return: Nothing.
  */
  int size = turtle->height * turtle->width * 3;
  FILE *out = fopen(filename, "wb");
  fprintf(out, "P6\n%d %d %d\n", turtle->width,
          turtle->height, MAX_COLOR); //PPM header
  fwrite(turtle->data, 1, size, out);
  fclose(out);
}


unsigned char * createImgData(int height, int width) {
  /*
  Initializes the image array for a turtle structure.
  :param: height: The height of the image array.
  :param: width: The width of the image array.
  :return: An array of size height * width * 3 all set to 255.
  */
  unsigned char *data;
  int i, size;
  size = height * width * 3;
  data = (unsigned char *) malloc(size);
  for(i = 0; i < size; i++) {
    *(data + i) = 255;
  }
  return data;
}


void setPixel(int x, int y, Turtle *turtle) {
  /*
  Sets pixel(s) to the proper color when a turtle writes on it.
  :param: x: The x positon of the turtle.
  :param: y: The y position of the turtle.
  :param: turtle: The turtle doing the writing.
  :return: Nothing.
  */
  int j,k;
  for(j=0; j<turtle->thickness; j++) {
    for(k=0; k<turtle->thickness; k++) {
      *(turtle->data + (3 * ((turtle->height - y + (turtle->thickness/2) - j) * (turtle->width))) + (3 * (x - (turtle->thickness/2) + k))) = turtle->colorR;
      *(turtle->data + (3 * ((turtle->height - y + (turtle->thickness/2) - j) * (turtle->width))) + (3 * (x - (turtle->thickness/2) + k)) + 1) = turtle->colorG;
      *(turtle->data + (3 * ((turtle->height - y + (turtle->thickness/2) - j) * (turtle->width))) + (3 * (x - (turtle->thickness/2) + k)) + 2) = turtle->colorB;
    }
  }
}


void ppmPenUp(Turtle *turtle) {
  /*
  Sets a turtle's pen to up.
  :param: turtle: The turtle to adjust.
  :return: Nothing.
  */
  turtle->pen = 0;
}


void ppmPenDown(Turtle *turtle) {
  /*
  Sets a turtle's pen to down.
  :param: turtle: The turtle to adjust.
  :return: Nothing.
  */
  turtle->pen = 1;
}


void ppmLeftTurn(Turtle *turtle, float angle) {
  /*
  Turns a turtle to the left.
  :param: turtle: The turtle to adjust.
  :param: angle: The amount left in degrees.
  :return: Nothing.
  */
  if ((turtle->heading + angle) < 360) {
      turtle->heading = turtle->heading + angle;
  }
  else {
    turtle->heading = turtle->heading + angle - 360;
  }
}


void ppmRightTurn(Turtle *turtle, float angle) {
  /*
  Turns a turtle to the right.
  :param: turtle: The turtle to adjust.
  :param: angle: The amount right in degrees.
  :return: Nothing.
  */
  if ((turtle->heading - angle) >= 0) {
      turtle->heading = turtle->heading - angle;
  }
  else {
    turtle->heading = turtle->heading - angle + 360;
  }
}


void ppmForward(Turtle *turtle, int length) {
  /*
  Moves a turtle forward, and writes if the pen is down.
  :param: turtle: The turtle to adjust.
  :param: length: The amount forward in pixels.
  :return: Nothing.
  */
  if(turtle->pen == 0) {
    float x1 = turtle->x;
    float y1 = turtle->y;
    int i;
    float x2,y2;
    x2 = ((cos(turtle->heading * DEGREES_MULTIPLIER) * length) + (float) x1);
    y2 = ((sin(turtle->heading * DEGREES_MULTIPLIER) * length) + (float) y1);
    turtle->x =  x2;
    turtle->y =  y2;
  }
  else {
    float x1 = turtle->x;
    float y1 = turtle->y;
    int i;
    float dx,dy,x2,y2;
    x2 = ((cos(turtle->heading * DEGREES_MULTIPLIER) * length) + (float) x1);
    y2 = ((sin(turtle->heading * DEGREES_MULTIPLIER) * length) + (float) y1);
    dx = (float)(x2-x1)/POINTS_PER_LINE;
    dy = (float)(y2-y1)/POINTS_PER_LINE;
    for(i=0; i<POINTS_PER_LINE; i++) {
      setPixel((int) (x1 + (dx * i)), (int) (y1 + (dy * i)), turtle);
      turtle->x =  x2;
      turtle->y =  y2;
    }
  }
}


void ppmBackward(Turtle *turtle, int length) {
  /*
  Moves a turtle backward, and writes if the pen is down.
  :param: turtle: The turtle to adjust.
  :param: length: The amount backward in pixels.
  :return: Nothing.
  */
  if(turtle->pen == 0) {
    float x1 = turtle->x;
    float y1 = turtle->y;
    int i;
    float x2,y2;
    x2 = ((float) x1 - (cos(turtle->heading * DEGREES_MULTIPLIER) * length));
    y2 = ((float) y1 - (sin(turtle->heading * DEGREES_MULTIPLIER) * length));
    turtle->x = x2;
    turtle->y = y2;
  }
  else {
    float x1 = turtle->x;
    float y1 = turtle->y;
    int i;
    float dx,dy,x2,y2;
    x2 = ((float) x1 - (cos(turtle->heading * DEGREES_MULTIPLIER) * length));
    y2 = ((float) y1 - (sin(turtle->heading * DEGREES_MULTIPLIER) * length));
    dx = (float)(x2-x1)/POINTS_PER_LINE;
    dy = (float)(y2-y1)/POINTS_PER_LINE;
    for(i=0; i<POINTS_PER_LINE; i++) {
      setPixel((int) (x1 + (dx * i)), (int) (y1 + (dy * i)), turtle);
      turtle->x = x2;
      turtle->y = y2;
    }
  }
}


void ppmPenSize(Turtle *turtle, int thickness) {
  /*
  Sets the width of the turtle's pen.
  :param: turtle: The turtle to adjust.
  :param: thickness: Pen thickness in pixels.
  :return: Nothing.
  */
  turtle->thickness = thickness;
}


void ppmPenColor(Turtle *turtle, unsigned char r, unsigned char g,
                 unsigned char b) {
  /*
  Sets the color of the turtle's pen.
  :param: turtle: The turtle to adjust.
  :param: r: The red value of the new color.
  :param: g: The green value of the new color.
  :param: b: The blue value of the new color.
  :return: Nothing.
  */
  turtle->colorR = r;
  turtle->colorG = g;
  turtle->colorB = b;
}
