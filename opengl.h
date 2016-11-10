#include <GL/freeglut.h>
#include "global.h"
#include "inputhandler.h"

/*******************************************************************************
 * 									Globals 								   *
 ******************************************************************************/


/*******************************************************************************
 * 								Function Definitions 						   *
 ******************************************************************************/
// OpenGL Callbacks
void keyboard( unsigned char key, int x, int y );
void display( void );
void reshape( int w, int h );

// Misc.
void init();
int GetScreenWidth();
int GetScreenHeight();
