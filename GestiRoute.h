// --------------------------------
// Auteur : Alexandre l'Heritier
// PcSimuLesBouchons v2.0 : Classe GestiRoute
// --------------------------------

#ifndef DEF_GESTIROUTE
#define DEF_GESTIROUTE

#include "Route.h"
#include <vector>
#include <string>

class GestiRoute
{
public:
	// Constructeurs
	GestiRoute(int nb_voiture);

	// Méthodes
	std::string affichageRoutes();
	void sortieAffichage();
	void plusEtape();

	// Accesseurs
	int vitesse();
	void setTouche(char clavier);
	bool getQuit();

private:
	// Attributs
	std::vector<Route> routes;											// Contient toutes les routes à gérer.
	std::vector<Route> routes_liee;										// Contient toutes les routes liées à des 'routes'.
	std::vector<std::vector<int>> liaisons;								// Contient tous les liens entre les 'routes' et leurs liaisons ({{pos routes, pos routes_liee}, {...}...})
	int route_a_gerer;													// Contient la position de la 'routes' séléctionnée par l'utilisateur.
	int position_curseur;												// Contient la position du curseur dans l'interface.
	int etape;															// Contient le nombre d'étape effectué tous les 'vitDeDefil' miliseconde. (mais les calculs peuvent prendre un peu plus de temps).
	int mode;															// Contient le mode séléctionné (Nash / VDR)
	int vitDeDefil;														// Contient le temps entre deux "avancée de voiture" et d'affichage si aucune touche n'ai appuyé (sinon actualisation de l'affichage).
	int etape_temp;														// Contient le contenu de 'etape' lorsqu'il y a pause (comme ça, etape contient 0 et la route devient immobile).
	int vitDeDefil_temp;												// Contient le contenu de 'vitDeDefil' lorsqu'il y a pause (comme ça, on met 9999 ms dans 'vitDeDefil' et ça permet d'éviter les actualisations inutiles).
	bool affichage_instruction;											// Contient le choix de l'utilisateur sur l'affichage de l'aide minimale dans l'interface.
	bool quit;															// Contient le choix de l'utilisateur sur quitter le programme ou pas.
	int mode_affichage;													// Contient le mode d'affichage choisi par l'utilisateur (Vitesse et Immatriculation ou Vitesse seule ou Immatriculation seule).
	bool pause;															// Contient si le programme est sur pause ou pas.
	std::vector<std::vector<Route>> rembobinage_routes;					// Contient les 'routes' d'avant, permettant de revenir à un état d'avant.
	std::vector<std::vector<Route>> rembobinage_routes_liee;			// Contient les 'routes_liee' d'avant.
	std::vector<std::vector<std::vector<int>>> rembobinage_liaisons;	// Contient les 'liaisons' d'avant.
	int nb_rembobinage;													// Contient le nombre d'enregistrement que l'on veut.
	int cb_de_rembobinage;												// Contient le la position du rembobinage que l'utilisateur veut aller.

	// Méthodes
	bool intIn(int intt, std::vector<int> dans);
	void ajouterRoute(int nb_voiture);
	void supprimerRoute();
	bool voitureIn(Voiture v, std::vector<Voiture> dans);
	void creerliaisonRoutes();
	void gestiLiaison();
	void supprimeLiaison();
	void help();
	std::vector<int> routesLiee(int pos);
	std::string nbEspaceAffichage(int nb_espace, int chiffre);
	void ajouterVoiture();
	void enleverVoiture();
	void ajouterRembobinage();
	void rembobiner();
	void enleverRembobinage();
	void setProbaFrein(int pourcent);
	void setProbaResteArret(int pourcent);
	void setTailleRoute(int taille);
	int getNbRoutes();
	int getNbVoiture();
	void setLimiteVitesse(int v);
};

#endif
