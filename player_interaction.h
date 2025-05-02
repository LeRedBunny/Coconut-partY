/*
nécessite l'inclusion de:
stdio.h
*/

int askInt (int a, int b) {
	/* Asks the player to input an integer in [a; b] */
	
	int n;
	printf("Entrez un nombre entre %d et %d inclus : ", a, b);
	do {
		scanf("%d", &n);
	} while (a > n || n > b);
	
	return n;
}

int choice (char **options, int n) {
	/* Prints the options and asks the player to choose, returns the chosen index */	
	
	int k;
	
	for (int i = 0; i < n; i++) {
		printf("%d : %s\n", 1 + i, options[i]);
	}
	printf(">>> ");
	do {
		scanf("%d", &k);
	} while(k <= 0 || k > n);
	
	return k - 1;
}
