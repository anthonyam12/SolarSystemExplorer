/*
    ***** TexturedObjects *****

Rotating cube/sphere/teapot, illustrating texture maps in OpenGL.

Author: John M. Weiss, Ph.D.
Class:  CSC433/533 Computer Graphics
Date:   Fall 2016
Ref:    Angel, OpenGL Primer, 2008

*/

#include "textures.h"

// draw a polygon from the list of vertices, mapping texture coordinates
void polygon( int a, int b, int c , int d )
{
    // vertices of cube (polygon faces)
    static GLfloat vertices[][3] = {{ -1.0, -1.0, -1.0}, {1.0, -1.0, -1.0},
        {1.0, 1.0, -1.0}, { -1.0, 1.0, -1.0}, { -1.0, -1.0, 1.0},
        {1.0, -1.0, 1.0}, {1.0, 1.0, 1.0}, { -1.0, 1.0, 1.0}
    };

    // associated colors
    static GLfloat colors[][4] = {{0.0, 0.0, 0.0, 1.0}, {1.0, 0.0, 0.0, 1.0},
        {1.0, 1.0, 0.0, 1.0}, {0.0, 1.0, 0.0, 1.0}, {0.0, 0.0, 1.0, 1.0},
        {1.0, 0.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0}, {0.0, 1.0, 1.0, 1.0}
    };

    // draw polygon from the list of vertices, mapping texture coordinates and assigning colors
    glBegin( GL_POLYGON );
        glColor4fv( colors[a] );
        glTexCoord2f( 0.0, 0.0 );
        glVertex3fv( vertices[a] );
        glColor4fv( colors[b] );
        glTexCoord2f( 0.0, 1.0 );
        glVertex3fv( vertices[b] );
        glColor4fv( colors[c] );
        glTexCoord2f( 1.0, 1.0 );
        glVertex3fv( vertices[c] );
        glColor4fv( colors[d] );
        glTexCoord2f( 1.0, 0.0 );
        glVertex3fv( vertices[d] );
    glEnd();
}

// build cube from polygonal faces
void colorcube( void )
{
    polygon( 0, 3, 2, 1 );
    polygon( 2, 3, 7, 6 );
    polygon( 3, 0, 4, 7 );
    polygon( 1, 2, 6, 5 );
    polygon( 4, 5, 6, 7 );
    polygon( 5, 4, 0, 1 );
    glColor3f( 1.0, 1.0, 1.0);
}
