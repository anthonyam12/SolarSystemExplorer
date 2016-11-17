/*******************************************************************************
* Authors: Anthony Morast, Samuel Carroll
* Date: 11/18/2016
* 
* CSC - 533 Computer Graphics, Dr. John Weiss
* Program 3 - Solar System Simulation
*
* Description:
*	The global.h header file contains all of the various state variables and objects
* used throughout the solar system simulation. This includes structs, classes, 
* libraries used throughout, an array of celestial objects, and various variables
* that help define the current state of the animation and how to position and 
* draw the planets.
*
*******************************************************************************/
#include <string>			// primarily for filenames and planet names
#include <iostream>			// mostly for testing, could remove at submission
#include <stdio.h>			// files
#include <stdlib.h>			// random
#include <time.h>			// random seed
#include <GL/freeglut.h>	// glut

using namespace std;

// Holds three floats representing the amounf of red, green, and blue in 
// a color. Values for r, g, b between 0 and 1, inclusive
struct Color 
{
	float r;
	float g;
	float b;
};

// The image struct allows for simple storage of image information in the planet
// class. It contains the number of rows, number of columns, and a pointer to 
// the data associated with an image. 
struct Image 
{
	int rows;
	int cols;
	unsigned char* ptr;
};

// The planet class holds all relevant information about our celestial objects. 
class Planet 
{
	public:
		Planet( float r, float d, float y, float da, float size, string n, Color c );
		Planet();

		// Getters
		float getRadius();
		float getDistance();
		float getYear();
		float getDay();
		float getScaledSize();
		Color getColor();
		string getName();
		Image getImage();

		// Setters
		void setRadius( float r );
		void setDistance( float d );
		void setYear( float y );
		void setDay( float d );
		void setScaledSize( float size );
		void setName( string n );
		void setColor( Color c );
		void setImage( unsigned char* i, int r, int c );

		// public update vars
		float hourOfDay;
		float dayOfYear;
		float animateIncrement;
	private:
		float radius;
		float distance;
		float year;
		float day;
		float scaledSize;
		Color color;
		string name;
		Image img;
};

// Used to determine and set the current Texture state. The celestial 
// objects can be represented as wireframe spheres, flat/smooth shaded
// spheres, or spheres with BMP images textue mapped to them.
enum Texture { Wireframe, Flat, Smooth, TextureMap };

// Lots of stuff in here that probably should't be
// couldn't get rid of the redefinition errors elsewhere
#ifndef GLOBAL_H
#define GLOBAL_H
int ScreenWidth = 1200;			// initial screen width
int ScreenHeight = 600;			// initial screen height
float CamZ = -100.0;			// initial 'zoom' value, 
								//  need to back the camera off to see the scene
float CamY = 0.0;				// initial camera translation in the y dir
float CamX = 0.0;				// initial camera translation in the x dir
float IncrementMult = 1.0;		// increased/decreased to control animation speed
bool SingleStep = false;		// toggles our single step mode
bool Paused = false;			// toggles our Pause state
float PreviousMult = 1.0;		// when coming out of Paused or Single Step mode
								//   this is used to restore animation speed
float RotateX = 0.0;			// initial camera x rotation
float RotateY = 15.0;			// initial camera y rotation
float RotateZ = 0.0;			// initial camera z rotation
bool LightsEnabled = true;		// used to determine if our lights are toggled on or off

Planet Planets[10];				// stores the celestial objects
Texture texture;				// the current texture state of the simulation
#endif 
