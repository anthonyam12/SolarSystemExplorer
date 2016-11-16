/*
    ***** TexturedObjects *****

Rotating cube/sphere/teapot, illustrating texture maps in OpenGL.

Author: John M. Weiss, Ph.D.
Class:  CSC433/533 Computer Graphics
Date:   Fall 2016
Ref:    Angel, OpenGL Primer, 2008

*/

#include "textures.h"

typedef unsigned char byte;
bool LoadBmpFile( const char* filename, int &nrows, int &ncols, byte* &image );

// read texture map from BMP file
// Ref: Buss, 3D Computer Graphics, 2003.
int loadTexture( char *filename )
{
    int nrows, ncols;
    byte* image;
    if ( !LoadBmpFile( filename, nrows, ncols, image ) )
    {
        printf( "Error: unable to load %s\n", filename );
        return -1;
    }

    // building mipmaps is not essential, but can improve mapping
    // glTexImage2D( GL_TEXTURE_2D, 0, 3, ncols, nrows, 0, GL_RGB, GL_UNSIGNED_BYTE, image );
    gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, ncols, nrows, GL_RGB, GL_UNSIGNED_BYTE, image );
    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );

    delete [] image;
    return 0;
}

// build a checkerboard texture pattern
void makeTexture()
{
    GLubyte image[64][64][3];
    for ( int i = 0; i < 64; i++ )
    {
        for ( int j = 0; j < 64; j++ )
        {
            int c = ( ( ( i & 0x8 ) == 0 ) ^ ( ( j & 0x8 ) == 0 ) ) * 255;
            image[i][j][0] = ( GLubyte ) c;
            image[i][j][1] = ( GLubyte ) c;
            image[i][j][2] = ( GLubyte ) c;
        }
    }

    // building mipmaps is not essential, but can improve mapping
    glTexImage2D( GL_TEXTURE_2D, 0, 3, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, image );
    // gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, 64, 64, GL_RGB, GL_UNSIGNED_BYTE, image );
    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE  );
}
