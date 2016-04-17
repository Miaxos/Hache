# include <stdio.h>

# define TAILLE_MAX 1024

// Copie dans input ce que l'utilisateur à saisi
void getInput(char *input) {
	fgets(input, TAILLE_MAX*sizeof(char), stdin);
}
