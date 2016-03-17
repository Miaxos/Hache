# include <stdio.h>

# include "prompt.h"
# include "callFunction.h"

# define TAILLE_MAX 1024

int main() {
	char input[TAILLE_MAX];

	while (prompt(input) != NULL) {
		callFunction(input);
	}
	return 0;
}
