// --------------------------------
// Auteur : Alexandre l'Heritier
// PcSimuLesBouchonsQE v0.3 : Classe Interface
// --------------------------------

#include "Interface.h"
#include "GestiRoute.h"

Interface::Interface()
{
	GestiRoute r = GestiRoute(10);
	QWidget *centre = new QWidget;

	//Widgets affichés au dessus des onglets.
	QLabel *titreProg = new QLabel;
	afficheRoute = new QTextEdit;

	titreProg->setText("PcSimuLesBouchons Qt Edition v0.1");
	afficheRoute->setReadOnly(true);

	QGridLayout *layoutPrincipal = new QGridLayout;
	layoutPrincipal->addWidget(titreProg, 0, 0, 1, 3);
	layoutPrincipal->addWidget(afficheRoute, 1, 0, 1, 3);

	QTabWidget *onglets = new QTabWidget;
	QWidget *contOnglet1 = new QWidget;
	QGridLayout *onglet1 = new QGridLayout;

	// Onglet 1.
	QLabel *nb_de_route = new QLabel("Nombre de route");
	QPushButton *nb_de_route_moins = new QPushButton("<");
	QPushButton *nb_de_route_moins2 = new QPushButton("<<");
	QPushButton *nb_de_route_plus = new QPushButton(">");
	QPushButton *nb_de_route_plus2 = new QPushButton(">>");
	nb_de_route_affiche = new QLabel;

	QLabel *num_de_route = new QLabel("Numéro de la route à gérer");
	QPushButton *num_de_route_moins = new QPushButton("<");
	QPushButton *num_de_route_plus = new QPushButton(">");
	num_de_route_affiche = new QLabel;

	QLabel *nb_de_voiture = new QLabel("Nombre de voiture sur la route");
	QPushButton *nb_de_voiture_moins = new QPushButton("<");
	QPushButton *nb_de_voiture_moins2 = new QPushButton("<<");
	QPushButton *nb_de_voiture_plus = new QPushButton(">");
	QPushButton *nb_de_voiture_plus2 = new QPushButton(">>");
	nb_de_voiture_affiche = new QLabel;

	QLabel *mode = new QLabel("Mode de la route");
	mode_change = new QPushButton("VDR");
	mode_affiche = new QLabel;

	QLabel *proba_frein = new QLabel("Probabilité de freinage");
	QPushButton *proba_frein_moins = new QPushButton("<");
	QPushButton *proba_frein_moins2 = new QPushButton("<<");
	QPushButton *proba_frein_plus = new QPushButton(">");
	QPushButton *proba_frein_plus2 = new QPushButton(">>");
	proba_frein_affiche = new QLabel;

	QLabel *proba_redemar = new QLabel("Probabilité de redémarrage");
	QPushButton *proba_redemar_moins = new QPushButton("<");
	QPushButton *proba_redemar_moins2 = new QPushButton("<<");
	QPushButton *proba_redemar_plus = new QPushButton(">");
	QPushButton *proba_redemar_plus2 = new QPushButton(">>");
	proba_redemar_affiche = new QLabel;

	QLabel *proba_depass = new QLabel("Probabilité de dépassement");
	QPushButton *proba_depass_moins = new QPushButton("<");
	QPushButton *proba_depass_moins2 = new QPushButton("<<");
	QPushButton *proba_depass_plus = new QPushButton(">");
	QPushButton *proba_depass_plus2 = new QPushButton(">>");
	proba_depass_affiche = new QLabel;

	QLabel *limite_vitesse = new QLabel("Limite de vitesse de la route");
	QPushButton *limite_vitesse_moins = new QPushButton("<");
	QPushButton *limite_vitesse_moins2 = new QPushButton("<<");
	QPushButton *limite_vitesse_plus = new QPushButton(">");
	QPushButton *limite_vitesse_plus2 = new QPushButton(">>");
	limite_vitesse_affiche = new QLabel;

	QLabel *taille_de_route = new QLabel("Taille de la route");
	QPushButton *taille_de_route_moins = new QPushButton("<");
	QPushButton *taille_de_route_moins2 = new QPushButton("<<");
	QPushButton *taille_de_route_plus = new QPushButton(">");
	QPushButton *taille_de_route_plus2 = new QPushButton(">>");
	taille_de_route_affiche = new QLabel;

	QLabel *nb_de_liaison = new QLabel("Nombre de voie de la route");
	QPushButton *nb_de_liaison_moins = new QPushButton("<");
	QPushButton *nb_de_liaison_moins2 = new QPushButton("<<");
	QPushButton *nb_de_liaison_plus = new QPushButton(">");
	QPushButton *nb_de_liaison_plus2 = new QPushButton(">>");
	nb_de_liaison_affiche = new QLabel;

	onglet1->addWidget(nb_de_route, 0, 0, 1, 5);
	onglet1->addWidget(nb_de_route_moins2, 1, 0);
	onglet1->addWidget(nb_de_route_moins, 1, 1);
	onglet1->addWidget(nb_de_route_affiche, 1, 2);
	onglet1->addWidget(nb_de_route_plus, 1, 3);
	onglet1->addWidget(nb_de_route_plus2, 1, 4);

	onglet1->addWidget(num_de_route, 2, 0, 1, 5);
	onglet1->addWidget(num_de_route_moins, 3, 1);
	onglet1->addWidget(num_de_route_affiche, 3, 2);
	onglet1->addWidget(num_de_route_plus, 3, 3);

	onglet1->addWidget(nb_de_voiture, 4, 0, 1, 5);
	onglet1->addWidget(nb_de_voiture_moins2, 5, 0);
	onglet1->addWidget(nb_de_voiture_moins, 5, 1);
	onglet1->addWidget(nb_de_voiture_affiche, 5, 2);
	onglet1->addWidget(nb_de_voiture_plus, 5, 3);
	onglet1->addWidget(nb_de_voiture_plus2, 5, 4);

	onglet1->addWidget(mode, 6, 0, 1, 5);
	onglet1->addWidget(mode_change, 7, 0);
	onglet1->addWidget(mode_affiche, 7, 2);

	onglet1->addWidget(proba_frein, 8, 0, 1, 5);
	onglet1->addWidget(proba_frein_moins2, 9, 0);
	onglet1->addWidget(proba_frein_moins, 9, 1);
	onglet1->addWidget(proba_frein_affiche, 9, 2);
	onglet1->addWidget(proba_frein_plus, 9, 3);
	onglet1->addWidget(proba_frein_plus2, 9, 4);

	onglet1->addWidget(proba_redemar, 10, 0, 1, 5);
	onglet1->addWidget(proba_redemar_moins2, 11, 0);
	onglet1->addWidget(proba_redemar_moins, 11, 1);
	onglet1->addWidget(proba_redemar_affiche, 11, 2);
	onglet1->addWidget(proba_redemar_plus, 11, 3);
	onglet1->addWidget(proba_redemar_plus2, 11, 4);

	onglet1->addWidget(proba_depass, 12, 0, 1, 5);
	onglet1->addWidget(proba_depass_moins2, 13, 0);
	onglet1->addWidget(proba_depass_moins, 13, 1);
	onglet1->addWidget(proba_depass_affiche, 13, 2);
	onglet1->addWidget(proba_depass_plus, 13, 3);
	onglet1->addWidget(proba_depass_plus2, 13, 4);

	onglet1->addWidget(limite_vitesse, 14, 0, 1, 5);
	onglet1->addWidget(limite_vitesse_moins2, 15, 0);
	onglet1->addWidget(limite_vitesse_moins, 15, 1);
	onglet1->addWidget(limite_vitesse_affiche, 15, 2);
	onglet1->addWidget(limite_vitesse_plus, 15, 3);
	onglet1->addWidget(limite_vitesse_plus2, 15, 4);

	onglet1->addWidget(taille_de_route, 16, 0, 1, 5);
	onglet1->addWidget(taille_de_route_moins2, 17, 0);
	onglet1->addWidget(taille_de_route_moins, 17, 1);
	onglet1->addWidget(taille_de_route_affiche, 17, 2);
	onglet1->addWidget(taille_de_route_plus, 17, 3);
	onglet1->addWidget(taille_de_route_plus2, 17, 4);

	onglet1->addWidget(nb_de_liaison, 18, 0, 1, 5);
	onglet1->addWidget(nb_de_liaison_moins2, 19, 0);
	onglet1->addWidget(nb_de_liaison_moins, 19, 1);
	onglet1->addWidget(nb_de_liaison_affiche, 19, 2);
	onglet1->addWidget(nb_de_liaison_plus, 19, 3);
	onglet1->addWidget(nb_de_liaison_plus2, 19, 4);

	QWidget *contOnglet2 = new QWidget;
	QGridLayout *onglet2 = new QGridLayout;

	// Onglet 2.
	QLabel *vitDeDef = new QLabel("Vitesse de défilement");
	QPushButton *vitDeDef_moins = new QPushButton("<");
	QPushButton *vitDeDef_moins2 = new QPushButton("<<");
	QPushButton *vitDeDef_plus = new QPushButton(">");
	QPushButton *vitDeDef_plus2 = new QPushButton(">>");
	vitDeDef_affiche = new QLabel;

	QLabel *modeAffiche = new QLabel("Mode d'affichage de la route");
	QPushButton *modeAffiche_moins = new QPushButton("<");
	QPushButton *modeAffiche_plus = new QPushButton(">");
	modeAffiche_affiche = new QLabel;

	QLabel *nbEtape = new QLabel("Nombre d'étape");
	QPushButton *nbEtape_moins = new QPushButton("<");
	QPushButton *nbEtape_moins2 = new QPushButton("<<");
	QPushButton *nbEtape_plus = new QPushButton(">");
	QPushButton *nbEtape_plus2 = new QPushButton(">>");
	nbEtape_affiche = new QLabel;

	onglet2->addWidget(vitDeDef, 0, 0, 1, 5);
	onglet2->addWidget(vitDeDef_moins2, 1, 0);
	onglet2->addWidget(vitDeDef_moins, 1, 1);
	onglet2->addWidget(vitDeDef_affiche, 1, 2);
	onglet2->addWidget(vitDeDef_plus, 1, 3);
	onglet2->addWidget(vitDeDef_plus2, 1, 4);

	onglet2->addWidget(modeAffiche, 2, 0, 1, 5);
	onglet2->addWidget(modeAffiche_moins, 3, 1);
	onglet2->addWidget(modeAffiche_affiche, 3, 2);
	onglet2->addWidget(modeAffiche_plus, 3, 3);

	onglet2->addWidget(nbEtape, 4, 0, 1, 5);
	onglet2->addWidget(nbEtape_moins2, 5, 0);
	onglet2->addWidget(nbEtape_moins, 5, 1);
	onglet2->addWidget(nbEtape_affiche, 5, 2);
	onglet2->addWidget(nbEtape_plus, 5, 3);
	onglet2->addWidget(nbEtape_plus2, 5, 4);

	QWidget *contOnglet3 = new QWidget;
	QGridLayout *onglet3 = new QGridLayout;

	// Onglet 3.
	QLabel *nbRembobi = new QLabel("Nombre de rembobinage");
	QPushButton *nbRembobi_moins = new QPushButton("<");
	QPushButton *nbRembobi_moins2 = new QPushButton("<<");
	QPushButton *nbRembobi_plus = new QPushButton(">");
	QPushButton *nbRembobi_plus2 = new QPushButton(">>");
	nbRembobi_affiche = new QLabel;

	QLabel *numRembobi = new QLabel("Enregistrement numéro");
	QPushButton *numRembobi_moins = new QPushButton("<");
	QPushButton *numRembobi_plus = new QPushButton(">");
	numRembobi_affiche = new QLabel;

	onglet3->addWidget(nbRembobi, 0, 0, 1, 5);
	onglet3->addWidget(nbRembobi_moins2, 1, 0);
	onglet3->addWidget(nbRembobi_moins, 1, 1);
	onglet3->addWidget(nbRembobi_affiche, 1, 2);
	onglet3->addWidget(nbRembobi_plus, 1, 3);
	onglet3->addWidget(nbRembobi_plus2, 1, 4);

	onglet3->addWidget(numRembobi, 2, 0, 1, 5);
	onglet3->addWidget(numRembobi_moins, 3, 1);
	onglet3->addWidget(numRembobi_affiche, 3, 2);
	onglet3->addWidget(numRembobi_plus, 3, 3);

	contOnglet1->setLayout(onglet1);
	onglets->addTab(contOnglet1, "Gestion des routes");
	contOnglet2->setLayout(onglet2);
	onglets->addTab(contOnglet2, "Affichage");
	contOnglet3->setLayout(onglet3);
	onglets->addTab(contOnglet3, "Rembobinage");

	layoutPrincipal->addWidget(onglets, 2, 0, 1, 3);

	QPushButton *pause = new QPushButton("Pause");
	QPushButton *aide = new QPushButton("Aide");
	QPushButton *quitter = new QPushButton("Quitter");
	layoutPrincipal->addWidget(pause, 3, 0);
	layoutPrincipal->addWidget(aide, 3, 1);
	layoutPrincipal->addWidget(quitter, 3, 2);

	connect(pause, SIGNAL(clicked()), this, SLOT(pause()));
	connect(aide, SIGNAL(clicked()), this, SLOT(aide()));
	connect(quitter, SIGNAL(clicked()), qApp, SLOT(quit()));

	centre->setLayout(layoutPrincipal);
	setCentralWidget(centre);

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(plusUn()));
	timer->start(r.vitesse());

	connect(nb_de_route_moins, SIGNAL(clicked()), this, SLOT(nbRouteM()));
	connect(nb_de_route_moins2, SIGNAL(clicked()), this, SLOT(nbRouteM2()));
	connect(nb_de_route_plus, SIGNAL(clicked()), this, SLOT(nbRouteP()));
	connect(nb_de_route_plus2, SIGNAL(clicked()), this, SLOT(nbRouteP2()));

	connect(num_de_route_moins, SIGNAL(clicked()), this, SLOT(numRouteM()));
	connect(num_de_route_plus, SIGNAL(clicked()), this, SLOT(numRouteP()));

	connect(nb_de_voiture_moins, SIGNAL(clicked()), this, SLOT(nbVoitureM()));
	connect(nb_de_voiture_moins2, SIGNAL(clicked()), this, SLOT(nbVoitureM2()));
	connect(nb_de_voiture_plus, SIGNAL(clicked()), this, SLOT(nbVoitureP()));
	connect(nb_de_voiture_plus2, SIGNAL(clicked()), this, SLOT(nbVoitureP2()));

	connect(mode_change, SIGNAL(clicked()), this, SLOT(changeMode()));

	connect(proba_frein_moins, SIGNAL(clicked()), this, SLOT(probaFreinM()));
	connect(proba_frein_moins2, SIGNAL(clicked()), this, SLOT(probaFreinM2()));
	connect(proba_frein_plus, SIGNAL(clicked()), this, SLOT(probaFreinP()));
	connect(proba_frein_plus2, SIGNAL(clicked()), this, SLOT(probaFreinP2()));

	connect(proba_redemar_moins, SIGNAL(clicked()), this, SLOT(probaRedemarM()));
	connect(proba_redemar_moins2, SIGNAL(clicked()), this, SLOT(probaRedemarM2()));
	connect(proba_redemar_plus, SIGNAL(clicked()), this, SLOT(probaRedemarP()));
	connect(proba_redemar_plus2, SIGNAL(clicked()), this, SLOT(probaRedemarP2()));

	connect(proba_depass_moins, SIGNAL(clicked()), this, SLOT(probaDepassM()));
	connect(proba_depass_moins2, SIGNAL(clicked()), this, SLOT(probaDepassM2()));
	connect(proba_depass_plus, SIGNAL(clicked()), this, SLOT(probaDepassP()));
	connect(proba_depass_plus2, SIGNAL(clicked()), this, SLOT(probaDepassP2()));

	connect(limite_vitesse_moins, SIGNAL(clicked()), this, SLOT(limiteVitesseM()));
	connect(limite_vitesse_moins2, SIGNAL(clicked()), this, SLOT(limiteVitesseM2()));
	connect(limite_vitesse_plus, SIGNAL(clicked()), this, SLOT(limiteVitesseP()));
	connect(limite_vitesse_plus2, SIGNAL(clicked()), this, SLOT(limiteVitesseP2()));

	connect(taille_de_route_moins, SIGNAL(clicked()), this, SLOT(tailleRouteM()));
	connect(taille_de_route_moins2, SIGNAL(clicked()), this, SLOT(tailleRouteM2()));
	connect(taille_de_route_plus, SIGNAL(clicked()), this, SLOT(tailleRouteP()));
	connect(taille_de_route_plus2, SIGNAL(clicked()), this, SLOT(tailleRouteP2()));

	connect(nb_de_liaison_moins, SIGNAL(clicked()), this, SLOT(nbLiaisonM()));
	connect(nb_de_liaison_moins2, SIGNAL(clicked()), this, SLOT(nbLiaisonM2()));
	connect(nb_de_liaison_plus, SIGNAL(clicked()), this, SLOT(nbLiaisonP()));
	connect(nb_de_liaison_plus2, SIGNAL(clicked()), this, SLOT(nbLiaisonP2()));

	connect(vitDeDef_moins, SIGNAL(clicked()), this, SLOT(vitDeDefM()));
	connect(vitDeDef_moins2, SIGNAL(clicked()), this, SLOT(vitDeDefM2()));
	connect(vitDeDef_plus, SIGNAL(clicked()), this, SLOT(vitDeDefP()));
	connect(vitDeDef_plus2, SIGNAL(clicked()), this, SLOT(vitDeDefP2()));

	connect(modeAffiche_moins, SIGNAL(clicked()), this, SLOT(modeAfficheM()));
	connect(modeAffiche_plus, SIGNAL(clicked()), this, SLOT(modeAfficheP()));

	connect(nbEtape_moins, SIGNAL(clicked()), this, SLOT(nbEtapeM()));
	connect(nbEtape_moins2, SIGNAL(clicked()), this, SLOT(nbEtapeM2()));
	connect(nbEtape_plus, SIGNAL(clicked()), this, SLOT(nbEtapeP()));
	connect(nbEtape_plus2, SIGNAL(clicked()), this, SLOT(nbEtapeP2()));

	connect(nbRembobi_moins, SIGNAL(clicked()), this, SLOT(nbRembobiM()));
	connect(nbRembobi_moins2, SIGNAL(clicked()), this, SLOT(nbRembobiM2()));
	connect(nbRembobi_plus, SIGNAL(clicked()), this, SLOT(nbRembobiP()));
	connect(nbRembobi_plus2, SIGNAL(clicked()), this, SLOT(nbRembobiP2()));

	connect(numRembobi_moins, SIGNAL(clicked()), this, SLOT(numRembobiM()));
	connect(numRembobi_plus, SIGNAL(clicked()), this, SLOT(numRembobiP()));
}

