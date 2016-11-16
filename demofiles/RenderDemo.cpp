/*
    ***** RenderDemo.cpp *****

Rotate Utah teapot, illustrating wireframe display, shaded graphics, and texture mapping.
Ref: Angel, Interactive Computer Graphics, 2007.

Usage:			RenderDemo texture.bmp

Key controls:	Space toggles animation
				+/- speeds up/slows down animation
				l - toggle lighting/color mode
				s - toggle flat/smooth shading
				t - texture mapping
				T - texture mapping plus lighting
				w - toggle wireframe/polygon
				Esc - exit

Modifications (JMW):
Fall 2016 - Several minor mods for CSC433/533 demo.
*/

// various declarations

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <GL/glut.h>

typedef unsigned char byte;

bool LoadBmpFile( const char* filename, int &nrows, int &ncols, byte* &image );

// global vars (for idle callback)
float angleinc = 0.5;
GLfloat theta[] = { 0.0, 0.0, 0.0 };
GLint axis = 2;

// callback functions

// idle callback
void spinObject()
{
    // spin cube about selected axis
    theta[axis] += angleinc;
    if ( theta[axis] > 360.0 ) theta[axis] -= 360.0;
    else if ( theta[axis] < 0 ) theta[axis] += 360.0;
    glutPostRedisplay();
}

// display callback
void display()
{
    // clear frame buffer and depth buffer
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // rotate teapot
    glLoadIdentity();
    glRotatef( theta[0], 1.0, 0.0, 0.0 );
    glRotatef( theta[1], 0.0, 1.0, 0.0 );
    glRotatef( theta[2], 0.0, 0.0, 1.0 );

    // draw teapot and swap buffers
    glFrontFace( GL_CW );    // teapot requires clockwise vertex ordering
    glutSolidTeapot( 1.0 );
    glutSwapBuffers();
}

// reshape callback
void reshape( int w, int h )
{
    glViewport( 0, 0, w, h );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    if ( w <= h )
        glOrtho( -2.0, 2.0, -2.0 * ( GLfloat ) h / ( GLfloat ) w,
                 2.0 * ( GLfloat ) h / ( GLfloat ) w, -10.0, 10.0 );
    else
        glOrtho( -2.0 * ( GLfloat ) w / ( GLfloat ) h,
                 2.0 * ( GLfloat ) w / ( GLfloat ) h, -2.0, 2.0, -10.0, 10.0 );
    glMatrixMode( GL_MODELVIEW );
}

// keypress handler
void key( unsigned char k, int x, int y )
{
    static bool spin = true, light = true, shade = false, wire = false;
    switch ( k )
    {
	    case ' ':
		    ( spin = !spin ) ? glutIdleFunc( spinObject ) : glutIdleFunc( NULL );
			break;

        case '+': angleinc += 0.1; break;
        case '-': angleinc -= 0.1; break;

        case 'l':
		    ( light = !light ) ? glEnable( GL_LIGHTING ) : glDisable( GL_LIGHTING );
            glDisable( GL_TEXTURE_2D );
			break;

        case 't': glDisable( GL_LIGHTING ); glEnable( GL_TEXTURE_2D );  break;
        case 'T': glEnable( GL_LIGHTING );  glEnable( GL_TEXTURE_2D );  break;

        case 's':
		    ( shade = !shade ) ? glShadeModel( GL_FLAT ) : glShadeModel( GL_SMOOTH );
			break;

		case 'w':
		    ( wire = !wire ) ? glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ) : glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
			break;

        case 'x': axis = 0; break;
        case 'y': axis = 1; break;
        case 'z': axis = 2; break;

        case  27: exit( 0 ); break;
    }
    glutPostRedisplay();
}

// popup menu handler
void MainMenuHandler( int item )
{
    switch ( item )
    {
        case 1: glutIdleFunc( spinObject ); break;
        case 2: glutIdleFunc( NULL ); break;
		
        case 3: angleinc += 0.1; break;
        case 4: angleinc -= 0.1; break;
        
		case 5: axis = 0; break;
        case 6: axis = 1; break;
        case 7: axis = 2; break;

        case 8:  glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ); glDisable( GL_LIGHTING ); glDisable( GL_TEXTURE_2D ); break;
        case 9:  glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ); glEnable( GL_LIGHTING ); glShadeModel( GL_FLAT ); glDisable( GL_TEXTURE_2D ); break;
        case 10: glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ); glEnable( GL_LIGHTING ); glShadeModel( GL_SMOOTH ); glDisable( GL_TEXTURE_2D ); break;
        case 11: glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ); glEnable( GL_LIGHTING ); glEnable( GL_TEXTURE_2D ); break;

        case 12: exit( 0 ); break;
    }
    glutPostRedisplay();
}

