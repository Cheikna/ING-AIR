#include "../DatabaseFiles/sqlite3.h"
#include "../../SDK/XPlaneSDKIncludes.h"
/**
*	Ce fichier AircraftsPositions.h contient tous les prototypes de tous les m�thodes qui vont �tre appel�es par la suite.
*	Les diff�rentes m�thodes ci-dessous seront impl�ment�es dans le fichier AircraftPositions.cpp
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

	// M�thodes de la classe
	double			getLatitude();
	double			getLongitude();

	std::string		getLatitudeAsString();
	std::string		getLongitudeAsString();

	void			writeInLogFile();
	void			insertPositionsIntoDatabase();
	void			selectPositionsFromDatabase();
	void			closeDatabase();
};
