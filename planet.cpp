/*******************************************************************************
* Author: Anthony Morast, Samuel Carroll
* Date: 11/18/16
*
* CSC 533 - Computer Graphics, Dr. John Weiss
*
* Description:
*	The planet class is used throught the solar system simulation to store data 
* about our various celestial objects, viz. the Sun, Earth's moon, and the 8 
* planets.
*
*******************************************************************************/
#include "global.h"

/*******************************************************************************
* Author: Anthony Morast, Samuel Carroll
* /brief Empty constructor
*
* /params none
* /return none
*******************************************************************************/
Planet::Planet() {}

/*******************************************************************************
* Author: Anthony Morast, Samuel Carroll
* /brief Planet constructor with most of its attributes
*
* A constructor for the planet class that sets the planet's radius, distance, 
* days in year, hours in day, scaled size, name, and color. Additionally the 
* planet's hourOfDay, dayOfYear and animateIncrement are set which are used
* for the planet's animation in the simulation. 
*
* /params 
*		r - the planet's radius
*		d - the planet's distance (typically from the sun in millions of km)
*		y - days in a year
*		da - hours in a day
*		size - the planets scaled size w.r.t the sun
*		n - planet's name
*		c - the color of the planet
* /return none
*******************************************************************************/
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

/*******************************************************************************
* Author: Anthony Morast, Samuel Carroll
* /brief Getters for the Planet class' attributes
*
* Various getters that return all of the planet objects attributes except the 
* attributes used for animation of the solar system. 
*
* /params none
* /return none
*******************************************************************************/
float Planet::getRadius() { return radius; }
float Planet::getDistance() { return distance; }
float Planet::getYear() { return year; }
float Planet::getDay() { return day; }
float Planet::getScaledSize() { return scaledSize; }
Color Planet::getColor() { return color; }
string Planet::getName() { return name; }
Image Planet::getImage() { return img; }

/*******************************************************************************
* Author: Anthony Morast, Samuel Carroll
* /brief Setters for the Planet class' attributes
*
* Setters used to modify the planet object's various attributes. There is a 
* setter for every attribute excluding the attributes used in the animation.
*
* /params none
* /return none
*******************************************************************************/
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

