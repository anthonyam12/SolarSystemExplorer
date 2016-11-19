/*******************************************************************************
* Authors: Anthony Morast, Samuel Carroll
* Date: 11/18/2016
* 
* CSC - 533 Computer Graphics, Dr. John Weiss
* Program 3 - Solar System Simulation
*
* Usage:
* 	solar
* 
* Description:
*	A simulation of the solar system including the Sun, Earth's moon, and the 8 
* planets; Mercury, Venus, Earth, Mars, Jupiter, Saturn, Uranus, and Neptune. 
* The planets all orbit the sun and revolve on their own axes while Earth's
* moon revolves around the Earth. Also drawn are the rings of Saturn. 
*	
* The following is a key mapping for user inputs, 
*		s - toggles 'single step' mode in which the user can step through the simulation
*		<space> - takes a step while in single step mode
*		r - toggles pause 
*		f - toggles flat/smooth shading
*		w - switches celestial objects to wireframe spheres
*		t - maps images of the planets to the planets
*		A/a - 'A' speeds up the simulation, 'a' slows down the simulation
*		+/- - zoom in and out 
*		X/x Y/y Z/z - rotate the solar system about the x,y, and z axes, respectively
*		l - toggles the lights 
*		MouseWheel in/out - zooms in and out 
* 		Arrow Keys - pans left, right, up, and down
* 		Mouse Left Click and drag - rotate around the x and y axes
* 		Mouse Right Click - pop up menues
* 
* Additionally, we incorporated a mouse menu containing much (or all) of the 
* functionality associated with the mouse and keyboard. This menu is accessed
* via right-click. 
* 
* Using the keymap above the user can change attributes of the simulation, most
* interestingly the texture mapping and shading diffrences and the animation 
* speeds. 
*
* Known Bugs:
*	- pan, rotate seem to act a bit funky
*	- rotate x curves
*
* Potential Improvements
*
*******************************************************************************/
#include "solar.h"

// Main - doesn't really do anything besides init things and get the ball rolling
int main(int argc, char*argv[])
{
	// Init rand, create celestial objects, get random orbit positions
	srand( time( NULL ) );
	CreatePlanetArray();
	InitPlanetOrbitPosition();

	// let OpenGL/glut take over
	glutInit( &argc, argv );
	InitOpenGl();
	glutMainLoop();
	
	// a useless statement 
	return 0;
}

/*******************************************************************************
* Author: Anthony Morast, Samuel Carroll
* \brief Inits OpenGL attributes
*
* Class the OpenGL init function (opengl.cpp) to initialize some OpenGL 
* attributes.
*
* \params none
* \return none
*******************************************************************************/
void InitOpenGl()
{
	init();
}

