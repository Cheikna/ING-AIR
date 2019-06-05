#include "../../SDK/XPlaneSDKIncludes.h"
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string.h>
/**
*	Ce fichier AircraftsPositions.h contient tous les prototypes de tous les méthodes qui vont être appelées par la suite.
*	Les différentes méthodes ci-dessous seront implémentées dans le fichier AircraftPositions.cpp
*/
class Aircraft {

private : 
	// Fichier où les positions de l'avion vont être écrites
	const std::string	aircraftPositionsFileName = "aircraft-positions.txt";
	std::ofstream		aircraftPositionsFile;

	std::string		getLatitudeAsString();
	std::string		getLongitudeAsString();

public :
	// Constructeur
	Aircraft();

	// Méthodes de la classe
	double			getLatitude();
	double			getLongitude();
	void			writeInLogFile();
	void			openAircraftPositionsFile();
	void			writeInPositionsFile();
	void			closeAircraftPositionsFile();

	// Retourne un nombre entre 0 et maxExclusive (exclus)
	double			getRandomNumber(int maxExclusive);
};
