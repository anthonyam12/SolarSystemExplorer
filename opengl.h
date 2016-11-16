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
extern float CamZ;
extern float CamY;
extern float CamX;
extern float IncrementMult;

const int Esc = 27;			// exit program
const int s = 's'; 			// smooth shading
const int f = 'f';			// flat shading
const int w = 'w';			// wireframe
const int t = 't';			// texture mapping
const int i = 'i';			// zoom (i)n
const int o = 'o';			// zoom (o)ut
const int Plus = '+';		// speed up animation
const int Minus = '-';		// slow down animation

// FUNCTIONS
// OpenGL Callbacks
void keyboard( unsigned char key, int x, int y );
void special( int key, int x, int y );
void display( void );
void reshape( int w, int h );
void mouseclick( int button, int state, int x, int y );

// Misc.
void init();
void SetupTextureMapping();
