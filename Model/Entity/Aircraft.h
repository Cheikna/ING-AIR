#include "../DatabaseFiles/sqlite3.h"
#include "../../SDK/XPlaneSDKIncludes.h"
/**
*	Ce fichier AircraftsPositions.h contient tous les prototypes de tous les méthodes qui vont être appelées par la suite.
*	Les différentes méthodes ci-dessous seront implémentées dans le fichier AircraftPositions.cpp
*/
class Aircraft {

private : 
	const std::string databasePath = "D:\\GitHub\\ING-AIR\\GeometryDatabase.db";
	const std::string tableName = "COORDINATES_2";
	sqlite3 *database;
	int result;

public :
	// Constructeur
	Aircraft();

	// Méthodes de la classe
	double			getLatitude();
	double			getLongitude();

	std::string		getLatitudeAsString();
	std::string		getLongitudeAsString();

	void			writeInLogFile();
	void			insertPositionsIntoDatabase();
	void			selectPositionsFromDatabase();
	void			closeDatabase();
};
