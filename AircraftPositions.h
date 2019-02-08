#include "XPlaneSDKIncludes.h"
/**
*	Ce fichier AircraftsPositions.h contient tous les prototypes de tous les méthodes qui vont être appelées par la suite.
*	Les différentes méthodes ci-dessous seront implémentées dans le fichier AircraftPositions.cpp
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

	// Méthodes de la classe
	static double			getLatitude();
	static double			getLongitude();

	static std::string		getLatitudeAsString();
	static std::string		getLongitudeAsString();

	static void				writeInLogFile();
	static void				writeAircraftPositionsInFile(std::string fileName);
};