void Interface::plusUn()
{
	r.plusEtape();
	actualiserAffichage();
}

void Interface::actualiserAffichage()
{
	afficheRoute->setText(QString::fromStdString(r.affichageRoutes()));
	nb_de_route_affiche->setText(QString::fromStdString(std::to_string(r.getNbRoutes())));
	num_de_route_affiche->setText(QString::fromStdString(std::to_string(r.getNumRoute())));
	nb_de_voiture_affiche->setText(QString::fromStdString(std::to_string(r.getNbVoiture())));
	if (r.getMode() == 0)
	{
		mode_affiche->setText("Nash");
		mode_change->setText("VDR");
	}
	else
	{
		mode_affiche->setText("VDR");
		mode_change->setText("Nash");
	}
	proba_frein_affiche->setText(QString::fromStdString(std::to_string(r.getProbaFrein())));
	proba_redemar_affiche->setText(QString::fromStdString(std::to_string(r.getProbaRedemar())));
	proba_depass_affiche->setText(QString::fromStdString(std::to_string(r.getProbaDepass())));
	limite_vitesse_affiche->setText(QString::fromStdString(std::to_string(r.getLimiteVitesse())));
	taille_de_route_affiche->setText(QString::fromStdString(std::to_string(r.getTailleRoute())));
	nb_de_liaison_affiche->setText(QString::fromStdString(std::to_string(r.getNbLiaison())));
	vitDeDef_affiche->setText(QString::fromStdString(std::to_string(r.vitesse())));
	if (r.getModeAffiche() == 0)
	{
		modeAffiche_affiche->setText("Immatriculation et Vitesse");
	}
	else if (r.getModeAffiche() == 1)
	{
		modeAffiche_affiche->setText("Vitesse");
	}
	else
	{
		modeAffiche_affiche->setText("Immatriculation");
	}
	nbEtape_affiche->setText(QString::fromStdString(std::to_string(r.getEtape())));
	nbRembobi_affiche->setText(QString::fromStdString(std::to_string(r.getNbRembob())));
	numRembobi_affiche->setText(QString::fromStdString(std::to_string(r.getNumRembob())));
}

