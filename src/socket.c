// Socket.c
// @Desc: Gestion des sockets
// @Help: http://www.tutorialspoint.com/unix_sockets/index.htm

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>


int main( int argc, char *argv[] ) {
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
   // bzero((char *) &serv_addr, sizeof(serv_addr));
   
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

   // clilen = sizeof(cli_addr);
   
   //Accept and incoming connection
   puts("Waiting for incoming connections...");
   clilen = sizeof(struct sockaddr_in);
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
      perror("ERROR reading from socket");
      exit(1);
   }
   
   printf("Here is the message: %s\n",buffer);
   
   /* Write a response to the client */
   n = write(new_socket,"I got your message",18);
   
   if (n < 0) {
      perror("ERROR writing to socket");
      exit(1);
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
