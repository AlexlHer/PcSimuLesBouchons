// --------------------------------
// Auteur : Alexandre l'Heritier
// PcSimuLesBouchons v1.0 : Classe GestiRoute
// --------------------------------

#include "GestiRoute.h"
#include <iostream>

using namespace std;

// Blocs permettant de faite des pauses ou des clear selon le system d'exploitation.
#ifdef _WIN32
	#define Clear system("cls")
	#define Pause system("pause.")
#else
	#define Clear system("clear")
	#define Pause system("read a")
#endif

/*
Operateur permettant d'additionner deux vectors de voiture.
@params Les deux vectors à assembler.
@return Le vector resultat.
*/
vector<Voiture> operator+(vector<Voiture> &a, vector<Voiture> &b)
{
	// On crée un vector qui sera returner.
	vector<Voiture> v;

	// Pour tous les éléments des deux vector, on met l'élément i dans v.
	for (int i = 0; i < a.size(); i++)
	{
		v.push_back(a[i]);
	}
	for (int i = 0; i < b.size(); i++)
	{
		v.push_back(b[i]);
	}

	// On retourne le vector v.
	return v;
}

/*
Méthode permettant de rechercher intt dans le vector dans.
@param intt l'entier à rechercher.
@param dans le vector dans lequel rechercher intt.
@return un booleen, true si intt est dans dans, false sinon.
*/
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

/*
Constructeur permettant d'initialiser un GestiRoute avec une route par défaut de nb_voiture voiture(s).
@param nb_voiture le nombre de voiture à mettre sur la route par défaut.
*/
GestiRoute::GestiRoute(int nb_voiture)
{
	// On construit une route avec nb_voiture voiture(s).
	Route r = Route(nb_voiture);

	// On l'ajoute dans le vector routes.
	routes.push_back(r);

	// On initialise les differantes variables.
	temps_attente = 1;
	route_a_gerer = 0;
	position_curseur = 0;
	etape = 1;
	mode = 0;
	vitDeDefil = 500;
	affichage_instruction = true;
	quit = false;
	mode_affichage = 0;
}

/*
Méthode permettant d'ajouter une route de la même taille que la route par défaut.
@param nb_voiture Le nombre de voiture à mettre sur la route.
*/
void GestiRoute::ajouterRoute(int nb_voiture)
{
	// On crée la route.
	Route r = Route(nb_voiture, routes[0].getTailleRoute());

	// On la met dans le vector routes.
	routes.push_back(r);
}

/*
Methode pour supprimer la dernière route du vector routes.
*/
void GestiRoute::supprimerRoute()
{
	routes.resize(routes.size() - 1);
}

/*
Méthode permettant de savoir si la voiture v est dans le vector dans.
@param v la voiture à rechercher dans dans.
@param dans le vector dans lequel rechercher la voiture v.
@return un booleen, true si v est dans dans, false sinon.
*/
bool GestiRoute::voitureIn(Voiture v, vector<Voiture> dans)
{
	// On parcours le vector dans pour trouver v.
	for (int i = 0; i < dans.size(); i++)
	{
		if (dans[i].getImatriculation() == v.getImatriculation() && dans[i].getVitesse() == v.getVitesse())
		{
			return true;
		}
	}
	return false;
}

/*
Méthode permettant de créer une liaison sur la route actuellement séléctionné.
*/
void GestiRoute::creerliaisonRoutes()
{
	// On crée une route avec aucune voiture et de la même taille que la route à laquelle il faut ajouter la liaison.
	Route r = Route(0, routes[route_a_gerer].getTailleRoute());

	// On ajoute la liaison au vector contenant toutes les liaisons.
	routes_liee.push_back(r);

	// On crée un vector int qui contiendera le lien entre les routes : {{position de la route principale dans routes, position de la route liée dans routes_liee}, {X, X}, ...}
	vector<int> v;

	// On met la position de la route et la position de la route liée.
	v.push_back(route_a_gerer);
	v.push_back(routes_liee.size() - 1);

	// On ajoute le vector lien dans le vector contenant tous les liens.
	liaisons.push_back(v);
}

