#include "../../SDK/XPlaneSDKIncludes.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
/**
*	Ce fichier AircraftsPositions.h contient tous les prototypes de tous les méthodes qui vont être appelées par la suite.
*	Les différentes méthodes ci-dessous seront implémentées dans le fichier AircraftPositions.cpp
*/
class Aircraft {

private : 
	// Fichier où les positions de l'avion vont être écrites
	const std::string	aircraftPositionsFileName = "aircraft_positions.txt";
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
