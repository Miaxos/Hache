# include <stdio.h>

# include "prompt.h"
# include "callFunction.h"

# define TAILLE_MAX 30

int main() {
	char input[TAILLE_MAX];
	while (1) {
		prompt(input);
		callFunction(input);
	}
	return 0;
}
