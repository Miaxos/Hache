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

	char input[TAILLE_MAX], function[TAILLE_MAX];
	printf("\033c");
	do {
		printf(">>> ");
		getInput(input);
		if (isFunction(getFunctionName(input, function))) {
			printf("Function does not exist. Type help to get help.\n");
		} else callFunction(input);
	} while(1);

	return 0;
}


