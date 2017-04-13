// --------------------------------
// Auteur : Alexandre l'Heritier
// Projet Bouchon v0.6 : Classe Voiture
// --------------------------------

#include "Voiture.h"

Voiture::Voiture()
{
	vitesse = -1;
	imatriculation = -1;
}

Voiture::Voiture(int numero)
{
	vitesse = 0;
	imatriculation = numero;
}

Voiture::Voiture(int numero, int vitess)
{
	vitesse = vitess;
	imatriculation = numero;
}

void Voiture::setImatriculation(int numero)
{
	imatriculation = numero;
}

void Voiture::setVitesse(int vitess)
{
	vitesse = vitess;
}

int Voiture::getImatriculation()
{
	return imatriculation;
}

int Voiture::getVitesse()
{
	return vitesse;
}
