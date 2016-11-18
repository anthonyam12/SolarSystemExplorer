#include "opengl.h"

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
	// w/p - wireframe
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
			cba.ToggleSingleStep();
			break;
		case f:
			cba.ToggleShading();
			break;
		case w:
		case p:
			cba.ToggleWireframe();
			break;
		case t:
			cba.ToggleTextureMapping();
			break;
		case Minus:
			cba.Zoom( false );
			break;
		case Plus:
			cba.Zoom( true );
			break;
		case r:
			cba.TogglePause();
			break;
		case Space:
			break;
		case A:
			cba.AnimationSpeed( true );
			break;
		case a:
			cba.AnimationSpeed( false );
			break;
		case X:
			cba.Rotate( 1, true );
			break;
		case xx:
			cba.Rotate( 1, false );
			break;
		case Y:
			cba.Rotate( 2, true );
			break;
		case yy:
			cba.Rotate( 2, false );
			break;
		case Z:
			cba.Rotate( 3, true );
			break;
		case z:
			cba.Rotate( 3, false );
			break;
		case l:
			cba.ToggleLights();
			break;
		case Esc:
			exit( 0 );
			break;
	}

	// funky logic to be able to change the simulation attributes
	// without taking a 'step' 
	if ( ( SingleStep && key != Space ) || Paused )
		// need this to be 0 to prevent the simulation from moving when paused
		// or in single step mode if we press any button besides space. 
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
*		mouse left click - rotate around x and y
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
		cba.Zoom( true );
	if( button == 4 )
		cba.Zoom( false );
	if( button == GLUT_LEFT_BUTTON )
	{ 
		StartX = x; StartY = y; 
	}
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
	cba.Pan( key );
	glutPostRedisplay();
}

/*******************************************************************************
* Author: Anthony Morast, Samuel Carrol
* /brief Callback handlers for the mouse menus
*
* These five methods (mainmenu, animationMenu, rotateMenu, panMenu, and 
* objectViewMenu) are the callbacks for the OpenGL pop-up menu. Each method makces
* a call into the CallbackAction class where we actually determine which actions
* to perform and performs them. The exception being the mainmenu handler which 
* can only perform one action (exiting).
*
* params
*		item - the menu item clicked
* returns none
*******************************************************************************/
void animationMenu( int item )
{
	cba.AnimationClick( item );
	if ( item == 3 && SingleStep )
		IncrementMult = PreviousMult;
	else if ( SingleStep  || Paused )
		IncrementMult = 0.0;
}
void rotateMenu( int item )
{
	cba.RotateClick( item );
	if ( SingleStep  || Paused )
		IncrementMult = 0.0;
}
void panMenu( int item )
{
	cba.PanClick( item );
	if ( SingleStep  || Paused )
		IncrementMult = 0.0;
}
void objectViewMenu( int item )
{
	cba.ObjectViewClick( item );
	if ( SingleStep  || Paused )
		IncrementMult = 0.0;
}
void mainmenu( int item )
{
	if ( item == 1 )
		exit(0);
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
			break;
	}

	// set the position of the scene
    glTranslatef ( CamX, CamY, CamZ );

    // Rotate around the scene based on user input
    glRotatef( RotateX, 0.0, 1.0, 0.0 );
	glRotatef( RotateY, 1.0, 0.0, 0.0 );
	glRotatef( RotateZ, 0.0, 0.0, 1.0 );

	
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	glDisable( GL_TEXTURE_2D );
	glColor3f( 0.0, 1.0, 0.0 );
	for ( int i = 1; i < 9; i++ )
	{
		Planet &p = Planets[i];
		float baseDistance = (20.0*i)+(p.getDistance()/10.0);
		// draw rings
		glPushMatrix();
			GLUquadric *orbit = gluNewQuadric();
			gluQuadricOrientation( orbit, GLU_INSIDE );
			glRotatef( 90.0, 1, 0, 0 );
			gluCylinder( orbit,  baseDistance, baseDistance+.001, .0001, 80, 80 );	
		glPopMatrix();
	}
	if ( texture != Wireframe )
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	if ( texture == TextureMap )
		glEnable( GL_TEXTURE_2D );

	Planets[0].DrawSun();
	for (int i = 1; i < 9; i++)
	{
		Planet &p = Planets[i];
		p.Draw( i );
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
	gluPerspective( 60, aspectRatio, 1, 2000 ); 
	
    glMatrixMode( GL_MODELVIEW );
}

