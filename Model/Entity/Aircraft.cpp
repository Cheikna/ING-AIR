#include "Aircraft.h"


Aircraft::Aircraft()
{	
	// Exemple of database path : "D:\\GitHub\\ING-AIR\\GeometryDatabase.db"
	result = sqlite3_open(databasePath.c_str(), &database);

	if (result)
	{
		XPLMDebugString("Error when opening the database :\n");
	}
	else
	{
		XPLMDebugString("The database was opened Successfully!\n");
	}

}


double Aircraft::getLatitude()
{
	return XPLMGetDatad(XPLMFindDataRef("sim/flightmodel/position/latitude"));
}

double Aircraft::getLongitude()
{
	return XPLMGetDatad(XPLMFindDataRef("sim/flightmodel/position/longitude"));
}

std::string Aircraft::getLatitudeAsString()
{
	double latitude = Aircraft::getLatitude();
	std::string convertedLatitude = "0";
	if (latitude != NULL) {
		convertedLatitude = std::to_string(latitude);
	}
	return convertedLatitude;

}

std::string Aircraft::getLongitudeAsString()
{
	double longitude = Aircraft::getLongitude();
	std::string convertedLongitude = "0";
	if (longitude != NULL) {
		convertedLongitude = std::to_string(longitude);
	}
	
	return convertedLongitude;
}

void Aircraft::writeInLogFile()
{
	XPLMDebugString("\n\n\n");
	XPLMDebugString("========================================= Positions - Cheikna ========================================\n");
	std::string position = "Latitude : " + Aircraft::getLatitudeAsString() + " ---------------- Longitude : " + Aircraft::getLongitudeAsString();
	XPLMDebugString(position.c_str());
	XPLMDebugString("\n\n");
}

void Aircraft::insertPositionsIntoDatabase()
{
	std::string sql = "insert into " + tableName + "(longitude, latitude) values (" + getLatitudeAsString() + "," + getLongitudeAsString() + ");";

	char* messaggeError;
	int result = sqlite3_exec(database, sql.c_str(), NULL, 0, &messaggeError);

	if (result != SQLITE_OK)
	{
		XPLMDebugString("Error when executing the request\n");
	}
	else
	{
		XPLMDebugString("Request successfully executed !\n");
	}
}


int display(void * data, int argc, char ** argv, char ** azColName)
{
	int i;
	fprintf(stderr, "%s: ", (const char*)data);

	for (i = 0; i<argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");
	return 0;
}

void Aircraft::selectPositionsFromDatabase()
{
	std::string sql = "select * from " + tableName + ";";
	const char* data = "Callback function called";
	char* messaggeError;
	int result = sqlite3_exec(database, sql.c_str(), display, (void*)data, &messaggeError);

	if (result != SQLITE_OK)
	{
		XPLMDebugString("Error when executing the request\n");
	}
	else
	{
		XPLMDebugString("Request successfully executed !\n");
	}
}

void Aircraft::closeDatabase()
{
	sqlite3_close(database);
	XPLMDebugString("The database has been closed\n");
}
