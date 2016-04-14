#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>

#include <signal.h>


#include "../inc/getInput.h"
#include "../inc/functions.h"
#include "../inc/socket.h"

#define TAILLE_MAX 256



int main() {
	/*
	Au démarrage on va lancer un processus serveur fils.
	*/
	// Code création du thread.

	char *input, **tab;
	int i = 0;
	chdir("../");
	printf("\033c"); // Clear
	int executeOnServer = 0;
	char workingdir[1024];
	char *workingdirlib = getenv("PTERMINAL");
	if (workingdirlib == NULL)
	{
		printf("Les librairies personnels ne sont pas chargés, merci d'indiquer le répertoire des executables dans la variable d'environnement PTERMINAL.");
	}
	//getcwd(workingdirlib, 1024);
	chdir("bin");

	// Variables socket SERVER
	pid_t child = fork();
	int my_socket, new_socket, clilen;
	int port;
	char buffer[256];
	struct sockaddr_in server, client;
	int  n;

	if (child == 0)
	{
		// Creation du socket.
		my_socket = socket(AF_INET, SOCK_STREAM, 0);
		if (my_socket < 0) {
			perror("Erreur dans \'ouverture du socket.");
			exit(1);
		}
		srand(time(NULL));
		port = (rand()%10000)+10000;
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
		clilen = sizeof(struct sockaddr_in);
		printf("Serveur lancé sur le port: %d.\n", port);

	}

	do {
		// Input du terminal
		input = malloc(TAILLE_MAX*sizeof(char));
		memset(input, '\0', sizeof(char));

		// Tableau où on va stocker les commandes
		tab = malloc(TAILLE_MAX*sizeof(char*));
		for (i=0 ; i<TAILLE_MAX; i++) tab[i] = malloc(TAILLE_MAX*sizeof(char));
		for (i=0 ; i<TAILLE_MAX; i++) memset(tab[i], '\0', TAILLE_MAX*sizeof(char));

		do {
			getcwd(workingdir, 1024); // On récupère le répertoire de travail.
			printf("prompt1.0: %s> ", workingdir);
			fflush(stdout);
			if(child == 0) {
				new_socket = accept(my_socket, (struct sockaddr *)&client, (socklen_t*)&clilen);
				if (new_socket<0)
				{
					perror("Erreur à l'acceptation: ");
					exit(1);
				}
				bzero(buffer,256);
				n = read( new_socket,buffer,255 );
				if (n < 0) {
					perror("Erreur à la lecture depuis le socket: ");
					exit(1);
				}
				close(1);
				dup2(1, 2);
				dup(new_socket);
				
			}
			else {
			getInput(input);
			}
		} while (input[0] == '\n');

		if (child==0)
		{
			inputTotab(buffer, tab);
		}
		else {
			inputTotab(input, tab);
		}		

		// executerInput
		if (executeOnServer == 1) {
			// On balance au serveur la requête et on attend le retour.
		}
		else {
			executerInput(tab, workingdirlib, child);
		}
		fflush(stdout);

		if(child == 0)
		{
			shutdown(new_socket, 0);
			fflush(stdout);
			listen(my_socket,5);
			clearerr(stdout);
			clearerr(stderr);
			fpurge(stdout);
		}

		for (i=0 ; i<TAILLE_MAX; i++) free(tab[i]);
		free(tab);
		free(input);

	} while(1);

	return 0;
}

