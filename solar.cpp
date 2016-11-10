#include "solar.h"

int main(int argc, char*argv[])
{
	CreatePlanetArray();

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
	Planet sun = Planet( 696000, 0, 0, 25, "Sun" );
	Planet mercury = Planet( 2439, 58, 88, 1416, "Mercury" );
	Planet venus = Planet( 6052, 108, 225, 5832, "Venus" );
	Planet earth = Planet( 6378, 150, 365, 24, "Earth" );
	Planet mars = Planet( 3394, 228, 687, 24.6, "Mars" );
	Planet jupiter = Planet( 71398, 779, 4332, 9.8, "Jupiter" );
	Planet saturn = Planet( 60270, 1424, 10761, 10.2, "Saturn" );
	Planet uranus = Planet( 25550, 2867, 30682, 15.5, "Uranus" );
	Planet neptune = Planet( 24750, 4493, 60195, 15.8, "Neptune" );
	Planet moon = Planet( 1738, 0.384, 27.3, 27.3, "Moon" );

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
}

