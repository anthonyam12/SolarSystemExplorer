#include "global.h"

Planet::Planet() {}

Planet::Planet( float r, float d, float y, float da, float size, string n)
{
	radius = r;
	distance = d;
	year = y;
	day = da;
	scaledSize = size;
	name = n;
}

float Planet::GetRadius() { return radius; }
float Planet::GetDistance() { return distance; }
float Planet::GetYear() { return year; }
float Planet::GetDay() { return day; }
float Planet::GetScaledSize() { return scaledSize; }
string Planet::GetName() { return name; }

void Planet::SetRadius( float r ) { radius = r; }
void Planet::SetDistance( float d ) { distance = d; }
void Planet::SetYear( float y ) { year = y; }
void Planet::SetDay( float d ) { day = d; }
void Planet::SetScaledSize( float size ) { scaledSize = size; }
void Planet::SetName( string n ) { name = n; }
