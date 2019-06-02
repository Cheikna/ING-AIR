#include "Aircraft.h"


Aircraft::Aircraft(){}


double Aircraft::getLatitude()
{
	// R�cup�ration de la donn�e fournie par les dataRefs de X-PLANE
	return XPLMGetDatad(XPLMFindDataRef("sim/flightmodel/position/latitude"));
}

double Aircraft::getLongitude()
{
	// R�cup�ration de la donn�e fournie par les dataRefs de X-PLANE
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
	XPLMDebugString("========================================= Positions ========================================\n");
	std::string position = "Longitude : " + Aircraft::getLongitudeAsString() + " ---------------- Latitude : " + Aircraft::getLatitudeAsString();
	XPLMDebugString(position.c_str());
	XPLMDebugString("\n\n");
}

void Aircraft::openAircraftPositionsFile()
{
	aircraftPositionsFile.open(aircraftPositionsFileName);
	XPLMDebugString("Aircraft positions file opened");
}

void Aircraft::writeInPositionsFile()
{
	//Dans le fichier on �crit une position par ligne 
	// latitude and longitude
	aircraftPositionsFile << getLongitudeAsString() << "and" << getLatitudeAsString() << std::endl;
}

void Aircraft::closeAircraftPositionsFile()
{
	aircraftPositionsFile.close();
	XPLMDebugString("Aircraft positions file closed");
}

double Aircraft::getRandomNumber(int maxExclusive)
{
	return rand() % maxExclusive;
}
