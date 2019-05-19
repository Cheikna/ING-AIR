import sqlite3
import time

databasePath = "position.sqlite"
tableName = "ingAir"
positionsFileName = "aircraft-positions.txt"
# Creation du fichier s'il n'existe pas
file = open(positionsFileName, 'w+')
file.close()

connection = sqlite3.connect(databasePath)
connection.enable_load_extension(True)
# Chargement obligatoire des extensions spatialite
connection.execute("SELECT load_extension('mod_spatialite')")
cursor = connection.cursor()

# Creation de la table
cursor.executescript(""" 
		DROP TABLE IF EXISTS  """ + tableName + """ ;
		CREATE TABLE IF NOT EXISTS """ + tableName + """ (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL, measured_value DOUBLE NOT NULL);
		SELECT InitSpatialMetaData();
		SELECT AddGeometryColumn('""" + tableName + """', 'the_geom', 4326, 'POINT', 'XY');
	""")
connection.commit()

#Lecture des positions
f = open(positionsFileName, "r")
f2 = open("database-log.txt", "a")
previousLine = ''
count = 1
while(True):
	currentLine = f.readline()
	print(currentLine)
	if(currentLine == previousLine):
		print("same as previousLine")
		time.sleep(5)
	else :
		print("new positions")
		positions = currentLine.split("and")
		latitude = positions[0]
		longitude = positions[1]
		f2.write("latitude : " + latitude)
		f2.write("longitude : " + longitude)
		f2.write(str(count) + "=======================")
		cursor.executescript("""
			INSERT INTO """ + tableName + """ VALUES (NULL, 'execfile2 test """ + str(count) + """', 2.34567, GeomFromText('POINT(2.02 3.03)', 4326)); 
			""")
		connection.commit()
	count += 1
f.close()
f2.close()
