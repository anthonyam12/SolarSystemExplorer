#include <string>
#include <iostream>
#include <GL/freeglut.h>

using namespace std;

struct Color 
{
	float r;
	float g;
	float b;
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

		// Setters
		void setRadius( float r );
		void setDistance( float d );
		void setYear( float y );
		void setDay( float d );
		void setScaledSize( float size );
		void setName( string n );
		void setColor( Color c );
	private:
		float radius;
		float distance;
		float year;
		float day;
		float scaledSize;
		Color color;
		string name;
};

enum Texture { Wireframe, Flat, Smooth, TextureMap };

#ifndef GLOBAL_H
#define GLOBAL_H
int ScreenWidth = 1200;
int ScreenHeight = 600;

Planet Planets[10];
Texture texture;
#endif 
