// --------------------------------
// Auteur : Alexandre l'Heritier
// PcSimuLesBouchons v1.0 : Classe Voiture
// --------------------------------

#ifndef DEF_VOITURE
#define DEF_VOITURE

class Voiture
{
	public:
		// Constructeurs
		Voiture();
		Voiture(int numero);
		Voiture(int numero, int vitess);

		// Accesseurs
		void setImatriculation(int numero);
		void setVitesse(int vitess);
		int getImatriculation();
		int getVitesse();

	private:
		// Attributs
		int vitesse;
		int imatriculation;
};

#endif
