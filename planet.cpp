#include "global.h"

Planet::Planet() {}

Planet::Planet( float r, float d, float y, float da, float size, string n, Color c )
{
	radius = r;
	distance = d;
	year = y;
	day = da;
	scaledSize = size;
	name = n;
	color = c;

	hourOfDay = 0.0;
	dayOfYear = 0.0;
	animateIncrement = da;
}

float Planet::getRadius() { return radius; }
float Planet::getDistance() { return distance; }
float Planet::getYear() { return year; }
float Planet::getDay() { return day; }
float Planet::getScaledSize() { return scaledSize; }
Color Planet::getColor() { return color; }
string Planet::getName() { return name; }
Image Planet::getImage() { return img; }

void Planet::setRadius( float r ) { radius = r; }
void Planet::setDistance( float d ) { distance = d; }
void Planet::setYear( float y ) { year = y; }
void Planet::setDay( float d ) { day = d; }
void Planet::setScaledSize( float size ) { scaledSize = size; }
void Planet::setColor( Color c ) { color = c; };
void Planet::setName( string n ) { name = n; }
void Planet::setImage( unsigned char* i, int r, int c ) 
{ 
	img.ptr = i;
	img.rows = r;
	img.cols = c;
}

