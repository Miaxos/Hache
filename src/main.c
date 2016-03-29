#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
# include <stdlib.h>


#include "../inc/getInput.h"
#include "../inc/functions.h"
#include "../inc/socket.h"

#define TAILLE_MAX 30


int main() {
	/*
	Au démarrage on va lancer un processus serveur fils.
	*/
	// Code création du thread.

	char *input, **argv;
	int i = 0, status;

	printf("\033c");


	do {
		input = malloc(TAILLE_MAX*sizeof(char));
		argv = malloc(TAILLE_MAX*sizeof(char*));
		for (i=0 ; i<TAILLE_MAX; i++) argv[i] = malloc(TAILLE_MAX*sizeof(char));
		for (i=0 ; i<TAILLE_MAX; i++) {
			memset(argv[i], '\0', TAILLE_MAX*sizeof(char));
		}
		memset(input, '\0', sizeof(char));

		printf(">>> ");
		getInput(input);
		parseCommande(input, argv);
		if (isFunction(argv[0])) {
			printf("Function %s does not exist. Type help to get help.\n", argv[0]);
		} else {
			status = callFunction(argv);
			printf("Done with status %i\n", WEXITSTATUS(status));
		}
		
		for (i=0; i<TAILLE_MAX; i++) free(argv[i]);
		free(argv);
		free(input);

	} while(1);

	return 0;
}


