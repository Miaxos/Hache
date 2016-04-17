# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>

# include "../inc/functions.h"

# define TAILLE_MAX 1024


//	Booléen qui renvoie 1 si la fonction existe, 0 sinon 2 si c'est une fonction bash
int isFunction(const char *function) {
	// if (!strcmp(function,"myls")) return 0;
	// if (!strcmp(function,"mydu")) return 0;
	// if (!strcmp(function,"mypwd")) return 0;

	if (!strcmp(function,"clear")) return 2; // Done
	if (!strcmp(function,"cd")) return 2; // Done mais erreurs à gérer
	if (!strcmp(function,"exit")) return 2; // Done
	if (!strcmp(function, "connect")) return 2;

	if (!strcmp(function, "<<")) return 10; // A faire ça existe ? 
	if (!strcmp(function, "<")) return 9; // A faire

	if (!strcmp(function, ">>")) return 8; // Done mais deg'
	if (!strcmp(function, ">")) return 7; // Done mais deg'

	if (!strcmp(function, "&")) return 6; // A faire
	if (!strcmp(function, "|")) return 5; // A faire
	if (!strcmp(function, "||")) return 4; // Done mais deg'
	if (!strcmp(function, "&&")) return 3; // Done mais deg'
	return 1;
}


// 	Renvoie le nom de la fonction utilisé sans ses paramètres
/*	
	Exemple : getFunctionName("myls /home/eliot/Documents", function) copie "myls" dans function2
*/
char* getFunctionName(const char *function, char *function2) {
	char c;
	int compteur = 0;
	while ((c=function[compteur]) != ' ' && (c=function[compteur]) != '\n') function2[compteur++] = c;
	function2[compteur] = '\0';
	return function2;
}

int callFunction(int argc, char **argv, char *workingdirlib, SCmd* tabcommandes[]) {
	char temp[TAILLE_MAX];
	char workingdir[1024];
	getcwd(workingdir, 1024);
	int status;
	if (fork() == 0) {
		// on est dans le fils
		#ifdef LIB
		// Mode librairie statiques
		int i = 0;
		while(i < TAILLE_MAX) {
			if (!strcmp(argv[0], GetName(tabcommandes[i]))) {
				status = (GetFunction(tabcommandes[i]))(argc, argv);
				exit(1);
			}
			i++;
		}
		#endif

		sprintf(temp, "%s/%s", workingdir, argv[0]);
		if (access(temp, F_OK) != 0) 
		{
			sprintf(temp, "%s/%s", workingdirlib, argv[0]);
			if (access(temp, F_OK ) != 0)
			{
				sprintf(temp, "/bin/%s", argv[0]);
				if (access(temp, F_OK ) != 0)
				{
					sprintf(temp, "/usr/local/bin/%s", argv[0]);
					if (access(temp, F_OK ) != 0)
					{
						sprintf(temp, "/usr/bin/%s", argv[0]);
						if (access(temp, F_OK ) != 0)
						{
							sprintf(temp, "/sbin/%s", argv[0]);
						}
					}
				}
			}
		}
		strcpy(argv[0], temp);
		// printf("%d\n",access(temp, F_OK )); // -1 = pas acces 0 = acces
		if (access(temp,F_OK)==0)
		{
			status = execvp(temp, argv);
		}
		else
		{
			perror("Erreur ");
		}
		exit(1);
	} else {
		wait(&status);
	}
	// printf("EXITSTATUS: %d\n", WEXITSTATUS(status));
	// WEXITSTATUS: 0 : OK 1: ERROR
	return WEXITSTATUS(status);
}

//	Renvoie la longueur d'une chaine
int len(const char *string) {
	return (int)strlen(string);
}

//	Renvoie un "booléen" si le caractère passé en paramètre est un "délimiteur" (ou plutôt un opérateur)
//		-> Fonction utilisée dans inputTotab
int isDelimiter(char c) {
	if (c == '|') return 1;
	if (c == '<') return 1;
	if (c == '&') return 1;
	if (c == '>') return 1;
	if (c == '\n') return 1;
	return 0;
}

