// --------------------------------
// Auteur : Alexandre l'Heritier
// Projet Bouchon v0.6
// --------------------------------
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>
#include <chrono>
#include "GestiRoute.h"

using namespace std::chrono;
using namespace std;

int time_start_value;
int time_end_value;

void init_timer() {
	time_start_value = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

bool has_passed(unsigned int arg_time) {
	time_end_value = duration_cast< milliseconds >(system_clock::now().time_since_epoch()).count();
	return (time_end_value - time_start_value >= arg_time);
}

#ifdef _WIN32
	#include <windows.h>
	#include <conio.h>

	#define PRESSEDKEY _kbhit()
	#define GETKEY _getch()
	#define CLEAR system("cls")
	#define KEYINIT 0
	#define KEYEND  0
	#ifndef NULL 
	#define NULL 0
#endif 

#else
	#include <stdio.h>
	#include <termios.h>
	#include <unistd.h>
	#include <sys/types.h>
	#include <sys/time.h>

	void changemode(int dir)
	{
		static struct termios oldt, newt;

		if (dir == 1)
		{
			tcgetattr(STDIN_FILENO, &oldt);
			newt = oldt;
			newt.c_lflag &= ~(ICANON | ECHO);
			tcsetattr(STDIN_FILENO, TCSANOW, &newt);
		}
		else
			tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	}

	int _kbhit(void)
	{
		struct timeval tv;
		fd_set rdfs;

		tv.tv_sec = 0;
		tv.tv_usec = 0;

		FD_ZERO(&rdfs);
		FD_SET(STDIN_FILENO, &rdfs);

		select(STDIN_FILENO + 1, &rdfs, NULL, NULL, &tv);
		return FD_ISSET(STDIN_FILENO, &rdfs);
	}

	#define PRESSEDKEY _kbhit()
	#define GETKEY getchar()
	#define CLEAR system("clear")
	#define KEYINIT changemode(1)
	#define KEYEND  changemode(0)
	#ifndef NULL 
	#define NULL 0
#endif 
#endif

int main() 
{
	bool arret = false;
	int nb_voiture = 10;
	GestiRoute r = GestiRoute(nb_voiture);

	while (!arret)
	{
		CLEAR;
		r.affichageRoutes();
		r.affichageCommandes();
		init_timer();
		while (!has_passed(r.vitesse()))
		{
			if (PRESSEDKEY)
			{
				r.setTouche(GETKEY);
				CLEAR;
				r.affichageRoutes();
				r.affichageCommandes();
			}
		}
		r.plusEtape();
	}
	return 0;
}

/**
Changelog :
A venir :
Readme Github.
Passage de version beta en version stable.
Passage de l'affichage version beta en affichage version finale.
Ajout des commentaires.
Nettoyage du code.
Optimisation du code.

v0.6 :
(build 140/13/04/2017)
Gestion de la liaison de route pour le d�passement de voiture dans GestiRoute.
Integration des liaisons dans toutes les fonctions existante.
Corrections dans les Route::ajouteVoiture et dans les Route::enleveVoiture pour corriger probleme de multiple voiture avec la meme immatriculation.
Cr�ation de Route::actualiserTabVoiture() pour r�soudre des bugs de comparaison de voiture.
Amelioration de GestiRoute::affichageRoute() pour le multi-liaison.
Ajout et suppression des voitures en prenant en compte les voitures sur les liaisons.
Commandes pour controler les routes misent dans GestiRoute pour pouvoir gerer les liaisons avec les routes.
Ajout des touches + et - pour accelerer la vitesse de changement de commande.
Verification de toutes les modifications et des integrations dans les fonctions existante.

v0.5 :
(build 104/09/04/2017)
Verification compl�te de la methode Route::modele apr�s la d�couverte d'un bug de remplacement de voiture.
Debuggage de la methode Route::modele() avec le debuggeur VS++.
 : - Correction de quelques lignes avec des calculs erron�s.
   - Verification de la partie permettant d'avancer les voitures avec leurs vitesses.
   - Lisibilit� du code accrue.
Possibilit� de mettre en pause la simulation.
Possibilit� de mettre plusieurs routes.
Bug au niveau des "voitures fantomes" resolu.
Taille de route par defaut passe de 18*3 a 10*2.
Gestion du multi-route ajouter dans l'affichage.

v0.4 :
(build 72/06/04/2017)
Cr�ation de GestiRoute, qui permet de g�rer compl�tement une Route :
- Affichage version test.
- Une seule route pour l'instant
Refonte du main.cpp pour GestiRoute.


v0.3 :
(build 65/06/04/2017)

Gestion des commandes (inclut tous les syst�mes d'exploitation (UNIX/WIN)).
Am�lioration de la fonction temporaire d'affichage.
Cr�ation d'un chrono pour la vitesse de la route.
Classe Route am�lior� (ajout et suppression de voiture facilit�s).
Ajout d'un operator pour comparer les voitures.
Correction d'un bug touchant l'al�atoire (le srand �tait mal plac�).


v0.2 :
(build 32/02/04/2017)

Corrections de bugs pour le d�placement de voiture dans la fonction Route::modeleNash().
Un constructeur enlev� dans Route.


v0.1 : 
(build 1/02/04/2017)

Dans class Route :
Route(int nbVoiture);
Route(int nbVoiture, int limite);
Route(int nbVoiture, int limite, int tailleRoute);
void ajouterVoiture(int numVoiture);
void enleverVoiture(int numVoiture);
void placementAleatoireDepart();
void tempsPlus(int temps);
std::vector<int> tabAffiche();
int tailleRoute();
void setLimiteVitesse(int vit);
int espaceAvant(int imaticulation);
void setProbaFrein(int pourcent);

std::vector<Voiture> tabVoiture;
std::vector<Voiture> tabRoute;
int limiteDeVitesse;
int probaFrein;

void modeleNash();
bool determineFrein();

Dans class Voiture :
Voiture();
Voiture(int numero);
Voiture(int numero, int vitess);
void setImatriculation(int numero);
void setVitesse(int vitess);
int getImatriculation();
int getVitesse();

int vitesse;
int imatriculation;

Premi�re version du projet bouchon.
D�but : 01/04/2017
**/
