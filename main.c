#include "game.h"
#include "map.h"
#include "crabs.h"
#include "monkey.h"
#include "random.h"
#include "player_interaction.h"
#include "save.h"


void mainMenu () {
	
	
	printf("\nBienvenue à Coconut PartY!");
	
	char *options[3] = {
			    "Démarrer",
				"Continuer",
			    "Quitter"
			    };
	
	int data_ready = 0;
	GameData data;
	while (!data_ready) {
		
		int option = choice(options, 3);
		switch (option) {
			
			case 0 :
				printf("\nParamètres de la partie : ");
				
				printf("\nHauteur de l'île : ");
				int height = askInt(10, MAP_SIZE_Y_MAX);
				
				printf("\nLargeur de l'île : ");
				int width = askInt(10, MAP_SIZE_X_MAX);
				
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

				data_ready = 1;

				break;
			
			case 1 :
				; // this line is important don't remove
				Save *saves = getSaves();

				char *options[4];
				for (int i = 0; i < 3; i++) {
					options[i] = saves[i].name;
				}
				options[3] = "Annuler";

				int n;
				printf("\nChoisissez la sauvegarde à charger : ");
				do {
					n = choice(options, 4);
				} while (strlen(options[n]) == 4 && options[n][0] == 'V');

				if (n != 3) {
					data = saves[n].data;
					data_ready = 1;
				}
				
				break;
			
			case 2 :
				printf("\nAu revoir!");
				exit(0);
		}
	}

	int score = game(data);
	if (score) {
		printf("\nVous avez eu un score de %d!\n", score);
		sleep(1);
	}
}

int main () {
	
	while(1) {
		mainMenu();
	}
	
	return 0;
}
