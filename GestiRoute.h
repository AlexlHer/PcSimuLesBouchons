// --------------------------------
// Auteur : Alexandre l'Heritier
// PcSimuLesBouchons v1.0 : Classe GestiRoute
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
	std::vector<Route> routes;
	std::vector<Route> routes_liee;
	std::vector<std::vector<int>> liaisons;
	int temps_attente;
	int route_a_gerer;
	int position_curseur;
	int etape;
	int mode;
	int vitDeDefil;
	int etape_temp;
	int vitDeDefil_temp;
	bool affichage_instruction;
	bool quit;
	int mode_affichage;

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
	void setProbaFrein(int pourcent);
	void setProbaResteArret(int pourcent);
	void setTailleRoute(int taille);
	int getNbRoutes();
	int getNbVoiture();
	void setLimiteVitesse(int v);
};

#endif
