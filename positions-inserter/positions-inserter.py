#testé avec la version 2.7.15 de python

import sqlite3

def getConnection(databaseName) :
    connection = sqlite3.connect(databaseName)
    connection.enable_load_extension(True)
    connection.execute("SELECT load_extension('mod_spatialite')")
    return connection

def executeGeometryInsert(databaseName) :
	connection = getConnection(databaseName)
	connection.execute("INSERT INTO test_geom (the_geom, measured_value, name, id) VALUES (GeomFromText('POINT(11.01 11.02)', 4326), 11.123456789, 'python3', NULL);")
	connection.commit()

executeGeometryInsert("C:/Users/cheik/Desktop/db.sqlite")
