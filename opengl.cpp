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
/*******************************************************************************
* Author: Anthony Morast, Samuel Carroll
* \brief OpenGL callback to handle standard keyboard input
*
* The OpenGL callback to handle keyboard input. The keyboard input is mapped as
* follows:
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
*
* If we are in Single Step or Pause mode the disply is redrawn but with no 
* movement of the planets. Otherwise doing things like animating or changing
* textures would now work while in these modes OR would cause us to take a 
* 'step' in the simulation, which is not desired.
*
* \params 
*		key - the key value pressed
*		x - x position of key press
*		y - y position of key press
* \return none
*******************************************************************************/
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
	// X/x, Y/y, Z/z - rotate the simulation
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

/*******************************************************************************
* Author: Anthony Morast, Samuel Carroll
* \brief Handles mouse input
*
* Handles input from the mouse's buttons. Interactions are mapped as
*		mouse wheel out/down - zoom out 
*		mouse wheel up/in - zoom in 
*
* \params 
*		button - the mouse button pressed
*		state - pressed/released etc
*		x - x position of the mouse click
*		y - y position of the mouse click
* \return none
*******************************************************************************/
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

/*******************************************************************************
* Author: Anthony Morast, Samuel Carroll
* \brief Handles input from 'special' key presses
*
* In our case the only special keys handled are up, down, left, and right arrow
* keys. These keys are used to pan up, down, left, and right. 
*
* \params 
*		key - values of key pressed
*		x - x position of key press
*		y - y position of key press
* \return none
*******************************************************************************/
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


/*******************************************************************************
* Author: Anthony Morast, Samuel Carroll
* \brief Draws the current simulation state
*
* Determines how we want to texture our objects then draws the objects in the
* simulation. As part of the object display we set the rotation and translation
* of each planet. The translation defines where in the solar system the object
* will be drawn, this is dependent on the planet's distance from the sun (except
* for the moon and saturn rings).
*
* At the end of the method we request the display method be called again so that
* the simulation is constantly being updated. 
*
* \params none
* \return none
*******************************************************************************/
void display( void )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();
	
	// sets the OpenGL attributes we need set depending on
	// how we want to texture our objects
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

	// set the position of the scene
    glTranslatef ( CamX, CamY, CamZ );

    // Rotate around the scene based on user input
    glRotatef( RotateX, 0.0, 1.0, 0.0 );
	glRotatef( RotateY, 1.0, 0.0, 0.0 );
	glRotatef( RotateZ, 0.0, 0.0, 1.0 );
	
    // Draw the sun	depending on current texture mode
	//glClear( GL_DEPTH_BUFFER_BIT );
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
	if( LightsEnabled )
	{
		// light for the sun -- I don't think this is position correctly
		glEnable( GL_LIGHT0 );
		GLfloat la[4] = { .5, .5, .5, 1.0 }; // ambient light
		GLfloat ld[4] = { 1.0, 1.0, 0.5, 1.0 }; // diffuse light
		GLfloat ls[4] = { 1.0, 1.0, 0.5, 1.0 }; // specular light
		GLfloat lp[4] = { 1.0, 1.0, 0.0, 1.0 }; // light position
	
		// create sun light source
		glLightfv( GL_LIGHT0, GL_AMBIENT, la );
		glLightfv( GL_LIGHT0, GL_DIFFUSE, ld );
		glLightfv( GL_LIGHT0, GL_SPECULAR, ls );
		glLightfv( GL_LIGHT0, GL_POSITION, lp );
	}
	
	for (int i = 1; i < 9; i++)
	{
		GLUquadric *quad = gluNewQuadric();
		Planet &p = Planets[i];

		// select multiplier to prevent ridiculous spinning
		p.hourOfDay += p.animateIncrement*(IncrementMult > 0.25 ? IncrementMult : 0.5);
		p.dayOfYear = p.dayOfYear + ((p.animateIncrement*IncrementMult) / p.getDay());
		p.hourOfDay = p.hourOfDay - ( (int)( p.hourOfDay / p.getDay() ) ) * p.getDay();
		p.dayOfYear = p.dayOfYear - ( (int)( p.dayOfYear / p.getYear() ) ) * p.getYear();
	
		glPushMatrix();
		if ( texture != TextureMap )
		{
			Color c = p.getColor();
			glColor3f( c.r, c.g, c.b ); 
		}
		else 
		{
			// map the BMPs to the planets if in TextureMap mode
			unsigned char* img = p.getImage().ptr;
			int nrows = p.getImage().rows, ncols = p.getImage().cols;
			gluQuadricTexture (quad, GL_TRUE);
			glTexImage2D( GL_TEXTURE_2D, 0, 3, ncols, nrows, 0, 
						  GL_RGB, GL_UNSIGNED_BYTE, img );
			glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
		}
		glRotatef( 360.0 * p.dayOfYear / p.getYear(), 0.0, 1.0, 0.0 );
		glTranslatef( (30.0*i)+(p.getDistance()/100.0), 0.0, 0.0 );		
		if( p.getName() == "Earth" )
			glPushMatrix();
		// rotation on the planet's axis
		glRotatef( 360.0 * p.hourOfDay / p.getDay(), 0.0, 1.0, 0.0 );
		gluSphere( quad, p.getScaledSize(), 15, 15 );
		// draw the moon if earth
		if( p.getName() == "Earth" )
		{
			glPopMatrix();
			GLUquadric *moonq = gluNewQuadric();
    		glRotatef( 360.0 * 12.0 * p.dayOfYear / 365.0, 0.0, 1.0, 0.0 );
	   	 	glTranslatef( p.getScaledSize() + 1.1, 0.0, 0.0 );
			Planet moon = Planets[9];
			// handle moons texture
			if( texture != TextureMap )
			{
				Color mc = moon.getColor();
				glColor3f( mc.r, mc.g, mc.b );
			}
			else 
			{	
				unsigned char* img = moon.getImage().ptr;
				int nrows = moon.getImage().rows, ncols = moon.getImage().cols;
				gluQuadricTexture (moonq, GL_TRUE);
				glTexImage2D( GL_TEXTURE_2D, 0, 3, ncols, nrows, 0, 
							  GL_RGB, GL_UNSIGNED_BYTE, img );
				glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
			}
   			gluSphere( moonq, moon.getScaledSize(), 10, 10 );
		}
		glPopMatrix();
	}

	glFlush();
	glutSwapBuffers();
	
	// if we're not paused or in single step mode redraw display
	if ( !SingleStep && !Paused )
		glutPostRedisplay();
}

