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
extern float PreviousMult;
extern bool SingleStep;
extern bool Paused;
extern bool NonMove;
extern float RotateX;
extern float RotateY;
extern float RotateZ;

const int Esc = 27;			// exit program
const int s = 's'; 			// smooth shading
const int f = 'f';			// flat shading
const int w = 'w';			// wireframe
const int t = 't';			// texture mapping
const int r = 'r';			// resume/stop simulation
const int a = 'a';			// slow down animation
const int A = 'A';			// speed up animation
const int Space = ' ';		// single step
const int Plus = '+';		// zoom in
const int Minus = '-';		// zoom out
const int X = 'X';			// rotate left in X direction
const int xx = 'x';			// rotate right in X direction
const int Y = 'Y';			// rotate up in Y direction
const int yy = 'y';			// rotate down in Y direction
const int Z = 'Z';			// rotate up/right in the Z direction
const int z = 'z';			// rotate left/down in the Z direction

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
