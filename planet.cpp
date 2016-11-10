#include "planet.h"


Planet::Planet() {}

Planet::Planet( float r, float d, float y, float da, string n)
{
	radius = r;
	distance = d;
	year = y;
	day = da;
	name = n;
}

float Planet::GetRadius() { return radius; }
float Planet::GetDistance() { return distance; }
float Planet::GetYear() { return year; }
float Planet::GetDay() { return day; }
string Planet::GetName() { return name; }

void Planet::SetRadius( float r ) { radius = r; }
void Planet::SetDistance( float d ) { distance = d; }
void Planet::SetYear( float y ) { year = y; }
void Planet::SetDay( float d ) { day = d; }
void Planet::SetName( string n ) { name = n; }
