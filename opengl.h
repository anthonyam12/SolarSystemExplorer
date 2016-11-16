#ifndef GLOBAL_H
#define GLOBAL_H
#include "global.h"
#endif

// GLOBALS
extern Planet Planets[10];
extern int ScreenHeight;
extern int ScreenWidth;
extern Texture texture;
extern GLuint textureNames[10];

const int Esc = 27;			// exit program
const int s = 's'; 			// smooth shading
const int f = 'f';			// flat shading
const int w = 'w';			// wireframe
const int t = 't';			// texture mapping

// FUNCTIONS
// OpenGL Callbacks
void keyboard( unsigned char key, int x, int y );
void display( void );
void reshape( int w, int h );

// Misc.
void init();
void SetupTextureMapping();
