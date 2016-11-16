/*
    ***** TexturedObjects *****

Rotating cube/sphere/teapot, illustrating texture maps in OpenGL.

Author: John M. Weiss, Ph.D.
Class:  CSC433/533 Computer Graphics
Date:   Fall 2016
Ref:    Angel, OpenGL Primer, 2008

*/

#include <cstdio>
#include <cstdlib>
#include <GL/freeglut.h>

// global vars
extern GLfloat theta[];
extern GLint axis;
extern float speed;
extern int objtype;
extern GLUquadricObj* sphere;

// function prototypes
void reshape( int w, int h );
void display( void );
void key( unsigned char ch, int x, int y );
void special( int key, int x, int y );              // not used
void mouse( int btn, int state, int x, int y );     // not used
void idle();
int loadTexture( char *filename );
void makeTexture();
void colorcube( void );
