#ifndef DEF_GESTIROUTE
#define DEF_GESTIROUTE

#include "Route.h"
#include <vector>
#include <string>

class GestiRoute
{
public:
	GestiRoute(int nb_voiture);
	void ajouterRoute(int nb_voiture);
	void supprimerRoute();
	int getNbRoutes();
	void setTouche(char clavier);
	void affichageRoutes();
	void affichageCommandes();
	void plusEtape();

	int vitesse();

private:
	std::vector<Route> routes;
	int temps_attente;
	int route_a_gerer;
	int position_curseur;
	int etape;
	int mode;
	std::string route_a_afficher;
	int vitDeDefil;
	int etape_temp;
	void liaisonRoutes();
};

#endif