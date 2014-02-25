*** Application lourde ***

Prérequis :
 - OpenSSL

Qt :

Pour ce logiciel, nous utilisons Qt version 5.2. Lien pour téléchargement : http://qt-project.org/downloads
Qt est un Framework libre, qui permet de compiler l'application sur n'importe quel OS (il y a cependant besoin d'ajouter les dll adéquat).

Structure :

La structure est auto-généré par Qt, il suffit de lancer le .pro et il s'occupe du reste.
Il crée les .cpp, .h et .ui dans le même dossier ; et un dossier dans le dossier parent. Celui-ci regroupe tous les fichiers et dossiers une fois l'application lancé.
Ainsi les images et autres dll seront stockés dans ce dossier (release ou debug).

L'exécution :

Pour lancer le programme sans passé par Qt Creator, il faut utiliser le .exe se trouvant dans le dossier debug. Mais pour cela il faut également que Qt5Cored.dll soit installé sur votre ordinateur.