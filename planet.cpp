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
* \brief Draws the planet and it's accompanying objects
*
* Calculates the day of the year and the hour of the day and rotates based on 
* these values. The object is translated a certain distance away from the sun
* based on its distance to the sun and 'i' which sets it a certain amount away
* from the sun along with its distance. Depending on our current texture selected
* we will draw the planet in its preset color or we will map the texture associated
* with the planet to the gluSphere.
*
* \params i - index in the planet array (where it's located in the solar system)
* \return none
*******************************************************************************/
void Planet::Draw( int i )
{
	GLUquadric *quad = gluNewQuadric();

	// select multiplier to prevent ridiculous spinning
	hourOfDay += animateIncrement*(IncrementMult > 0.25 ? IncrementMult : 0.5);
	dayOfYear = dayOfYear + ((animateIncrement*IncrementMult) / getDay());
	hourOfDay = hourOfDay - ( (int)( hourOfDay / getDay() ) ) * getDay();
	dayOfYear = dayOfYear - ( (int)( dayOfYear / getYear() ) ) * getYear();
	
	glPushMatrix();
	if ( texture != TextureMap )
	{
		glColor3f( color.r, color.g, color.b ); 
	}
	else
	{
		// map the BMPs to the planets if in TextureMap mode
		unsigned char* imgPtr = img.ptr;
		int nrows = img.rows, ncols = img.cols;
		gluQuadricTexture (quad, GL_TRUE);
		glTexImage2D( GL_TEXTURE_2D, 0, 3, ncols, nrows, 0, 
					  GL_RGB, GL_UNSIGNED_BYTE, imgPtr );
		glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
	}
	glRotatef( 360.0 * dayOfYear / getYear(), 0.0, 1.0, 0.0 );
	glTranslatef( (20.0*i)+(getDistance()/10.0), 0.0, 0.0 );
	if( getName() == "Earth" )
		glPushMatrix();
	// rotation on the planet's axis
	glRotatef( 360.0 * hourOfDay / getDay(), 0.0, 1.0, 0.0 );
	gluSphere( quad, getScaledSize(), 15, 15 );

	// draw name
	glDisable( GL_TEXTURE_2D );
	glColor3f( 0.0, 1.0, 0.0 );
	glRasterPos3f( 0.0, getScaledSize()*1.2, 0.0 );
	glutBitmapString( GLUT_BITMAP_9_BY_15, (const unsigned char*)name.c_str() );
	if( texture == TextureMap )
		glEnable( GL_TEXTURE_2D );
	
	// draw the moon if earth
	if( getName() == "Earth" )
	{
		glPopMatrix();
		GLUquadric *moonq = gluNewQuadric();
   		glRotatef( 360.0 * 12.0 * dayOfYear / 365.0, 0.0, 1.0, 0.0 );
   	 	glTranslatef( getScaledSize() + 1.1, 0.0, 0.0 );
		Planet moon = Planets[9];
		// handle moons texture
		if( texture != TextureMap )
		{
			Color mc = moon.getColor();
			glColor3f( mc.r, mc.g, mc.b );
		}
		else
		{	
			unsigned char* imgm = moon.getImage().ptr;
			int nrows = moon.getImage().rows, ncols = moon.getImage().cols;
			gluQuadricTexture (moonq, GL_TRUE);
			glTexImage2D( GL_TEXTURE_2D, 0, 3, ncols, nrows, 0, 
						  GL_RGB, GL_UNSIGNED_BYTE, imgm );
			glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
		}
 		gluSphere( moonq, moon.getScaledSize(), 10, 10 );
		glDisable( GL_TEXTURE_2D );
		glColor3f( 0.0, 1.0, 0.0 );
		glRasterPos3f( 0.0, moon.getScaledSize()*1.2, 0.0 );
		glutBitmapString( GLUT_BITMAP_9_BY_15, (const unsigned char*)moon.getName().c_str() );
		if ( texture == TextureMap )
			glEnable( GL_TEXTURE_2D );
	}
	glPopMatrix();
}

/*******************************************************************************
* Author: Anthony Morast, Samuel Carroll
* \brief Draws the sun and sets it up as a light source
*
* Draws the sun a set size and texture, either color or associated image based
* on our current mode, and sets the sun up as a light source. 
*
* \params none
* \return none
*******************************************************************************/
void Planet::DrawSun()
{
    // Draw the sun	depending on current texture mode
	GLUquadric *quad = gluNewQuadric();
	if( texture != TextureMap )
	{
    	glColor3f( 1.0, 1.0, 0.0 );
	}
	else
	{
		unsigned char* imgPtr = img.ptr;
		int nrows = img.rows, ncols = img.cols;
		gluQuadricTexture ( quad, GL_TRUE );
		glTexImage2D( GL_TEXTURE_2D, 0, 3, ncols, nrows, 0, 
					  GL_RGB, GL_UNSIGNED_BYTE, imgPtr );
		glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
	}
    gluSphere( quad, 20, 20, 20 );
	if( LightsEnabled )
	{
		// light for the sun
		glEnable( GL_LIGHT0 );
		GLfloat la[4] = { .5, .5, .5, .8 }; // ambient light
		GLfloat ld[4] = { 1.0, 1.0, 0.5, 1.0 }; // diffuse light
		GLfloat ls[4] = { 1.0, 1.0, 0.5, 1.0 }; // specular light
		GLfloat lp[4] = { 1.0, 1.0, 0.0, 1.0 }; // light position
	
		// create sun light source
		glLightfv( GL_LIGHT0, GL_AMBIENT, la );
		glLightfv( GL_LIGHT0, GL_DIFFUSE, ld );
		glLightfv( GL_LIGHT0, GL_SPECULAR, ls );
		glLightfv( GL_LIGHT0, GL_POSITION, lp );
	}
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

