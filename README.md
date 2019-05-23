# ING-AIR ✈️

# Mise en place du projet
Après avoir créer un compte sur gitHub, installer gitHub Desktop.
Une fois le lien d'invitation pour le project accepté, cloner le projet.

Pour cloner le projet :
chercher le projet sur gitHub.com (si vous ne le trouver pas cliquez sur le logo de gitHub en haut à gauche de la page et rechercher le répertoire dans la partie gauche nommée Repositories).
Une fois le projet trouvé, cliquer sur 'Clone or download' puis 'Open in Desktop'
![](images/git_clone.png)

Une fenêtre devrait s'afficher pour vous demander d'ouvrir GitHubDesktop.exe. Cliquer sur Ouvrir

![](images/git_open_desktop.png)

GitHubDesktop devrait s'ouvrir en vous demandant de choisir l'emplacement local que vous voulez pour le clonage. Choisissez l'emplacement que vous voulez.
![](images/git_local_repo.png)

Enfin, ouvrir le fichier .sln pour commencer à travailler.

# Organisation du projet
## Le projet se découpe en deux grandes parties

### 1ère partie : le dossier **positions-retriver**
Ce dossier dont les scripts ont principalement été écrits en C++ permet la récupération de la position de l'avion dans le jeu X-Plane 1 via un plugin. Ce dernier va enregister les positions dans un fichier texte. Le nom du fichier texte est donné dans la classe Aircraft.h

### 2ème partie : le dossier **positions-inserter**
Ce dossier dont les scripts ont principalement été écrits en python permet l'insertion de données dans une BDD SQLite. En effet, le but de la partie précédente était d'écrire les positions de l'avion dans un fichier texte. Le script __positions-reader-inserter.py__ va se charger de lire les positions qui ont été enregistrées puis de les sauvegarder en base de données.

# Mise en place du système de récupération des positions de l'avion : Génération & Installation du plugin
Après avoir ouvert le projet, fait un clique-droit sur la solution, puis cliquer sur 'Générer la solution'
![](images/vs_compil.png)

Une fois la solution compilée, se rendre jusqu'au dossier ING-AIR (pas besoin d'aller jusqu'au fichier .xpl), en regarder le chemin indiqué dans la console.

![](images/vs_compil_end.png)

Copier le dossier ING-AIR dans le dossier plugins du jeu X-Plane 11 (pour trouver le dossier plugins suivre le chemin: X-Plane 11\Resources\plugins)

Le plugin est prêt à être utilisé.

# Mise en place du système d'enregistrement des positions dans une base de données SQLite
La version de python qui a été utilisée est la version 2.7.15 qui sera en archive dans le dossier
