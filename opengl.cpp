#include "opengl.h"


/*******************************************************************************
 * 								OpenGL Callbacks 							   *
 ******************************************************************************/
void keyboard( unsigned char key, int x, int y )
{
	
}

void display( void )
{
	glLoadIdentity();
	glClear( GL_COLOR_BUFFER_BIT );
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	float DayOfYear = 0;
	float HourOfDay = 0;

	// Back off eight units to be able to view from the origin.
    //glTranslatef ( 0.0, 0.0, -8.0 );

    // Rotate the plane of the elliptic
    // (rotate the model's plane about the x axis by fifteen degrees)
    glRotatef( 15.0, 1.0, 0.0, 0.0 );

    // Draw the sun	-- as a yellow, wireframe sphere
    glColor3f( 1.0, 1.0, 0.0 );
    gluSphere( gluNewQuadric(), 1, 20, 20 );

    // Draw the Earth
    // First position it around the sun. Use DayOfYear to determine its position.
    glRotatef( 360.0 * DayOfYear / 365.0, 0.0, 1.0, 0.0 );
	glPushMatrix();
    glTranslatef( Planets[3].GetDistance()/50, 0.0, 0.0 );
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
	float based = Planets[1].GetDistance();
	for( int i = 1; i < 9; i++ )
	{
		float div = i >=5 ? i : 1;
		cout << ((Planets[i].GetDistance()/based)*base)/div << endl;
		glPushMatrix();
		glTranslatef( ((Planets[i].GetDistance()/based)*base)/div, 0, 0 );
		gluSphere( gluNewQuadric(), Planets[i].GetScaledSize(), 20, 20 );
		glPopMatrix();
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
    if ( w <= h )
        glOrtho( -14.0, 14.0, -14.0 * aspectRatio, 14.0 * aspectRatio, -10.0, 10.0 );
    else
        glOrtho( -14.0 * aspectRatio, 14.0 * aspectRatio, -14.0, 14.0, -10.0, 10.0 ); 
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
}
