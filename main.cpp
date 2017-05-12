// --------------------------------
// Auteur : Alexandre l'Heritier
// PcSimuLesBouchons v3.0
// --------------------------------

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "GestiRoute.h"

using namespace std::chrono;
using namespace std;

// Variables globales pour gérer le chrono.
int time_start_value;
int time_end_value;

// Procédure permettant d'initialiser le chrono.
void init_timer() {
	time_start_value = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

/*
Fonction permettant de savoir si le temps arg_time est passé.
@param Le temps en miliseconde.
@return un booleen true si le temps arg_time est passé, false sinon.
*/
bool has_passed(unsigned int arg_time) {
	time_end_value = duration_cast< milliseconds >(system_clock::now().time_since_epoch()).count();
	return (time_end_value - time_start_value >= arg_time);
}


// Blocs permettant de definir des "raccourcis" pour capturer les touches et autres, selon le systeme d'exploitation.
// Windows
#ifdef _WIN32
#include <windows.h>
#include <conio.h>

#define AppuiTouche _kbhit()
#define Clavier _getch()
#define Clear system("cls")

// UNIX (MACOS/LINUX)
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

#define AppuiTouche _kbhit()
#define Clavier getchar()
#define Clear system("clear")
#endif

// Fonction principale.
int main()
{
	// On crée un GestiRoute pour gérer plusieurs routes. On met 10 voitures sur la route par défaut.
	GestiRoute r = GestiRoute(10);

	// Tant que getQuit renvoi false.
	while (!r.getQuit())
	{
		// Partie qui sera affiché toutes les r.vitesse() ms.
		r.sortieAffichage();

		// On initialise le chrono.
		init_timer();

		// La boucle tourne tant que r.vitesse() ms n'est pas écoulée.
		while (!has_passed(r.vitesse()))
		{
			// Si on appuie sur une touche.
			if (AppuiTouche)
			{
				// On donne la touche à r.
				r.setTouche(Clavier);
				// On affiche les routes et les commandes à chaque fois qu'on appuie sur une touche.
				r.sortieAffichage();
			}
		}
		// On fait avancer la route le nombre de fois voulu.
		r.plusEtape();
	}
	return 0;
}

/**
Changelog :

v3.0 : (version SuperStable)
(build 186/28/04/2017)
Optimisation de l'affichage pour éviter trop de clignotement (mais impossible de les enlever pour l'instant).
Modification de l'affichage des commandes :
- Tri en fonction des commandes.
- Affichage de catégories.
Ajout de condition pour le depassement de voitures.
Optimisations au niveau des determine_proba dans Route et GestiRoute.
[Maj du projet Visual Studio 2015 vers Visual Studio 2017]

v2.0 : (version SuperStable)
(build 170/24/04/2017)
Changement de l'algorithme de dépassement des voitures dans les liaisons.
Construction des fonctions permettant un retour arrière !
Ajout des touches Début et Fin pour l'interface.
Vitesse limité au nombre de case -1, liée à Route::espaceAvant qui détermine que la voiture
de devant est elle_même. Pas utile de résoudre cela puisque l'interet de mettre une seule voiture sur
la route est nul.
Correction de la boucle infinie lorsqu'une liaison est vide et qu'elle passe dans gestiLiaison.
Bug dans supprimeLiaison résolu.
Bug de compilation g++ résolu (compilateur testés : VS++ et g++).
Encore un peu de commentaire !
Déplacement de ajouterRembobinage() de affichageRoute à etapePlus pour éviter les "trous" dans les enregistrement dù à l'appuie sur les touches.

v1.0 :
(build 152/23/04/2017)
Projet bouchon devient PcSimuLesBouchons (ou PcSLB).
Sortie de beta pour l'affichage.
Help integré.
Pause améliorée.
Bug resolu : Quand on enleve une route et que cette route est séléctionnée.
Activation du mode VDR en changant proba q.
Possibilité de modifier la limite de vitesse.
Code de l'affichage amélioré.
Bugs restant.

Version BetaNonStable :
v0.6 :
(build 140/13/04/2017)
Gestion de la liaison de route pour le dépassement de voiture dans GestiRoute.
Integration des liaisons dans toutes les fonctions existante.
Corrections dans les Route::ajouteVoiture et dans les Route::enleveVoiture pour corriger probleme de multiple voiture avec la meme immatriculation.
Création de Route::actualiserTabVoiture() pour résoudre des bugs de comparaison de voiture.
Amelioration de GestiRoute::affichageRoute() pour le multi-liaison.
Ajout et suppression des voitures en prenant en compte les voitures sur les liaisons.
Commandes pour controler les routes misent dans GestiRoute pour pouvoir gerer les liaisons avec les routes.
Ajout des touches + et - pour accelerer la vitesse de changement de commande.
Verification de toutes les modifications et des integrations dans les fonctions existante.

v0.5 :
(build 104/09/04/2017)
Verification complète de la methode Route::modele après la découverte d'un bug de remplacement de voiture.
Debuggage de la methode Route::modele() avec le debuggeur VS++.
: - Correction de quelques lignes avec des calculs erronés.
- Verification de la partie permettant d'avancer les voitures avec leurs vitesses.
- Lisibilité du code accrue.
Possibilité de mettre en pause la simulation.
Possibilité de mettre plusieurs routes.
Bug au niveau des "voitures fantomes" resolu.
Taille de route par defaut passe de 18*3 a 10*2.
Gestion du multi-route ajouter dans l'affichage.

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
