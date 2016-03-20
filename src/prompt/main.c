# include <stdio.h>

# include "prompt.h"
# include "callFunction.h"

# define TAILLE_MAX 1024

int main() {
	char input[TAILLE_MAX];

	// Clear terminal
	printf("\033c" );
	printf("prompt$ " );

	while (prompt(input) != NULL) {
		callFunction(input);
		printf("prompt$ " );
	}
	return 0;
}
