#include <string>
#include <iostream>
#include <stdio.h>			// files
#include <GL/freeglut.h>

using namespace std;

struct Color 
{
	float r;
	float g;
	float b;
};

struct Image 
{
	int rows;
	int cols;
	unsigned char* ptr;
};

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

enum Texture { Wireframe, Flat, Smooth, TextureMap };

// Lots of stuff in here that probably should't be
// couldn't get rid of the redefinition errors elsewhere
#ifndef GLOBAL_H
#define GLOBAL_H
int ScreenWidth = 1200;
int ScreenHeight = 600;
float CamZ = -100.0;
float CamY = 0.0;
float CamX = 0.0;
float IncrementMult = 1.0;
bool SingleStep = false;
bool Paused = false;
float PreviousMult = 1.0;
float RotateX = 0.0;
float RotateY = 15.0;
float RotateZ = 0.0;

Planet Planets[10];
Texture texture;
GLuint textureNames[10];
#endif 
