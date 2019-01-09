#include "XPLMDisplay.h"
#include "XPLMGraphics.h"
#include "XPLMUtilities.h"
#include "XPLMDataAccess.h"
#include "XPLMUtilities.h"
#include <string.h>
#include <string>
#include <sstream>
#if IBM
	#include <windows.h>
#endif
#if LIN
	#include <GL/gl.h>
#elif __GNUC__
	#include <OpenGL/gl.h>
#else
	#include <GL/gl.h>
#endif

#ifndef XPLM300
	#error This is made to be compiled against the XPLM300 SDK
#endif

#include <direct.h>
#include <time.h>
#include <ctime>
#include <iostream>
#include <fstream>

int left, bottom, right, top;
void writeInLogFile();
double latitude, longitude;
//std::unordered_set<EventKeyboard::KeyCode> _pressedKeys;

// An opaque handle to the window we will create
static XPLMWindowID	g_window;
XPLMCreateWindow_t params;

// Callbacks we will register when we create our window
void				XPluginUpdate(XPLMWindowID in_window_id, void * in_refcon);
int					dummy_mouse_handler(XPLMWindowID in_window_id, int x, int y, int is_down, void * in_refcon) { return 0; }
XPLMCursorStatus	dummy_cursor_status_handler(XPLMWindowID in_window_id, int x, int y, void * in_refcon) { return xplm_CursorDefault; }
int					dummy_wheel_handler(XPLMWindowID in_window_id, int x, int y, int wheel, int clicks, void * in_refcon) { return 0; }
void				dummy_key_handler(XPLMWindowID in_window_id, char key, XPLMKeyFlags flags, char virtual_key, void * in_refcon, int losing_focus) { }
void				setWindowParams();
void writeAircraftPositionsInFile(std::string fileName);


//Cette méthode est appelée une seule fois, lors du lancement de X-Plane
PLUGIN_API int XPluginStart(
							char *		outName,
							char *		outSig,
							char *		outDesc)
{
	strcpy(outName, "ING-AIR");
	strcpy(outSig, "xpsdk.examples.ing_air");
	strcpy(outDesc, "Le plugin ING-AIR");

	//permet de démarer un exécutable qui doit être présent dans la racine du fichier ING-AIR
	//system("start TestExe.exe");
	setWindowParams();

	g_window = XPLMCreateWindowEx(&params);
	return g_window != NULL;

}

//Cette méthode est appelée plusieurs fois automatiquement
void	XPluginUpdate(XPLMWindowID in_window_id, void * in_refcon)
{
	latitude = XPLMGetDatad(XPLMFindDataRef("sim/flightmodel/position/latitude"));
	longitude = XPLMGetDatad(XPLMFindDataRef("sim/flightmodel/position/longitude"));
	std::string convertedLatitude = std::to_string(latitude);
	std::string convertedLongitude = std::to_string(longitude);
	//writeInLogFile()
	XPLMDebugString("========================================= TEST ========================================\n");
	std::stringstream positionSStream;
	positionSStream << "Position lue  ----- Latitude : " << convertedLatitude << " Longitude : " << convertedLongitude << "\n";
	std::string position = positionSStream.str();
	XPLMDebugString(position.c_str());
	writeAircraftPositionsInFile("AircraftPositions.txt");






	
	//writeInLogFile();
}


PLUGIN_API void	XPluginStop(void)
{
	// Since we created the window, we'll be good citizens and clean it up
	XPLMDestroyWindow(g_window);
	g_window = NULL;
}



PLUGIN_API void XPluginDisable(void) { }
PLUGIN_API int  XPluginEnable(void) { return 1; }
PLUGIN_API void XPluginReceiveMessage(XPLMPluginID inFrom, int inMsg, void * inParam) { }

void writeInLogFile()
{
	XPLMDebugString("\n\n\n");
	XPLMDebugString("Nouveau Test d'écriture dans le fichier Log.txt");
	XPLMDebugString("\n\n\n");

}

void writeAircraftPositionsInFile(std::string fileName)
{
	std::ofstream("AircraftsPosition.txt");
	std::ofstream outfile;
	double latitude = XPLMGetDatad(XPLMFindDataRef("sim/flightmodel/position/latitude"));
	double longitude = XPLMGetDatad(XPLMFindDataRef("sim/flightmodel/position/longitude"));
	std::string convertedLatitude = std::to_string(latitude);
	std::string convertedLongitude = std::to_string(longitude);
	XPLMDebugString("========================================= TEST ========================================\n");
	std::stringstream positionSStream;
	positionSStream << "Position lue  ----- Latitude : " << convertedLatitude << " Longitude : " << convertedLongitude << "\n";
	std::string position = positionSStream.str();
	outfile << position;
	//outfile.close();
}

/*void controlLogic()
{
	if (_pressedKeys.size())
	{
		// if else should be in order of priority
		if (_pressedKeys.find(EventKeyboard::KeyCode::KEY_UP_ARROW) != _pressedKeys.end())
		{
			if (_pressedKeys.find(EventKeyboard::KeyCode::KEY_RIGHT_ARROW) != _pressedKeys.end())
			{
				// UP + RIGHT
			}
			else if (_pressedKeys.find(EventKeyboard::KeyCode::KEY_LEFT_ARROW) != _pressedKeys.end())
			{
				// UP + LEFT
			}
			else
			{
				// only UP
			}
		}
		else if (...)
		{
		}
		...
	}
}*/

void setWindowParams()
{
	params.structSize = sizeof(params);
	params.visible = 1;
	params.drawWindowFunc = XPluginUpdate;
	params.handleMouseClickFunc = dummy_mouse_handler;
	params.handleMouseWheelFunc = dummy_wheel_handler;
	params.handleKeyFunc = dummy_key_handler;
	params.handleCursorFunc = dummy_cursor_status_handler;
	params.refcon = NULL;

	int hauteur, largeur;
	XPLMGetScreenSize(&largeur, &hauteur);

	left = largeur / 3;
	right = largeur / 3;
	top = hauteur / 3;
	bottom = hauteur / 3;

	params.left = left + 50;
	params.bottom = bottom + 150;
	params.right = params.left + 200;
	params.top = params.bottom + 200;
}

