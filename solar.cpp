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
	// scale the sun down a bit
	Planet sun = Planet( 36000, 0, 0, 25, 1, "Sun" );
	float sunSize = sun.GetRadius();

	Planet mercury = Planet( 2439, 58, 88, 1416, 2439.0/sunSize, "Mercury" );
	Planet venus = Planet( 6052, 108, 225, 5832, 6052.0/sunSize, "Venus" );
	Planet earth = Planet( 6378, 150, 365, 24, 6378.0/sunSize, "Earth" );
	Planet mars = Planet( 3394, 228, 687, 24.6, 3394.0/sunSize, "Mars" );
	Planet jupiter = Planet( 71398, 779, 4332, 9.8, 71398.0/sunSize, "Jupiter" );
	Planet saturn = Planet( 60270, 1424, 10761, 10.2, 60270.0/sunSize, "Saturn" );
	Planet uranus = Planet( 25550, 2867, 30682, 15.5, 25550.0/sunSize, "Uranus" );
	Planet neptune = Planet( 24750, 4493, 60195, 15.8, 24750.0/sunSize, "Neptune" );
	Planet moon = Planet( 1738, 0.384, 27.3, 27.3, 1738.0/sunSize, "Moon" );

//	Planet mercury = Planet( 2439, 58, 88, 1416, 1, "Mercury" );
//	Planet venus = Planet( 6052, 108, 225, 5832, 1, "Venus" );
//	Planet earth = Planet( 6378, 150, 365, 24, 1, "Earth" );
//	Planet mars = Planet( 3394, 228, 687, 24.6, 1, "Mars" );
//	Planet jupiter = Planet( 71398, 779, 4332, 9.8, 1, "Jupiter" );
//	Planet saturn = Planet( 60270, 1424, 10761, 10.2, 1, "Saturn" );
//	Planet uranus = Planet( 25550, 2867, 30682, 15.5, 1, "Uranus" );
//	Planet neptune = Planet( 24750, 4493, 60195, 15.8, 1, "Neptune" );
//	Planet moon = Planet( 1738, 0.384, 27.3, 27.3, 1, "Moon" );

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
		if( Planets[i].GetScaledSize() > 1.0 )
			Planets[i].SetScaledSize( 1.0 );
		Planets[i].SetScaledSize( Planets[i].GetScaledSize() * 10 );
	}
}


