# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define TAILLE_MAX 30


//	Booléen qui renvoie 1 si la fonction existe, 0 sinon
int isFunction(const char *function) {
	if (!strcmp(function,"myls")) return 0;
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

int callFunction(const char *function) {
	char function2[TAILLE_MAX];
	sprintf(function2, "../commands/%s", function);
	return system(function2);
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
void inputTotab(char input[TAILLE_MAX], char inputTab[TAILLE_MAX][TAILLE_MAX]) {
	enum Etats { Etat1,Etat2,Etat3,Etat4,Etat5,Etat6,Etat7,Etat8,Etat9,EtatF };

	int i = 0, compteur = 0, compteur2 = 0;
	char c;
	enum Etats curEtat = Etat1;
	int fini = 0;

	while (!fini) {
		switch (curEtat) {
		case Etat1 :
			c = input[i++]; //printf("%c", c);
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
			c = input[i++]; //printf("%c", c);
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
			break;
		}
	}

}
