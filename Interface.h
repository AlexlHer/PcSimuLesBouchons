// --------------------------------
// Auteur : Alexandre l'Heritier
// PcSimuLesBouchonsQE v0.3 : Classe Interface
// --------------------------------

#ifndef DEF_INTERFACE
#define DEF_INTERFACE

#include <QtWidgets>
#include "GestiRoute.h"

class Interface : public QMainWindow
{
	Q_OBJECT

	public:
		Interface();
		void actualiserAffichage();

	public slots:
		void plusUn();

		void pause();

		void aide();

		void nbRouteM();
		void nbRouteM2();
		void nbRouteP();
		void nbRouteP2();

		void numRouteM();
		void numRouteP();

		void nbVoitureM();
		void nbVoitureM2();
		void nbVoitureP();
		void nbVoitureP2();

		void changeMode();

		void probaFreinM();
		void probaFreinM2();
		void probaFreinP();
		void probaFreinP2();

		void probaRedemarM();
		void probaRedemarM2();
		void probaRedemarP();
		void probaRedemarP2();

		void probaDepassM();
		void probaDepassM2();
		void probaDepassP();
		void probaDepassP2();

		void limiteVitesseM();
		void limiteVitesseM2();
		void limiteVitesseP();
		void limiteVitesseP2();

		void tailleRouteM();
		void tailleRouteM2();
		void tailleRouteP();
		void tailleRouteP2();

		void nbLiaisonM();
		void nbLiaisonM2();
		void nbLiaisonP();
		void nbLiaisonP2();

		void vitDeDefM();
		void vitDeDefM2();
		void vitDeDefP();
		void vitDeDefP2();

		void modeAfficheM();
		void modeAfficheP();

		void nbEtapeM();
		void nbEtapeM2();
		void nbEtapeP();
		void nbEtapeP2();

		void nbRembobiM();
		void nbRembobiM2();
		void nbRembobiP();
		void nbRembobiP2();

		void numRembobiM();
		void numRembobiP();

	private:
		QTextEdit *afficheRoute;
		QLabel *nb_de_route_affiche;
		QLabel *num_de_route_affiche;
		QLabel *nb_de_voiture_affiche;
		QLabel *mode_affiche;
		QLabel *proba_frein_affiche;
		QLabel *proba_redemar_affiche;
		QLabel *proba_depass_affiche;
		QLabel *limite_vitesse_affiche;
		QLabel *taille_de_route_affiche;
		QLabel *nb_de_liaison_affiche;
		QPushButton *mode_change;
		QLabel *vitDeDef_affiche;
		QLabel *modeAffiche_affiche;
		QLabel *nbRembobi_affiche;
		QLabel *numRembobi_affiche;
		QLabel *nbEtape_affiche;
		QTimer *timer;
		GestiRoute r = GestiRoute(10);
};

#endif