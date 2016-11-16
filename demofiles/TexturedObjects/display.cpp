/*
    ***** TexturedObjects *****

Rotating cube/sphere/teapot, illustrating texture maps in OpenGL.

Author: John M. Weiss, Ph.D.
Class:  CSC433/533 Computer Graphics
Date:   Fall 2016
Ref:    Angel, OpenGL Primer, 2008

*/

#include "textures.h"

// display callback
void display( void )
{
    // clear frame buffer and z buffer
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // rotate cube and redraw
    glLoadIdentity();
    glRotatef( theta[0], 1.0, 0.0, 0.0 );
    glRotatef( theta[1], 0.0, 1.0, 0.0 );
    glRotatef( theta[2], 0.0, 0.0, 1.0 );
    switch ( objtype )
    {
        case '1': colorcube(); break;
        case '2': gluSphere( sphere, 1, 64, 64 ); break;
        case '3': glutSolidTeapot( 1.0 ); break;
    }

    // swap buffers (implicitly calls glFlush)
    glutSwapBuffers();
}

// window resizing callback
void reshape( int w, int h )
{
    glViewport( 0, 0, w, h );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    if ( w <= h )
        glOrtho( -2.0, 2.0, -2.0 * ( GLfloat ) h / ( GLfloat ) w, 2.0 * ( GLfloat ) h / ( GLfloat ) w, -10.0, 10.0 );
    else
        glOrtho( -2.0 * ( GLfloat ) w / ( GLfloat ) h, 2.0 * ( GLfloat ) w / ( GLfloat ) h, -2.0, 2.0, -10.0, 10.0 );
    glMatrixMode( GL_MODELVIEW );
}
