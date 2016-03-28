#include <stdio.h>
#include <unistd.h>

#include "../inc/getInput.h"
#include "../inc/functions.h"
#include "../inc/socket.h"

#define TAILLE_MAX 30


int main() {
	/*
	Au démarrage on va lancer un processus serveur fils.
	*/
	// Code création du thread.

	char input[TAILLE_MAX], **argv;
	int i = 0;

	argv = malloc(TAILLE_MAX*sizeof(char*));
	for ( ; i<TAILLE_MAX; i++) argv[i] = malloc(TAILLE_MAX*sizeof(char));

	printf("\033c");
	do {
		printf(">>> ");
		getInput(input);
		parseCommande(input, argv);
		if (isFunction(argv[0])) {
			printf("Function does not exist. Type help to get help.\n");
		} else callFunction(input);
	} while(1);

	return 0;
}


