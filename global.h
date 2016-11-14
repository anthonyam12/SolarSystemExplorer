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
		Planet( float r, float d, float y, float da, float size, string n );
		Planet();

		// Getters
		float GetRadius();
		float GetDistance();
		float GetYear();
		float GetDay();
		float GetScaledSize();
		string GetName();

		// Setters
		void SetRadius( float r );
		void SetDistance( float d );
		void SetYear( float y );
		void SetDay( float d );
		void SetScaledSize( float size );
		void SetName( string n );
	private:
		float radius;
		float distance;
		float year;
		float day;
		float scaledSize;
		string name;
};

#ifndef GLOBAL_H
#define GLOBAL_H
int ScreenWidth = 1200;
int ScreenHeight = 600;

Planet Planets[10];
#endif 