/*******************************************************************************
* Author: Anthony Morast, Samuel Carroll
* \brief Rotates the scene based on mouse movement
*
* A startx and starty postion are created when the user clicks the left
* mouse button. This method tracks that motion and rotates the solar system scene
* according the the mouse movement.
*
* \params x - current mouse x
* 		  y - current mouse y
* \return none
*******************************************************************************/
void mousedrag( int x, int y )
{
	float change = 1.0;
	if( x < StartX )
		RotateX += change;
	else if ( x > StartX )
		RotateX -= change;

	if( y < StartY )
		RotateY -= change;
	else if ( y > StartY )
		RotateY += change;

	StartX = x;
	StartY = y;
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
	glutMouseFunc( mouseclick );
	glutMotionFunc( mousedrag );
	
	// enable texture tpye attributes
	glEnable( GL_DEPTH_TEST );
    glEnable( GL_TEXTURE_2D );

	// setups some params for texture mapping
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

	// create the ambient light source and menus
	CreateLights();
	CreateMenus();

	// init to the wireframe model
	texture = Wireframe;
}

/*******************************************************************************
* Author: Anthony Morast, Samuel Carroll
* \brief Creates the light sources for our simulation
*
* Creates the light ambient ligh source in the simulation. 
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

/*******************************************************************************
* Author: Anthony Morast, Samuel Carroll
* \brief Creats the main menu and multiple submenus
*
* Creates the main menu mostly comprised of submenus. The submenus allow for 
* a division between different types of actions. 
*
* \params none
* \return none
*******************************************************************************/
void CreateMenus()
{
	int value = 1;
	int animateMenu = glutCreateMenu( animationMenu );
	glutAddMenuEntry( "Toggle Lights (l)", value++ );
	glutAddMenuEntry( "Toggle Single Step Mode (s)", value++ );
	glutAddMenuEntry( "Take Step (<space>)", value++ );
	glutAddMenuEntry( "Toggle Pause (r)", value++ );
	glutAddMenuEntry( "Increase Animation Speed (A)", value++ );
	glutAddMenuEntry( "Decrease Animation Speed (a)", value++ );
	
	value = 1;
	int rotatemenu = glutCreateMenu( rotateMenu );
	glutAddMenuEntry( "Rotate X+ (X)", value++ );
	glutAddMenuEntry( "Rotate X- (x)", value++ );
	glutAddMenuEntry( "Rotate Y+ (Y)", value++ );
	glutAddMenuEntry( "Rotate Y- (y)", value++ );
	glutAddMenuEntry( "Rotate Z+ (Z)", value++ );
	glutAddMenuEntry( "Rotate Z- (z)", value++ );

	value = 1;
	int panmenu = glutCreateMenu( panMenu );
	glutAddMenuEntry( "Pan Left (LeftArrow)", value++ );
	glutAddMenuEntry( "Pan Right (RightArrow)", value++ );
	glutAddMenuEntry( "Pan Up (UpArrow)", value++ );
	glutAddMenuEntry( "Pan Down (DownArrow)", value++ );
	glutAddMenuEntry( "Zoom In (+)", value++ );
	glutAddMenuEntry( "Zoom Out (-)", value++ );
	
	value = 1;
	int objectview = glutCreateMenu( objectViewMenu );
	glutAddMenuEntry( "Wireframe Objects (w)", value++ );
	glutAddMenuEntry( "Toggle Smooth/Flat Shading (f)", value++ );
	glutAddMenuEntry( "Texture Mapped (t)", value++ );
	
	value = 1;
	glutCreateMenu( mainmenu );
	glutAddSubMenu( "Simulation Options", animateMenu );
	glutAddSubMenu( "Rotate Scene", rotatemenu );
	glutAddSubMenu( "Panning/Zooming", panmenu );
	glutAddSubMenu( "Change Object View", objectview );
	glutAddMenuEntry( "Exit (esc)", value++ );
	
	glutAttachMenu( GLUT_RIGHT_BUTTON );
}
