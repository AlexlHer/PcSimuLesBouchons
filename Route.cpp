// --------------------------------
// Auteur : Alexandre l'Heritier
// PcSimuLesBouchons v3.0 : Classe Route
// --------------------------------

#include "Route.h"
#include <iostream>

using namespace std;

/*
Constructeur d'une route vide.
*/
Route::Route()
{
	// On initialise l'aléatoire.
	srand(time(NULL));

	// On donne une limite de vitesse.
	limiteDeVitesse = 5;

	// On donne une probabilité de frenage aléatoire.
	probaFrein = 10;

	// On donne une probabilité de redémarrage de voiture.
	probaResteArret = 50;
}

/*
Constructeur d'une route avec un nombre de voiture défini.
@param nbVoiture Le nombre de voiture.
*/
Route::Route(int nbVoiture)
{
	// On initialise l'aléatoire.
	srand(time(NULL));

	// On donne une limite de vitesse.
	limiteDeVitesse = 5;

	// Pour chaque voiture.
	for (int i = 0; i < nbVoiture; i++)
	{
		// On crée une voiture avec i comme immatriculation.
		Voiture v(i);

		// On défini une vitesse aléatoire entre 0 et limiteDeVitesse.
		v.setVitesse(rand() % limiteDeVitesse);

		// On l'ajoute dans la liste des voitures.
		tabVoiture.push_back(v);
	}
	// On fait une route avec deux cases par voitures.
	tabRoute.resize(nbVoiture * 2);

	// On donne une probabilité de frenage aléatoire.
	probaFrein = 10;

	// On donne une probabilité de redémarrage de voiture.
	probaResteArret = 50;

	// On place les voitures sur la route de manière aléatoire.
	Route::placementAleatoireDepart();
}

/*
Constructeur d'une route avec un nombre de voiture et une taille de route défini.
@param nbVoiture Le nombre de voiture.
@param tailleRoute La taille de la route.
*/
Route::Route(int nbVoiture, int tailleRoute)
{
	// On initialise l'aléatoire.
	srand(time(NULL));

	// On donne une limite de vitesse.
	limiteDeVitesse = 5;

	// Pour chaque voiture.
	for (int i = 0; i < nbVoiture; i++)
	{
		// On crée une voiture avec i comme immatriculation.
		Voiture v(i);

		// On défini une vitesse aléatoire entre 0 et limiteDeVitesse.
		v.setVitesse(rand() % limiteDeVitesse);

		// On l'ajoute dans la liste des voitures.
		tabVoiture.push_back(v);
	}
	// On défini la taille de la route.
	tabRoute.resize(tailleRoute);

	// On donne une probabilité de frenage aléatoire.
	probaFrein = 10;

	// On donne une probabilité de redémarrage de voiture.
	probaResteArret = 50;

	// On place les voitures sur la route de manière aléatoire.
	Route::placementAleatoireDepart();
}

/*
Methode permettant de savoir si un entier se trouve dans un vector int.
@param intt l'entier à rechercher.
@param dans le vector dans lequel rechercher.
@return true si l'entier à été trouver, false sinon.
*/
bool Route::intIn(int intt, vector<int> dans)
{
	// Pour tous les éléments de la liste.
	for (int i = 0; i < dans.size(); i++)
	{
		// Si ça correspond, on renvoi true.
		if (dans[i] == intt)
		{
			return true;
		}
	}
	// Si aucune correspondance, on renvoi false.
	return false;
}

/*
Méthode pour ajouter une voiture dans la route.
*/
void Route::ajouterVoiture()
{
	// Si il y a encore de la place sur la route.
	if (tabVoiture.size() < tabRoute.size())
	{
		// Vector qui contiendera les immatriculations déjà prise dans la route.
		vector<int> immatri;

		// On rempli le vector avec toutes les immatriculations des voitures de la route.
		for (int i = 0; i < tabVoiture.size(); i++)
		{
			immatri.push_back(tabVoiture[i].getImatriculation());
		}

		// Compteur pour savoir quelle immatriculation est dispo.
		int a = 0;

		while (Route::intIn(a, immatri))
		{
			a++;
		}

		// On prend une voiture vide.
		Voiture v;

		// On lui donne une immatriculation non utilisé.
		v.setImatriculation(a);

		// On lui donne une vitesse aléatoire.
		v.setVitesse(rand() % limiteDeVitesse);

		// On met la voiture dans le tableau de voiture de la route.
		tabVoiture.push_back(v);

		// On place aléatoirement la voiture sur la route.
		Route::placementAleatoire(v);
	}
}

