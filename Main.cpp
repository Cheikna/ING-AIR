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


static const char * g_pop_out_label = "Pop Out";
static const char * g_pop_in_label = "Pop In";
static float g_pop_button_lbrt[4]; // left, bottom, right, top
static float g_position_button_lbrt[4]; // left, bottom, right, top

static int	coord_in_rect(float x, float y, float * bounds_lbrt) { return ((x >= bounds_lbrt[0]) && (x < bounds_lbrt[2]) && (y < bounds_lbrt[3]) && (y >= bounds_lbrt[1])); }


void	draw(XPLMWindowID in_window_id, void * in_refcon)
{
	char scratch_buffer[150];
	float col_white[] = { 1.0, 1.0, 1.0 };

	XPLMSetGraphicsState(
		0 /* no fog */,
		0 /* 0 texture units */,
		0 /* no lighting */,
		0 /* no alpha testing */,
		1 /* do alpha blend */,
		1 /* do depth testing */,
		0 /* no depth writing */
	);


	// We draw our rudimentary button boxes based on the height of the button text
	int char_height;
	XPLMGetFontDimensions(xplmFont_Proportional, NULL, &char_height, NULL);

	// We'll change the text of the pop-in/pop-out button based on our current state
	int is_popped_out = XPLMWindowIsPoppedOut(in_window_id);
	const char * pop_label = is_popped_out ? g_pop_in_label : g_pop_out_label;

	int l, t, r, b;
	XPLMGetWindowGeometry(in_window_id, &l, &t, &r, &b);

	// Draw our buttons
	{
		// Position the pop-in/pop-out button in the upper left of the window (sized to fit the
		g_pop_button_lbrt[0] = l + 10;
		g_pop_button_lbrt[3] = t - 15;
		g_pop_button_lbrt[2] = g_pop_button_lbrt[0] + XPLMMeasureString(xplmFont_Proportional, pop_label, strlen(pop_label)); // *just* wide enough to fit the button text
		g_pop_button_lbrt[1] = g_pop_button_lbrt[3] - (1.25f * char_height); // a bit taller than the button text

																			 // Position the "move to lower left" button just to the right of the pop-in/pop-out button
		const char * position_btn_text = "Move to Lower Left";
		g_position_button_lbrt[0] = g_pop_button_lbrt[2] + 30;
		g_position_button_lbrt[1] = g_pop_button_lbrt[1];
		g_position_button_lbrt[2] = g_position_button_lbrt[0] + XPLMMeasureString(xplmFont_Proportional, position_btn_text, strlen(position_btn_text));
		g_position_button_lbrt[3] = g_pop_button_lbrt[3];

		// Draw the boxes around our rudimentary buttons
		float green[] = { 0.0, 1.0, 0.0, 1.0 };
		glColor4fv(green);
		glBegin(GL_LINE_LOOP);
		{
			glVertex2i(g_pop_button_lbrt[0], g_pop_button_lbrt[3]);
			glVertex2i(g_pop_button_lbrt[2], g_pop_button_lbrt[3]);
			glVertex2i(g_pop_button_lbrt[2], g_pop_button_lbrt[1]);
			glVertex2i(g_pop_button_lbrt[0], g_pop_button_lbrt[1]);
		}
		glEnd();
		glBegin(GL_LINE_LOOP);
		{
			glVertex2i(g_position_button_lbrt[0], g_position_button_lbrt[3]);
			glVertex2i(g_position_button_lbrt[2], g_position_button_lbrt[3]);
			glVertex2i(g_position_button_lbrt[2], g_position_button_lbrt[1]);
			glVertex2i(g_position_button_lbrt[0], g_position_button_lbrt[1]);
		}
		glEnd();

		// Draw the button text (pop in/pop out)
		XPLMDrawString(col_white, g_pop_button_lbrt[0], g_pop_button_lbrt[1] + 4, (char *)pop_label, NULL, xplmFont_Proportional);

		// Draw the button text (reposition)
		XPLMDrawString(col_white, g_position_button_lbrt[0], g_position_button_lbrt[1] + 4, (char *)position_btn_text, NULL, xplmFont_Proportional);
	}

	// Draw a bunch of informative text
	{
		// Set the y position for the first bunch of text we'll draw to a little below the buttons
		int y = g_pop_button_lbrt[1] - 2 * char_height;

		// Display the total global desktop bounds
		{
			int global_desktop_lbrt[4];
			XPLMGetScreenBoundsGlobal(&global_desktop_lbrt[0], &global_desktop_lbrt[3], &global_desktop_lbrt[2], &global_desktop_lbrt[1]);
			sprintf(scratch_buffer, "Global desktop bounds: (%d, %d) to (%d, %d)", global_desktop_lbrt[0], global_desktop_lbrt[1], global_desktop_lbrt[2], global_desktop_lbrt[3]);
			XPLMDrawString(col_white, l, y, scratch_buffer, NULL, xplmFont_Proportional);
			y -= 1.5 * char_height;
		}

		// Display our bounds
		if (XPLMWindowIsPoppedOut(in_window_id)) // we are in our own first-class window, rather than "floating" within X-Plane's own window
		{
			int window_os_bounds[4];
			XPLMGetWindowGeometryOS(in_window_id, &window_os_bounds[0], &window_os_bounds[3], &window_os_bounds[2], &window_os_bounds[1]);
			sprintf(scratch_buffer, "OS Bounds: (%d, %d) to (%d, %d)", window_os_bounds[0], window_os_bounds[1], window_os_bounds[2], window_os_bounds[3]);
			XPLMDrawString(col_white, l, y, scratch_buffer, NULL, xplmFont_Proportional);
			y -= 1.5 * char_height;
		}
		else
		{
			int global_bounds[4];
			XPLMGetWindowGeometry(in_window_id, &global_bounds[0], &global_bounds[3], &global_bounds[2], &global_bounds[1]);
			sprintf(scratch_buffer, "Window bounds: %d %d %d %d", global_bounds[0], global_bounds[1], global_bounds[2], global_bounds[3]);
			XPLMDrawString(col_white, l, y, scratch_buffer, NULL, xplmFont_Proportional);
			y -= 1.5 * char_height;
		}

		// Display whether we're in front of our our layer
		{
			sprintf(scratch_buffer, "In front? %s", XPLMIsWindowInFront(in_window_id) ? "Y" : "N");
			XPLMDrawString(col_white, l, y, scratch_buffer, NULL, xplmFont_Proportional);
			y -= 1.5 * char_height;
		}

		// Display the mouse's position info text
		{
			int mouse_global_x, mouse_global_y;
			XPLMGetMouseLocationGlobal(&mouse_global_x, &mouse_global_y);
			sprintf(scratch_buffer, "Draw mouse (global): %d %d\n", mouse_global_x, mouse_global_y);
			XPLMDrawString(col_white, l, y, scratch_buffer, NULL, xplmFont_Proportional);
			y -= 1.5 * char_height;
		}
	}

}

