# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define TAILLE_MAX 1024

int callFunction(const char *function) {
	char *commande[TAILLE_MAX];
	char libdir[2048]; // Current Working Directory
	int status = 0;
	sprintf(commande[0], "/Users/anthonygriffon/Desktop/Hache/lib/%s", function);
	//puts(commande);
	// On va vérifier que l'executable existe avant d'essayer de le lancer du lib.
	// Si il n'existe pas on va ensuite regarder dans le répertoire courant.
	// Et si il n'y est pas non plus on va simplement afficher que la commande est inconnue.
	if(access(commande[0], X_OK) != -1)
	{
		// X_OK: Permettre l'execution du fichier
		printf("1");
		status = system(commande[0]);
		return status;
	}
	else 
	{
	    // file doesn't exist
	    printf(commande[0]);
	    printf("2");
	    status = 0;
	    return status;
	}
	return status;
}