/*
Méthode pour voir si certaines voitures peuvent aller sur les liaisons ou sur la route principale et les déplacer.
*/
void GestiRoute::gestiLiaison()
{
	// On prend deux voitures vides et deux routes vides.
	vector<Voiture> r1, r2;
	Route *route1, *route2;

	// Pour toutes les routes du vector routes.
	for (int i = 0; i < routes.size(); i++)
	{
		// On prend toutes les positions des liaisons de la route i du vector liaisons que l'on met dans v.
		vector<int> v = GestiRoute::routesLiee(i);

		// Pour toutes les liaisons de i dans v.
		for (int k = 0; k < v.size(); k++)
		{
			// Si nous avons plusieurs liaisons, les voitures doivent se déplacer sur les liaisons d'à coté.
			// Donc si k = 0, on fait route <-> 1ere liaison.
			if (k == 0)
			{
				r1 = routes[liaisons[v[0]][0]].tabAffiche();
				r2 = routes_liee[liaisons[v[0]][1]].tabAffiche();
				route1 = &routes[liaisons[v[0]][0]];
				route2 = &routes_liee[liaisons[v[0]][1]];
			}
			
			// Et puis n eme liaison <-> n+1 eme liaison.
			else
			{
				r1 = routes_liee[liaisons[v[k-1]][1]].tabAffiche();
				r2 = routes_liee[liaisons[v[k]][1]].tabAffiche();
				route1 = &routes_liee[liaisons[v[k-1]][1]];
				route2 = &routes_liee[liaisons[v[k]][1]];
			}
			// On crée un vector qui contiendera toutes les voitures qui se sont déjà déplacer pour éviter de les redéplacer.
			vector<Voiture> temp;

			// Pour toutes les voitures de route r1 (on peux faire toutes les voitures, même les vides car les vides ont une vitesse de -1).
			for (int j = 0; j < r1.size() - 1; j++)
			{
				// On verifie si notre voiture est arreté, celle de devant est aussi arreté, la case d'à coté est vide et celle de devant est vide.
				if (r1[j].getVitesse() == 0 && r1[j + 1].getVitesse() == 0 && r2[j].getImatriculation() == -1 && r2[j + 1].getImatriculation() == -1)
				{
					// Si c'est le cas, on enleve la voiture et on la place à coté, une case plus haute (en diagonale).
					route1->enleverVoiture(r1[j].getImatriculation());
					route2->ajouterVoiture(r1[j], j + 1);

					// On actualise r1 et r2.
					r1 = route1->tabAffiche();
					r2 = route2->tabAffiche();

					// On met la voiture déplacé dans le vector pour pas la redéplacer.
					temp.push_back(r1[j]);
				}
			}
			// Pour toutes les voitures de route r2 (on peux faire toutes les voitures, même les vides car les vides ont une vitesse de -1).
			for (int j = 0; j < r2.size() - 1; j++)
			{
				// On verifie si notre voiture est arreté, celle de devant est aussi arreté, la case d'à coté est vide et celle de devant est vide.
				if (r2[j].getVitesse() == 0 && r2[j + 1].getVitesse() == 0 && r1[j].getImatriculation() == -1 && r1[j + 1].getImatriculation() == -1 && !GestiRoute::voitureIn(r2[j], temp))
				{
					// Si c'est le cas, on enleve la voiture et on la place à coté, une case plus haute (en diagonale).
					route2->enleverVoiture(r2[j].getImatriculation());
					route1->ajouterVoiture(r2[j], j + 1);

					// On actualise r1 et r2.
					r1 = route1->tabAffiche();
					r2 = route2->tabAffiche();
				}
			}
		}
	}
}

/*
Méthode pour supprimer une liaison de la route séléctionnée.
*/
void GestiRoute::supprimeLiaison()
{
	// Pour tous les éléments de liaisons.
	for (int i = 0; i < liaisons.size(); i++) 
	{
		// 
		if (liaisons[i][0] == route_a_gerer)
		{
			routes_liee.erase(routes_liee.begin() + liaisons[i][1]);
			liaisons.erase(liaisons.begin() + i);
		}
	}
}