int	handle_mouse(XPLMWindowID in_window_id, int x, int y, XPLMMouseStatus is_down, void * in_refcon)
{
	if (is_down == xplm_MouseDown)
	{
		const int is_popped_out = XPLMWindowIsPoppedOut(in_window_id);
		if (!XPLMIsWindowInFront(in_window_id))
		{
			XPLMBringWindowToFront(in_window_id);
		}
		else if (coord_in_rect(x, y, g_pop_button_lbrt)) // user clicked the pop-in/pop-out button
		{
			XPLMSetWindowPositioningMode(in_window_id, is_popped_out ? xplm_WindowPositionFree : xplm_WindowPopOut, 0);
		}
		else if (coord_in_rect(x, y, g_position_button_lbrt)) // user clicked the "move to lower left" button
		{
			// If we're popped out, and the user hits the "move to lower left" button,
			// we need to move them to the lower left of their OS's desktop space (units are pixels).
			// On the other hand, if we're a floating window inside of X-Plane, we need
			// to move to the lower left of the X-Plane global desktop (units are boxels).
			void(*get_geometry_fn)(XPLMWindowID, int *, int *, int *, int *) = is_popped_out ? &XPLMGetWindowGeometryOS : &XPLMGetWindowGeometry;
			int lbrt_current[4];
			get_geometry_fn(in_window_id, &lbrt_current[0], &lbrt_current[3], &lbrt_current[2], &lbrt_current[1]);

			int h = lbrt_current[3] - lbrt_current[1];
			int w = lbrt_current[2] - lbrt_current[0];
			void(*set_geometry_fn)(XPLMWindowID, int, int, int, int) = is_popped_out ? &XPLMSetWindowGeometryOS : &XPLMSetWindowGeometry;

			// Remember, the main monitor's origin is *not* guaranteed to be (0, 0), so we need to query for it in order to move the window to its lower left
			int bounds[4] = { 0 }; // left, bottom, right, top
			if (is_popped_out)
			{
				XPLMGetScreenBoundsGlobal(&bounds[0], &bounds[3], &bounds[2], &bounds[1]);
			}
			else
			{
				XPLMGetAllMonitorBoundsOS(receive_main_monitor_bounds, bounds);
			}

			set_geometry_fn(in_window_id, bounds[0], bounds[1] + h, bounds[0] + w, bounds[1]);
		}
	}
	return 1;
}

void receive_main_monitor_bounds(int inMonitorIndex, int inLeftBx, int inTopBx, int inRightBx, int inBottomBx, void * refcon)
{
	int * main_monitor_bounds = (int *)refcon;
	if (inMonitorIndex == 0) // the main monitor
	{
		main_monitor_bounds[0] = inLeftBx;
		main_monitor_bounds[1] = inBottomBx;
		main_monitor_bounds[2] = inRightBx;
		main_monitor_bounds[3] = inTopBx;
	}
}

