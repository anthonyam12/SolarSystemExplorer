#ifndef GLOBAL_H
#define GLOBAL_H
#include "global.h"
#endif

#include "opengl.h"

// GLOBALS
extern Planet Planets[10];
extern int ScreenHeight;
extern int ScreenWidth;

// FUNCTIONS 
void InitOpenGl();
void CreatePlanetArray();
void SetPlanetBitmaps();

// ext. functions
bool LoadBmpFile( const char* filename, int &rows, int &cols, unsigned char* &imgPtr );
