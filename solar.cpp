#include "solar.h"

int main(int argc, char*argv[])
{
	glutInit( &argc, argv );
	InitOpenGl();
	glutMainLoop();
}

void InitOpenGl()
{
	init();
}
