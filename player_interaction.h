
#ifndef PLAYER_INTERACTION_H
#define PLAYER_INTERACTION_H


#include <stdio.h>



#include "header.h"

int askInt (int a, int b) {
	/* Asks the player to input an integer in [a; b] */
	
	int n;
	printf("Entrez un nombre entre %d et %d inclus : ", a, b);
	do {
		scanf("%d", &n);
	} while (a > n || n > b);
	
	return n;
}

Vector askPosition (int height, int width) {
	/* Asks the player to input a vector */
	printf("Entrez les coordonnées x et y de la position : ");
	return vector(askInt(1, width) - 1, askInt(1, height) - 1);
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

int binaryChoice () {
	/* Lets the player choose between yes and no */
	char *yn = {"Oui", "Non"};
	return choice(yn, 2);
}
#endif
