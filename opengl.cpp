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
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

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

	// Back off eight units to be able to view from the origin.
    glTranslatef ( 0.0, 0.0, -100.0 );

    // Rotate the plane of the elliptic
    // (rotate the model's plane about the x axis by fifteen degrees)
    glRotatef( 15.0, 1.0, 0.0, 0.0 );

    // Draw the Earth
    // First position it around the sun. Use DayOfYear to determine its position.
    //glRotatef( 360.0 * DayOfYear / 365.0, 0.0, 1.0, 0.0 );
	glPushMatrix();
    glTranslatef( Planets[3].getDistance()/50, 0.0, 0.0 );
    // Second, rotate the earth on its axis. Use HourOfDay to determine its rotation.
    //glRotatef( 360.0 * HourOfDay / 24.0, 0.0, 1.0, 0.0 );
    // Third, draw the earth as a wireframe sphere.
    glColor3f( 0.2, 0.2, 1.0 );
    //glutWireSphere( Planets[3].GetScaledSize(), 10, 10 );
    glPopMatrix();						// Restore matrix state

	// Draw the moon. Use DayOfYear to control its rotation around the earth
//    glRotatef( 360.0 * 12.0 * DayOfYear / 365.0, 0.0, 1.0, 0.0 );
//    glTranslatef( 0.7, 0.0, 0.0 );
//    glColor3f( 0.3, 0.7, 0.3 );
//    glutWireSphere( 0.1, 5, 5 );

	for( int i = 8; i >= 1; i-- )
	{
		Planet &p = Planets[i];
		p.hourOfDay += p.animateIncrement;
		p.dayOfYear = p.dayOfYear + (p.animateIncrement / p.getDay());
		p.hourOfDay = p.hourOfDay - ( (int)( p.hourOfDay / p.getDay() ) ) * p.getDay();
		p.dayOfYear = p.dayOfYear - ( (int)( p.dayOfYear / p.getYear() ) ) * p.getYear();

		// need to specify normals in here for smooth shading
		Color c = p.getColor();
		glColor3f( c.r, c.g, c.b ); 
		glPushMatrix(); 
			glRotatef( 360.0 * p.dayOfYear / p.getYear(), 0.0, 1.0, 0.0 );
			glRotatef( 360.0 * p.hourOfDay / p.getDay(), 0.0, 1.0, 0.0 );
			glTranslatef( 15*i, 0.0, 0.0 );
			gluSphere( gluNewQuadric(), p.getScaledSize(), 15, 15 );
		glPopMatrix();
	}

    // Draw the sun	-- as a yellow, wireframe sphere
	glClear( GL_DEPTH_BUFFER_BIT );
    glColor3f( 1.0, 1.0, 0.0 );
    gluSphere( gluNewQuadric(), 10, 20, 20 );

	glutSwapBuffers();
	glutPostRedisplay();
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

	glEnable( GL_NORMALIZE );
	glEnable( GL_DEPTH_TEST );
    glEnable( GL_TEXTURE_2D );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

	SetupTextureMapping();

	texture = Flat;
}

void SetupTextureMapping()
{
	glGenTextures( 9, &textureNames[0] );
	for( int i = 0; i <= 9; i++ )
	{
		glBindTexture( GL_TEXTURE_2D, textureNames[i] );
		Image img = Planets[i].getImage();
		gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, img.cols, img.rows,
						  GL_RGB, GL_UNSIGNED_BYTE, img.ptr );
	}
}
