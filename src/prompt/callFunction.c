# include <stdio.h>
# include <stdlib.h>

# define TAILLE_MAX 30

int callFunction(const char *function) {
	char function2[TAILLE_MAX];
	sprintf(function2, "./lib/%s", function);
	int status = system(function2);
	return status;
}
