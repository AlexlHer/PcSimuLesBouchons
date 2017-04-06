// --------------------------------
// Auteur : Alexandre l'Heritier
// Projet Bouchon v0.4
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
	int nb_voiture = 18;
	GestiRoute r = GestiRoute(nb_voiture);

	while (!arret)
	{
		r.affichageRoutes();
		r.plusEtape();
		init_timer();
		while (!has_passed(1000))
		{
			CLEAR;
			r.affichageCommandes();
			if (PRESSEDKEY)
			{
				r.setTouche(GETKEY);
			}
		}
	}
	return 0;
}

/**
Changelog :

v0.4 :
(build 72/06/04/2017)
Création de GestiRoute, qui permet de gérer complétement une Route :
- Affichage version test.
- Une seule route pour l'instant
Refonte du main.cpp pour GestiRoute.


v0.3 :
(build 65/06/04/2017)

Gestion des commandes (inclut tous les systèmes d'exploitation (UNIX/WIN)).
Amélioration de la fonction temporaire d'affichage.
Création d'un chrono pour la vitesse de la route.
Classe Route amélioré (ajout et suppression de voiture facilités).
Ajout d'un operator pour comparer les voitures.
Correction d'un bug touchant l'aléatoire (le srand était mal placé).


v0.2 :
(build 32/02/04/2017)

Corrections de bugs pour le déplacement de voiture dans la fonction Route::modeleNash().
Un constructeur enlevé dans Route.


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

Première version du projet bouchon.
Début : 01/04/2017
**/
