#include "solar.h"

int main(int argc, char*argv[])
{
	srand( time( NULL ) );
	CreatePlanetArray();
	InitPlanetOrbitPosition();

	glutInit( &argc, argv );
	InitOpenGl();
	glutMainLoop();
}

void InitOpenGl()
{
	init();
}

void CreatePlanetArray()
{
	Color color;
	color.r = 1.0; color.g = 1.0; color.b = 0.0;
	// scale the sun down a bit
	Planet sun = Planet( 36000, 0, 0, 25, 1, "Sun", color );
	float sunSize = sun.getRadius();

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

	// clip size
	for( int i = 0; i < 10; i++ ) 
	{
		if( Planets[i].getScaledSize() > 1.0 )
			Planets[i].setScaledSize( 1.0 );
		Planets[i].setScaledSize( Planets[i].getScaledSize() * 10 );
	}

	SetPlanetBitmaps();
}

void SetPlanetBitmaps() 
{
	unsigned char* img;
	int rows;
	int cols;

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
}


void InitPlanetOrbitPosition()
{
	// planet max is it's 'year' max days per year
	for( int i = 1; i < 9; i++ )
	{
		Planet &p = Planets[i];
		p.dayOfYear = rand() % (int)p.getYear();
	}
}
