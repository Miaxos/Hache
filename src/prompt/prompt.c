# include <stdio.h>

# define TAILLE_MAX 1024

char *prompt(char *input) {
	return fgets(input, TAILLE_MAX*sizeof(char), stdin);
}
