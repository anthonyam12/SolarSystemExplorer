#include <GL/freeglut.h>
#include "global.h"

/*******************************************************************************
 * 									Globals 								   *
 ******************************************************************************/


/*******************************************************************************
 * 								Function Definitions 						   *
 ******************************************************************************/
// OpenGL Callbacks
void keyboard( unsigned char key, int x, int y );
void display( void );
void reshape( int x, int y );

// Misc.
void init();
int GetScreenWidth();
int GetScreenHeight();
