/*******************************************************************************
* Authors: Anthony Morast, Samuel Carroll
* Date: 11/18/2016
* 
* CSC - 533 Computer Graphics, Dr. John Weiss
* Program 3 - Solar System Simulation
*
* Description:
*	Callbackactions.cpp is a class used to handle callback action from OpenGL
* callback functions. This class was implemented to minimize code in the opengl.cpp
* file. Found in this file are functions called from opengl.cpp when we need to 
* perform any of the actions from user input.
*
*******************************************************************************/
#ifndef GLOBAL_H
#define GLOBAL_H
#include "global.h"
#endif

// External globals from global.h
extern Texture texture;
extern float CamZ;
extern float CamY;
extern float CamX;
extern float IncrementMult;
extern float PreviousMult;
extern bool SingleStep;
extern bool Paused;
extern float RotateX;
extern float RotateY;
extern float RotateZ;
extern bool LightsEnabled;

/*******************************************************************************
* Author: Anthony Morast, Samuel Carroll
* \brief Toggles single step mode 
*
* \params none
* \return none
*******************************************************************************/
void CallbackAction::ToggleSingleStep()
{
	if ( !Paused )
	{
		SingleStep = !SingleStep;
		if ( SingleStep )
			PreviousMult = IncrementMult;
		else
			IncrementMult = PreviousMult;
	}
}

/*******************************************************************************
* Author: Anthony Morast, Samuel Carroll
* \brief Toggles pause/resume
*
* \params none
* \return none
*******************************************************************************/
void CallbackAction::TogglePause()
{
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
}

/*******************************************************************************
* Author: Anthony Morast, Samuel Carroll
* \brief Toggles flat/smooth shading
*
* \params none
* \return none
*******************************************************************************/
void CallbackAction::ToggleShading()
{
	if ( texture == Flat )
		texture = Smooth;
	else 
		texture = Flat;
}

/*******************************************************************************
* Author: Anthony Morast, Samuel Carroll
* \brief Toggles wireframe display of the celestial objects
*
* \params none
* \return none
*******************************************************************************/
void CallbackAction::ToggleWireframe()
{
	texture = Wireframe;
}

/*******************************************************************************
* Author: Anthony Morast, Samuel Carroll
* \brief Toggles texture mapping of the images associated with the objects
*
* \params none
* \return none
*******************************************************************************/
void CallbackAction::ToggleTextureMapping()
{
	texture = TextureMap;
	glEnable( GL_TEXTURE_2D );
}

/*******************************************************************************
* Author: Anthony Morast, Samuel Carroll
* \brief Turns on or off OpenGL lighting
*
* \params none
* \return none
*******************************************************************************/
void CallbackAction::ToggleLights()
{
	LightsEnabled = !LightsEnabled;
	if( LightsEnabled )
		glEnable( GL_LIGHTING );
	else 
		glDisable( GL_LIGHTING );	
}

/*******************************************************************************
* Author: Anthony Morast, Samuel Carroll
* \brief Increases or decreases animation speed
*
* \params increase - true to increase the speed, false to decrease
* \return none
*******************************************************************************/
void CallbackAction::AnimationSpeed( bool increase )
{
	if( increase )
	{
		IncrementMult = IncrementMult == 0 ? .25 : 
						IncrementMult * 2;
		if ( Paused || SingleStep )
		{
			PreviousMult = PreviousMult == 0 ? .25 : 
						   PreviousMult * 2;
		}
	}
	else 
	{
		IncrementMult /= 2.0;
		if( Paused || SingleStep )
			PreviousMult /= 2;
	}
		
}

/*******************************************************************************
* Author: Anthony Morast, Samuel Carroll
* \brief Zooms in or out
*
* Zooms in or out on the simulation depending on user inout.
*
* \params zoomIn - true if zooming in, false if out
* \return none
*******************************************************************************/
void CallbackAction::Zoom( bool zoomIn )
{
	if( zoomIn )
		CamZ += 5;
	else 
		CamZ -= 5;
}

/*******************************************************************************
* Author: Anthony Morast, Samuel Carroll
* \brief Rotates the scene based on user input
*
* Rotates the scene based on user input. If the user presses a capital X, Y, or Z
* the rotation is positive (right, up, clockwise) along the x, y, z axes respectively. 
* Thus, 'up' will be true.
*
* Similarly if the user presses a lower case x, y, z the rotation is negative
* (left, down, counterclockwise) along the x, y, z axes respectively. 
*
* \params axis - axis of rotatin 1 = x, 2 = y, 3 = z
		  up - true for positve rotation, false for negative
* \return none
*******************************************************************************/
void CallbackAction::Rotate( int axis, bool up )
{
	// 1 - x
	// 2 - y
	// 3 - z
	switch( axis )
	{
		case 1:
			RotateX = up ? RotateX - 1.0 : RotateX + 1.0;
			break;
		case 2:
			RotateY = up ? RotateY + 1.0 : RotateY - 1.0;
			break;
		case 3:
			RotateZ = up ? RotateZ - 1.0 : RotateZ + 1.0;
			break;		
	}
}

/*******************************************************************************
* Author: Anthony Morast, Samuel Carroll
* \brief Pans the camera depending on the button pressed
*
* Performs the panning action when a user presses up, down, left, or right keys.. 
*
* \params key - the key pressed
* \return none
*******************************************************************************/
void CallbackAction::Pan( int key )
{
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
	}
}

/*******************************************************************************
* Author: Anthony Morast, Samuel Carroll
* \brief Popup menu action handlers 
*
* The following four functions are used to determine which menu item is selected
* when the user selects and action from any of our sub-menues. The functions 
* probably don't need individual headers as the are easy to follow and just call
* the functions defined above. 
*
* \params item - the menu item pressed
* \return none
*******************************************************************************/
void CallbackAction::PanClick( int item )
{
	switch( item )
	{
		case 1:
			Pan( GLUT_KEY_LEFT );
			break;
		case 2:
			Pan( GLUT_KEY_RIGHT );
			break;
		case 3:
			Pan( GLUT_KEY_UP );
			break;
		case 4:
			Pan( GLUT_KEY_DOWN );
			break;
		case 5:
			Zoom( true );
			break;
		case 6:
			Zoom( false );
			break;
	}
}
void CallbackAction::ObjectViewClick( int item )
{
	switch( item )
	{
		case 1:
			ToggleWireframe();
			break;
		case 2:
			ToggleShading();
			break;
		case 3:
			ToggleTextureMapping();
			break;
	}
}
void CallbackAction::RotateClick( int item )
{
	switch( item )
	{
		case 1:
			Rotate( 1, true );
			break;
		case 2:
			Rotate( 1, false );
			break;
		case 3:
			Rotate( 2, true );
			break;
		case 4:
			Rotate( 2, false );
			break;
		case 5:
			Rotate( 3, true );
			break;
		case 6:
			Rotate( 3, false );
			break;
	}
}
void CallbackAction::AnimationClick( int item )
{
	switch( item )
	{
		case 1:
			ToggleLights();
			break;
		case 2:
			ToggleSingleStep();
			break;
		case 4:
			TogglePause();
			break;
		case 5:
			AnimationSpeed( true );
			break;
		case 6:
			AnimationSpeed( false );
			break;
	}
}
