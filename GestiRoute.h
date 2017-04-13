#ifndef DEF_GESTIROUTE
#define DEF_GESTIROUTE

#include "Route.h"
#include <vector>
#include <string>

class GestiRoute
{
public:
	bool intIn(int intt, std::vector<int> dans);
	GestiRoute(int nb_voiture);
	void ajouterRoute(int nb_voiture);
	void supprimerRoute();
	bool voitureIn(Voiture v, std::vector<Voiture> dans);
	void creerliaisonRoutes();
	void gestiLiaison();
	void supprimeLiaison();
	std::vector<int> routesLiee(int pos);
	int getNbRoutes();
	void setTouche(char clavier);
	void affichageRoutes();
	void affichageCommandes();
	void plusEtape();

	int vitesse();

	void ajouterVoiture();

	void enleverVoiture();

	int getNbVoiture();

	void setProbaFrein(int pourcent);

	void setProbaResteArret(int pourcent);

	void setTailleRoute(int taille);

private:
	std::vector<Route> routes;
	std::vector<Route> routes_liee;
	std::vector<std::vector<int>> liaisons;
	int temps_attente;
	int route_a_gerer;
	int position_curseur;
	int etape;
	int mode;
	std::string route_a_afficher;
	int vitDeDefil;
	int etape_temp;
};

#endif
