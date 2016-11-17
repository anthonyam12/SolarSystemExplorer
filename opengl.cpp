#include "opengl.h"

/***
*
* NOTE!!!!!!!!!!!!!!! IF this file becomes > 500 lines, move the input handling
* to another class/cpp file. Since most things modified are global this should
* be no problem. We would just cut and paste the openGL callbacks to another 
* file/class and set the functions differently in init().
*
*/

// ext. functions
bool LoadBmpFile( const char* filename, int &rows, int &cols, unsigned char* &imgPtr );

/*******************************************************************************
 * 								OpenGL Callbacks 							   *
 ******************************************************************************/
void keyboard( unsigned char key, int x, int y )
{
	// s - single step
	// f - flat/smooth shading toggle
	// w - wireframe
	// t - texture mapping
	// r - pause/resume
	// A/a - speed up/down animation
	// ' ' - single step step
	// + - zoom in
	// - - zoom out
	switch( key ) 
	{
		case s:
			if ( !Paused )
			{
				SingleStep = !SingleStep;
				if ( SingleStep )
					PreviousMult = IncrementMult;
				else
					IncrementMult = PreviousMult;
			}
			break;
		case f:
			if ( texture == Flat )
				texture = Smooth;
			else 
				texture = Flat;
			break;
		case w:
			texture = Wireframe;
			break;
		case t:
			texture = TextureMap;
			glEnable( GL_TEXTURE_2D );
			break;
		case Minus:
			CamZ -= 5;
			break;
		case Plus:
			CamZ += 5;
			break;
		case r:
			if ( !SingleStep )
			{
				Paused = !Paused;
				if ( Paused )
				{
					PreviousMult = IncrementMult;
					IncrementMult = 0.0;
				}
				else
					IncrementMult = PreviousMult;
			}
			break;
		case Space:
			break;
		case A:
			IncrementMult = IncrementMult == 0 ? .25 : 
							IncrementMult * 2;
			if ( Paused || SingleStep )
			{
				PreviousMult = PreviousMult == 0 ? .25 : 
							   PreviousMult * 2;
			}
			break;
		case a:
			IncrementMult /= 2.0;
			if( Paused || SingleStep )
				PreviousMult /= 2;
			break;
		case X:
			RotateX -= 1.0;
			break;
		case xx:
			RotateX += 1.0;
			break;
		case Y:
			RotateY += 1.0;
			break;
		case yy:
			RotateY -= 1.0;
			break;
		case Z:
			RotateZ += 1.0;
			break;
		case z:
			RotateZ -= 1.0;
			break;
		case l:
			LightsEnabled = !LightsEnabled;
			if ( LightsEnabled )
				glEnable( GL_LIGHTING );
			else
				glDisable( GL_LIGHTING );
			break;
		case Esc:
			exit( 0 );
			break;
	}
	// funky logic to be able to change the simulation attributes
	// without taking a 'step' 
	if ( ( SingleStep && key != Space ) || Paused )
		IncrementMult = 0.0;
	else if ( SingleStep )
		IncrementMult = PreviousMult;

	glutPostRedisplay();
}

void mouseclick( int button, int state, int x, int y )
{
	// mouse wheel in - zoom in
	// mouse wheel out - zoom out
	if( button == 3 ) // mouse wheel 'in', zoom in
		CamZ += 5.0;
	if( button == 4 )
		CamZ -= 5.0;

	glutPostRedisplay();
}

