/*******************************************************************************
* Author: Anthony Morast, Samuel Carroll
*
* CSC - 533 Computer Graphics, Dr. John Weiss
* Program 3 - Solar System Simulation
* 
* Description:
* 	The header file for solar.cpp. The header file contains function definitions
* and declares the external global variables located in global.h
*
*******************************************************************************/
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
void InitPlanetOrbitPosition();

// ext. functions
bool LoadBmpFile( const char* filename, int &rows, int &cols, unsigned char* &imgPtr );