/*******************************************************************************
* Author: Anthony Morast, Samuel Carroll
* \brief OpenGL callback to handle window reshaping
*
* Adjusts our camera perspective based on the new window's width and height.
*
* \params 
*		w - new window width
*		h - new window height
* \return none
*******************************************************************************/
void reshape( int w, int h )
{
 	float aspectRatio;
    h = ( h == 0 ) ? 1 : h;
    w = ( w == 0 ) ? 1 : w;
    glViewport( 0, 0, w, h );
    aspectRatio = ( float ) w / ( float ) h;

	// adjust projection based on new screen size
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();	
	gluPerspective( 60, aspectRatio, 1, 1000 ); 
	
    glMatrixMode( GL_MODELVIEW );
}

/*******************************************************************************
 * 									Misc.									   *
 ******************************************************************************/
/*******************************************************************************
* Author: Anthony Morast, Samuel Carroll
* \brief Initialize our simulation (mostly the OpenGL components)
*
* Initialzie OpenGL attributes such as the window attributes and certain att.
* we need to properly draw and texture the celestial objects. 
*
* \params none
* \return none
*******************************************************************************/
void init() 
{
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
	
	// window settings 
	glutInitWindowSize( ScreenWidth, ScreenHeight );
	glutInitWindowPosition( 200, 200 );
	glutCreateWindow( "Solar System Simulation" );
	
	// clear screen color - black
	glClearColor( 0.0, 0.0, 0.0, 0.0 );
	glClearDepth( 1.0 );

	// callbacks
	glutDisplayFunc( display );
	glutSpecialFunc( special );
	glutReshapeFunc( reshape );
	glutKeyboardFunc( keyboard );
	
	// enable texture tpye attributes
	glEnable( GL_DEPTH_TEST );
    glEnable( GL_TEXTURE_2D );

	// setups some params for texture mapping
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

	// create the light sources
	CreateLights();

	// init to the wireframe model
	texture = Wireframe;
}

/*******************************************************************************
* Author: Anthony Morast, Samuel Carroll
* \brief Creates the light sources for our simulation
*
* Creates the light sources in the simulation. There are two primary light 
* sources used. Ambient light throught the entire scene and the sun. The sun
* emits primarily yellow light but some blue is included so Neptune and Uranus
* aren't green. 
*
* \params none
* \return none
*******************************************************************************/
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
}
