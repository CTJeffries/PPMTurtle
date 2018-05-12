// Colby Jeffries & Matt King-Smith
// ppmturtle.h
// Originally written in Fall 2015, updated in Spring 2018.

/*
This library provides functions to generate a .ppm output
of a "turtle" similar Python turtles. It replicates much of the turtle
functionality. This is mean for neat visualizations and educational
purposes.
*/

// Turtle structure.
typedef struct Turtle {
  float x;
  float y;
  float heading;
  int pen;
  int thickness;

  unsigned char colorR;
  unsigned char colorG;
  unsigned char colorB;

  int height;
  int width;
  unsigned char *data;
}Turtle;


// Initialization Functions
Turtle *createTurtle(float heading, float x, float y, int pen,
                     int height, int width, int thickness);
unsigned char * createImgData(int height, int width);


// Image Export Functions
void imgGenerate(Turtle *turle, char *filename);


// Image Modification Functions
void setPixel(int x, int y, Turtle *turtle);

// Turtle Commands
void ppmPenUp(Turtle *turtle);
void ppmPenDown(Turtle *turtle);
void ppmLeftTurn(Turtle *turtle, float angle);
void ppmRightTurn(Turtle *turtle, float angle);
void ppmForward(Turtle *turtle, int length);
void ppmBackward(Turtle *turtle, int length);
void ppmPenSize(Turtle *turtle, int thickness);
void ppmpenColor(Turtle *turtle, unsigned char r, unsigned char g,
                 unsigned char b);