void Interface::pause()
{
	r.setTouche(32);
	actualiserAffichage();
}

void Interface::aide()
{
	QMessageBox::question(this, "Aide de PcSimuLesBouchons", QString::fromStdString(r.help()));
}

void Interface::nbRouteM()
{
	r.setPositionCurseur(0);
	r.setTouche(75);
	actualiserAffichage();
}

void Interface::nbRouteM2()
{
	r.setPositionCurseur(0);
	r.setTouche(45);
	actualiserAffichage();
}

void Interface::nbRouteP()
{
	r.setPositionCurseur(0);
	r.setTouche(77);
	actualiserAffichage();
}

void Interface::nbRouteP2()
{
	r.setPositionCurseur(0);
	r.setTouche(43);
	actualiserAffichage();
}

void Interface::numRouteM()
{
	r.setPositionCurseur(1);
	r.setTouche(75);
	actualiserAffichage();
}

void Interface::numRouteP()
{
	r.setPositionCurseur(1);
	r.setTouche(77);
	actualiserAffichage();
}

void Interface::nbVoitureM()
{
	r.setPositionCurseur(2);
	r.setTouche(75);
	actualiserAffichage();
}

void Interface::nbVoitureM2()
{
	r.setPositionCurseur(2);
	r.setTouche(45);
	actualiserAffichage();
}

