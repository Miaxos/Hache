#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h> // Pour OS X


#include "../inc/getInput.h"
#include "../inc/functions.h"
#include "../inc/socket.h"

#define TAILLE_MAX 256


int main() {
	/*
	Au démarrage on va lancer un processus serveur fils.
	*/
	// Code création du thread.

	char *input, **argv, **tab;
	int i = 0, status, j = 0, forceEnd = 0;

	printf("\033c");


	do {
		//input		
		input = malloc(TAILLE_MAX*sizeof(char));
		memset(input, '\0', sizeof(char));

		//tab
		tab = malloc(TAILLE_MAX*sizeof(char*));
		for (i=0 ; i<TAILLE_MAX; i++) tab[i] = malloc(TAILLE_MAX*sizeof(char));
		for (i=0 ; i<TAILLE_MAX; i++) memset(tab[i], '\0', TAILLE_MAX*sizeof(char));

		do {
			printf(">>> ");
			getInput(input);
		} while (input[0] == '\n');

		inputTotab(input, tab);
		
		while((tab[j][0] != '\n') && !forceEnd) {
			
			// printf("%s\n",tab[j]);
			//argv
			argv = malloc(TAILLE_MAX*sizeof(char*));
			for (i=0 ; i<TAILLE_MAX; i++) argv[i] = malloc(TAILLE_MAX*sizeof(char));
			for (i=0 ; i<TAILLE_MAX; i++) memset(argv[i], '\0', TAILLE_MAX*sizeof(char));

			parseCommande(tab[j], argv);

			if (isFunction(argv[0]) == 1) {
				if (!(strcmp(argv[0], "&&"))) {
					if (status) forceEnd = 1;
				} else if (!(strcmp(argv[0], "||"))) {
					if (!status) forceEnd = 1;
				} else {
					printf("Function %s does not exist. Type help to get help.\n", argv[0]);
				}
			} else if(isFunction(argv[0]) == 0) {

				status = callFunction(argv);
				//printf("Done with status %i\n", WEXITSTATUS(status));
			} else {
				
				if (!strcmp(tab[j],"clear")) {
					printf("\033c");
				}

				if (!strcmp(argv[0],"cd")){

					// execvp("/Users/anthonygriffon/Desktop/Hache/commands/myls", argv);
					printf("%s\n",argv[1]);
					printf("Blbl\n");


				}



			}
			for (i=0 ; i<TAILLE_MAX; i++) free(argv[i]);
			free(argv);
			j++;
		}

		j = 0;
		forceEnd = 0;

		for (i=0 ; i<TAILLE_MAX; i++) free(tab[i]);
		free(tab);
		free(input);

	} while(1);

	return 0;
}

int creationSocket() {
	
	// Fonction de création de socket
	// Création d'un socket d'écoute qui va ensuite traiter les infos
	int my_socket, new_socket, clilen;
	int port;
	char buffer[256];
	struct sockaddr_in server, client;
	int  n;
	
	// Creation du socket
	my_socket = socket(AF_INET, SOCK_STREAM, 0);

	// En cas d'erreur
	if (my_socket < 0) {
		perror("Erreur dans \'ouverture du socket.");
		exit(1);
	}
	
	// Structure du socket	
	port = 10002;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(port);
	
	// Bind de l'adresse
	if (bind(my_socket, (struct sockaddr *) &server, sizeof(server)) < 0) {
		perror("Erreur: Bind failed.");
		exit(1);
	}
		
	// Mode écoute (second argument: la queue).
	listen(my_socket,5);
		
	//On accepte les connections
	puts("Waiting for incoming connections...");
	clilen = sizeof(struct sockaddr_in);
	while(1)
	{
		new_socket = accept(my_socket, (struct sockaddr *)&client, (socklen_t*)&clilen);
		if (new_socket<0)
		{
			perror("Erreur: Accept failed.");
			exit(1);
		}

		/* If connection is established then start communicating */
		bzero(buffer,256);
		n = read( new_socket,buffer,255 );
		
		if (n < 0) {
			perror("Erreur: lecture depuis le socket");
			exit(1);
		}
		
		// On récupère le message
		// On redirige la sortie standard dup2()
		// On le traite
		// On balance
		printf("Message: %s\n",buffer);
		
		/* Write a response to the client */
		n = write(new_socket,"I got your message",18);
		
		if (n < 0) {
			perror("ERROR writing to socket");
			exit(1);
		}
	}   
	return 0;

}


