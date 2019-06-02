#include "Model\Entity\Aircraft.h"

/*********************************************
*************** Attributes *******************
*********************************************/
int left, bottom, right, top;
Aircraft aircraft;


/********************************************
***************** Methods *******************
*********************************************/
// An opaque handle to the window we will create
static XPLMWindowID	g_window;

// Callbacks we will register when we create our window
void				update(XPLMWindowID in_window_id, void * in_refcon);
int					dummy_mouse_handler(XPLMWindowID in_window_id, int x, int y, int is_down, void * in_refcon) { return 0; }
XPLMCursorStatus	dummy_cursor_status_handler(XPLMWindowID in_window_id, int x, int y, void * in_refcon) { return xplm_CursorDefault; }
int					dummy_wheel_handler(XPLMWindowID in_window_id, int x, int y, int wheel, int clicks, void * in_refcon) { return 0; }
void				dummy_key_handler(XPLMWindowID in_window_id, char key, XPLMKeyFlags flags, char virtual_key, void * in_refcon, int losing_focus) { }


PLUGIN_API int XPluginStart(
	char *		outName,
	char *		outSig,
	char *		outDesc)
{
	strcpy(outName, "ING-AIR");
	strcpy(outSig, "xpsdk.examples.ing_air");
	strcpy(outDesc, "Le plugin ING-AIR");

	// Les éléments ci-dessous proviennent d'un plugin récupéré
	// Il semblerait que la suppression des lignes ci-dessous empêche le bon fonctionnement du plugin 
	// qui récupère les données dans le jeu
	XPLMCreateWindow_t params;
	params.structSize = sizeof(params);
	params.visible = 1;
	params.drawWindowFunc = update;
	// Note on "dummy" handlers:
	// Even if we don't want to handle these events, we have to register a "do-nothing" callback for them
	params.handleMouseClickFunc = dummy_mouse_handler;
	//--params.handleRightClickFunc = dummy_mouse_handler;
	params.handleMouseWheelFunc = dummy_wheel_handler;
	params.handleKeyFunc = dummy_key_handler;
	params.handleCursorFunc = dummy_cursor_status_handler;
	params.refcon = NULL;
	int hauteur, largeur;
	XPLMGetScreenSize(&largeur, &hauteur);
	//left = 0; bottom = 0; right = 0; top = 0;

	left = largeur / 3;
	right = largeur / 3;
	top = hauteur / 3;
	bottom = hauteur / 3;

	params.left = left + 50;
	params.bottom = bottom + 150;
	params.right = params.left + 200;
	params.top = params.bottom + 200;

	g_window = XPLMCreateWindowEx(&params);
	// Ouverture du fichier afin d'y écrire les positions de l'avion
	aircraft.openAircraftPositionsFile();
	return g_window != NULL;
}

PLUGIN_API void	XPluginStop(void)
{
	aircraft.closeAircraftPositionsFile();
	XPLMDestroyWindow(g_window);
	g_window = NULL;
}

PLUGIN_API void XPluginDisable(void) { }
PLUGIN_API int  XPluginEnable(void) { return 1; }
PLUGIN_API void XPluginReceiveMessage(XPLMPluginID inFrom, int inMsg, void * inParam) { }

/**
* La méthode update est appelée régulièrement (toutes les milliseconds, il semblerait)
*/
void update(XPLMWindowID in_window_id, void * in_refcon)
{
	//aircraft.writeInLogFile();
	// Ecriture des positions successives de l'avion dans le fichier ouvert dans la méthode XPluginStart
	aircraft.writeInPositionsFile();
}
