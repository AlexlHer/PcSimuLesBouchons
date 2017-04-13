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
		Route(int nbVoiture, int tailleRoute);
		bool intIn(int i, std::vector<int> dans);
		void ajouterVoiture();
		void ajouterVoiture(int imatriculation);
		void ajouterVoiture(Voiture v);
		void ajouterVoiture(Voiture v, int pos);
		void enleverVoiture();
		void enleverVoiture(int imatriculation);
		void placementAleatoire(Voiture v);
		void placementAleatoireDepart();
		void tempsPlus(int temps, int modeleNV);
		std::vector<Voiture> tabAffiche();
		std::vector<Voiture> getTabVoiture();
		int getTailleRoute();
		void setTailleRoute(int taille);
		void setLimiteVitesse(int vit);
		int espaceAvant(int imaticulation);
		void setProbaFrein(int pourcent);
		int getProbaFrein();
		void setProbaResteArret(int pourcent);
		int getProbaResteArret();
		int getNbVoiture();

	private:
		std::vector<Voiture> tabVoiture;
		std::vector<Voiture> tabRoute;
		int limiteDeVitesse;
		int probaFrein;
		int probaResteArret;

		bool determineFrein();
		void actualiserTabVoiture();
		void modele(int nom_modele);
		bool determineResteArret();
};

#endif