void Interface::nbVoitureP()
{
	r.setPositionCurseur(2);
	r.setTouche(77);
	actualiserAffichage();
}

void Interface::nbVoitureP2()
{
	r.setPositionCurseur(2);
	r.setTouche(43);
	actualiserAffichage();
}

void Interface::changeMode()
{
	r.setPositionCurseur(3);
	if (r.getMode() == 0)
	{
		r.setTouche(77);
	}
	else
	{
		r.setTouche(75);
	}
	actualiserAffichage();
}

void Interface::probaFreinM()
{
	r.setPositionCurseur(4);
	r.setTouche(75);
	actualiserAffichage();
}

void Interface::probaFreinM2()
{
	r.setPositionCurseur(4);
	r.setTouche(45);
	actualiserAffichage();
}

void Interface::probaFreinP()
{
	r.setPositionCurseur(4);
	r.setTouche(77);
	actualiserAffichage();
}

void Interface::probaFreinP2()
{
	r.setPositionCurseur(4);
	r.setTouche(43);
	actualiserAffichage();
}

void Interface::probaRedemarM()
{
	r.setPositionCurseur(5);
	r.setTouche(75);
	actualiserAffichage();
}

void Interface::probaRedemarM2()
{
	r.setPositionCurseur(5);
	r.setTouche(45);
	actualiserAffichage();
}

