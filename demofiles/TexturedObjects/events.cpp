/*
    ***** TexturedObjects *****

Rotating cube/sphere/teapot, illustrating texture maps in OpenGL.

Author: John M. Weiss, Ph.D.
Class:  CSC433/533 Computer Graphics
Date:   Fall 2016
Ref:    Angel, OpenGL Primer, 2008

*/

#include "textures.h"

// idle callback, spins cube about selected axis
void idle()
{
    theta[axis] += speed;     // or 0.1
    if ( theta[axis] > 360.0 ) theta[axis] -= 360.0;
    glutPostRedisplay();
}

// keyboard callback (press spacebar to start/stop animation)
void key( unsigned char k, int x, int y )
{
    static bool anim = true;

    switch ( k )
    {
        // select object type
        case '1': case '2': case '3': objtype = k; break;

        // toggle animation (spacebar)
        case ' ': ( anim = !anim ) ? glutIdleFunc( idle ) : glutIdleFunc( NULL ); break;
        
        // animation speed
        case '+': case '=': speed *= 2; break;
        case '-': speed /= 2; if ( speed <= 0 ) speed = 0.1; break;

        // select axis of rotation
        case 'x': case 'X': axis = 0; break;
        case 'y': case 'Y': axis = 1; break;
        case 'z': case 'Z': axis = 2; break;

        // exit on Escape key
        case  27: exit( 0 ); break;
    }
}
