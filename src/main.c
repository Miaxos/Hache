# include <stdio.h>

# include "../inc/getInput.h"
# include "../inc/functions.h"

# define TAILLE_MAX 30

int main() {
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