/*
Méthode pour donner toutes les liaisons de la route pos.
*/
vector<int> GestiRoute::routesLiee(int pos)
{
	// Vector qui sera retourner et qui contiendera les positions des liens dans liaisons.
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

/*
Méthode permettant de déterminer l'effet de la touche clavier.
@param clavier la touche de clavier sur laquelle on appuie.
*/
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

	// Si on appuie sur N.
	if (clavier == 'n' || clavier == 'N')
	{
		// On change affichage_instruction.
		if (affichage_instruction)
			affichage_instruction = false;
		else
			affichage_instruction = true;
	}

	// Si on appuie sur A.
	if (clavier == 'a' || clavier == 'A')
		GestiRoute::help();

	// Si on appuie sur Q.
	if (clavier == 'q' || clavier == 'Q')
		quit = true;

	// Si on appuie sur Espace.
	else if (clavier == 32)
	{
		// Si le programme n'est pas sur pause.
		if(etape_temp == 0)
		{
			// On save les valeurs actuel et on met sur pause.
			etape_temp = etape;
			etape = 0;
			vitDeDefil_temp = vitDeDefil;
			vitDeDefil = 9999;
		}
		else
		{
			// On remet en normal.
			etape = etape_temp;
			etape_temp = 0;
			vitDeDefil = vitDeDefil_temp;
			vitDeDefil_temp = 0;
		}

	}

	// Si on appuie sur Haut.
	if (clavier == 72)
	{
		// On change la position du curseur.
		position_curseur--;
		if (position_curseur < 0)
		{
			position_curseur = 0;
		}
	}

	// Si on appuie sur Bas.
	else if (clavier == 80)
	{
		// On change la position du curseur.
		position_curseur++;
		if (position_curseur > 11)
		{
			position_curseur = 11;
		}
	}

	// Si on appuie sur Gauche ou Moins.
	else if (clavier == 75 || clavier == 45)
	{
		// Si le curseur est en position 0.
		if (position_curseur == 0)
		{
			// Si on appuie sur Gauche, on supprime une route, si on appuie sur Moins, deux routes.
			if(routes.size() > 1)
				GestiRoute::supprimerRoute();

			if (clavier == 45)
			{
				if (routes.size() > 1)
				GestiRoute::supprimerRoute();
			}
			// On évite que la route séléctionnée soit celle supprimée, pour éviter les bugs.
			if (route_a_gerer == routes.size())
				route_a_gerer--;
		}

		// Si le curseur est en position 1.
		else if (position_curseur == 1)
		{
			// Si on appuie sur Gauche ou sur Moins, on change de route à gérer.
			route_a_gerer--;
			if (route_a_gerer < 0)
			{
				route_a_gerer = 0;
			}
		}

		// Si le curseur est en position 2.
		else if (position_curseur == 2)
		{
			// Si on appuie sur Gauche, on enleve une route, si on appuie sur Moins, on en enleve 5.
			GestiRoute::enleverVoiture();
			if (clavier == 45)
			{
				for (int i = 0; i < 4; i++)
				{
					GestiRoute::enleverVoiture();
				}
			}
		}

		// Si le curseur est en position 3.
		else if (position_curseur == 3)
		{
			// Si on appuie sur Gauche, on fait -1 à la proba de freinage, si on appuie sur Moins, on fait -10.
			GestiRoute::setProbaFrein(routes[route_a_gerer].getProbaFrein() - 1);

			if (clavier == 45)
			{
				GestiRoute::setProbaFrein(routes[route_a_gerer].getProbaFrein() - 9);
			}
		}

		// Si le curseur est en position 4.
		else if (position_curseur == 4)
		{
			// Si on appuie sur Gauche, on fait -1 à la proba de redemarrage, si on appuie sur Moins, on fait -10.
			GestiRoute::setProbaResteArret(routes[route_a_gerer].getProbaResteArret() - 1);
			if (clavier == 45)
			{
				GestiRoute::setProbaResteArret(routes[route_a_gerer].getProbaResteArret() - 9);
			}
			mode = 1;
		}

		// Si le curseur est en position 5.
		else if (position_curseur == 5)
		{
			// Si on fait Gauche ou Moins, on enleve une étape.
			etape--;
			if (etape < 0)
			{
				etape = 0;
			}
		}

		// Si le curseur est en position 6.
		else if (position_curseur == 6)
		{
			// Si on appuie sur Gauche, on fait -1 à la taille route, si on appuie sur Moins, on fait -5.
			GestiRoute::setTailleRoute(routes[route_a_gerer].getTailleRoute() - 1);
			if (clavier == 45)
			{
				GestiRoute::setTailleRoute(routes[route_a_gerer].getTailleRoute() - 4);
			}
		}

		// Si le curseur est en position 7.
		else if (position_curseur == 7)
		{
			// Si on fait Gauche ou Moins, on change de mode.
			mode--;
			if (mode < 0)
			{
				mode = 0;
			}
		}

		// Si le curseur est en position 8.
		else if (position_curseur == 8)
		{
			// Si on fait Gauche, on fait -10 ms, si on fait Moins, on fait -100 ms.
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

		// Si le curseur est en position 9.
		else if (position_curseur == 9)
		{
			// On supprime une liaison.
			GestiRoute::supprimeLiaison();
		}

		else if (position_curseur == 10)
		{
			GestiRoute::setLimiteVitesse(routes[route_a_gerer].getLimiteVitesse() - 1);
			if (clavier == 45)
			{
				GestiRoute::setLimiteVitesse(routes[route_a_gerer].getLimiteVitesse() - 4);
			}
		}
		else if (position_curseur == 11)
		{
			mode_affichage--;
			if (mode_affichage < 0)
				mode_affichage = 0;
		}
	}

	// Si on appuie sur Droite ou Plus.
	else if (clavier == 77 || clavier == 43)
	{

		// Si le curseur est en position 0.
		if (position_curseur == 0)
		{
			// Si on appuie sur Droite, on ajoute une route, si on appuie sur Plus, deux routes.
			GestiRoute::ajouterRoute(routes[0].getNbVoiture());
			if (clavier == 43)
			{
				GestiRoute::ajouterRoute(routes[0].getNbVoiture());
			}
		}

		// Si le curseur est en position 1.
		else if (position_curseur == 1)
		{
			// Si on appuie sur Droite ou sur Plus, on change de route à gérer.
			route_a_gerer++;
			if (route_a_gerer >= routes.size())
			{
				route_a_gerer = routes.size()-1;
			}
		}

		// Si le curseur est en position 2.
		else if (position_curseur == 2)
		{
			// Si on appuie sur Droite, on ajoute une route, si on appuie sur Plus, on en ajoute 5.
			GestiRoute::ajouterVoiture();
			if (clavier == 43)
			{
				for (int i = 0; i < 4; i++)
				{
					GestiRoute::ajouterVoiture();;
				}
			}
		}

		// Si le curseur est en position 3.
		else if (position_curseur == 3)
		{
			// Si on appuie sur Droite, on fait +1 à la proba de freinage, si on appuie sur Plus, on fait +10.
			GestiRoute::setProbaFrein(routes[route_a_gerer].getProbaFrein() + 1);
			if (clavier == 43)
			{
				GestiRoute::setProbaFrein(routes[route_a_gerer].getProbaFrein() + 9);
			}
		}

		// Si le curseur est en position 4.
		else if (position_curseur == 4)
		{
			// Si on appuie sur Droite, on fait +1 à la proba de redemarrage, si on appuie sur Plus, on fait +10.
			GestiRoute::setProbaResteArret(routes[route_a_gerer].getProbaResteArret() + 1);
			if (clavier == 43)
			{
				GestiRoute::setProbaResteArret(routes[route_a_gerer].getProbaResteArret() + 9);
			}
			mode = 1;
		}

		// Si le curseur est en position 5.
		else if (position_curseur == 5)
		{
			// Si on fait Droite ou Plus, on ajoute une étape.
			etape++;
		}

		// Si le curseur est en position 6.
		else if (position_curseur == 6)
		{
			// Si on appuie sur Droite, on fait +1 à la taille route, si on appuie sur Plus, on fait +5.
			GestiRoute::setTailleRoute(routes[route_a_gerer].getTailleRoute() + 1);
			if (clavier == 43)
			{
				GestiRoute::setTailleRoute(routes[route_a_gerer].getTailleRoute() + 4);
			}
		}

		// Si le curseur est en position 7.
		else if (position_curseur == 7)
		{
			// Si on fait Droite ou Plus, on change de mode.
			mode++;
			if (mode > 1)
			{
				mode = 1;
			}
		}

		// Si le curseur est en position 8.
		else if (position_curseur == 8)
		{
			// Si on fait Droite, on fait +10 ms, si on fait Plus, on fait +100 ms.
			vitDeDefil += 10;
			if (clavier == 43)
			{
				vitDeDefil += 90;
			}
		}

		// Si le curseur est en position 9.
		else if (position_curseur == 9)
		{
			// On ajoute une liaison.
			GestiRoute::creerliaisonRoutes();
		}

		else if (position_curseur == 10)
		{
			GestiRoute::setLimiteVitesse(routes[route_a_gerer].getLimiteVitesse() + 1);
			if (clavier == 43)
			{
				GestiRoute::setLimiteVitesse(routes[route_a_gerer].getLimiteVitesse() + 4);
			}
		}

		else if (position_curseur == 11)
		{
			mode_affichage++;
			if (mode_affichage > 2)
				mode_affichage = 2;
		}
	}
}

/*
Méthode permettant l'affichage des routes et des liaisons.
*/
string GestiRoute::affichageRoutes()
{
	// Variable temp qui permet de stocker l'immatriculation avec ou sans le 0 derrière.
	string temp = "";

	// Variable qui contiendera le texte à afficher.
	string route_a_afficher = "";

	// Pour toutes les routes.
	for (int i = 0; i < routes.size(); i++)
	{
		// On stocke la route à afficher.
		vector<Voiture> v = routes[i].tabAffiche();

		// Pour toutes les places de la route.
		for (int j = 0; j < v.size(); j++)
		{
			// Si la place est occupé par une voiture vide, on fait une case vide.
			if (v[j].getImatriculation() == -1)
			{
				if(mode_affichage == 0)
					route_a_afficher.append("[    ]");
				else if (mode_affichage == 1)
					route_a_afficher.append("[ ]");
				else
					route_a_afficher.append("[  ]");
			}

			// Sinon on écrit une voiture avec immatriculation et vitesse.
			else
			{
				temp = "";
				route_a_afficher.append("[");

				if (mode_affichage == 0 || mode_affichage == 2)
				{
					if (v[j].getImatriculation() <= 9)
						temp += "0";
					temp += to_string(v[j].getImatriculation());
					route_a_afficher.append(temp);
					if (mode_affichage == 0)
						route_a_afficher.append(";");
				}
				if (mode_affichage == 0 || mode_affichage == 1)
				{
					route_a_afficher.append(to_string(v[j].getVitesse()));
				}
				route_a_afficher.append("]");
			}
		}

		// On crée un vector avec tous les emplacements des liaisons de la route, dans le vector routes_liee.
		vector<int> a = GestiRoute::routesLiee(i);

		// Pour toutes les liaisons de la route i.
		for(int k = 0; k < a.size(); k++)
		{
			// On fait un retour à la ligne après la route ou les liaisons.
			route_a_afficher.append("\n");

			// On prend la a eme route liee.
			vector<Voiture> v = routes_liee[liaisons[a[k]][1]].tabAffiche();

			// Pour toutes les places de la route.
			for (int j = 0; j < v.size(); j++)
			{
				if (v[j].getImatriculation() == -1)
				{
					if (mode_affichage == 0)
						route_a_afficher.append("[    ]");
					else if (mode_affichage == 1)
						route_a_afficher.append("[ ]");
					else
						route_a_afficher.append("[  ]");
				}
				else
				{
					temp = "";
					route_a_afficher.append("[");

					if (mode_affichage == 0 || mode_affichage == 2)
					{
						if (v[j].getImatriculation() <= 9)
							temp += "0";
						temp += to_string(v[j].getImatriculation());
						route_a_afficher.append(temp);
						if (mode_affichage == 0)
							route_a_afficher.append(";");
					}
					if (mode_affichage == 0 || mode_affichage == 1)
					{
						route_a_afficher.append(to_string(v[j].getVitesse()));
					}
					route_a_afficher.append("]");
				}
			}
		}
		// On sépare les routes.
		route_a_afficher.append("\n");
		route_a_afficher.append("--------------------------------------------------------");
		route_a_afficher.append("\n");
	}
	return route_a_afficher;
}

/*
Méthode permettant de déterminer le nombre d'espaces selon le nombre de chiffres de chiffre et du nombre d'espace demandé.
@param nb_espace Le nombre d'espace demandé.
@param chiffre Le chiffre à analiser.
@return Les espaces à afficher.
*/
string GestiRoute::nbEspaceAffichage(int nb_espace, int chiffre)
{
	// La chaine de caractère qui sera renvoyée.
	string fin = "";

	// Selon le nombre de chiffre dans chiffre, on enleve des espaces dans nb_espace.
	if (chiffre <= 9)
		nb_espace -= 0;
	else if (chiffre <= 99)
		nb_espace -= 1;
	else if (chiffre <= 999)
		nb_espace -= 2;
	else if (chiffre <= 9999)
		nb_espace -= 3;
	else if (chiffre <= 99999)
		nb_espace -= 4;
	else if (chiffre <= 999999)
		nb_espace -= 5;
	else if (chiffre <= 9999999)
		nb_espace -= 6;

	// On crée la chaine de caractère avec le nombre d'espace restant.
	for (int i = 0; i < nb_espace; i++)
		fin += " ";
	
	return fin;
}

/*
Méthode permettant d'afficher les routes et les commandes.
*/
void GestiRoute::sortieAffichage()
{
	// On initialise le nombre d'espace maximum que l'on veux et temp qui permettera de déterminer le nombre d'espace.
	int nb_espaces = 10, temp = 0;

	// On affiche les premières infos.
	cout << "   ----------------------" << endl << "   PcSimuLesBouchons v1.0" << endl << "   ----------------------" << endl;
	cout << "--------------------------------------------------------" << endl;

	// On affiche les routes.
	cout << GestiRoute::affichageRoutes() << endl;

	cout << endl;

	// Si on demande d'afficher les instructions ou pas.
	if(affichage_instruction)
		cout << "Utilisez les fleches directionnelles pour modifier les parametres." << endl << endl;

	// Si on est sur le curseur.
	if (position_curseur == 0)
		cout << "<[(";
	else
		cout << "  (";

	// On affiche l'info.
	temp = routes.size();
	cout << temp;

	// Si on est sur le curseur.
	if (position_curseur == 0)
		cout << ")]>";
	else
		cout << ")  ";

	// On affiche la correspondance.
	cout << GestiRoute::nbEspaceAffichage(nb_espaces, temp) << "Nombre(s) de route(s)";

	cout << endl;

	if (position_curseur == 1)
		cout << "<[(";
	else
		cout << "  (";

	temp = route_a_gerer+1;
	cout << temp;

	if (position_curseur == 1)
		cout << ")]>";
	else
		cout << ")  ";

	cout << GestiRoute::nbEspaceAffichage(nb_espaces, temp) << "Numero de route a gerer";

	cout << endl;

	if (position_curseur == 2)
		cout << "<[(";
	else
		cout << "  (";

	temp = GestiRoute::getNbVoiture();
	cout << temp;

	if (position_curseur == 2)
		cout << ")]>";
	else
		cout << ")  ";

	cout << GestiRoute::nbEspaceAffichage(nb_espaces, temp) << "Nombre(s) de voiture(s) sur la route";

	cout << endl;

	if (position_curseur == 3)
		cout << "<[(";
	else
		cout << "  (";

	temp = routes[route_a_gerer].getProbaFrein();
	cout << temp;

	if (position_curseur == 3)
		cout << ")]>";
	else
		cout << ")  ";

	cout << GestiRoute::nbEspaceAffichage(nb_espaces, temp) << "Probabilite de freinage";

	cout << endl;

	if (position_curseur == 4)
		cout << "<[(";
	else
		cout << "  (";

	temp = routes[route_a_gerer].getProbaResteArret();
	cout << temp;

	if (position_curseur == 4)
		cout << ")]>";
	else
		cout << ")  ";

	cout << GestiRoute::nbEspaceAffichage(nb_espaces, temp) << "Probabilite de redemarrage";

	cout << endl;

	if (position_curseur == 5)
		cout << "<[(";
	else
		cout << "  (";

	temp = etape;
	cout << temp;

	if (position_curseur == 5)
		cout << ")]>";
	else
		cout << ")  ";

	cout << GestiRoute::nbEspaceAffichage(nb_espaces, temp) << "Nombre d'etape a chaque affichage";

	cout << endl;

	if (position_curseur == 6)
		cout << "<[(";
	else
		cout << "  (";

	temp = routes[route_a_gerer].getTailleRoute();
	cout << temp;

	if (position_curseur == 6)
		cout << ")]>";
	else
		cout << ")  ";

	cout << GestiRoute::nbEspaceAffichage(nb_espaces, temp) << "Taille de la route";

	cout << endl;

	if (position_curseur == 7)
		cout << "<[(";
	else
		cout << "  (";

	cout << (mode == 0 ? "Nash" : "VDR");

	if (position_curseur == 7)
		cout << ")]>";
	else
		cout << ")  ";

	cout << GestiRoute::nbEspaceAffichage(nb_espaces, (mode == 0 ? 1000 : 100)) << "Mode";

	cout << endl;

	if (position_curseur == 8)
		cout << "<[(";
	else
		cout << "  (";

	temp = vitDeDefil;
	cout << temp;

	if (position_curseur == 8)
		cout << ")]>";
	else
		cout << ")  ";

	cout << GestiRoute::nbEspaceAffichage(nb_espaces, temp) << "Vitesse de defilement";

	cout << endl;

	if (position_curseur == 9)
		cout << "<[(";
	else
		cout << "  (";

	temp = GestiRoute::routesLiee(route_a_gerer).size();
	cout << temp;

	if (position_curseur == 9)
		cout << ")]>";
	else
		cout << ")  ";

	cout << GestiRoute::nbEspaceAffichage(nb_espaces, temp) << "Nombre de liaisons";

	cout << endl;

	if (position_curseur == 10)
		cout << "<[(";
	else
		cout << "  (";

	temp = routes[route_a_gerer].getLimiteVitesse();
	cout << temp;

	if (position_curseur == 10)
		cout << ")]>";
	else
		cout << ")  ";

	cout << GestiRoute::nbEspaceAffichage(nb_espaces, temp) << "Limite de vitesse";

	cout << endl;

	if (position_curseur == 11)
		cout << "<[(";
	else
		cout << "  (";

	cout << (mode_affichage == 0 ? "Im/Vi" : mode_affichage == 1 ? "Vitesse" : "Immatri");

	if (position_curseur == 11)
		cout << ")]>";
	else
		cout << ")  ";

	cout << GestiRoute::nbEspaceAffichage(nb_espaces, (mode_affichage == 0 ? 10000 : 1000000)) << "Mode d'affichage";

	cout << endl;
	if (affichage_instruction)
	{
		cout << endl;
		cout << "Appuyer sur \"Espace\" pour mettre en pause la simulation." << endl << "Appuyer sur \"A\" pour afficher l'aide." << endl;
		cout << "Appuyer sur \"N\" pour masquer/afficher les instructions." << endl << "Appuyer sur \"Q\" pour quitter" << endl;
	}

}

/*
Méthode permettant d'avancer les routes et les liaisons.
*/
void GestiRoute::plusEtape()
{
	// On avance les routes etape fois.
	for (int i = 0; i < routes.size(); i++)
	{
		routes[i].tempsPlus(etape, mode);
	}

	// On avance les routes_liee etape fois.
	for (int i = 0; i < routes_liee.size(); i++)
	{
		routes_liee[i].tempsPlus(etape, mode);
	}
	// On gere les dépassements sur d'autres voies.
	GestiRoute::gestiLiaison();
}

/*
Accesseur retournant la vitesse de défilement.
@return La vitesse.
*/
int GestiRoute::vitesse()
{
	return vitDeDefil;
}

/*
Méthode permettant d'ajouter une voiture en prenant en compte les liaisons.
*/
void GestiRoute::ajouterVoiture()
{
	// On prend toutes les positions des liaisons de route_a_gerer.
	vector<int> v = GestiRoute::routesLiee(route_a_gerer);

	// Si il n'y a pas de liaisons, on n'a pas besoin de plus de tests.
	if (v.size() == 0)
	{
		routes[route_a_gerer].ajouterVoiture();
	}

	// Sinon.
	else
	{
		// On crée un vector contenant toutes les voitures sur toutes les liaisons ainsi que la route.
		vector<Voiture> totalVoiture = routes[route_a_gerer].getTabVoiture();
		for (int i = 0; i < v.size(); i++)
		{
			totalVoiture = totalVoiture + routes_liee[liaisons[v[i]][1]].getTabVoiture();
		}

		// On récupere toutes les immatriculations des voitures.
		vector<int> immatri;
		for (int i = 0; i < totalVoiture.size(); i++)
		{
			immatri.push_back(totalVoiture[i].getImatriculation());
		}

		// On prend la premiere immatriculation libre.
		int a = 0;

		while (GestiRoute::intIn(a, immatri))
		{
			a++;
		}

		// On ajoute la voiture avec l'immatriculation libre.
		routes[route_a_gerer].ajouterVoiture(a);
	}
}

/*
Méthode permettant d'enlever une voiture en prenant en compte les liaisons.
*/
void GestiRoute::enleverVoiture()
{
	// On prend toutes les positions des liaisons de route_a_gerer.
	vector<int> v = GestiRoute::routesLiee(route_a_gerer);

	// Si il n'y a pas de liaisons, on n'a pas besoin de plus de tests.
	if (v.size() == 0)
	{
		if (routes[route_a_gerer].getNbVoiture() > 1)
		{
			routes[route_a_gerer].enleverVoiture();
		}
	}
	else
	{
		// On crée un vector contenant toutes les voitures sur toutes les liaisons ainsi que la route.
		vector<Voiture> totalVoiture = routes[route_a_gerer].getTabVoiture();
		for (int i = 0; i < v.size(); i++)
		{
			totalVoiture = totalVoiture + routes_liee[liaisons[v[i]][1]].getTabVoiture();
		}

		// Si il y a plus d'une voiture.
		if (totalVoiture.size() > 1)
		{
			// On regarde si il y a des voitures sur les liaisons et si oui, on garde la position de la liaisons.
			int a = -1;

			// Pour toutes les liaisons.
			for (int i = 0; i < v.size(); i++)
			{
				// On prend la dernière liaisons avec plus d'une voiture.
				if (routes_liee[liaisons[v[i]][1]].getNbVoiture() > 1)
				{
					a = i;
				}
			}
			// On enleve d'abord les voitures sur les liaisons.
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

/*
Méthode pour afficher l'aide.
*/
void GestiRoute::help()
{
	Clear;
	cout << "   -------------------------" << endl;
	cout << "   PcSimuLesBouchons (PcSLB)" << endl;
	cout << "     Alexandre l'Heritier   " << endl;
	cout << "   -------------------------" << endl;
	cout << endl;
	cout << "Bienvenue dans PcSLB, programme cree pour le second semestre de L1 MPI." << endl;
	cout << "Le but de ce programme est de simuler une route que l'on peut controler." << endl;
	cout << "La route est representee avec des crochets comme ceci : [   ][   ][   ]." << endl;
	cout << "Une voiture est represente comme ceci : [X;Y]" << endl;
	cout << "X etant son immatriculation unique et Y sa vitesse." << endl;
	cout << "Les routes sont separees avec cela : -----------------------------------." << endl;
	cout << "Les liaisons des routes ne sont pas separées pour representer une route" << endl;
	cout << "a plusieurs voies." << endl;
	cout << "Bon jeu !" << endl;
	Pause;
}

/*
Accesseur renvoyant quit.
@return true si on veut quitter le programme.
*/
bool GestiRoute::getQuit()
{
	return quit;
}

/*
Méthode permettant d'avoir le nombre de voiture sur une route avec ses liaisons.
@return Le nombre de voiture.
*/
int GestiRoute::getNbVoiture()
{
	// On prend toutes les positions des routes liee.
	vector<int> v = GestiRoute::routesLiee(route_a_gerer);

	// On prend toutes les voitures de la routes.
	vector<Voiture> totalVoiture = routes[route_a_gerer].getTabVoiture();
	for (int i = 0; i < v.size(); i++)
	{
		totalVoiture = totalVoiture + routes_liee[liaisons[v[i]][1]].getTabVoiture();
	}

	return totalVoiture.size();
}

/*
Méthode permettant de mettre une proba sur la route et ses liaisons.
@param Le nouveau pourcentage.
*/
void GestiRoute::setProbaFrein(int pourcent)
{
	vector<int> v = GestiRoute::routesLiee(route_a_gerer);
	for (int i = 0; i < v.size(); i++)
	{
		routes_liee[liaisons[v[i]][1]].setProbaFrein(pourcent);
	}
	routes[route_a_gerer].setProbaFrein(pourcent);
}

/*
Méthode permettant de mettre une proba sur la route et ses liaisons.
@param Le nouveau pourcentage.
*/
void GestiRoute::setProbaResteArret(int pourcent)
{
	vector<int> v = GestiRoute::routesLiee(route_a_gerer);
	for (int i = 0; i < v.size(); i++)
	{
		routes_liee[liaisons[v[i]][1]].setProbaResteArret(pourcent);
	}
	routes[route_a_gerer].setProbaResteArret(pourcent);
}

/*
Méthode permettant de mettre une taille de route sur la route et ses liaisons.
@param La nouvelle taille.
*/
void GestiRoute::setTailleRoute(int taille)
{
	vector<int> v = GestiRoute::routesLiee(route_a_gerer);
	for (int i = 0; i < v.size(); i++)
	{
		routes_liee[liaisons[v[i]][1]].setTailleRoute(taille);
	}
	routes[route_a_gerer].setTailleRoute(taille);
}

/*
Méthode permettant de modifier la limite de vitesse pour la route et ses liaisons.
*/
void GestiRoute::setLimiteVitesse(int vit)
{
	vector<int> v = GestiRoute::routesLiee(route_a_gerer);
	for (int i = 0; i < v.size(); i++)
	{
		routes_liee[liaisons[v[i]][1]].setLimiteVitesse(vit);
	}
	routes[route_a_gerer].setLimiteVitesse(vit);
}

/*
Accesseur qui retourne le nombre de route.
@return le nombre de route.
*/
int GestiRoute::getNbRoutes()
{
	return routes.size();
}
