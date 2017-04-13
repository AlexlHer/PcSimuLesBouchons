// --------------------------------
// Auteur : Alexandre l'Heritier
// Projet Bouchon v0.6 : Classe Route
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

Route::Route()
{
	srand(time(NULL));
	limiteDeVitesse = 5;
	probaFrein = 10;
	probaResteArret = 50;
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
	tabRoute.resize(nbVoiture*2);
	probaFrein = 10;
	probaResteArret = 50;
	Route::placementAleatoireDepart();
}

/* Constructeur complet
 * @param nbVoiture Le nombre de voiture.
 * @param limite La limite de vitesse.
 * @param tailleRoute La taille de la route.
 * @param frein Le pourcentage de freinage al�atoire.
 */
Route::Route(int nbVoiture, int tailleRoute)
{
	srand(time(NULL));
	limiteDeVitesse = 5;
	for (int i = 0; i < nbVoiture; i++)
	{
		Voiture v(i);
		v.setVitesse(rand() % limiteDeVitesse);
		tabVoiture.push_back(v);
	}
	tabRoute.resize(tailleRoute);
	probaFrein = 10;
	probaResteArret = 50;
	Route::placementAleatoireDepart();
}

bool Route::intIn(int intt, vector<int> dans)
{
	for (int i = 0; i < dans.size(); i++)
	{
		if (dans[i] == intt)
		{
			return true;
		}
	}
	return false;
}

void Route::ajouterVoiture() 
{
	if(tabVoiture.size() < tabRoute.size())
	{
		vector<int> immatri;
		for (int i = 0; i < tabVoiture.size(); i++)
		{
			immatri.push_back(tabVoiture[i].getImatriculation());
		}

		int a = 0;

		while (Route::intIn(a, immatri))
		{
			a++;
		}

		Voiture v;
		v.setImatriculation(a);
		v.setVitesse(rand() % limiteDeVitesse);
		tabVoiture.push_back(v);
		Route::placementAleatoire(v);
	}
}

void Route::ajouterVoiture(int imatriculation)
{
	if (tabVoiture.size() < tabRoute.size())
	{
		Voiture v;
		v.setImatriculation(imatriculation);
		v.setVitesse(rand() % limiteDeVitesse);
		tabVoiture.push_back(v);
		Route::placementAleatoire(v);
	}
}

void Route::ajouterVoiture(Voiture v)
{
	if (tabVoiture.size() < tabRoute.size())
	{
		tabVoiture.push_back(v);
		Route::placementAleatoire(v);
	}
}

void Route::ajouterVoiture(Voiture v, int pos)
{
	if (tabVoiture.size() < tabRoute.size())
	{
		if (pos < tabRoute.size())
		{
			tabVoiture.push_back(v);
			tabRoute[pos] = v;
		}
	}
}

void Route::enleverVoiture()
{
	Voiture v1, v2;
	v2 = tabVoiture[tabVoiture.size() - 1];
	tabVoiture.pop_back();
	for (int i = 0; i < tabRoute.size(); i++)
	{
		if (tabRoute[i].getImatriculation() == v2.getImatriculation())
		{
			tabRoute[i] = v1;
		}
	}
}

void Route::enleverVoiture(int imatriculation)
{
	Voiture w;
	int a = 0;
	for (int i = 0; i < tabVoiture.size(); i++)
	{
		if (tabVoiture[i].getImatriculation() == imatriculation)
		{
			tabVoiture.erase(tabVoiture.begin() + i);
		}
	}
	for (int i = 0; i < tabRoute.size(); i++)
	{
		if (tabRoute[i].getImatriculation() == imatriculation)
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

void Route::tempsPlus(int temps, int modeleNV)
{
	for (int i = 0; i < temps; i++)
	{
		Route::modele(modeleNV);
	}
}

int  Route::getTailleRoute()
{
	return tabRoute.size();
}

void Route::setTailleRoute(int taille)
{
	if (taille < tabRoute.size())
	{
		if (taille >= tabVoiture.size())
		{
			vector<Voiture> v;
			for (int i = taille; i < tabRoute.size(); i++) {
				if (tabRoute[i].getImatriculation() != -1) {
					v.push_back(tabRoute[i]);
				}
			}
			tabRoute.resize(taille);
			for (int i = 0; i < v.size(); i++)
			{
				Route::placementAleatoire(v[i]);
			}
		}
	}
	else
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

void Route::setProbaResteArret(int pourcent)
{
	if (pourcent < 0) pourcent = 0;
	if (pourcent > 100) pourcent = 100;
	probaResteArret = pourcent;
}

int  Route::getProbaResteArret()
{
	return probaResteArret;
}

bool Route::determineResteArret()
{
	vector<bool> a(probaResteArret, true);
	for (int i = 0; i < 100 - probaResteArret; i++)
	{
		a.push_back(false);
	}
	return a[rand() % 100];
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

void Route::actualiserTabVoiture()
{
	for (int i = 0; i < tabVoiture.size(); i++)
	{
		for (int j = 0; j < tabRoute.size(); j++)
		{
			if (tabVoiture[i].getImatriculation() == tabRoute[j].getImatriculation())
			{
				tabVoiture[i].setVitesse(tabRoute[j].getVitesse());
			}
		}
	}
}

void Route::modele(int nom_modele)
{
	int a = 0, b = 0;
	for (int i = 0; i < tabVoiture.size(); i++)
	{
		while (tabRoute[a].getImatriculation() == -1)
		{
			a++;
		}

		int vitesseVoiture = tabRoute[a].getVitesse();
		int immatriVoiture = tabRoute[a].getImatriculation();

		if ( !(nom_modele == 1 && vitesseVoiture == 0 && Route::determineResteArret()))
		{
			if (limiteDeVitesse > vitesseVoiture)
			{
				vitesseVoiture++;
			}

			b = Route::espaceAvant(immatriVoiture) - 1;
			//cout << b << endl;
			if (vitesseVoiture > b)
			{
				vitesseVoiture = b;
			}

			if (Route::determineFrein())
			{
				vitesseVoiture--;
			}

			if (vitesseVoiture < 0)
			{
				vitesseVoiture = 0;
			}
			//cout << tabRoute[a].getVitesse() << endl;

			tabRoute[a].setVitesse(vitesseVoiture);
		}
		a++;
	}
	a = 0, b = 0;
	int c;
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
		if (a != b)
		{
			//if (tv[b].getVitesse() != -1)
			//{
			//	cout << "Erreur !!! " << tv[a].getImatriculation() << " ; "<< tv[b].getImatriculation();
			//	cin >> c;
			//}
			v = tv[a];
			tv[a] = tv[b];
			tv[b] = v;
		}
		a++;
	}
	tabRoute = tv;
	Route::actualiserTabVoiture();
}

int Route::getNbVoiture()
{
	return tabVoiture.size();
}

vector<Voiture> Route::tabAffiche()
{
	return tabRoute;
}

vector<Voiture> Route::getTabVoiture()
{
	return tabVoiture;
}
