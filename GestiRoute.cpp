// --------------------------------
// Auteur : Alexandre l'Heritier
// Projet Bouchon v0.5 : Classe GestiRoute
// --------------------------------
#include "GestiRoute.h"
#include <iostream>

using namespace std;

GestiRoute::GestiRoute(int nb_voiture)
{
	Route r = Route(nb_voiture);
	routes.push_back(r);
	temps_attente = 1;
	route_a_gerer = 0;
	position_curseur = 0;
	etape = 1;
	mode = 0;
	vitDeDefil = 500;
}

void GestiRoute::ajouterRoute(int nb_voiture)
{
	Route r = Route(nb_voiture, routes[0].getTailleRoute());
	routes.push_back(r);
}

void GestiRoute::supprimerRoute()
{
	routes.resize(routes.size() - 1);
}

void GestiRoute::liaisonRoutes()
{

}

int GestiRoute::getNbRoutes()
{
	return routes.size();
	return 1;
}

void GestiRoute::setTouche(char clavier)
{
	//     ------
	//     | 72 |
	//----------------
	//| 75 | 80 | 77 |
	//----------------
	// Espace = 32

	if (clavier == 72)
	{
		position_curseur--;
		if (position_curseur < 0)
		{
			position_curseur = 0;
		}
	}

	else if (clavier == 32)
	{
		if(etape_temp == 0)
		{
			etape_temp = etape;
			etape = 0;
		}
		else
		{
			etape = etape_temp;
			etape_temp = 0;
		}

	}

	else if (clavier == 80)
	{
		position_curseur++;
		if (position_curseur > 8)
		{
			position_curseur = 8;
		}
	}

	else if (clavier == 75)
	{
		if (position_curseur == 0)
		{
			if(routes.size() > 1)
			GestiRoute::supprimerRoute();
		}
		else if (position_curseur == 1)
		{
			route_a_gerer--;
			if (route_a_gerer < 0)
			{
				route_a_gerer = 0;
			}
		}

		else if (position_curseur == 2)
		{
			if (routes[route_a_gerer].getNbVoiture() > 1)
			{
				routes[route_a_gerer].enleverVoiture();
			}
		}

		else if (position_curseur == 3)
		{
			routes[route_a_gerer].setProbaFrein(routes[route_a_gerer].getProbaFrein() - 1);
		}

		else if (position_curseur == 4)
		{
			routes[route_a_gerer].setProbaResteArret(routes[route_a_gerer].getProbaResteArret() - 1);
		}

		else if (position_curseur == 5)
		{
			etape--;
			if (etape < 0)
			{
				etape = 0;
			}
		}

		else if (position_curseur == 6)
		{
			routes[route_a_gerer].setTailleRoute(routes[route_a_gerer].getTailleRoute() - 1);
		}

		else if (position_curseur == 7)
		{
			mode--;
			if (mode < 0)
			{
				mode = 0;
			}
		}
		else if (position_curseur == 8)
		{
			vitDeDefil -= 10;
			if (vitDeDefil <= 0)
			{
				vitDeDefil = 10;
			}
		}
	}

	else if (clavier == 77)
	{

		if (position_curseur == 0)
		{
			GestiRoute::ajouterRoute(routes[0].getNbVoiture());
		}
		else if (position_curseur == 1)
		{
			route_a_gerer++;
			if (route_a_gerer >= routes.size())
			{
				route_a_gerer = routes.size()-1;
			}
		}

		else if (position_curseur == 2)
		{
			routes[route_a_gerer].ajouterVoiture();
		}

		else if (position_curseur == 3)
		{
			routes[route_a_gerer].setProbaFrein(routes[route_a_gerer].getProbaFrein() + 1);
		}

		else if (position_curseur == 4)
		{
			routes[route_a_gerer].setProbaResteArret(routes[route_a_gerer].getProbaResteArret() + 1);
		}

		else if (position_curseur == 5)
		{
			etape++;
		}

		else if (position_curseur == 6)
		{
			routes[route_a_gerer].setTailleRoute(routes[route_a_gerer].getTailleRoute() + 1);
		}

		else if (position_curseur == 7)
		{
			mode++;
			if (mode > 1)
			{
				mode = 1;
			}
		}
		else if (position_curseur == 8)
		{
			vitDeDefil += 10;
		}
	}
}

void GestiRoute::affichageRoutes()
{
	route_a_afficher = "";
	for (int i = 0; i < routes.size(); i++)
	{
		vector<Voiture> v = routes[i].tabAffiche();
		for (int j = 0; j < v.size(); j++)
		{
			if (v[j].getImatriculation() == -1)
			{
				route_a_afficher.append("[    ]");
			}
			else
			{
				route_a_afficher.append("[");
				route_a_afficher.append(to_string(v[j].getImatriculation()));
				route_a_afficher.append(";");
				route_a_afficher.append(to_string(v[j].getVitesse()));
				route_a_afficher.append("]");
			}
		}
		route_a_afficher.append("\n");
		route_a_afficher.append("--------------------------------------------------------");
		route_a_afficher.append("\n");
	}
}

void GestiRoute::affichageCommandes()
{
	cout << route_a_afficher << endl;
	cout << endl;

	if (position_curseur == 0)
		cout << "<[";
	cout << "(" << routes.size() << ")  Nb route";
	if (position_curseur == 0)
		cout << "]>";

	cout << endl;

	if (position_curseur == 1)
		cout << "<[";
	cout << "(" << route_a_gerer << ")  Num route a gerer";
	if (position_curseur == 1)
		cout << "]>";

	cout << endl;

	if (position_curseur == 2)
		cout << "<[";
	cout << "(" << routes[route_a_gerer].getNbVoiture() << ")  Nb voiture";
	if (position_curseur == 2)
		cout << "]>";

	cout << endl;

	if (position_curseur == 3)
		cout << "<[";
	cout << "(" << routes[route_a_gerer].getProbaFrein() << ")  Proba p";
	if (position_curseur == 3)
		cout << "]>";

	cout << endl;

	if (position_curseur == 4)
		cout << "<[";
	cout << "(" << routes[route_a_gerer].getProbaResteArret() << ")  Proba q";
	if (position_curseur == 4)
		cout << "]>";

	cout << endl;

	if (position_curseur == 5)
		cout << "<[";
	cout << "(" << etape << ")  Etape";
	if (position_curseur == 5)
		cout << "]>";

	cout << endl;

	if (position_curseur == 6)
		cout << "<[";
	cout << "(" << routes[route_a_gerer].getTailleRoute() << ")  Taille route";
	if (position_curseur == 6)
		cout << "]>";

	cout << endl;

	if (position_curseur == 7)
		cout << "<[";
	cout << "(" << (mode==0 ? "Nash" : "VDR") << ")  Mode";
	if (position_curseur == 7)
		cout << "]>";

	cout << endl;

	if (position_curseur == 8)
		cout << "<[";
	cout << "(" << vitDeDefil << ")  VitDeDefil";
	if (position_curseur == 8)
		cout << "]>";

	cout << endl;
}

void GestiRoute::plusEtape()
{
	for (int i = 0; i < routes.size(); i++)
	{
		routes[i].tempsPlus(etape, mode);
	}
}

int GestiRoute::vitesse()
{
	return vitDeDefil;
}
