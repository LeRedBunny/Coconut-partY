
/*
nécessite l'inclusion de:
time.h
stdlib.h
math.h
*/


int randint (int a, int b) {
	/* Returns a random integer in [a; b] */
	return a + rand() % (1 + b - a);
}

int randbool (float p, int n) {
	/* Returns 1 with a probability of p with precision of n digits */
	return randint(1, p * pow(10, n)) <= p * pow(10, n);
}
