# include <stdio.h>

# define TAILLE_MAX 30

void prompt(char *input) {
	fgets(input, TAILLE_MAX*sizeof(char), stdin);
}
