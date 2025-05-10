#ifndef PLAYER_INTERACTION_H
#define PLAYER_INTERACTION_H

#include "header.h"

int askInt (int a, int b) {
    /* Makes the player input an integer in [a; b] */
    int n;
    do {
        printf("Entrez un nombre entre %d et %d : ", a, b);
        scanf("%d", &n);
    } while (n < a || n > b);
    return n;
}

Vector askPosition (int width, int height) {
    /* Makes the player input two integers in [0; width] and [0; height] */
    Vector v;
    printf("\nX : ");
    v.x = askInt(0, width);
    printf("Y : ");
    v.y = askInt(0, height);
    return v;
}

int choice (char *options[], int n) {
    /* Asks the player to choose between n options */
    int k;
    for (int i = 0; i < n; i++) {
        printf("\n%d : %s", 1 + i, options[i]);
    }
    do {
        printf("\n>>> ");
        scanf("%d", &k);
    } while (k <= 0 || n < k);
    return k - 1;
}

int binaryChoice () {
    char *yn[2] = {"Oui", "Non"};
    return choice(yn, 2);
}

#endif