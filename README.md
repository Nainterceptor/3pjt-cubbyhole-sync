*** Application lourde ***

Pr�requis :
 - OpenSSL

Qt :

Pour ce logiciel, nous utilisons Qt version 5.2. Lien pour t�l�chargement : http://qt-project.org/downloads
Qt est un Framework libre, qui permet de compiler l'application sur n'importe quel OS (il y a cependant besoin d'ajouter les dll ad�quat).

Structure :

La structure est auto-g�n�r� par Qt, il suffit de lancer le .pro et il s'occupe du reste.
Il cr�e les .cpp, .h et .ui dans le m�me dossier ; et un dossier dans le dossier parent. Celui-ci regroupe tous les fichiers et dossiers une fois l'application lanc�.
Ainsi les images et autres dll seront stock�s dans ce dossier (release ou debug).

L'ex�cution :

Pour lancer le programme sans pass� par Qt Creator, il faut utiliser le .exe se trouvant dans le dossier debug. Mais pour cela il faut �galement que Qt5Cored.dll soit install� sur votre ordinateur.