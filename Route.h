// --------------------------------
// Auteur : Alexandre l'Heritier
// PcSimuLesBouchons v1.0 : Classe Route
// --------------------------------

#ifndef DEF_ROUTE
#define DEF_ROUTE

#include <vector>
#include <time.h>
#include "Voiture.h"

class Route
{
	public:
		// Constructeurs
		Route();
		Route(int nbVoiture);
		Route(int nbVoiture, int tailleRoute);

		// Méthodes
		void ajouterVoiture();
		void ajouterVoiture(int imatriculation);
		void ajouterVoiture(Voiture v);
		void ajouterVoiture(Voiture v, int pos);
		void enleverVoiture();
		void enleverVoiture(int imatriculation);
		void tempsPlus(int temps, int modeleNV);
		std::vector<Voiture> tabAffiche();
		std::vector<Voiture> getTabVoiture();

		// Accesseurs
		int getTailleRoute();
		void setTailleRoute(int taille);
		void setLimiteVitesse(int vit);
		int getLimiteVitesse();
		void setProbaFrein(int pourcent);
		int getProbaFrein();
		void setProbaResteArret(int pourcent);
		int getProbaResteArret();
		int getNbVoiture();

	private:
		// Attributs
		std::vector<Voiture> tabVoiture;
		std::vector<Voiture> tabRoute;
		int limiteDeVitesse;
		int probaFrein;
		int probaResteArret;

		// Méthodes
		bool determineFrein();
		void actualiserTabVoiture();
		void modele(int nom_modele);
		bool determineResteArret();
		bool intIn(int i, std::vector<int> dans);
		void placementAleatoire(Voiture v);
		void placementAleatoireDepart();
		int espaceAvant(int imaticulation);
};

#endif
