#ifndef DEF_VOITURE
#define DEF_VOITURE

class Voiture
{
	public:
		Voiture();
		Voiture(int numero);
		Voiture(int numero, int vitess);
		void setImatriculation(int numero);
		void setVitesse(int vitess);
		int getImatriculation();
		int getVitesse();
	private:
		int vitesse;
		int imatriculation;
};

#endif