int executerInput(char **tab, char *workingdirlib, pid_t child) {
	// Variables à add dans executerinput: buffer, sockfd, executeOnServer
	int i = 0;
	int forceEnd = 0;
	char **argv, **argv2;
	int j = 0;
	int andmode = 0;
	int skip = 0;
	int status = 0;
	// FILE * fp;
	int fd;
	fpos_t pos;

	// Variables socket CLIENT
	int sockfd, port_client, n;
   	struct sockaddr_in serv_addr;
   	struct hostent *server;
  	char server_reply[6000];
  	char buffer[256];

	while((tab[j][0] != '\n') && !forceEnd && (tab[j][0] != 0)) {		
		//printf("tab %d (%d)\n",j, tab[j][0]);
		//argv
		argv = malloc(TAILLE_MAX*sizeof(char*));
		for (i=0 ; i<TAILLE_MAX; i++) argv[i] = malloc(TAILLE_MAX*sizeof(char));
		for (i=0 ; i<TAILLE_MAX; i++) memset(argv[i], '\0', TAILLE_MAX*sizeof(char));

		argv2 = malloc(TAILLE_MAX*sizeof(char*));
		for (i=0 ; i<TAILLE_MAX; i++) argv2[i] = malloc(TAILLE_MAX*sizeof(char));
		for (i=0 ; i<TAILLE_MAX; i++) memset(argv2[i], '\0', TAILLE_MAX*sizeof(char));


		parseCommande(tab[j], argv);
		if (tab[j+1][0] != '\n' && tab[j+1][0]!=0 )
		{
			parseCommande(tab[j+1], argv2);
			if (isFunction(tab[j+1])==3) // &&
				// Done
			{
				andmode = 1;
			}
			else if (isFunction(tab[j+1])==4) // ||
				// Done
			{
				andmode = 2;
			}
			else if (isFunction(tab[j+1])==5) // |
			{
				andmode = 3;
			}
			else if (isFunction(tab[j+1])==6) // &
			{
				andmode = 4;
			}
			else if (isFunction(tab[j+1])==7) // >
				// Done
			{
				andmode = 5;
			}
			else if (isFunction(tab[j+1])==8) // >>
				// Done
			{
				andmode = 6;
			}

		}

		if(isFunction(argv[0]) != 2 && isFunction(argv[0]) < 3 && skip == 0) {

			if (andmode == 5)
			{
				//fp = fopen("file.txt", "w+");
				fflush(stdout);
				fgetpos(stdout, &pos);
				fd = dup(fileno(stdout));
				freopen(&tab[j+2][1], "w+", stdout); // Petite hack comme on met des espaces à chaque fois entre les trucs, pour éviter que on enregistre dans [ file.txt] et direct dans [file.txt]
													// Or petit probleme, si jamais on lance la commande: myls>file.txt ça enregistre dans [ile.txt] !
			}
			else if (andmode == 6)
			{
				//fp = fopen("file.txt", "w+");
				fflush(stdout);
				fgetpos(stdout, &pos);
				fd = dup(fileno(stdout));
				freopen(&tab[j+2][1], "a+", stdout); // Petite hack comme on met des espaces à chaque fois entre les trucs, pour éviter que on enregistre dans [ file.txt] et direct dans [file.txt]
													// Or petit probleme, si jamais on lance la commande: myls>file.txt ça enregistre dans [ile.txt] !
			}
			status = callFunction(argv, workingdirlib);
		    if (andmode == 5)
		    {

		    	fflush(stdout);
				dup2(fd, fileno(stdout));
		    	close(fd);     // fd no longer needed - the dup'ed handles are sufficient
		    	clearerr(stdout);
		    	fsetpos(stdout, &pos);

			}
			else if (andmode == 6)
			{
				fflush(stdout);
				dup2(fd, fileno(stdout));
		    	close(fd);     // fd no longer needed - the dup'ed handles are sufficient
		    	clearerr(stdout);
		    	fsetpos(stdout, &pos);
			}
		    //fclose(fp);
			//printf("Done with status %i\n", WEXITSTATUS(status));
		} else {
			if (skip == 0)
			{
				if (!strcmp(tab[j],"clear")) {
					printf("\033c");
				}

				if (!strcmp(tab[j],"exit")) {
					kill(child, 9);
					exit(1);
				}

				if (!strcmp(argv[0],"connect")) {
					if (argv[2] == NULL || argv[1] == NULL)
					{
						fprintf(stderr, "Utilisation: connect host port.\n");
					}
					else
					{
						printf("Blbl\n");
						int connectLoop = 0;
						while (connectLoop == 0)
						{
							connectLoop = 1;
							port_client = atoi(argv[2]);
							// On cree le socket.
							sockfd = socket(AF_INET, SOCK_STREAM, 0);
							if (sockfd < 0) {
								perror("Erreur à l'ouverture du socket:");
								break;
							}
							server = gethostbyname(argv[1]);
							if (server == NULL) {
							    fprintf(stderr,"Erreur: l'hôte est incorrect.\n");
							  	break;
							}
							bzero((char *) &serv_addr, sizeof(serv_addr));
							serv_addr.sin_family = AF_INET;
							bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
							serv_addr.sin_port = htons(port_client);
							if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
								perror("Erreur à la connection:");
								break;
							}
							printf("prompt-dp$>");
							bzero(buffer,256);
							fgets(buffer,255,stdin);

							if(!strcmp(buffer, "exit\n"))
							{
								n = write(sockfd, "clear\n", strlen("clear\n"));
								memset(server_reply, 0, sizeof server_reply);
								if( recv(sockfd, server_reply , 6000 , 0) < 0)
								{
									printf("Erreur dans la reception des données:\n");
									break;
								}
								shutdown(sockfd,0);
								break;
							}
							n = write(sockfd, buffer, strlen(buffer));
							if (n < 0) {
								perror("Erreur dans l'écriture du socket:");
								break;
							}
							memset(server_reply, 0, sizeof server_reply);
							if( recv(sockfd, server_reply , 6000 , 0) < 0)
							{
								printf("Erreur dans la reception des données:\n");
								break;
							}
							puts(server_reply);
							shutdown(sockfd, 0);
							connectLoop = 0;
						}
					}
				}

				if (!strcmp(argv[0],"cd")){
					if(argv[1] != NULL)
					{
						status = chdir(argv[1]);
						if(status!=0){
				          perror("Erreur:");
				        }
				        else {
				        	printf(" ");
				        }
				        //printf("STATUS: %d\n", status);
				    }
				}
			}
		}
		switch(andmode) {
			case 1: // &&
				switch(status) {
					case 0:
						break;
					default:
						skip = 3;
						break;
				}
				andmode = 0;
				break;
			case 2: // ||
				switch(status) {
					case 0:
						skip = 3;
						break;
					default:
						break;
				}
				andmode = 0;
				break;
			case 5: // >
				switch(status) {
					default:
						skip = 3;
						break;
				}
				andmode = 0;
				break;
			case 6: // >>
				switch(status) {
					default:
						skip = 3;
						break;
				}
				andmode = 0;
				break;

		}
		if (skip > 0) {
			skip--;
		}

		for (i=0 ; i<TAILLE_MAX; i++) free(argv[i]);
		free(argv);
		for (i=0 ; i<TAILLE_MAX; i++) free(argv2[i]);
		free(argv2);
		j++;
	}
	return status;

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


