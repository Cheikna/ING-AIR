#include "XPLMDisplay.h"
#include "XPLMGraphics.h"
#include "XPLMUtilities.h"
#include "XPLMDataAccess.h"
#include "XPLMUtilities.h"
#include "AircraftPositions.h"
#include <string.h>
#include <string>
#include <sstream>
#if IBM
#include <windows.h>
#endif
#if LIN
#include <GL/gl.h>
#elif __GNUC__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#ifndef XPLM300
#error This is made to be compiled against the XPLM300 SDK
#endif

#include <direct.h>
#include <time.h>
#include <ctime>
#include <iostream>
#include <fstream>


AircraftPositions::AircraftPositions()
{
}

double AircraftPositions::getLatitude()
{
	return XPLMGetDatad(XPLMFindDataRef("sim/flightmodel/position/latitude"));
}

double AircraftPositions::getLongitude()
{
	return XPLMGetDatad(XPLMFindDataRef("sim/flightmodel/position/longitude"));
}

std::string AircraftPositions::getLatitudeAsString()
{
	double latitude = AircraftPositions::getLatitude();
	std::string convertedLatitude = std::to_string(latitude);
	std::stringstream latitudeStream;
	latitudeStream << convertedLatitude ;
	std::string latitudeAsString = latitudeStream.str();
	return latitudeAsString;

}

std::string AircraftPositions::getLongitudeAsString()
{
	double longitude = AircraftPositions::getLongitude();
	std::string convertedLongitude = std::to_string(longitude);
	std::stringstream longitudeStream;
	longitudeStream <<  convertedLongitude;
	std::string longitudeAsString = longitudeStream.str();
	return longitudeAsString;
}

void AircraftPositions::writeInLogFile()
{
	XPLMDebugString("\n\n\n");
	XPLMDebugString("========================================= Positions - Cheikna ========================================\n");
	std::string position = "Latitude : " + AircraftPositions::getLatitudeAsString() + " ---------------- Longitude : " + AircraftPositions::getLongitudeAsString();
	XPLMDebugString(position.c_str());
	XPLMDebugString("\n\n");
}

void AircraftPositions::writeAircraftPositionsInFile(std::string fileName)
{
	/*std::ofstream outfile;
	outfile.open("test_separate_code.txt");
	std::string convertedLatitude = AircraftPositions::getLatitudeAsString();
	std::string convertedLongitude = AircraftPositions::getLongitudeAsString();
	outfile << "========================================= Positions ========================================\n";
	std::stringstream positionsStream;
	positionsStream << "Position lue  ----- Latitude : " << convertedLatitude << " Longitude : " << convertedLongitude << "\n";
	std::string position = "Latitude : " + AircraftPositions ::getLatitudeAsString() + " ---------------- Longitude : " + AircraftPositions::getLongitudeAsString() ;
	outfile << position;

	std::ofstream myfile;
	myfile.open("exampleCheiknadansoko.txt");
	myfile << "Writing this to a file.\n";*/
	//myfile.close();
	std::ofstream("exampleCheiknadansoko.txt");
	std::ofstream outfile;
	outfile << "Ceci est un message test afin de vérifier si on peut créer et écrire dans un fichier texte à partir d'un plugin sous X-Plane11.\nCe fichier peut être supprimé.\nING-AIR :-)";
	outfile.close();
}
