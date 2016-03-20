# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include <string.h>
#include <assert.h>


# define TAILLE_MAX 1024


int callFunction(const char *function) {
	/*
	On récupère la séquence, on sépare les differentes commandes (les operateurs)
	*/
	char *commande[TAILLE_MAX];
	char libdir[2048]; // Current Working Directory
	int status = 0;

	// On coupe la fonction

	//printf(function);
	sprintf(commande[0], "./lib/%s", function);
	//puts(commande);
	// On va vérifier que l'executable existe avant d'essayer de le lancer du lib.
	// Si il n'existe pas on va ensuite regarder dans le répertoire courant.
	// Et si il n'y est pas non plus on va simplement afficher que la commande est inconnue.
	status = system(commande[0]);
	return status;

}
