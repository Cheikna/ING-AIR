import sqlite3
import time

databasePath = "position.sqlite"
tableName = "ING_AIR"
positionsFileName = "aircraft-positions.txt"

# Creation du fichier de base de donnee s'il n'existe pas. Le parametre a+ permet de creer le fichier s'il n'existe pas sans en effacer le contenu deja present
print("Creation of the database file in progress...")
databaseFile = open(databasePath, "a+")
databaseFile.close()
print("Database file created")

# Creation du fichier des positions s'il n'existe pas afin que le plugin position-reader fait en C++ puisse ecrire les position
file = open(positionsFileName, 'w+')
file.close()

# ID qui va etre cree pour nos mises a jour de positions afin d'eviter d'avoir inserer de nouvelles lignes car sqlite est limite a 500 lignes
myId = 0

connection = sqlite3.connect(databasePath)
connection.enable_load_extension(True)
# Chargement obligatoire des extensions spatialite
connection.execute("SELECT load_extension('mod_spatialite')")
cursor = connection.cursor()

print("Creation of the table " + tableName + " in progress. This operation may take some time (~3 minutes).")
# Creation de la table
cursor.executescript(""" 
		DROP TABLE IF EXISTS  """ + tableName + """ ;
		CREATE TABLE IF NOT EXISTS """ + tableName + """ (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, count INTEGER NOT NULL);
		SELECT InitSpatialMetaData();
		SELECT AddGeometryColumn('""" + tableName + """', 'the_geom', 4326, 'POINT', 'XY');
	""")
connection.commit()

print("The table " + tableName + " has been created.")
print("Processing positions...")
print("If you quit this window, the new positions will not be saved")
# Lecture des positions et insertion dans la base de donnee
f = open(positionsFileName, "r")
previousLine = ''
count = 1
while(True):
	# Lecture de la ligne suivante
	currentLine = f.readline()
	# Le regex de split est defini dans la classe Aircraft.cpp du projet positions-retriever fait en C++
	positions = currentLine.split("and")
	if(len(positions) >= 2):
		longitude = positions[0]
		latitude = positions[1]
		point = longitude + " " + latitude
		if(myId == 0):
			# Insertion de la premiere position recuperee
			cursor.executescript("""
				INSERT INTO """ + tableName + """ VALUES (NULL, """ + str(count) + """, GeomFromText('POINT(""" + point + """)', 4326)); 
				""")
			# Recuperation de l'id correspondant a cette derniere ligne creee
			cursor.execute(""" SELECT id FROM """ + tableName + """ ORDER BY id DESC LIMIT 1;""")
			myId = cursor.fetchone()[0]
			print("A new line has been created with the id : " + str(myId))

		else :			
			# Mise a jour des points ainsi que du count
			query = 'UPDATE  '  + tableName + '  SET count =  ' + str(count) +' , the_geom = GeomFromText(\'POINT(' + point + ')\', 4326) WHERE id =  '+ str(myId) +';'
			cursor.execute(query)
		connection.commit()
		# Augmente afin de connaitre le nombre de tour de boucle qui a ete fait
		count += 1
f.close()