/*******************************************************************************
* Author: Anthony Morast, Samuel Carroll
* \brief Creates the Planets array containing all the celestial objects
*
* Creates the Planets array by creating multiple Planet objects. The objects are
* created with a scaled size w.r.t. the sun and other values found in the PA3 
* writeup. After the planet objects are created they're added (mostly in order)
* to the Planets array. Once filled, the Planets array is iterated and the 
* scaled size of the planets is clipped and increased to better fit our display.
*
* \params none
* \return none
*******************************************************************************/
void CreatePlanetArray()
{
	// create a color for each planet
	Color color;
	color.r = 1.0; color.g = 1.0; color.b = 0.0;
	// scale the sun down a bit
	Planet sun = Planet( 36000, 0, 0, 25, 20, "Sun", color );
	float sunSize = sun.getRadius();

	// create the 8 planets and Earth's moon with their various values
	color.r = .5843; color.g = .502; color.b = .502;
	Planet mercury = Planet( 2439, 58, 88, 1416, 2439.0/sunSize, "Mercury", color );
	color.r = .8627; color.g = .8; color.b = .3765;
	Planet venus = Planet( 6052, 108, 225, 5832, 6052.0/sunSize, "Venus", color );
	color.r = 0.0; color.g = 0.0; color.b = 1.0;
	Planet earth = Planet( 6378, 150, 365, 24, 6378.0/sunSize, "Earth", color );
	color.r = .5843; color.g = 0.0; color.b = 0.0;
	Planet mars = Planet( 3394, 228, 687, 24.6, 3394.0/sunSize, "Mars", color );
	color.r = 1.0; color.g = .3372; color.b = 0.0509;
	Planet jupiter = Planet( 71398, 779, 4332, 9.8, 71398.0/sunSize, "Jupiter", color );
	color.r = .8549; color.g = .6471; color.b = .1254;
	Planet saturn = Planet( 60270, 1424, 10761, 10.2, 60270.0/sunSize, "Saturn", color );
	color.r = 0.0; color.g = .749; color.b = 1.0;
	Planet uranus = Planet( 25550, 2867, 30682, 15.5, 25550.0/sunSize, "Uranus", color );
	color.r = .1176; color.g = .5647; color.b = 1.0;
	Planet neptune = Planet( 24750, 4493, 60195, 15.8, 24750.0/sunSize, "Neptune", color );
	color.r = .8039; color.g = .7882; color.b = .7882;
	Planet moon = Planet( 1738, 0.384, 27.3, 27.3, 1738.0/sunSize, "Moon", color );
	Planet rings = Planet( 60000, 0.09, 0, 10.2, 50000.0/sunSize, "Rings", color );

	// fill the Planets array
	Planets[0] = sun;
	Planets[1] = mercury;
	Planets[2] = venus;
	Planets[3] = earth;
	Planets[4] = mars;
	Planets[5] = jupiter;
	Planets[6] = saturn;
	Planets[7] = uranus;
	Planets[8] = neptune;
	Planets[9] = moon;
	Planets[10] = rings;

	// clip the planets' scaled size and increase for our larger display
	for( int i = 1; i < 11; i++ ) 
	{
		if( Planets[i].getScaledSize() > 1.0)
			Planets[i].setScaledSize( 1.0 );
		Planets[i].setScaledSize( Planets[i].getScaledSize() * 10 );
	}

	// set the images associated with each planet
	SetPlanetBitmaps();
}

/*******************************************************************************
* Author: Anthony Morast, Samuel Carroll
* \brief Reads in BMPs which are to be mapped to all the celestial objects
*
* Using the LoadBmpFile(...) function provided by Dr. Wiess on the course website, 
* we read in the BMP images stored in the img subdirectory of our project. After
* reading the BMPs we set the Image associated with each Planet. The Image struct
* stores the images row count, column count, and a pointer to the image's data.
*
* \params none
* \return none
*******************************************************************************/
void SetPlanetBitmaps() 
{
	unsigned char* img;
	int rows;
	int cols;
	
	// read each BMP file associated with the objects and set the image on
	// the planet object
	LoadBmpFile( "img/sun.bmp", rows, cols, img );
	Planets[0].setImage( img, rows, cols );
	LoadBmpFile( "img/mercury.bmp", rows, cols, img );
	Planets[1].setImage( img, rows, cols );
	LoadBmpFile( "img/venus.bmp", rows, cols, img );
	Planets[2].setImage( img, rows, cols );
	LoadBmpFile( "img/earth.bmp", rows, cols, img );
	Planets[3].setImage( img, rows, cols );
	LoadBmpFile( "img/mars.bmp", rows, cols, img );
	Planets[4].setImage( img, rows, cols );
	LoadBmpFile( "img/jupiter.bmp", rows, cols, img );
	Planets[5].setImage( img, rows, cols );
	LoadBmpFile( "img/saturn.bmp", rows, cols, img );
	Planets[6].setImage( img, rows, cols );
	LoadBmpFile( "img/uranus.bmp", rows, cols, img );
	Planets[7].setImage( img, rows, cols );
	LoadBmpFile( "img/neptune.bmp", rows, cols, img );
	Planets[8].setImage( img, rows, cols );
	LoadBmpFile( "img/moon.bmp", rows, cols, img );
	Planets[9].setImage( img, rows, cols );
	LoadBmpFile( "img/saturnrings.bmp", rows, cols, img );
	Planets[10].setImage( img, rows, cols );
}

/*******************************************************************************
* Author: Anthony Morast, Samuel Carroll
* \brief Start the planets at a random position in their orbit
*
* Sets the starting point if each planets orbit. A planet's orbit is restricted 
* by 0 (the first day in its year) and the maximum number of days in its year. 
*
* \params none
* \return none
*******************************************************************************/
void InitPlanetOrbitPosition()
{
	// planet max is it's 'year' max days per year
	for( int i = 1; i < 9; i++ )
	{
		// generate and set a random orbit start location
		Planet &p = Planets[i];
		p.dayOfYear = rand() % (int)p.getYear();
	}
}
