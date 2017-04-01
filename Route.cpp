#include "Route.h"
#include <iostream>

using namespace std;

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
	tabRoute.resize(nbVoiture*2);
	probaFrein = 10;
	Route::placementAleatoireDepart();
}

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

void Route::ajouterVoiture(int numVoiture) 
{
	Voiture v;
	v.setImatriculation(numVoiture);
	tabVoiture.push_back(v);
}

void Route::enleverVoiture(int numVoiture)
{
	for (int i = 0; i < tabVoiture.size(); i++) 
	{
		if (tabVoiture[i].getImatriculation() == numVoiture)
		{
			//tabVoiture.erase(i);
		}
	}
}

void Route::placementAleatoireDepart()
{
	srand(time(NULL));
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

void Route::tempsPlus(int temps)
{
	for (int i = 0; i < temps; i++)
	{
		Route::modeleNash();
	}
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

int Route::tailleRoute()
{
	return tabRoute.size();
}

void Route::setLimiteVitesse(int vit)
{
	limiteDeVitesse = vit;
}

int Route::espaceAvant(int imaticulation)
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
	probaFrein = pourcent;
}

bool Route::determineFrein()
{
	srand(time(NULL));
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

		b = Route::espaceAvant(tabRoute[a].getImatriculation()) - 1;
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
