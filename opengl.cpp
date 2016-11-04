#include "opengl.h"

// put these in here rather than the header, was getting some redefinition errors
// couldn't find out where.
int ScreenWidth = 1200;
int ScreenHeight = 800;

/*******************************************************************************
 * 								OpenGL Callbacks 							   *
 ******************************************************************************/
void keyboard( unsigned char key, int x, int y )
{
	
}

void display( void )
{
	
}

void reshape( int x, int y )
{

}

/*******************************************************************************
 * 									Misc.									   *
 ******************************************************************************/
void init() 
{
	glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE );
	
	// window settings 
	glutInitWindowSize( ScreenWidth, ScreenHeight );
	glutInitWindowPosition( 200, 200 );
	glutCreateWindow( "Solar System" );
	
	// clear screen color - black
	glClearColor( 0.0, 0.0, 0.0, 1.0 );

	// callbacks
	glutDisplayFunc( display );
	glutReshapeFunc( reshape );
	glutKeyboardFunc( keyboard );
}

int GetScreenWidth() 
{
	return ScreenWidth;
}

int GetScreenHeight()
{
	return ScreenHeight;
}
