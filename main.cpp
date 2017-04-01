// --------------------------------
// Auteur : Alexandre l'Heritier
// Projet Bouchon v0.1
// --------------------------------
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Route.h"

using namespace std;

void affiche(vector<int>v)
{
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;
}

int main() 
{
	int a = 0;
	vector<int> v;
	Route r = Route(2);
	v = r.tabAffiche();
	affiche(v);
	r.tempsPlus(1);
	v = r.tabAffiche();
	affiche(v);
	cin >> a;
	return 0;
}

/**
Changelog :
v0.1 : 

Dans class Route :
Route(int nbVoiture);
Route(int nbVoiture, int limite);
Route(int nbVoiture, int limite, int tailleRoute);
void ajouterVoiture(int numVoiture);
void enleverVoiture(int numVoiture);
void placementAleatoireDepart();
void tempsPlus(int temps);
std::vector<int> tabAffiche();
int tailleRoute();
void setLimiteVitesse(int vit);
int espaceAvant(int imaticulation);
void setProbaFrein(int pourcent);

std::vector<Voiture> tabVoiture;
std::vector<Voiture> tabRoute;
int limiteDeVitesse;
int probaFrein;

void modeleNash();
bool determineFrein();

Dans class Voiture :
Voiture();
Voiture(int numero);
Voiture(int numero, int vitess);
void setImatriculation(int numero);
void setVitesse(int vitess);
int getImatriculation();
int getVitesse();

int vitesse;
int imatriculation;

Première version du projet bouchon.
Début : 01/04/2017
**/