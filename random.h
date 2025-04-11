#include <time.h>
#include <stdlib.h>

int randint (int a, int b) {
	/* Returns a random integer in [a; b] */
	return a + rand() % (1 + b - a);
}


