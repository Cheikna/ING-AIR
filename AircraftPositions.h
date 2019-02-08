#include "XPlaneSDKIncludes.h"
/**
*	Ce fichier AircraftsPositions.h contient tous les prototypes de tous les m�thodes qui vont �tre appel�es par la suite.
*	Les diff�rentes m�thodes ci-dessous seront impl�ment�es dans le fichier AircraftPositions.cpp
*/
class AircraftPositions {

private : 
	// Attributs
	/*int left;
	int bottom; 
	int right;
	int top;
	double latitude;
	double longitude;*/

public :
	// Constructeur
	AircraftPositions();

	// M�thodes de la classe
	static double			getLatitude();
	static double			getLongitude();

	static std::string		getLatitudeAsString();
	static std::string		getLongitudeAsString();

	static void				writeInLogFile();
	static void				writeAircraftPositionsInFile(std::string fileName);
};