void Interface::probaRedemarP()
{
	r.setPositionCurseur(5);
	r.setTouche(77);
	actualiserAffichage();
}

void Interface::probaRedemarP2()
{
	r.setPositionCurseur(5);
	r.setTouche(43);
	actualiserAffichage();
}

void Interface::probaDepassM()
{
	r.setPositionCurseur(6);
	r.setTouche(75);
	actualiserAffichage();
}

void Interface::probaDepassM2()
{
	r.setPositionCurseur(6);
	r.setTouche(45);
	actualiserAffichage();
}

void Interface::probaDepassP()
{
	r.setPositionCurseur(6);
	r.setTouche(77);
	actualiserAffichage();
}

void Interface::probaDepassP2()
{
	r.setPositionCurseur(6);
	r.setTouche(43);
	actualiserAffichage();
}

void Interface::limiteVitesseM()
{
	r.setPositionCurseur(7);
	r.setTouche(75);
	actualiserAffichage();
}

void Interface::limiteVitesseM2()
{
	r.setPositionCurseur(7);
	r.setTouche(45);
	actualiserAffichage();
}

void Interface::limiteVitesseP()
{
	r.setPositionCurseur(7);
	r.setTouche(77);
	actualiserAffichage();
}

void Interface::limiteVitesseP2()
{
	r.setPositionCurseur(7);
	r.setTouche(43);
	actualiserAffichage();
}

