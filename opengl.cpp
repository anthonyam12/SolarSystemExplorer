#include "opengl.h"


/*******************************************************************************
 * 								OpenGL Callbacks 							   *
 ******************************************************************************/
void keyboard( unsigned char key, int x, int y )
{
	// s - smooth shading
	// f - flat shading
	// w - wireframe
	// t - texture mapping
	switch( key ) 
	{
		case s:
			texture = Smooth;
			break;
		case f:
			texture = Flat;
			break;
		case w:
			texture = Wireframe;
			break;
		case t:
			texture = TextureMap;
			break;
		case Esc:
			exit( 0 );
			break;
	}
	glutPostRedisplay();
}

void display( void )
{
	glLoadIdentity();
	glClear( GL_COLOR_BUFFER_BIT );

	// Might make this a function
	switch( texture )
	{
		case Wireframe:
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
			break;
		case Flat:
			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
			glShadeModel( GL_FLAT );
			break;
		case Smooth:
			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
			glShadeModel( GL_SMOOTH );
			break;
		case TextureMap:
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
			break;
	}

	float DayOfYear = 0;
	float HourOfDay = 0;

	// Back off eight units to be able to view from the origin.
    glTranslatef ( 0.0, 0.0, -100.0 );

    // Rotate the plane of the elliptic
    // (rotate the model's plane about the x axis by fifteen degrees)
    glRotatef( 15.0, 1.0, 0.0, 0.0 );

    // Draw the sun	-- as a yellow, wireframe sphere
    glColor3f( 1.0, 1.0, 0.0 );
    gluSphere( gluNewQuadric(), 10, 20, 20 );

    // Draw the Earth
    // First position it around the sun. Use DayOfYear to determine its position.
    glRotatef( 360.0 * DayOfYear / 365.0, 0.0, 1.0, 0.0 );
	glPushMatrix();
    glTranslatef( Planets[3].getDistance()/50, 0.0, 0.0 );
    // Second, rotate the earth on its axis. Use HourOfDay to determine its rotation.
    glRotatef( 360.0 * HourOfDay / 24.0, 0.0, 1.0, 0.0 );
    // Third, draw the earth as a wireframe sphere.
    glColor3f( 0.2, 0.2, 1.0 );
//    glutWireSphere( Planets[3].GetScaledSize(), 10, 10 );
    glPopMatrix();						// Restore matrix state

	// Draw the moon. Use DayOfYear to control its rotation around the earth
//    glRotatef( 360.0 * 12.0 * DayOfYear / 365.0, 0.0, 1.0, 0.0 );
//    glTranslatef( 0.7, 0.0, 0.0 );
//    glColor3f( 0.3, 0.7, 0.3 );
//    glutWireSphere( 0.1, 5, 5 );

	float base = 1.5;
	float based = Planets[1].getDistance();
	for( int i = 1; i < 9; i++ )
	{
		// need to specify normals in here for smooth shading
		Color c = Planets[i].getColor();
		glColor3f( c.r, c.g, c.b );
		//glPushMatrix();
		//glTranslatef( ((Planets[i].GetDistance()/based)*base)/div, 0, 0 );
		glTranslatef( 15, 0.0, 0.0 );
		gluSphere( gluNewQuadric(), Planets[i].getScaledSize(), 15, 15 );
		//glPopMatrix();
	}

	glutSwapBuffers();
}

void reshape( int w, int h )
{
	ScreenWidth = w;
	ScreenHeight = h;

 	float aspectRatio;
    h = ( h == 0 ) ? 1 : h;
    w = ( w == 0 ) ? 1 : w;
    glViewport( 0, 0, w, h );
    aspectRatio = ( float ) w / ( float ) h;

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();	
	gluPerspective( 60, aspectRatio, -10, 10 ); 
    glMatrixMode( GL_MODELVIEW );
}

/*******************************************************************************
 * 									Misc.									   *
 ******************************************************************************/
void init() 
{
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
	
	// window settings 
	glutInitWindowSize( ScreenWidth, ScreenHeight );
	glutInitWindowPosition( 200, 200 );
	glutCreateWindow( "Solar System" );
	
	// clear screen color - black
	glClearColor( 0.0, 0.0, 0.0, 0.0 );
	glClearDepth( 1.0 );

	// callbacks
	glutDisplayFunc( display );
	glutReshapeFunc( reshape );
	glutKeyboardFunc( keyboard );

	texture = Flat;
}
