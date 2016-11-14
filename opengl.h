#ifndef GLOBAL_H
#define GLOBAL_H
#include "global.h"
#endif

// GLOBALS
extern Planet Planets[10];
extern int ScreenHeight;
extern int ScreenWidth;

// FUNCTIONS
// OpenGL Callbacks
void keyboard( unsigned char key, int x, int y );
void display( void );
void reshape( int w, int h );

// Misc.
void init();