void Interface::tailleRouteM()
{
	r.setPositionCurseur(8);
	r.setTouche(75);
	actualiserAffichage();
}

void Interface::tailleRouteM2()
{
	r.setPositionCurseur(8);
	r.setTouche(45);
	actualiserAffichage();
}

void Interface::tailleRouteP()
{
	r.setPositionCurseur(8);
	r.setTouche(77);
	actualiserAffichage();
}

void Interface::tailleRouteP2()
{
	r.setPositionCurseur(8);
	r.setTouche(43);
	actualiserAffichage();
}

void Interface::nbLiaisonM()
{
	r.setPositionCurseur(9);
	r.setTouche(75);
	actualiserAffichage();
}

void Interface::nbLiaisonM2()
{
	r.setPositionCurseur(9);
	r.setTouche(45);
	actualiserAffichage();
}

void Interface::nbLiaisonP()
{
	r.setPositionCurseur(9);
	r.setTouche(77);
	actualiserAffichage();
}

void Interface::nbLiaisonP2()
{
	r.setPositionCurseur(9);
	r.setTouche(43);
	actualiserAffichage();
}

void Interface::vitDeDefM()
{
	r.setPositionCurseur(10);
	r.setTouche(75);
	actualiserAffichage();
	timer->start(r.vitesse());
}