/*
Méthode pour ajouter une voiture dans la route.
@param imatriculation L'immatriculation à donner à la voiture.
*/
void Route::ajouterVoiture(int imatriculation)
{
	// Si il y a encore de la place sur la route.
	if (tabVoiture.size() < tabRoute.size())
	{
		// On prend une voiture vide.
		Voiture v;

		// On lui donne l'immatriculation.
		v.setImatriculation(imatriculation);

		// On lui donne une vitesse aléatoire.
		v.setVitesse(rand() % limiteDeVitesse);

		// On met la voiture dans le tableau de voiture de la route.
		tabVoiture.push_back(v);

		// On place aléatoirement la voiture sur la route.
		Route::placementAleatoire(v);
	}
}

/*
Méthode pour ajouter une voiture dans la route.
@param v La voiture à placer.
*/
void Route::ajouterVoiture(Voiture v)
{
	// Si il y a encore de la place sur la route.
	if (tabVoiture.size() < tabRoute.size())
	{
		// On met la voiture dans le tableau de voiture de la route.
		tabVoiture.push_back(v);

		// On place aléatoirement la voiture sur la route.
		Route::placementAleatoire(v);
	}
}

/*
Méthode pour ajouter une voiture dans la route.
@param v La voiture à placer.
@param pos la position de la voiture sur la route.
*/
void Route::ajouterVoiture(Voiture v, int pos)
{
	// Si il y a encore de la place sur la route.
	if (tabVoiture.size() < tabRoute.size())
	{
		// Si la position donnée ne dépasse pas la taille de la route.
		if (pos < tabRoute.size())
		{
			// On met la voiture dans le tableau de voiture de la route.
			tabVoiture.push_back(v);

			// On place la voiture sur la route.
			tabRoute[pos] = v;
		}
	}
}

/*
Méthode pour enlever la dernière voiture ajouté sur la route.
*/
void Route::enleverVoiture()
{
	// On crée deux Voitures vide.
	Voiture v1, v2;

	// La dernière voiture de tabVoiture est copié dans v2.
	v2 = tabVoiture[tabVoiture.size() - 1];

	// On supprime la dernière voiture de tabVoiture.
	tabVoiture.pop_back();

	// On recherche la voiture à supprimer du tabRoute.
	for (int i = 0; i < tabRoute.size(); i++)
	{
		// Si la voiture correspond, on l'a remplace par une voiture vide.
		if (tabRoute[i].getImatriculation() == v2.getImatriculation())
		{
			tabRoute[i] = v1;
		}
	}
}

/*
Méthode pour enlever une voiture particulière de la route.
@param imatriculation L'immatriculation de la voiture à retirer.
*/
void Route::enleverVoiture(int imatriculation)
{
	// On crée une voiture vide.
	Voiture w;

	// On recherche la voiture dans le tableau des voitures de la route et on la supprime.
	for (int i = 0; i < tabVoiture.size(); i++)
	{
		if (tabVoiture[i].getImatriculation() == imatriculation)
		{
			tabVoiture.erase(tabVoiture.begin() + i);
		}
	}
	// On recherche la voiture dans la route et on la remplace par une voiture vide.
	for (int i = 0; i < tabRoute.size(); i++)
	{
		if (tabRoute[i].getImatriculation() == imatriculation)
		{
			tabRoute[i] = w;
		}
	}
}

/*
Méthode pour placer une voiture sur la route de façon aléatoire.
@param v la voiture à placer.
*/
void Route::placementAleatoire(Voiture v)
{
	// On prend une position aléatoire sur la route.
	int a = rand() % tabRoute.size();

	// Tant que la position choisi contient une voiture non vide, on recommence.
	while (tabRoute[a].getImatriculation() != -1)
	{
		a = rand() % tabRoute.size();
	}
	// On met la voiture sur la position vide.
	tabRoute[a] = v;
}

/*
Méthode permettant de mettre les voitures contenu dans tabVoiture sur la route de façon aléatoire.
*/
void Route::placementAleatoireDepart()
{
	// On prend une variable qui contiendera une position prise aléatoirement.
	int a = 0;

	// Pour toutes les voitures du tableau de voiture.
	for (int i = 0; i < tabVoiture.size(); i++)
	{
		// On prend une position aléatoire.
		a = rand() % tabRoute.size();

		// Tant que cette position est occupé, on choisi une autre position et on reteste.
		while (tabRoute[a].getImatriculation() != -1)
		{
			a = rand() % tabRoute.size();
		}
		// On met la i eme voiture sur la position vide.
		tabRoute[a] = tabVoiture[i];
	}
}

/*
Méthode servant à faire avancer la route temps fois.
@param temps Le nombre de fois qu'il faut faire avancer les voitures en un coup.
@param modeleNV Le modele choisi (Nash/VDR)
*/
void Route::tempsPlus(int temps, int modeleNV)
{
	// On recommence temps nombre de fois.
	for (int i = 0; i < temps; i++)
	{
		// On execute la procedure permettant de faire une étape.
		Route::modele(modeleNV);
	}
}

