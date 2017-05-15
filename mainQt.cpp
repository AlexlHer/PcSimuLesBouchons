#include <QApplication>
#include <QtWidgets>
#include "Interface.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	Interface iinterface;
	iinterface.show();

	return a.exec();
}

/*
Changelog :
A faire :
Resoudre le bug du rembobinage.

v0.3 :
Les deux autres onglets sont complet.
Le programme est compatible avec le main de PcSLB v3.0.
Bug de pause r�solu.

v0.2 :
Ajout des commandes du premier onglet.
Ajout des affichages.

v0.1 :
Cr�ation de tous les boutons du premier onglet.
Affichage de la route op�rationnel.
*/