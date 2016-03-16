# Hache

Build IMG

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

### Interpréteur de commande

Codage de l’interpréteur de commande (type bash). Il doit:

	- Proposer un prompt à l’utilisateur.
	- Analyse la ligne de commande pour exécuter des fonctions (Commandes intégrés du binôme #2 et les programmes utilisateurs).
	- Prise en compte des opérateurs de redirection.
	- Possibilité de se connecter en réseau avec une commande « connect » (Sorte de ssh).

### Commandes usuelles

(A faire)





