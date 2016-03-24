#include <stdio.h>
#include <unistd.h>

#include "../inc/getInput.h"
#include "../inc/functions.h"

#define TAILLE_MAX 30


int main() {
	/*
	Au démarrage on va lancer un processus serveur fils.
	*/
	// Code création du thread.

	char input[TAILLE_MAX], function[TAILLE_MAX];
	printf("\033c");
	while (1) {
		printf(">>> ");
		getInput(input);
		if (isFunction(getFunctionName(input, function))) {
			printf("Function does not exist. Type help to get help.\n");
		} else callFunction(input);
	}
	return 0;
}


int createProcess() {
/*
Création de processus avec gestion d'
*/
	int pid;
	// On fork
	pid = fork();
	return pid;

}
