# PcSimuLesBouchons (ou PcSLB)
## Par Alexandre l'Heritier
Projet final d'Info121 du deuxième semestre de MPI.
Ce projet consiste à simuler une route avec des voitures pouvant créer des bouchons.

## ChangeLog de la dernière version (v2.0) : 
## (version SuperStable)
## (build 170/24/04/2017)

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