void special( int key, int x, int y )
{
	// up - pan up (+y)
	// down - pan down (-y)
	// left - pan left
	// right - pan right
	switch( key )
	{
		case GLUT_KEY_UP:
			CamY -= 2.0;
			break;
		case GLUT_KEY_DOWN:
			CamY += 2.0;
			break;
		case GLUT_KEY_RIGHT:
			CamX -= 2.0;
			break;
		case GLUT_KEY_LEFT:
			CamX += 2.0;
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
			glDisable( GL_TEXTURE_2D );
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
			break;
		case Flat:
			glDisable( GL_TEXTURE_2D );
			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
			glShadeModel( GL_FLAT );
			break;
		case Smooth:
			glDisable( GL_TEXTURE_2D );
			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
			glShadeModel( GL_SMOOTH );
			break;
		case TextureMap:
			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
			glShadeModel( GL_SMOOTH );
			break;
	}

	// back off of origin to see scene
    glTranslatef ( CamX, CamY, CamZ );

    // Rotate the plane of the elliptic
    glRotatef( RotateX, 0.0, 1.0, 0.0 );
	glRotatef( RotateY, 1.0, 0.0, 0.0 );
	glRotatef( RotateZ, 0.0, 0.0, 1.0 );
	
	for( int i = 8; i >= 1; i-- )
	{
		GLUquadric *quad = gluNewQuadric();
		Planet &p = Planets[i];
		// select multiplier to prevent ridiculous spinning
		p.hourOfDay += p.animateIncrement*(IncrementMult > 0.25 ? IncrementMult : 0.5);
		p.dayOfYear = p.dayOfYear + ((p.animateIncrement*IncrementMult) / p.getDay());
		p.hourOfDay = p.hourOfDay - ( (int)( p.hourOfDay / p.getDay() ) ) * p.getDay();
		p.dayOfYear = p.dayOfYear - ( (int)( p.dayOfYear / p.getYear() ) ) * p.getYear();

		// Make closer objects on top of not closer objects		
		glClear( GL_DEPTH_BUFFER_BIT );
		// need to specify normals in here for smooth shading
		if ( texture != TextureMap )
		{
			Color c = p.getColor();
			glColor3f( c.r, c.g, c.b ); 
		}
		else 
		{
			unsigned char* img = p.getImage().ptr;
			int nrows = p.getImage().rows, ncols = p.getImage().cols;
			gluQuadricTexture (quad, GL_TRUE);
			glTexImage2D( GL_TEXTURE_2D, 0, 3, ncols, nrows, 0, 
						  GL_RGB, GL_UNSIGNED_BYTE, img );
			glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
		}
		glPushMatrix(); 
			glRotatef( 360.0 * p.dayOfYear / p.getYear(), 0.0, 1.0, 0.0 );
			glTranslatef( p.getDistance()/100 + (30*i), 0.0, 0.0 );
			if( p.getName() == "Earth" )
				glPushMatrix();
			glRotatef( 360.0 * p.hourOfDay / p.getDay(), 0.0, 1.0, 0.0 );
			gluSphere( quad, p.getScaledSize(), 15, 15 );	
			// draw the moon if earth
			if( p.getName() == "Earth" )
			{
				glPopMatrix();
	    		glRotatef( 360.0 * 12.0 * p.dayOfYear / 365.0, 0.0, 1.0, 0.0 );
		   	 	glTranslatef( p.getScaledSize() + 1.1, 0.0, 0.0 );
				Planet moon = Planets[9];
				Color mc = moon.getColor();
				glColor3f( mc.r, mc.g, mc.b );
    			gluSphere( gluNewQuadric(), moon.getScaledSize(), 10, 10 );
			}
		glPopMatrix();	
	}

    // Draw the sun	-- as a yellow, wireframe sphere
	glClear( GL_DEPTH_BUFFER_BIT );
	GLUquadric *quad = gluNewQuadric();
	if( texture != TextureMap )
	{
    	glColor3f( 1.0, 1.0, 0.0 );
	}
	else 
	{
		Planet p = Planets[0];
		unsigned char* img = p.getImage().ptr;
		int nrows = p.getImage().rows, ncols = p.getImage().cols;
		gluQuadricTexture ( quad, GL_TRUE );
		glTexImage2D( GL_TEXTURE_2D, 0, 3, ncols, nrows, 0, 
					  GL_RGB, GL_UNSIGNED_BYTE, img );
		glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
	}
    gluSphere( quad, 20, 20, 20 );
	glutSwapBuffers();

	if ( !SingleStep && !Paused )
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
	gluPerspective( 60, aspectRatio, -100, 1 ); 
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
	glutSpecialFunc( special );
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
	CreateLights();

	texture = Wireframe;
}

void CreateLights()
{
	// enable lighting	
	glEnable( GL_LIGHTING );
	
	// setup light properties for colors and materials
	glEnable( GL_COLOR_MATERIAL );
	glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );

	// ambient light - weighted more towards yellow because of sun
	GLfloat lv[4] = { 0.2, 0.2, 0.2, 1.0 };
	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, lv );

	// light for the sun -- I don't think this is position correctly
	glEnable( GL_LIGHT0 );
	GLfloat la[4] = { 0.0, 0.0, 0.0, 1.0 }; // ambient light
	GLfloat ld[4] = { 1.0, 1.0, 0.5, 1.0 }; // diffuse light
	GLfloat ls[4] = { 0.0, 0.0, 0.0, 1.0 }; // specular light
	GLfloat lp[4] = { 0.0, 0.0, 0.0, 1.0 }; // light position
	glLightfv( GL_LIGHT0, GL_AMBIENT, la );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, ld );
	glLightfv( GL_LIGHT0, GL_SPECULAR, ls );
	glLightfv( GL_LIGHT0, GL_POSITION, lp );
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
