#include "game.h"
#include "map.h"
#include "crabs.h"
#include "monkey.h"
#include "random.h"
#include "player_interaction.h"



void mainMenu () {
	
	
	printf("\nBienvenue à Coconut PartY!");
	
	char *options[2] = {
			    "Démarrer",
			    "Quitter"
			    };
	int option = choice(options, 2);
	GameData data;
	switch (option) {
		
		case 0 :
			printf("\nParamètres de la partie : ");
			
			printf("\nHauteur de l'île : ");
			int height = askInt(0, MAP_SIZE_Y_MAX);
			
			printf("\nLargeur de l'île : ");
			int width = askInt(0, MAP_SIZE_X_MAX);
			
			unsigned long seed;
			printf("\nSouhaitez-vous entrer une seed ?");
			if (!binaryChoice()) {
				printf("\nSeed : ");
				scanf("%d", &seed);
			} else {
				seed = time(NULL);
				printf("\nSeed : %d", seed);
			}
			
			printf("\nEntrez le nombre de PV : ");
			data.health = askInt(1, 10);
			
			data.map = mapInit(width, height, DIR_RIGHT, seed);
			data.max_monkeys = maxMonkeys(data.map);
			data.monkeys = malloc(sizeof(Monkey) * data.max_monkeys);
			data.n_monkeys = 0;
			data.bananas = 10;
			data.rounds = roundNumber(data.map);
			data.round_number = 0;
			break;
		
		case 1 :
			printf("\nAu revoir!");
			exit(0);
	}
	
	int score = game(data);
	if (score) {
		printf("\nVous avez eu un score de %d!", score);
	}
}

int main () {
	
	while(1) {
		mainMenu();
	}
	
	return 0;
}
