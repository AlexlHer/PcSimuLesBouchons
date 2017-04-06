// --------------------------------
// Auteur : Alexandre l'Heritier
// Projet Bouchon v0.3 : Classe Route
// --------------------------------

#include "Route.h"
#include <iostream>

using namespace std;

bool operator==(Voiture &v1, Voiture &v2)
{
	if (v1.getImatriculation() == v2.getImatriculation() && v1.getVitesse() == v2.getVitesse())
	{
		return true;
	}
	return false;
}

/* Constructeur rapide
 * @param nbVoiture Le nombre de voiture.
 */
Route::Route(int nbVoiture)
{
	srand(time(NULL));
	limiteDeVitesse = 5;
	for (int i = 0; i < nbVoiture; i++)
	{
		Voiture v(i);
		v.setVitesse(rand() % limiteDeVitesse);
		tabVoiture.push_back(v);
	}
	tabRoute.resize(nbVoiture*3);
	probaFrein = 10;
	Route::placementAleatoireDepart();
}

/* Constructeur complet
 * @param nbVoiture Le nombre de voiture.
 * @param limite La limite de vitesse.
 * @param tailleRoute La taille de la route.
 * @param frein Le pourcentage de freinage aléatoire.
 */
Route::Route(int nbVoiture, int limite, int tailleRoute, int frein)
{
	srand(time(NULL));
	limiteDeVitesse = limite;
	for (int i = 0; i < nbVoiture; i++)
	{
		Voiture v(i);
		v.setVitesse(rand() % limiteDeVitesse);
		tabVoiture.push_back(v);
	}
	tabRoute.resize(tailleRoute);
	probaFrein = frein;
	Route::placementAleatoireDepart();
}

void Route::ajouterVoiture() 
{
	Voiture v;
	v.setImatriculation(tabVoiture.size());
	v.setVitesse(rand() % limiteDeVitesse);
	tabVoiture.push_back(v);
	Route::placementAleatoire(v);
}

void Route::ajouterVoiture(Voiture v)
{
	tabVoiture.push_back(v);
	Route::placementAleatoire(v);
}

void Route::ajouterVoiture(Voiture v, int pos)
{
	tabVoiture.push_back(v);
	tabRoute[pos] = v;
}

void Route::enleverVoiture()
{
	Voiture v;
	tabVoiture.resize(tabVoiture.size() - 1);
	for (int i = 0; i < tabRoute.size(); i++)
	{
		if (tabRoute[i].getImatriculation() == tabVoiture.size()-1)
		{
			tabRoute[i] = v;
		}
	}
}

void Route::enleverVoiture(Voiture v)
{
	Voiture w;
	for (int i = 0; i < tabVoiture.size(); i++)
	{
		if (tabVoiture[i] == v)
		{
			tabVoiture[i] = w;
		}
	}
	for (int i = 0; i < tabRoute.size(); i++)
	{
		if (tabRoute[i] == v)
		{
			tabRoute[i] = w;
		}
	}
}

void Route::placementAleatoire(Voiture v)
{
	int a = rand() % tabRoute.size();
	while (tabRoute[a].getImatriculation() != -1)
	{
		a = rand() % tabRoute.size();
	}
	tabRoute[a] = v;
}

void Route::placementAleatoireDepart()
{
	int a = 0;
	for (int i = 0; i < tabVoiture.size(); i++)
	{
		a = rand() % tabRoute.size();
		while(tabRoute[a].getImatriculation() != -1)
		{
			a = rand() % tabRoute.size();
		}
		tabRoute[a] = tabVoiture[i];
	}
}

void Route::tempsPlus(int temps, int modele)
{
	for (int i = 0; i < temps; i++)
	{
		if(modele == 0)
			Route::modeleNash();
	}
}

int  Route::getTailleRoute()
{
	return tabRoute.size();
}

void Route::setTailleRoute(int taille)
{
	tabRoute.resize(taille);
}

void Route::setLimiteVitesse(int vit)
{
	limiteDeVitesse = vit;
}

int  Route::espaceAvant(int imaticulation)
{
	int a = 0, b = 1;
	while (tabRoute[a].getImatriculation() != imaticulation)
	{
		a++;
	}

	if (a + b >= tabRoute.size())
	{
		a -= tabRoute.size();
	}
	
	while (tabRoute[a+b].getImatriculation() == -1)
	{
		if (a + b + 1 >= tabRoute.size())
		{
			a -= tabRoute.size();
		}
		b++;
	}
	return b;
}

void Route::setProbaFrein(int pourcent)
{
	if (pourcent < 0) pourcent = 0;
	if (pourcent > 100) pourcent = 100;
	probaFrein = pourcent;
}

int  Route::getProbaFrein()
{
	return probaFrein;
}

bool Route::determineFrein()
{
	vector<bool> a(probaFrein, true);
	for (int i = 0; i < 100 - probaFrein; i++)
	{
		a.push_back(false);
	}
	return a[rand() % 100];
}

void Route::modeleNash()
{
	int a = 0, b = 0;
	for (int i = 0; i < tabVoiture.size(); i++)
	{
		while (tabRoute[a].getImatriculation() == -1)
		{
			a++;
		}

		if (limiteDeVitesse > tabRoute[a].getVitesse())
		{
			tabRoute[a].setVitesse(tabRoute[a].getVitesse() + 1);
		}

		b = Route::espaceAvant(tabRoute[a].getImatriculation());
		//cout << b << endl;
		if (tabRoute[a].getVitesse() > b)
		{
			tabRoute[a].setVitesse(b);
		}

		if (Route::determineFrein())
		{
			tabRoute[a].setVitesse(tabRoute[a].getVitesse() - 1);
		}

		if (tabRoute[a].getVitesse() < 0)
		{
			tabRoute[a].setVitesse(0);
		}
		//cout << tabRoute[a].getVitesse() << endl;
		a++;
	}
	a = 0, b = 0;
	Voiture v;
	vector<Voiture> tv = tabRoute;
	for (int i = 0; i < tabVoiture.size(); i++)
	{
		while (tabRoute[a].getImatriculation() == -1)
		{
			a++;
		}
		//cout << a << endl;
		if (a + tv[a].getVitesse() >= tv.size())
		{
			b = a - tv.size() + tv[a].getVitesse();
		}
		else
		{
			b = a + tv[a].getVitesse();
		}
		v = tv[a];
		tv[a] = tv[b];
		tv[b] = v;
		a++;
	}
	tabRoute = tv;
}

vector<int> Route::tabAffiche()
{
	vector<int> v;
	for (int i = 0; i < tabRoute.size(); i++)
	{
		v.push_back(tabRoute[i].getVitesse());
	}
	return v;
}
