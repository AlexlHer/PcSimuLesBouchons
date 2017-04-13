// --------------------------------
// Auteur : Alexandre l'Heritier
// Projet Bouchon v0.6 : Classe GestiRoute
// --------------------------------
#include "GestiRoute.h"
#include <iostream>

using namespace std;

vector<Voiture> operator+(vector<Voiture> &a, vector<Voiture> &b)
{
	vector<Voiture> v;
	for (int i = 0; i < a.size(); i++)
	{
		v.push_back(a[i]);
	}
	for (int i = 0; i < b.size(); i++)
	{
		v.push_back(b[i]);
	}
	return v;
}

bool GestiRoute::intIn(int intt, vector<int> dans)
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

bool GestiRoute::voitureIn(Voiture v, vector<Voiture> dans)
{
	for (int i = 0; i < dans.size(); i++)
	{
		if (dans[i].getImatriculation() == v.getImatriculation() && dans[i].getVitesse() == v.getVitesse())
		{
			return true;
		}
	}
	return false;
}

void GestiRoute::creerliaisonRoutes()
{
	Route r = Route(0, routes[route_a_gerer].getTailleRoute());
	routes_liee.push_back(r);
	vector<int> v;
	v.push_back(route_a_gerer);
	v.push_back(routes_liee.size() - 1);
	liaisons.push_back(v);
}

void GestiRoute::gestiLiaison()
{
	vector<Voiture> r1, r2;
	Route *route1, *route2;

	for (int i = 0; i < routes.size(); i++)
	{
		vector<int> v = GestiRoute::routesLiee(i);
		for (int k = 0; k < v.size(); k++)
		{
			if (k == 0)
			{
				r1 = routes[liaisons[v[0]][0]].tabAffiche();
				r2 = routes_liee[liaisons[v[0]][1]].tabAffiche();
				route1 = &routes[liaisons[v[0]][0]];
				route2 = &routes_liee[liaisons[v[0]][1]];
			}
			else
			{
				r1 = routes_liee[liaisons[v[k-1]][1]].tabAffiche();
				r2 = routes_liee[liaisons[v[k]][1]].tabAffiche();
				route1 = &routes_liee[liaisons[v[k-1]][1]];
				route2 = &routes_liee[liaisons[v[k]][1]];
			}
			vector<Voiture> temp;

			for (int j = 0; j < r1.size() - 1; j++)
			{
				if (r1[j].getVitesse() == 0 && r1[j + 1].getVitesse() == 0 && r2[j].getImatriculation() == -1 && r2[j + 1].getImatriculation() == -1)
				{
					route1->enleverVoiture(r1[j].getImatriculation());
					route2->ajouterVoiture(r1[j], j + 1);

					r1 = route1->tabAffiche();
					r2 = route2->tabAffiche();
					temp.push_back(r1[j]);
				}
			}
			for (int j = 0; j < r2.size() - 1; j++)
			{
				if (r2[j].getVitesse() == 0 && r2[j + 1].getVitesse() == 0 && r1[j].getImatriculation() == -1 && r1[j + 1].getImatriculation() == -1 && !GestiRoute::voitureIn(r2[j], temp))
				{
					route2->enleverVoiture(r2[j].getImatriculation());
					route1->ajouterVoiture(r2[j], j + 1);

					r1 = route1->tabAffiche();
					r2 = route2->tabAffiche();
				}
			}
		}
	}
}

void GestiRoute::supprimeLiaison()
{
	for (int i = 0; i < liaisons.size(); i++) 
	{
		if (liaisons[i][0] == route_a_gerer)
		{
			//liaisons.erase(liaisons.begin() + i);
			liaisons.pop_back();
			//routes_liee.erase(routes_liee.begin() + liaisons[i][1]);
			routes_liee.pop_back();
		}
	}
}

