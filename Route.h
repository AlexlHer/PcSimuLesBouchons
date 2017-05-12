// --------------------------------
// Auteur : Alexandre l'Heritier
// PcSimuLesBouchons v3.0 : Classe Route
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
	int espaceAvant(int imaticulation);

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
	std::vector<Voiture> tabVoiture;	// Contient toutes les voitures présente sur la route.
	std::vector<Voiture> tabRoute;		// Contient la route (avec les voitures de tabVoiture et des "voiture vide".
	int limiteDeVitesse;				// Contient la limite de vitesse de la route.
	int probaFrein;						// Contient la proba de freinage des voitures.
	int probaResteArret;				// Contient la proba de redemarrage des voitures.

										// Méthodes
	bool determineFrein();
	void actualiserTabVoiture();
	void modele(int nom_modele);
	bool determineResteArret();
	bool intIn(int i, std::vector<int> dans);
	void placementAleatoire(Voiture v);
	void placementAleatoireDepart();
};

#endif
