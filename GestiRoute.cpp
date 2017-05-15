// --------------------------------
// Auteur : Alexandre l'Heritier
// PcSimuLesBouchons v4.0 : Classe GestiRoute
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
vector<Voiture> operator+(vector<Voiture> const& a9, vector<Voiture> const& b8)
{
	// On crée un vector qui sera returner.
	vector<Voiture> v;

	// Pour tous les éléments des deux vector, on met l'élément i dans v.
	for (int i = 0; i < a9.size(); i++)
	{
		v.push_back(a9[i]);
	}
	for (int i = 0; i < b8.size(); i++)
	{
		v.push_back(b8[i]);
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
	// On initialise l'aléatoire.
	srand(time(NULL));

	// On construit une route avec nb_voiture voiture(s).
	Route r = Route(nb_voiture);

	// On l'ajoute dans le vector routes.
	routes.push_back(r);

	// On initialise les differantes variables.
	route_a_gerer = 0;
	position_curseur = 0;
	etape = 1;
	mode = 0;
	vitDeDefil = 500;
	affichage_instruction = true;
	quit = false;
	mode_affichage = 0;
	nb_rembobinage = 10;
	cb_de_rembobinage = 0;
	etape_temp = 0;
	vitDeDefil_temp = 0;
	pause = false;
	// Pour que les commandes s'affiche.
	appuie_touche = true;
	masquer_commandes = false;
	probaDepassement = 50;
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
	int espace_avant;

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
				r1 = routes_liee[liaisons[v[k - 1]][1]].tabAffiche();
				r2 = routes_liee[liaisons[v[k]][1]].tabAffiche();
				route1 = &routes_liee[liaisons[v[k - 1]][1]];
				route2 = &routes_liee[liaisons[v[k]][1]];
			}
			// On crée un vector qui contiendera toutes les voitures qui se sont déjà déplacer pour éviter de les redéplacer.
			vector<Voiture> temp;

			// Pour toutes les voitures de route r1 (on peux faire toutes les voitures, même les vides car les vides ont une vitesse de -1).
			for (int j = 0; j < r1.size() - 1; j++)
			{
				// Espace avant entre notre voiture et la voiture suivante.
				espace_avant = route1->espaceAvant(r1[j].getImatriculation());

				// On verifie si notre voiture est plus rapide que l'espace avant, si la vitesse de la voiture suivante est inferieur a la vitesse de notre voiture, si la case d'à coté est vide et celle de devant est vide.
				if (((r1[j].getVitesse() >= espace_avant && r1[j].getVitesse() >= r1[espace_avant + 1].getVitesse())
					||
					(r1[j].getVitesse() == 0 && r1[j + 1].getVitesse() == 0)) && r2[j].getImatriculation() == -1 &&
					r2[j + 1].getImatriculation() == -1 && GestiRoute::determineDepassement())
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
				// Espace avant entre notre voiture et la voiture suivante.
				espace_avant = route2->espaceAvant(r2[j].getImatriculation());

				// On verifie si notre voiture est plus rapide que l'espace avant, si la vitesse de la voiture suivante est inferieur a la vitesse de notre voiture, si case d'à coté est vide et celle de devant est vide.
				if (((r2[j].getVitesse() > espace_avant && r2[j].getVitesse() > r2[espace_avant + 1].getVitesse())
					||
					(r1[j].getVitesse() == 0 && r1[j + 1].getVitesse() == 0)) && r1[j].getImatriculation() == -1 &&
					r1[j + 1].getImatriculation() == -1 && !GestiRoute::voitureIn(r2[j], temp) && GestiRoute::determineDepassement())
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
	vector<int> toutes_liaisons = GestiRoute::routesLiee(route_a_gerer);
	int pos_a_suppr = toutes_liaisons[toutes_liaisons.size() - 1];

	routes_liee.erase(routes_liee.begin() + liaisons[pos_a_suppr][1]);
	liaisons.erase(liaisons.begin() + pos_a_suppr);
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
	// Début = 71
	// Fin = 79

	appuie_touche = true;
	masquer_commandes = false;

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
	else if (clavier == 'a' || clavier == 'A')
	{
		Clear;
		cout << GestiRoute::help();
		Pause;
	}

	// Si on appuie sur Q.
	else if (clavier == 'q' || clavier == 'Q')
		quit = true;

	else if (clavier == 'c' || clavier == 'C')
		masquer_commandes = true;

	// Si on appuie sur Espace.
	else if (clavier == 32)
	{
		// Si le programme n'est pas sur pause.
		if (!pause)
		{
			// On save les valeurs actuel et on met sur pause.
			etape_temp = etape;
			etape = 0;
			vitDeDefil_temp = vitDeDefil;
			vitDeDefil = 9999;
			pause = true;
		}
		else
		{
			// On remet en normal.
			etape = etape_temp;
			etape_temp = 0;
			vitDeDefil = vitDeDefil_temp;
			vitDeDefil_temp = 0;
			pause = false;

			cb_de_rembobinage = 0;
			GestiRoute::enleverRembobinage();
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

	// Si on appuie sur Début.
	else if (clavier == 71)
	{
		position_curseur = 0;
	}

	// Si on appuie sur Fin.
	else if (clavier == 79)
	{
		position_curseur = (pause ? 13 : 12);
	}

	// Si on appuie sur Bas.
	else if (clavier == 80)
	{
		// On change la position du curseur.
		position_curseur++;
		if (position_curseur > (pause ? 14 : 13))
		{
			position_curseur = (pause ? 14 : 13);
		}
	}

	// Si on appuie sur Gauche ou Moins.
	else if (clavier == 75 || clavier == 45)
	{
		// Si le curseur est en position 0.
		if (position_curseur == 0)
		{
			// Si on appuie sur Gauche, on supprime une route, si on appuie sur Moins, deux routes.
			if (routes.size() > 1)
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

		// Si le curseur est en position 4.
		else if (position_curseur == 4)
		{
			// Si on appuie sur Gauche, on fait -1 à la proba de freinage, si on appuie sur Moins, on fait -10.
			GestiRoute::setProbaFrein(routes[route_a_gerer].getProbaFrein() - 1);

			if (clavier == 45)
			{
				GestiRoute::setProbaFrein(routes[route_a_gerer].getProbaFrein() - 9);
			}
		}

		// Si le curseur est en position 5.
		else if (position_curseur == 5)
		{
			// Si on appuie sur Gauche, on fait -1 à la proba de redemarrage, si on appuie sur Moins, on fait -10.
			GestiRoute::setProbaResteArret(routes[route_a_gerer].getProbaResteArret() - 1);
			if (clavier == 45)
			{
				GestiRoute::setProbaResteArret(routes[route_a_gerer].getProbaResteArret() - 9);
			}
			mode = 1;
		}

		// Si le curseur est en position 12.
		else if (position_curseur == 12)
		{
			// Si on fait Gauche ou Moins, on enleve une étape.
			etape--;
			if (etape < 0)
			{
				etape = 0;
			}
		}

		// Si le curseur est en position 08.
		else if (position_curseur == 8)
		{
			// Si on appuie sur Gauche, on fait -1 à la taille route, si on appuie sur Moins, on fait -5.
			GestiRoute::setTailleRoute(routes[route_a_gerer].getTailleRoute() - 1);
			if (clavier == 45)
			{
				GestiRoute::setTailleRoute(routes[route_a_gerer].getTailleRoute() - 4);
			}
		}

		// Si le curseur est en position 3.
		else if (position_curseur == 3)
		{
			// Si on fait Gauche ou Moins, on change de mode.
			mode--;
			if (mode < 0)
			{
				mode = 0;
			}
		}

		// Si le curseur est en position 10.
		else if (position_curseur == 10)
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
			if (GestiRoute::routesLiee(route_a_gerer).size() > 0)
			{
				// On supprime une liaison.
				GestiRoute::supprimeLiaison();
			}
		}

		// Si le curseur est en position 7.
		else if (position_curseur == 7)
		{
			// On modifie la limite de vitesse.
			GestiRoute::setLimiteVitesse(routes[route_a_gerer].getLimiteVitesse() - 1);
			if (clavier == 45)
			{
				GestiRoute::setLimiteVitesse(routes[route_a_gerer].getLimiteVitesse() - 4);
			}
		}

		// Si le curseur est en position 11.
		else if (position_curseur == 11)
		{
			// On change de mode d'affichage.
			mode_affichage--;
			if (mode_affichage < 0)
				mode_affichage = 0;
		}

		// Si le curseur est en position 13.
		else if (position_curseur == 13)
		{
			// On diminue le nombre d'enregistrement.
			nb_rembobinage--;
			if (clavier == 45)
			{
				nb_rembobinage -= 4;
			}
			if (nb_rembobinage < 0)
				nb_rembobinage = 0;
		}

		else if (position_curseur == 6)
		{
			// Si on appuie sur Gauche, on fait -1 à la proba de redemarrage, si on appuie sur Moins, on fait -10.
			probaDepassement--;
			if (clavier == 45)
			{
				probaDepassement -= 9;
			}
			if (probaDepassement < 0)
				probaDepassement = 0;
		}

		// Si le curseur est en position 13.
		else if (position_curseur == 14)
		{
			cb_de_rembobinage--;

			if (-cb_de_rembobinage > rembobinage_routes.size() - 1)
			{
				cb_de_rembobinage++;
			}
			GestiRoute::rembobiner();
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
				route_a_gerer = routes.size() - 1;
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

		// Si le curseur est en position 4.
		else if (position_curseur == 4)
		{
			// Si on appuie sur Droite, on fait +1 à la proba de freinage, si on appuie sur Plus, on fait +10.
			GestiRoute::setProbaFrein(routes[route_a_gerer].getProbaFrein() + 1);
			if (clavier == 43)
			{
				GestiRoute::setProbaFrein(routes[route_a_gerer].getProbaFrein() + 9);
			}
		}

		// Si le curseur est en position 5.
		else if (position_curseur == 5)
		{
			// Si on appuie sur Droite, on fait +1 à la proba de redemarrage, si on appuie sur Plus, on fait +10.
			GestiRoute::setProbaResteArret(routes[route_a_gerer].getProbaResteArret() + 1);
			if (clavier == 43)
			{
				GestiRoute::setProbaResteArret(routes[route_a_gerer].getProbaResteArret() + 9);
			}
			mode = 1;
		}

		// Si le curseur est en position 12.
		else if (position_curseur == 12)
		{
			// Si on fait Droite ou Plus, on ajoute une étape.
			etape++;
		}

		// Si le curseur est en position 8.
		else if (position_curseur == 8)
		{
			// Si on appuie sur Droite, on fait +1 à la taille route, si on appuie sur Plus, on fait +5.
			GestiRoute::setTailleRoute(routes[route_a_gerer].getTailleRoute() + 1);
			if (clavier == 43)
			{
				GestiRoute::setTailleRoute(routes[route_a_gerer].getTailleRoute() + 4);
			}
		}

		// Si le curseur est en position 3.
		else if (position_curseur == 3)
		{
			// Si on fait Droite ou Plus, on change de mode.
			mode++;
			if (mode > 1)
			{
				mode = 1;
			}
		}

		// Si le curseur est en position 10.
		else if (position_curseur == 10)
		{
			// Si on fait Droite, on fait +10 ms, si on fait Plus, on fait +100 ms.
			vitDeDefil += 10;
			if (clavier == 43)
			{
				vitDeDefil += 90;
			}
		}

		// Si le curseur est en position 98.
		else if (position_curseur == 9)
		{
			// On ajoute une liaison.
			GestiRoute::creerliaisonRoutes();
		}

		else if (position_curseur == 7)
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

		else if (position_curseur == 13)
		{
			nb_rembobinage++;
			if (clavier == 43)
			{
				nb_rembobinage += 4;
			}
		}

		else if (position_curseur == 6)
		{
			// Si on appuie sur Gauche, on fait -1 à la proba de redemarrage, si on appuie sur Moins, on fait -10.
			probaDepassement++;
			if (clavier == 43)
			{
				probaDepassement += 9;
			}
			if (probaDepassement > 100)
				probaDepassement = 100;
		}

		else if (position_curseur == 14)
		{
			cb_de_rembobinage++;
			if (cb_de_rembobinage > 0)
			{
				cb_de_rembobinage = 0;
			}
			GestiRoute::rembobiner();
		}
	}
}

/*
Méthode permettant de supprimer les enregistrements après celui que l'utilisateur à séléctionner.
*/
void GestiRoute::enleverRembobinage()
{
	for (int i = 0; i < -cb_de_rembobinage + 2; i++)
	{
		rembobinage_routes.pop_back();
		rembobinage_routes_liee.pop_back();
		rembobinage_liaisons.pop_back();
	}
}

/*
Méthode permettant d'enregistrer un etat de route
*/
void GestiRoute::ajouterRembobinage()
{
	rembobinage_routes.push_back(routes);
	rembobinage_routes_liee.push_back(routes_liee);
	rembobinage_liaisons.push_back(liaisons);

	// Pour pas dépasser la limite.
	if (rembobinage_routes.size() > nb_rembobinage + 1)
	{
		rembobinage_routes.erase(rembobinage_routes.begin());
		rembobinage_routes_liee.erase(rembobinage_routes_liee.begin());
		rembobinage_liaisons.erase(rembobinage_liaisons.begin());
	}
}

/*
Méthode permettant de revenir en arrière.
*/
void GestiRoute::rembobiner()
{
	int num_des_routes = rembobinage_routes.size() - 1 + cb_de_rembobinage;

	routes = rembobinage_routes[num_des_routes];
	routes_liee = rembobinage_routes_liee[num_des_routes];
	liaisons = rembobinage_liaisons[num_des_routes];
	Clear;
	GestiRoute::sortieAffichage();
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
Méthode permettant l'affichage des routes et des liaisons.
*/
string GestiRoute::affichageRoutes()
{
	// Variable temp qui permet de stocker l'immatriculation avec ou sans le 0 derrière.
	string temp = "";

	// Variable qui contiendera le texte à afficher.
	string routes_a_afficher = "";

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
				if (mode_affichage == 0)
					routes_a_afficher.append("[    ]");
				else if (mode_affichage == 1)
					routes_a_afficher.append("[ ]");
				else
					routes_a_afficher.append("[  ]");
			}

			// Sinon on écrit une voiture avec immatriculation et vitesse.
			else
			{
				temp = "";
				routes_a_afficher.append("[");

				if (mode_affichage == 0 || mode_affichage == 2)
				{
					if (v[j].getImatriculation() <= 9)
						temp += "0";
					temp += to_string(v[j].getImatriculation());
					routes_a_afficher.append(temp);
					if (mode_affichage == 0)
						routes_a_afficher.append(";");
				}
				if (mode_affichage == 0 || mode_affichage == 1)
				{
					routes_a_afficher.append(to_string(v[j].getVitesse()));
				}
				routes_a_afficher.append("]");
			}
		}

		// On crée un vector avec tous les emplacements des liaisons de la route, dans le vector routes_liee.
		vector<int> a = GestiRoute::routesLiee(i);

		// Pour toutes les liaisons de la route i.
		for (int k = 0; k < a.size(); k++)
		{
			// On fait un retour à la ligne après la route ou les liaisons.
			routes_a_afficher.append("\n");

			// On prend la a eme route liee.
			vector<Voiture> v = routes_liee[liaisons[a[k]][1]].tabAffiche();

			// Pour toutes les places de la route.
			for (int j = 0; j < v.size(); j++)
			{
				if (v[j].getImatriculation() == -1)
				{
					if (mode_affichage == 0)
						routes_a_afficher.append("[    ]");
					else if (mode_affichage == 1)
						routes_a_afficher.append("[ ]");
					else
						routes_a_afficher.append("[  ]");
				}
				else
				{
					temp = "";
					routes_a_afficher.append("[");

					if (mode_affichage == 0 || mode_affichage == 2)
					{
						if (v[j].getImatriculation() <= 9)
							temp += "0";
						temp += to_string(v[j].getImatriculation());
						routes_a_afficher.append(temp);
						if (mode_affichage == 0)
							routes_a_afficher.append(";");
					}
					if (mode_affichage == 0 || mode_affichage == 1)
					{
						routes_a_afficher.append(to_string(v[j].getVitesse()));
					}
					routes_a_afficher.append("]");
				}
			}
		}
		// On sépare les routes.
		routes_a_afficher.append("\n");
		routes_a_afficher.append("--------------------------------------------------------");
		routes_a_afficher.append("\n");
	}
	return routes_a_afficher;
}

/*
Méthode permettant de créer l'affichage des commandes.
*/
void GestiRoute::affichageCommandes()
{
	// On initialise le nombre d'espace maximum que l'on veux et temp qui permettera de déterminer le nombre d'espace.
	int nb_espaces = 10, temp = 0;

	commandes_a_afficher = "";

	commandes_a_afficher += "\n";

	// Si on demande d'afficher les instructions ou pas.
	if (affichage_instruction)
		commandes_a_afficher += "Utilisez les fleches directionnelles pour modifier les parametres.\n\n";


	commandes_a_afficher += "Gestion des routes :\n";
	// Si on est sur le curseur.
	if (position_curseur == 0)
		commandes_a_afficher += "<[(";
	else
		commandes_a_afficher += "  (";

	// On affiche l'info.
	temp = routes.size();
	commandes_a_afficher += to_string(temp);

	// Si on est sur le curseur.
	if (position_curseur == 0)
		commandes_a_afficher += ")]>";
	else
		commandes_a_afficher += ")  ";

	// On affiche la correspondance.
	commandes_a_afficher += GestiRoute::nbEspaceAffichage(nb_espaces, temp) + "Nombre(s) de route(s)";

	commandes_a_afficher += "\n";

	if (position_curseur == 1)
		commandes_a_afficher += "<[(";
	else
		commandes_a_afficher += "  (";

	temp = route_a_gerer + 1;
	commandes_a_afficher += to_string(temp);

	if (position_curseur == 1)
		commandes_a_afficher += ")]>";
	else
		commandes_a_afficher += ")  ";

	commandes_a_afficher += GestiRoute::nbEspaceAffichage(nb_espaces, temp) + "Numero de route a gerer";

	commandes_a_afficher += "\n";

	if (position_curseur == 2)
		commandes_a_afficher += "<[(";
	else
		commandes_a_afficher += "  (";

	temp = GestiRoute::getNbVoiture();
	commandes_a_afficher += to_string(temp);

	if (position_curseur == 2)
		commandes_a_afficher += ")]>";
	else
		commandes_a_afficher += ")  ";

	commandes_a_afficher += GestiRoute::nbEspaceAffichage(nb_espaces, temp) + "Nombre(s) de voiture(s) sur la route";

	commandes_a_afficher += "\n";

	if (position_curseur == 3)
		commandes_a_afficher += "<[(";
	else
		commandes_a_afficher += "  (";

	commandes_a_afficher += (mode == 0 ? "Nash" : "VDR");

	if (position_curseur == 3)
		commandes_a_afficher += ")]>";
	else
		commandes_a_afficher += ")  ";

	commandes_a_afficher += GestiRoute::nbEspaceAffichage(nb_espaces, (mode == 0 ? 1000 : 100)) + "Mode";

	commandes_a_afficher += "\n";

	if (position_curseur == 4)
		commandes_a_afficher += "<[(";
	else
		commandes_a_afficher += "  (";

	temp = routes[route_a_gerer].getProbaFrein();
	commandes_a_afficher += to_string(temp);

	if (position_curseur == 4)
		commandes_a_afficher += ")]>";
	else
		commandes_a_afficher += ")  ";

	commandes_a_afficher += GestiRoute::nbEspaceAffichage(nb_espaces, temp) + "Probabilite de freinage";

	commandes_a_afficher += "\n";

	if (position_curseur == 5)
		commandes_a_afficher += "<[(";
	else
		commandes_a_afficher += "  (";

	temp = routes[route_a_gerer].getProbaResteArret();
	commandes_a_afficher += to_string(temp);

	if (position_curseur == 5)
		commandes_a_afficher += ")]>";
	else
		commandes_a_afficher += ")  ";

	commandes_a_afficher += GestiRoute::nbEspaceAffichage(nb_espaces, temp) + "Probabilite de redemarrage";

	commandes_a_afficher += "\n";

	if (position_curseur == 6)
		commandes_a_afficher += "<[(";
	else
		commandes_a_afficher += "  (";

	temp = probaDepassement;
	commandes_a_afficher += to_string(temp);

	if (position_curseur == 6)
		commandes_a_afficher += ")]>";
	else
		commandes_a_afficher += ")  ";

	commandes_a_afficher += GestiRoute::nbEspaceAffichage(nb_espaces, temp) + "Probabilite de depassement";

	commandes_a_afficher += "\n";

	if (position_curseur == 7)
		commandes_a_afficher += "<[(";
	else
		commandes_a_afficher += "  (";

	temp = routes[route_a_gerer].getLimiteVitesse();
	commandes_a_afficher += to_string(temp);

	if (position_curseur == 7)
		commandes_a_afficher += ")]>";
	else
		commandes_a_afficher += ")  ";

	commandes_a_afficher += GestiRoute::nbEspaceAffichage(nb_espaces, temp) + "Limite de vitesse";

	commandes_a_afficher += "\n";

	if (position_curseur == 8)
		commandes_a_afficher += "<[(";
	else
		commandes_a_afficher += "  (";

	temp = routes[route_a_gerer].getTailleRoute();
	commandes_a_afficher += to_string(temp);

	if (position_curseur == 8)
		commandes_a_afficher += ")]>";
	else
		commandes_a_afficher += ")  ";

	commandes_a_afficher += GestiRoute::nbEspaceAffichage(nb_espaces, temp) + "Taille de la route";

	commandes_a_afficher += "\n";

	if (position_curseur == 9)
		commandes_a_afficher += "<[(";
	else
		commandes_a_afficher += "  (";

	temp = GestiRoute::routesLiee(route_a_gerer).size();
	commandes_a_afficher += to_string(temp);

	if (position_curseur == 9)
		commandes_a_afficher += ")]>";
	else
		commandes_a_afficher += ")  ";

	commandes_a_afficher += GestiRoute::nbEspaceAffichage(nb_espaces, temp) + "Nombre de liaisons";

	commandes_a_afficher += "\n";

	commandes_a_afficher += "\nAffichage :\n";

	if (position_curseur == 10)
		commandes_a_afficher += "<[(";
	else
		commandes_a_afficher += "  (";

	temp = vitDeDefil;
	commandes_a_afficher += to_string(temp);

	if (position_curseur == 10)
		commandes_a_afficher += ")]>";
	else
		commandes_a_afficher += ")  ";

	commandes_a_afficher += GestiRoute::nbEspaceAffichage(nb_espaces, temp) + "Vitesse de defilement";

	commandes_a_afficher += "\n";

	if (position_curseur == 11)
		commandes_a_afficher += "<[(";
	else
		commandes_a_afficher += "  (";

	commandes_a_afficher += (mode_affichage == 0 ? "Im/Vi" : mode_affichage == 1 ? "Vitesse" : "Immatri");

	if (position_curseur == 11)
		commandes_a_afficher += ")]>";
	else
		commandes_a_afficher += ")  ";

	commandes_a_afficher += GestiRoute::nbEspaceAffichage(nb_espaces, (mode_affichage == 0 ? 10000 : 1000000)) + "Mode d'affichage";

	commandes_a_afficher += "\n";

	if (position_curseur == 12)
		commandes_a_afficher += "<[(";
	else
		commandes_a_afficher += "  (";

	temp = etape;
	commandes_a_afficher += to_string(temp);

	if (position_curseur == 12)
		commandes_a_afficher += ")]>";
	else
		commandes_a_afficher += ")  ";

	commandes_a_afficher += GestiRoute::nbEspaceAffichage(nb_espaces, temp) + "Nombre d'etape a chaque affichage";

	commandes_a_afficher += "\n";

	commandes_a_afficher += "\nRembobinage :\n";

	if (position_curseur == 13)
		commandes_a_afficher += "<[(";
	else
		commandes_a_afficher += "  (";

	temp = nb_rembobinage;
	commandes_a_afficher += to_string(temp);

	if (position_curseur == 13)
		commandes_a_afficher += ")]>";
	else
		commandes_a_afficher += ")  ";

	commandes_a_afficher += GestiRoute::nbEspaceAffichage(nb_espaces, temp) + "Nombre de rembobinage";

	commandes_a_afficher += "\n";

	if (pause)
	{
		if (position_curseur == 14)
			commandes_a_afficher += "<[(";
		else
			commandes_a_afficher += "  (";

		temp = cb_de_rembobinage;
		commandes_a_afficher += to_string(temp);

		if (position_curseur == 14)
			commandes_a_afficher += ")]>";
		else
			commandes_a_afficher += ")  ";

		commandes_a_afficher += GestiRoute::nbEspaceAffichage(nb_espaces, temp) + "Rembobinage";

		commandes_a_afficher += "\n";
	}

	if (affichage_instruction)
	{
		commandes_a_afficher += "\n";
		commandes_a_afficher += "Appuyer sur \"Espace\" pour mettre en pause la simulation et pouvoir utiliser le rembobinage.\nAppuyer sur \"A\" pour afficher l'aide.\n";
		commandes_a_afficher += "Appuyer sur \"N\" pour masquer/afficher les instructions.\nAppuyer sur \"C\" pour marquer les commandes.\nAppuyer sur \"Q\" pour quitter";
	}

}

/*
Méthode permettant d'afficher les routes et les commandes (découpage permettant d'éviter les clignotements).
*/
void GestiRoute::sortieAffichage()
{
	// Si on appuie sur une touche, on actualise l'affichage des commandes et l'affichage des routes (sinon l'ajout des nouveaux �l�ments 
	// s'effectue apr�s l'actualisation avec 'VitDeDefil', sinon on actualise l'affichage des routes.
	if (appuie_touche)
	{
		GestiRoute::affichageCommandes();
		routes_a_afficher = GestiRoute::affichageRoutes();
		appuie_touche = false;
	}
	else
		routes_a_afficher = GestiRoute::affichageRoutes();
	// Pour r�duire les clignotements, on clear apr�s les calculs.
	Clear;

	// On affiche les premi�res infos.
	cout << "   ----------------------" << endl << "   PcSimuLesBouchons v3.0" << endl << "   ----------------------" << endl;
	cout << "--------------------------------------------------------" << endl;

	// On affiche les routes et les commandes.
	cout << routes_a_afficher;
	if (!masquer_commandes)
		cout << commandes_a_afficher;
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

	// On enregistre les changements.
	GestiRoute::ajouterRembobinage();
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
string GestiRoute::help()
{
	string fin;
	fin =   "   -------------------------\n";
	fin +=  "   PcSimuLesBouchons (PcSLB)\n";
	fin +=  "     Alexandre l'Heritier   \n";
	fin +=  "   -------------------------\n\n";
	fin +=  "Bienvenue dans PcSLB, programme cree pour le second semestre de L1 MPI.\n";
	fin +=  "Le but de ce programme est de simuler une route que l'on peut controler.\n";
	fin +=  "La route est representee avec des crochets comme ceci : [   ][   ][   ].\n";
	fin +=  "Une voiture est represente comme ceci : [X;Y]\n";
	fin +=  "X etant son immatriculation unique et Y sa vitesse.\n";
	fin +=  "Les routes sont separees avec cela : -----------------------------------.\n";
	fin +=  "Les liaisons des routes ne sont pas separées pour representer une route\n";
	fin +=  "a plusieurs voies.\n";
	fin +=  "Pour naviguer plus rapidement dans l'interface, vous pouvez utiliser les touches\n";
	fin +=  "Debut, Fin, +, -.\n";
	fin +=  "Bon jeu !\n";
	return fin;
}

/*
Méthode qui détermine si une voiture doit dépasser selon la probabilité.
*/
bool GestiRoute::determineDepassement()
{
	// On retourne true ou false selon la valeur de l'aleatoire.
	return (rand() % 100 < probaDepassement);
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

int GestiRoute::getProbaFrein()
{
	return routes[route_a_gerer].getProbaFrein();
}

int GestiRoute::getProbaRedemar()
{
	return routes[route_a_gerer].getProbaResteArret();
}

int GestiRoute::getProbaDepass()
{
	return probaDepassement;
}

int GestiRoute::getLimiteVitesse()
{
	return routes[route_a_gerer].getLimiteVitesse();
}

int GestiRoute::getTailleRoute()
{
	return routes[route_a_gerer].getTailleRoute();
}

int GestiRoute::getNbLiaison()
{
	return routesLiee(route_a_gerer).size();
}

int GestiRoute::getModeAffiche()
{
	return mode_affichage;
}

int GestiRoute::getEtape()
{
	return etape;
}

int GestiRoute::getNbRembob()
{
	return nb_rembobinage;
}

int GestiRoute::getNumRembob()
{
	return cb_de_rembobinage;
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

int GestiRoute::getNumRoute()
{
	return route_a_gerer+1;
}

void GestiRoute::setPositionCurseur(int pos)
{
	position_curseur = pos;
}

int GestiRoute::getMode()
{
	return mode;
}