vector<int> GestiRoute::routesLiee(int pos)
{
	vector<int> v;
	for (int i = 0; i < liaisons.size(); i++)
	{
		if (liaisons[i][0] == pos)
		{
			v.push_back(i);
		}
	}
	return v;
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
	// Plus + = 43
	// Moins - = 45

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
		if (position_curseur > 9)
		{
			position_curseur = 9;
		}
	}

	else if (clavier == 75 || clavier == 45)
	{
		if (position_curseur == 0)
		{
			if(routes.size() > 1)
			GestiRoute::supprimerRoute();
			if (clavier == 45)
			{
				if (routes.size() > 1)
				GestiRoute::supprimerRoute();
			}
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
			GestiRoute::enleverVoiture();
			if (clavier == 45)
			{
				for (int i = 0; i < 4; i++)
				{
					GestiRoute::enleverVoiture();
				}
			}
		}

		else if (position_curseur == 3)
		{
			GestiRoute::setProbaFrein(routes[route_a_gerer].getProbaFrein() - 1);

			if (clavier == 45)
			{
				GestiRoute::setProbaFrein(routes[route_a_gerer].getProbaFrein() - 9);
			}
		}

		else if (position_curseur == 4)
		{
			GestiRoute::setProbaResteArret(routes[route_a_gerer].getProbaResteArret() - 1);
			if (clavier == 45)
			{
				GestiRoute::setProbaResteArret(routes[route_a_gerer].getProbaResteArret() - 9);
			}
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
			GestiRoute::setTailleRoute(routes[route_a_gerer].getTailleRoute() - 1);
			if (clavier == 45)
			{
				GestiRoute::setTailleRoute(routes[route_a_gerer].getTailleRoute() - 4);
			}
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

			if (clavier == 45)
			{
				vitDeDefil -= 90;
			}

			if (vitDeDefil <= 0)
			{
				vitDeDefil = 10;
			}
		}
		else if (position_curseur == 9)
		{
			GestiRoute::supprimeLiaison();
		}
	}

	else if (clavier == 77 || clavier == 43)
	{

		if (position_curseur == 0)
		{
			GestiRoute::ajouterRoute(routes[0].getNbVoiture());
			if (clavier == 43)
			{
				GestiRoute::ajouterRoute(routes[0].getNbVoiture());
			}
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
			GestiRoute::ajouterVoiture();
			if (clavier == 43)
			{
				for (int i = 0; i < 4; i++)
				{
					GestiRoute::ajouterVoiture();;
				}
			}
		}

		else if (position_curseur == 3)
		{
			GestiRoute::setProbaFrein(routes[route_a_gerer].getProbaFrein() + 1);
			if (clavier == 43)
			{
				GestiRoute::setProbaFrein(routes[route_a_gerer].getProbaFrein() + 9);
			}
		}

		else if (position_curseur == 4)
		{
			GestiRoute::setProbaResteArret(routes[route_a_gerer].getProbaResteArret() + 1);
			if (clavier == 43)
			{
				GestiRoute::setProbaResteArret(routes[route_a_gerer].getProbaResteArret() + 9);
			}
		}

		else if (position_curseur == 5)
		{
			etape++;
		}

		else if (position_curseur == 6)
		{
			GestiRoute::setTailleRoute(routes[route_a_gerer].getTailleRoute() + 1);
			if (clavier == 43)
			{
				GestiRoute::setTailleRoute(routes[route_a_gerer].getTailleRoute() + 4);
			}
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
			if (clavier == 43)
			{
				vitDeDefil += 90;
			}
		}

		else if (position_curseur == 9)
		{
			GestiRoute::creerliaisonRoutes();
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
				route_a_afficher.append("[   ]");
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
		vector<int> a = GestiRoute::routesLiee(i);
		for(int k = 0; k < a.size(); k++)
		{
			route_a_afficher.append("\n");
			vector<Voiture> v = routes_liee[liaisons[a[k]][1]].tabAffiche();
			for (int j = 0; j < v.size(); j++)
			{
				if (v[j].getImatriculation() == -1)
				{
					route_a_afficher.append("[   ]");
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
	cout << "(" << GestiRoute::getNbVoiture() << ")  Nb voiture";
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

	if (position_curseur == 9)
		cout << "<[";
	cout << "(" << 0 << ")  Liaison";
	if (position_curseur == 9)
		cout << "]>";

	cout << endl;
}

void GestiRoute::plusEtape()
{
	for (int i = 0; i < routes.size(); i++)
	{
		routes[i].tempsPlus(etape, mode);
	}
	for (int i = 0; i < routes_liee.size(); i++)
	{
		routes_liee[i].tempsPlus(etape, mode);
	}
	GestiRoute::gestiLiaison();
}

int GestiRoute::vitesse()
{
	return vitDeDefil;
}

void GestiRoute::ajouterVoiture()
{
	vector<int> v = GestiRoute::routesLiee(route_a_gerer);
	if (v.size() == 0)
	{
		routes[route_a_gerer].ajouterVoiture();
	}
	else
	{
		vector<Voiture> totalVoiture = routes[route_a_gerer].getTabVoiture();
		for (int i = 0; i < v.size(); i++)
		{
			totalVoiture = totalVoiture + routes_liee[liaisons[v[i]][1]].getTabVoiture();
		}

		vector<int> immatri;
		for (int i = 0; i < totalVoiture.size(); i++)
		{
			immatri.push_back(totalVoiture[i].getImatriculation());
		}

		int a = 0;

		while (GestiRoute::intIn(a, immatri))
		{
			a++;
		}
		routes[route_a_gerer].ajouterVoiture(a);
	}
}

void GestiRoute::enleverVoiture()
{
	vector<int> v = GestiRoute::routesLiee(route_a_gerer);
	if (v.size() == 0)
	{
		if (routes[route_a_gerer].getNbVoiture() > 1)
		{
			routes[route_a_gerer].enleverVoiture();
		}
	}
	else
	{
		vector<Voiture> totalVoiture = routes[route_a_gerer].getTabVoiture();
		for (int i = 0; i < v.size(); i++)
		{
			totalVoiture = totalVoiture + routes_liee[liaisons[v[i]][1]].getTabVoiture();
		}

		if (totalVoiture.size() > 1)
		{
			int a = -1;
			for (int i = 0; i < v.size(); i++)
			{
				if (routes_liee[liaisons[v[i]][1]].getNbVoiture() > 1)
				{
					a = i;
				}
			}
			if (a != -1)
			{
				routes_liee[liaisons[v[a]][1]].enleverVoiture();
			}
			else
			{
				routes[route_a_gerer].enleverVoiture();
			}
		}
	}
}

int GestiRoute::getNbVoiture()
{
	vector<int> v = GestiRoute::routesLiee(route_a_gerer);
	vector<Voiture> totalVoiture = routes[route_a_gerer].getTabVoiture();
	for (int i = 0; i < v.size(); i++)
	{
		totalVoiture = totalVoiture + routes_liee[liaisons[v[i]][1]].getTabVoiture();
	}

	return totalVoiture.size();
}

void GestiRoute::setProbaFrein(int pourcent)
{
	vector<int> v = GestiRoute::routesLiee(route_a_gerer);
	for (int i = 0; i < v.size(); i++)
	{
		routes_liee[liaisons[v[i]][1]].setProbaFrein(pourcent);
	}
	routes[route_a_gerer].setProbaFrein(pourcent);
}

void GestiRoute::setProbaResteArret(int pourcent)
{
	vector<int> v = GestiRoute::routesLiee(route_a_gerer);
	for (int i = 0; i < v.size(); i++)
	{
		routes_liee[liaisons[v[i]][1]].setProbaResteArret(pourcent);
	}
	routes[route_a_gerer].setProbaResteArret(pourcent);
}

void GestiRoute::setTailleRoute(int taille)
{
	vector<int> v = GestiRoute::routesLiee(route_a_gerer);
	for (int i = 0; i < v.size(); i++)
	{
		routes_liee[liaisons[v[i]][1]].setTailleRoute(taille);
	}
	routes[route_a_gerer].setTailleRoute(taille);
}
