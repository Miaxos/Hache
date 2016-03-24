# Hache
[![build status](https://gitlab.univ-nantes.fr/E158196C/Hache/badges/master/build.svg)](https://gitlab.univ-nantes.fr/E158196C/Hache?ref=master)

## Prérequis

- GCC >= 5.3

## Introduction

Hache, projet C à rentre pour le 08/04/2016 à 23h59.
Le projet fonctionnel ainsi qu’un rapport technique doit être rendu (utiliser le mini-cours sur les appels systèmes et structures).

Il s’agit d’un Shell interactif en C. Le but est d’implémenter notre propre version de bash en C.

Nous serons notés sur:
 
	- Fonctionnement général de l’application (plantages…)
	- La qualité du code (gestion mémoire…)
	- Utilisation d’analyseurs statiques (cppchecker, frama-c,…)
	- Utilisation d’analyseurs dynamiques (valgrind…)
	- Débuggeurs.
	- La propreté du code (commentaires, indentation, …)
	- Compilation à l’aide d’un MakeFile.

## Division du travail

Le travail se divise en 2 binômes:

- Le premier travaille sur l’interpréteur de commande.
- Le second sur l’implémentation des commandes usuelles.

### Interpréteur de commande (ANTHONY et ELIOT)

Codage de l’interpréteur de commande (type bash). Il doit:

	- Proposer un prompt à l’utilisateur.
	- Analyse la ligne de commande pour exécuter des fonctions (Commandes intégrés du binôme #2 et les programmes utilisateurs).
	- Prise en compte des opérateurs de redirection.
	- Possibilité de se connecter en réseau avec une commande « connect » (Sorte de ssh).

### Commandes usuelles (MERIEM et AXEL)

Placez vos commandes (.c) dans le répertoire "commands".<br />
Ajoutez au makefile, pour chaque commande "mycommande.c" :<br />

mycommande.o: ./commands/mymycommande.c<br />
&nbsp;&nbsp;&nbsp;&nbsp;gcc -c ./commands/mycomande.c -o ./build/mycommande.o -Wall

Commandes à faire au minimum :

- ls
- cd
- cp
- mv
- mkdir
- clear (qui efface l'écran)

## Construction du terminal

L'arborescence une fois le build terminé sera sous cette forme:

	- /src/ contient les sources (.c) du shell
	- /commands/ contient les sources (.c) des commandes [cp, cd, ls, man, ...]
	- /inc/ contient les headers des sources de /src/
	- /build/ contient les fichiers .o réalisés au make
	- /bin/ contient l'executable

## Mode d'emploi

Pour compiler le programme :<br />
&nbsp;&nbsp;&nbsp;&nbsp;1) Se placer à la racine du projet<br />
&nbsp;&nbsp;&nbsp;&nbsp;2) make

Pour supprimer les fichiers .o :<br />
&nbsp;&nbsp;&nbsp;&nbsp;1) Se placer à la racine du projet<br />
&nbsp;&nbsp;&nbsp;&nbsp;2) make clean

Pour supprimer les fichiers .o et l'executable :<br />
&nbsp;&nbsp;&nbsp;&nbsp;1) Se placer à la racine du projet<br />
&nbsp;&nbsp;&nbsp;&nbsp;2) make proper	

Pour lancer le programme :<br />
&nbsp;&nbsp;&nbsp;&nbsp;1) Se placer dans le répertoire /bin/<br />
&nbsp;&nbsp;&nbsp;&nbsp;2) ./test