/*
Méthode qui détermine si une voiture doit redemarrer selon la probabilité.
*/
bool Route::determineResteArret()
{
	// On retourne true ou false selon la valeur de l'aleatoire.
	return (rand() % 100 < probaResteArret);
}

/*
Méthode qui détermine si une voiture doit freiner selon la probabilité.
*/
bool Route::determineFrein()
{
	// On retourne true ou false selon la valeur de l'aleatoire.
	return (rand() % 100 < probaFrein);
}

/*
Méthode permettant d'actualiser le tabVoiture avec les nouvelles vitesses.
*/
void Route::actualiserTabVoiture()
{
	// Double boucles qui, pour chaque voiture de tabVoiture, on recherche son actualisation dans tabRoute pour pouvoir actualiser chaque voiture de tabVoiture.
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

/*
Méthode utilisant la plupart des autres méthodes pour suivre le modèle décrite dans la feuille de consigne de projet.
@param nom_modele Le modèle à respecter (Nash:0/VDR:1)
*/
void Route::modele(int nom_modele)
{
	// Deux variables : a correcpond a la position de la voiture à déplacer et b une variable temp servant à stocker l'espace avant.
	int a = 0, b = 0;

	// Pour toutes les voitures de la route.
	for (int i = 0; i < tabVoiture.size(); i++)
	{
		// On recherche la voiture après la position a.
		while (tabRoute[a].getImatriculation() == -1)
		{
			a++;
		}

		// Pour un peu plus de clarté, on défini la vitesse de la voiture ainsi que son immatriculation dans deux variables.
		int vitesseVoiture = tabRoute[a].getVitesse();
		int immatriVoiture = tabRoute[a].getImatriculation();

		// On regarde si le modèle VDR est séléctionné, si la vitesse de la voiture est de 0 et si la proba de ne pas redemarrer est true.
		// On met un ! devant pour inverser le résultat.
		if (!(nom_modele == 1 && vitesseVoiture == 0 && Route::determineResteArret()))
		{
			// Si la voiture n'est pas à sa vitesse max, on ajoute +1 a sa vitesse.
			if (limiteDeVitesse > vitesseVoiture)
			{
				vitesseVoiture++;
			}

			if (limiteDeVitesse < vitesseVoiture)
			{
				vitesseVoiture = limiteDeVitesse;
			}

			// On regarde l'espace entre notre voiture et celle de devant.
			b = Route::espaceAvant(immatriVoiture);
			//cout << b << endl;

			// Si la voiture va trop vite par rapport à l'espace dispo, on lui donne une vitesse de b.
			if (vitesseVoiture > b)
			{
				vitesseVoiture = b;
			}

			// On regarde si la voiture freine aléatoirement, si oui, -1.
			if (Route::determineFrein())
			{
				vitesseVoiture--;
			}

			// Si la vitesse de la voiture est inferieur à 0, on la met a 0.
			if (vitesseVoiture < 0)
			{
				vitesseVoiture = 0;
			}
			//cout << tabRoute[a].getVitesse() << endl;

			// On met la nouvelle vitesse dans la voiture.
			tabRoute[a].setVitesse(vitesseVoiture);
		}
		// a++ pour acceder à la voiture d'en face.
		a++;
	}
	// Ici, a à la même fonction et b serre à stocker la nouvelle position de la voiture.
	a = 0, b = 0;

	// On crée une voiture temp vide.
	Voiture v;

	// On fait une copie du tableau, sinon une fois que l'on aurai avancer une voiture, quand
	// nous rechercheront la voiture d'après, on retomberai dessus.
	vector<Voiture> tv = tabRoute;

	// Pour toutes les voitures de tabVoiture.
	for (int i = 0; i < tabVoiture.size(); i++)
	{
		// On recherche la prochaine voiture.
		while (tabRoute[a].getImatriculation() == -1)
		{
			a++;
		}
		//cout << a << endl;

		// On evite le dépassement de tableau si, lorsque l'on ajoute la vitesse, il y a dépassement.
		if (a + tv[a].getVitesse() >= tv.size())
		{
			b = a - tv.size() + tv[a].getVitesse();
		}

		// Sinon on ajoute juste la vitesse.
		else
		{
			b = a + tv[a].getVitesse();
		}

		// Si il n'y a pas de déplacement, aucune utilité de faire la suite.
		if (a != b)
		{
			//if (tv[b].getVitesse() != -1)
			//{
			//	cout << "Erreur !!! " << tv[a].getImatriculation() << " ; "<< tv[b].getImatriculation();
			//	cin >> c;
			//}

			// On fait un échange de voiture.
			tv[b] = tv[a];
			tv[a] = v;
		}
		// On change de voiture.
		a++;
	}
	// On remet le tableau temporaire dans le tableau original.
	tabRoute = tv;

	// On actualise tabVoiture.
	Route::actualiserTabVoiture();
}

/*
Méthode qui donne l'espace entre deux voitures.
@param imatriculation L'immatriculation de la voiture a partir de laquelle il faut déterminer l'espace avant (on l'appelera v).
@return l'espace avant.
*/
int  Route::espaceAvant(int imaticulation)
{
	// Pour éviter le bug de la route vide sur une liaison.
	if (tabVoiture.size() == 0)
	{
		return 0;
	}

	// Deux variables : a correspond à la position de la voiture v 
	// et b la position de la voiture b à partir de la voiture a (en cas de retour au début du tableau).
	int a = 0, b = 1;

	// On cherche la voiture v.
	while (tabRoute[a].getImatriculation() != imaticulation)
	{
		a++;
	}

	// Si on dépasse directement le tableau, on retourne au début (sinon le while dépassera le tableau).
	if (a + b >= tabRoute.size())
	{
		a -= tabRoute.size();
	}

	// Tant que l'on trouve pas de voiture non vide.
	while (tabRoute[a + b].getImatriculation() == -1)
	{
		// Si l'étape suivante mène à un dépassement de tableau, on rectifie maintenant.
		if (a + b + 1 >= tabRoute.size())
		{
			a -= tabRoute.size();
		}
		// On regarde sur la case d'après.
		b++;
	}

	// Comme b correspond à la position de la voiture d'en face, on doit faire -1 pour avoir le nombre de case.
	return b - 1;
}

/*
Accesseur retournant la route.
*/
vector<Voiture> Route::tabAffiche()
{
	return tabRoute;
}

/*
Accesseur retournant le tableau de voiture.
@return Le tabVoiture.
*/
vector<Voiture> Route::getTabVoiture()
{
	return tabVoiture;
}

/*
Accesseur retournant le nombre de voiture de la route.
@return Le nombre de voiture de la route.
*/
int Route::getNbVoiture()
{
	return tabVoiture.size();
}

/*
Accesseur retournant la taille de la route.
@return la taille de la route.
*/
int  Route::getTailleRoute()
{
	return tabRoute.size();
}

/*
Procedure permettant d'agrandir ou de rétrécir la taille de la route.
@param la taille voulu.
*/
void Route::setTailleRoute(int taille)
{
	// On verifie si on demande un rétrécicement ou un agrandissement.
	if (taille < tabRoute.size())
	{
		// On verifie si on peut rétrécir la route sans perdre de voiture.
		if (taille >= tabVoiture.size())
		{
			// On crée un vector qui contiendra toutes les voitures à déplacer.
			vector<Voiture> v;

			// On rempli le vector avec toutes les voitures qui dépassent de la nouvelle taille de la route.
			for (int i = taille; i < tabRoute.size(); i++) {
				// On prend toutes les voitures non vide.
				if (tabRoute[i].getImatriculation() != -1) {
					v.push_back(tabRoute[i]);
				}
			}
			// On redimmentionne la route.
			tabRoute.resize(taille);

			// On replace toutes les voitures du vector de manière aléatoire.
			for (int i = 0; i < v.size(); i++)
			{
				Route::placementAleatoire(v[i]);
			}
		}
	}
	// Si il s'agit d'un agrandissement, pas besoin de verification.
	else
		tabRoute.resize(taille);
}

/*
Accesseur permettant de modifier la limite de vitesse de la route.
@param vit La nouvelle limite de vitesse.
*/
void Route::setLimiteVitesse(int vit)
{
	if (vit < 1)
	{
		vit = 1;
	}
	limiteDeVitesse = vit;
}

/*
Accesseur permettant de récuperer la limite de vitesse.
*/
int Route::getLimiteVitesse()
{
	return limiteDeVitesse;
}

/*
Accesseur permettant de changer la probabilité de freinage aléatoire.
*/
void Route::setProbaFrein(int pourcent)
{
	// On verifie que le nouveau pourcentage est entre 0 et 100.
	if (pourcent < 0) pourcent = 0;
	if (pourcent > 100) pourcent = 100;

	probaFrein = pourcent;
}

/*
Accesseur qui returne la probabilité de freinage aléatoire actuel.
@return La probabilité de frenage aléatoire.
*/
int  Route::getProbaFrein()
{
	return probaFrein;
}

/*
Accesseur permettant de changer la probabilité de redemarrage.
*/
void Route::setProbaResteArret(int pourcent)
{
	// On verifie que le nouveau pourcentage est entre 0 et 100.
	if (pourcent < 0) pourcent = 0;
	if (pourcent > 100) pourcent = 100;

	probaResteArret = pourcent;
}

/*
Accesseur qui returne la probabilité de redemarrage actuel.
@return La probabilité de redemarrage.
*/
int  Route::getProbaResteArret()
{
	return probaResteArret;
}
