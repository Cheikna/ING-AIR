#include "../../SDK/XPlaneSDKIncludes.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
/**
*	Ce fichier AircraftsPositions.h contient tous les prototypes de tous les m�thodes qui vont �tre appel�es par la suite.
*	Les diff�rentes m�thodes ci-dessous seront impl�ment�es dans le fichier AircraftPositions.cpp
*/
class Aircraft {

private : 
	// Fichier o� les positions de l'avion vont �tre �crites
	const std::string	aircraftPositionsFileName = "aircraft_positions.txt";
	std::ofstream		aircraftPositionsFile;

	std::string		getLatitudeAsString();
	std::string		getLongitudeAsString();

public :
	// Constructeur
	Aircraft();

	// M�thodes de la classe
	double			getLatitude();
	double			getLongitude();

	void			writeInLogFile();
	void			openAircraftPositionsFile();
	void			writeInPositionsFile();
	void			closeAircraftPositionsFile();

	// Retourne un nombre entre 0 et maxExclusive (exclus)
	double			getRandomNumber(int maxExclusive);
};