void Interface::vitDeDefM2()
{
	r.setPositionCurseur(10);
	r.setTouche(45);
	actualiserAffichage();
	timer->start(r.vitesse());
}

void Interface::vitDeDefP()
{
	r.setPositionCurseur(10);
	r.setTouche(77);
	actualiserAffichage();
	timer->start(r.vitesse());
}

void Interface::vitDeDefP2()
{
	r.setPositionCurseur(10);
	r.setTouche(43);
	actualiserAffichage();
	timer->start(r.vitesse());
}

void Interface::modeAfficheM()
{
	r.setPositionCurseur(11);
	r.setTouche(75);
	actualiserAffichage();
	timer->start(r.vitesse());
}

void Interface::modeAfficheP()
{
	r.setPositionCurseur(11);
	r.setTouche(77);
	actualiserAffichage();
	timer->start(r.vitesse());
}

void Interface::nbEtapeM()
{
	r.setPositionCurseur(12);
	r.setTouche(75);
	actualiserAffichage();
}

void Interface::nbEtapeM2()
{
	r.setPositionCurseur(12);
	r.setTouche(45);
	actualiserAffichage();
}

void Interface::nbEtapeP()
{
	r.setPositionCurseur(12);
	r.setTouche(77);
	actualiserAffichage();
}

void Interface::nbEtapeP2()
{
	r.setPositionCurseur(12);
	r.setTouche(43);
	actualiserAffichage();
}

void Interface::nbRembobiM()
{
	r.setPositionCurseur(13);
	r.setTouche(75);
	actualiserAffichage();
}

void Interface::nbRembobiM2()
{
	r.setPositionCurseur(13);
	r.setTouche(45);
	actualiserAffichage();
}

void Interface::nbRembobiP()
{
	r.setPositionCurseur(13);
	r.setTouche(77);
	actualiserAffichage();
}

void Interface::nbRembobiP2()
{
	r.setPositionCurseur(13);
	r.setTouche(43);
	actualiserAffichage();
}

void Interface::numRembobiM()
{
	r.setPositionCurseur(14);
	r.setTouche(75);
	actualiserAffichage();
}

void Interface::numRembobiP()
{
	r.setPositionCurseur(14);
	r.setTouche(77);
	actualiserAffichage();
}
