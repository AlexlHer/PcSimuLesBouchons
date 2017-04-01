#ifndef DEF_ROUTE
#define DEF_ROUTE

#include <vector>
#include <time.h>
#include "Voiture.h"

class Route
{
	public:
		Route(int nbVoiture);
		Route(int nbVoiture, int limite, int tailleRoute, int frein);
		void ajouterVoiture(int numVoiture);
		void enleverVoiture(int numVoiture);
		void placementAleatoireDepart();
		void tempsPlus(int temps);
		std::vector<int> tabAffiche();
		int tailleRoute();
		void setLimiteVitesse(int vit);
		int espaceAvant(int imaticulation);
		void setProbaFrein(int pourcent);

	private:
		std::vector<Voiture> tabVoiture;
		std::vector<Voiture> tabRoute;
		int limiteDeVitesse;
		int probaFrein;

		void modeleNash();
		bool determineFrein();
};

#endif