//	Découpe un input dans un tableau de strings
/*	
	Exemple :
			char input[30];
			char resultat[30][30];
			input = "commande1&&commande2|commande4&\n";
			inputTotab(input, resultat);

			maintenant resultat est : [[commande1][&&][commande2][|][commande4][&][\n][]...[]]
*/
int inputTotab(const char *input, char **inputTab) {
	enum Etats { Etat1,Etat2,Etat3,Etat4,Etat5,Etat6,Etat7,Etat8,Etat9,EtatF };

	int i = 0, compteur = 0, compteur2 = 0;
	char c;
	enum Etats curEtat = Etat1;
	int fini = 0;

	int background = 0;

	while (!fini) {
		switch (curEtat) {
		case Etat1 :
			c = input[i++]; // printf("%c\n", c);
			if (!(isDelimiter(c))) {
				inputTab[compteur][compteur2++] = c;
			} else {
				inputTab[compteur][compteur2++] = '\0';
				compteur++;
				compteur2 = 0;
				inputTab[compteur][compteur2++] = c;
				if (c=='<') {
					curEtat = Etat2;
				} else if (c=='>') {
					curEtat = Etat4;
				} else if (c=='|') {
					curEtat = Etat6;
				} else if (c=='&') {
					curEtat = Etat8;
				} else if (c=='\n') {
					curEtat = EtatF;
				}
			}
			break;
		case Etat2 :
			c = input[i++]; //printf("%c", c);
			if (!(isDelimiter(c))) {
				inputTab[compteur][compteur2++] = '\0';
				compteur2 = 0;
				compteur++;
				inputTab[compteur][compteur2++] = c;
				curEtat = Etat1;
			} else if (c=='<') {
				inputTab[compteur][compteur2++] = c;
				curEtat = Etat3;
			}
			break;
		case Etat3 :
			c = input[i++]; //printf("%c", c);
			if (!(isDelimiter(c))) {
				inputTab[compteur][compteur2++] = '\0';
				compteur2 = 0;
				compteur++;
				curEtat = Etat1;
				inputTab[compteur][compteur2++] = c;
			}
			break;
		case Etat4 :
			c = input[i++]; //printf("%c", c);
			if (!(isDelimiter(c))) {
				inputTab[compteur][compteur2++] = '\0';
				compteur2 = 0;
				compteur++;
				inputTab[compteur][compteur2++] = c;
				curEtat = Etat1;
			} else if (c=='>') {
				inputTab[compteur][compteur2++] = c;
				curEtat = Etat5;
			}
			break;
		case Etat5 :
			c = input[i++]; //printf("%c", c);
			if (!(isDelimiter(c))) {
				inputTab[compteur][compteur2++] = '\0';
				compteur2 = 0;
				compteur++;
				curEtat = Etat1;
				inputTab[compteur][compteur2++] = c;
			}
			break;
		case Etat6 :
			c = input[i++]; //printf("%c", c);
			if (!(isDelimiter(c))) {
				inputTab[compteur][compteur2++] = '\0';
				compteur2 = 0;
				compteur++;
				inputTab[compteur][compteur2++] = c;
				curEtat = Etat1;
			} else if (c=='|') {
				inputTab[compteur][compteur2++] = c;
				curEtat = Etat7;
			}
			break;
		case Etat7 :
			c = input[i++]; //printf("%c", c);
			if (!(isDelimiter(c))) {
				inputTab[compteur][compteur2++] = '\0';
				compteur2 = 0;
				compteur++;
				curEtat = Etat1;
				inputTab[compteur][compteur2++] = c;
			}
			break;
		case Etat8 :
			c = input[i++]; // printf("\n%d\n", c);
			if (!(isDelimiter(c))) {
				inputTab[compteur][compteur2++] = '\0';
				compteur2 = 0;
				compteur++;
				inputTab[compteur][compteur2++] = c;
				curEtat = Etat1;
			} else if (c=='&') {
				inputTab[compteur][compteur2++] = c;
				curEtat = Etat7;
			} else if (c=='\n') {
				compteur++;
				inputTab[compteur][compteur2++] = c;
				inputTab[compteur][compteur2++] = '\0';
				curEtat = EtatF;
				background = 1;
			}
			break;
		case Etat9 :
			c = input[i++]; //printf("%c", c);
			if (!(isDelimiter(c))) {
				inputTab[compteur][compteur2++] = '\0';
				compteur2 = 0;
				compteur++;
				curEtat = Etat1;
				inputTab[compteur][compteur2++] = c;
			}
			break;
		case EtatF :
			fini = 1;
			//printf("fin parse\n");
			// printf("compteur: %d\n", compteur);
			break;
		}
	}
	return background;

}

// Parseur de commandes
/*
	Exemple :
		char *commande = "myls -a /home/eliot"
		char **argv;
		parseCommande(commande, argv) retourne le nombre d'argument (ici 3)
		et argv devient ["myls","-a","/home/eliot"]
*/
int parseCommande(const char *commande, char **argv) {
	int i = 0, j = 0, k = 0, newparam = 0, argc = 0;
	char c;

	while ((c=commande[i]) == ' ') i++;

	while (((c = commande[i]) != '\0') && ((c = commande[i]) != '\n')) {
		
		if (c == ' ') {
			newparam = 0;
		} else {
			if (newparam == 0) {
				newparam = 1;
				j++;
				k = 0;
				argc++;
			}
			argv[j-1][k++] = c;
		}
		i++;
	}
	argv[j] = NULL;

	return argc;
}
