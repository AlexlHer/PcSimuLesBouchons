#ifndef DEF_ROUTE
#define DEF_ROUTE

#include <vector>
#include <time.h>
#include "Voiture.h"

class Route
{
	public:
		Route();
		Route(int nbVoiture);
		Route(int nbVoiture, int limite, int tailleRoute, int frein);
		void ajouterVoiture();
		void ajouterVoiture(Voiture v);
		void ajouterVoiture(Voiture v, int pos);
		void enleverVoiture();
		void enleverVoiture(Voiture v);
		void placementAleatoire(Voiture v);
		void placementAleatoireDepart();
		void tempsPlus(int temps, int modele);
		std::vector<Voiture> tabAffiche();
		int getTailleRoute();
		void setTailleRoute(int taille);
		void setLimiteVitesse(int vit);
		int espaceAvant(int imaticulation);
		void setProbaFrein(int pourcent);
		int getProbaFrein();
		int getNbVoiture();

	private:
		std::vector<Voiture> tabVoiture;
		std::vector<Voiture> tabRoute;
		int limiteDeVitesse;
		int probaFrein;
		void modeleNash();
		bool determineFrein();
};

#endif
