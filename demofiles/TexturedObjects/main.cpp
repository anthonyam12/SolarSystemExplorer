/*
    ***** TexturedObjects *****

Rotating cube/sphere/teapot, illustrating texture maps in OpenGL.

Author: John M. Weiss, Ph.D.
Class:  CSC433/533 Computer Graphics
Date:   Fall 2016
Ref:    Angel, OpenGL Primer, 2008

*/

#include "textures.h"

// global vars
GLfloat theta[] = {0.0, 0.0, 0.0};
GLint axis = 2;
float speed = 0.5;
int objtype = '1';
GLUquadricObj* sphere;

// main function
int main( int argc, char **argv )
{
    // GLUT inits: need both double buffering and z buffer
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize( 500, 500 );
    glutCreateWindow( "textured objects" );

    // callbacks
    glutReshapeFunc( reshape );
    glutDisplayFunc( display );
    glutKeyboardFunc( key );
    glutIdleFunc( idle );

    glClearColor( 1.0, 1.0, 1.0, 1.0 );

    // texture mapping
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_TEXTURE_2D );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );     // or GL_CLAMP
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	if ( argc == 1 )
        makeTexture();
    else if ( loadTexture( argv[1] ) )
        return -1;

    // generate GLU quadric sphere with surface normals and texture coordinates
    sphere = gluNewQuadric( );
    gluQuadricDrawStyle( sphere, GLU_FILL );
    gluQuadricNormals( sphere, GLU_SMOOTH );
    gluQuadricTexture( sphere, GL_TRUE );

    // event loop
    glutMainLoop();
}