// create the right mouse button menu
void CreateMenus()
{
    // main menu
    glutCreateMenu( MainMenuHandler );

    // add menu entries
    int value = 1;
    glutAddMenuEntry( "start spinning", value++ );
    glutAddMenuEntry( "stop spinning", value++ );
    glutAddMenuEntry( "increase speed (+)", value++ );
    glutAddMenuEntry( "decrease speed (-)", value++ );
    glutAddMenuEntry( "x-axis spin", value++ );
    glutAddMenuEntry( "y-axis spin", value++ );
    glutAddMenuEntry( "z-axis spin", value++ );

    glutAddMenuEntry( "wireframe", value++ );
    glutAddMenuEntry( "flat shading", value++ );
    glutAddMenuEntry( "smooth shading", value++ );
    glutAddMenuEntry( "texture mapping", value++ );
    glutAddMenuEntry( "exit (Esc)", value++ );

    glutAttachMenu( GLUT_RIGHT_BUTTON );
}

// set up light and material properties
void initLightModel()
{
    GLfloat mat_specular[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat mat_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat mat_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat mat_shininess = { 100.0 };

    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient );
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );
    glMaterialf( GL_FRONT, GL_SHININESS, mat_shininess );

    GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 10.0, 10.0, 10.0, 1.0 };

    glLightfv( GL_LIGHT0, GL_POSITION, light_position );
    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse );
    glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular );

    glShadeModel( GL_SMOOTH );
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );

    glEnable( GL_DEPTH_TEST );
    glColor3f ( 0.5, 0.5, 0.5 );
    glEnable( GL_NORMALIZE );    // automatic normalization of normals
    glEnable( GL_CULL_FACE );    // eliminate backfacing polygons
    glCullFace( GL_BACK );
}

// read texture map from BMP file
// Ref: Buss, 3D Computer Graphics, 2003.
int loadTextureFromFile( char *filename )
{
    int nrows, ncols;
    byte* image;
    if ( !LoadBmpFile( filename, nrows, ncols, image ) )
    {
        std::cerr << "Error: unable to load " << filename << std::endl;
        return -1;
    }

    // Pixel alignment: each row is word aligned (aligned to a 4 byte boundary)
    // Therefore, no need to call glPixelStore( GL_UNPACK_ALIGNMENT, ... );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, ncols, nrows, GL_RGB, GL_UNSIGNED_BYTE, image );
    
    delete [] image;

    return 0;
}

// set up texture map
void initTextureMap( char *filename )
{
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_TEXTURE_2D );
    if ( loadTextureFromFile( filename ) == 0 )
        glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
}

// build a checkerboard texture pattern
void makeTexture( GLubyte image[64][64][3] )
{
    for ( int i = 0; i < 64; i++ )
    {
        for ( int j = 0; j < 64; j++ )
        {
            int c = ( ( ( i & 0x8 ) == 0 ) ^ ( ( j & 0x8 ) ) == 0 ) * 255;
            image[i][j][0] = ( GLubyte ) c;
            image[i][j][1] = ( GLubyte ) c;
            image[i][j][2] = ( GLubyte ) c;
        }
    }
}

// main function
int main( int argc, char **argv )
{
    char *filename = argc > 1 ? strdup( argv[1] ) : NULL;

    // need both double buffering and a depth buffer
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize( 500, 500 );
    glutCreateWindow( "teapot texture" );

    glutReshapeFunc( reshape );
    glutDisplayFunc( display );
    glutIdleFunc( spinObject );
    glutKeyboardFunc( key );

    // create menus
    CreateMenus();

	if ( filename )
	{
        initTextureMap( filename );
	}
	else
	{
		GLubyte image[64][64][3];
		makeTexture( image );
		glTexImage2D( GL_TEXTURE_2D, 0, 3, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, image );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	}
	
    initLightModel();

    glClearColor( 1.0, 1.0, 1.0, 1.0 );

    glutMainLoop();
}
