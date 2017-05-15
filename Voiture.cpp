// --------------------------------
// Auteur : Alexandre l'Heritier
// PcSimuLesBouchons v4.0 : Classe Voiture
// --------------------------------

#include "Voiture.h"

/*
Operateur de comparaison pour savoir si une voiture est identique à une autre.
@params Les deux voitures à comparer.
@return true si les vitesses et les immatriculations correspondent, false sinon.
*/
bool operator==(Voiture &v6, Voiture &v8)
{
	if (v6.getImatriculation() == v8.getImatriculation() && v6.getVitesse() == v8.getVitesse())
	{
		return true;
	}
	return false;
}

/*
Constructeur d'une voiture "vide".
*/
Voiture::Voiture()
{
	vitesse = -1;
	imatriculation = -1;
}

/*
Constructeur d'une voiture avec une immatriculation particulière et une vitesse nulle.
@param numero L'immatriculation voulu.
*/
Voiture::Voiture(int numero)
{
	vitesse = 0;
	imatriculation = numero;
}

/*
Constructeur d'une voiture avec une immatriculation particulière et une vitesse particulière.
@param numero L'immatriculation voulu.
@param vitess La vitesse voulu.
*/
Voiture::Voiture(int numero, int vitess)
{
	vitesse = vitess;
	imatriculation = numero;
}

/*
On defini une immatriculation pour la voiture.
@param numero Le numero d'immatriculation à définir.
*/
void Voiture::setImatriculation(int numero)
{
	imatriculation = numero;
}

/*
On defini une vitesse pour la voiture.
@param vitess La vitesse à définir.
*/
void Voiture::setVitesse(int vitess)
{
	vitesse = vitess;
}

/*
Renvoi l'immatriculation de la voiture.
@return L'immatriculation de la voiture.
*/
int Voiture::getImatriculation()
{
	return imatriculation;
}

/*
Renvoi la vitesse de la voiture.
@return La vitesse de la voiture.
*/
int Voiture::getVitesse()
{
	return vitesse;
}
