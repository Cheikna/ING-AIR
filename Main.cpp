#include "AircraftPositions.h"


// Callbacks we will register when we create our window
void				XPluginUpdate(XPLMWindowID in_window_id, void * in_refcon);


//Cette m�thode est appel�e une seule fois, lors du lancement de X-Plane
PLUGIN_API int XPluginStart(
							char *		outName,
							char *		outSig,
							char *		outDesc)
{
	strcpy(outName, "ING-AIR");
	strcpy(outSig, "xpsdk.examples.ing_air");
	strcpy(outDesc, "Le plugin ING-AIR");

	return 0;

}

//Cette m�thode est appel�e plusieurs fois automatiquement
void XPluginUpdate(XPLMWindowID in_window_id, void * in_refcon)
{
	std::ofstream myfile("example.txt");
	if (myfile.is_open())
	{
		myfile << "This is a line.\n";
		myfile << "This is another line.\n";
		myfile.close();
	}

	std::ofstream("mainExampleCheiknadansoko.txt");
	std::ofstream outfile;
	outfile << "Ceci est un message test afin de v�rifier si on peut cr�er et �crire dans un fichier texte � partir d'un plugin sous X-Plane11.\nCe fichier peut �tre supprim�.\nING-AIR :-)";
	outfile.close();
	AircraftPositions::writeAircraftPositionsInFile("test_separate_code.txt");	
	AircraftPositions::writeInLogFile();
}


PLUGIN_API void	XPluginStop(void)
{
	// Since we created the window, we'll be good citizens and clean it up
	/*XPLMDestroyWindow(g_window);
	g_window = NULL;*/
}

PLUGIN_API void XPluginDisable(void) { }
PLUGIN_API int  XPluginEnable(void) { return 1; }
PLUGIN_API void XPluginReceiveMessage(XPLMPluginID inFrom, int inMsg, void * inParam) { }
