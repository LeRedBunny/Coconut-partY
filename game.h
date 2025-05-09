
#ifndef GAME_H
#define GAME_H

#include "header.h"


#define START_CRABS 3
#define CRAB_MULTIPLIER 1.2
#define MAX_HEIGHT 100
#define MAX_WIDTH 100
#define MONKEY_PRICE 25
#define MONKEY_UPGRADE_PRICE 15
#define CRAB_BANANA_DROP 10

int gameRound (GameData *data) {
	/* Runs a single round/wave of crabs, returns 1 if player won and 0 if they lost */
	
	// Create crabs
	int n_crabs = START_CRABS * pow(CRAB_MULTIPLIER, data->round_number);
	Crab *crabs = malloc(n_crabs * sizeof(Crab));
	if (crabs == NULL) {exit(1); }
	
	
	// Main round
	int alive = 1;
	int crab_timer = crabTimer();
	int crabs_to_spawn = 1;
	while (!allDead(crabs, n_crabs) && alive) {
		
		//display(data->map, crabs, n_crabs, data->monkeys, data->n_monkeys);
		
		// Move crabs
		for (Crab *crab = crabs; crab < crabs + n_crabs; crab++) {
			if (crab->path_index >= 0) {
				move(crab, data->map);
			}
		}
		
		// Shoot crabs
		for (int i = 0; i < data->n_monkeys; i++) {
			data->bananas += CRAB_BANANA_DROP * shoot(data->monkeys[i], crabs, n_crabs, data->map); 
		}
		
		// Spawn in a new crab
		crab_timer -= crabs_to_spawn;
		if (!crab_timer) {
			crab_timer = crabTimer();
			crabs_to_spawn = spawnCrab(crabs, n_crabs);
		}
		
		data->health -= checkKing(crabs, n_crabs, data->map.path_length);
		if (!data->health) {
			alive = 0;
		}
	}
	
	// End of round
	free(crabs);
	
	return alive;
}



void displayGame (GameData data) {
	printf("Vie : %d\nBananes : %d", data.health, data.bananas);
	display(data.map, NULL, 0, data.monkeys, data.n_monkeys);
}


int manage (GameData *data) {
	/* Returns 1 if player quits */
	int quit = 0;
	int option;
	
	char *options[4] =  {"Acheter",
			     "Améliorer",
			     "Passer",
			     "Sauvegarder et quitter"
			     };
	
	while (!quit) {
		printf("Voulez-vous acheter des singes, améliorer ou passer à la manche suivante ?");
		option = choice(options, 4); 
		switch (option) {
		
			case 0 :
				if (data->bananas >= MONKEY_PRICE) {
					data->bananas -= MONKEY_PRICE;
					Vector position = askPosition(data->map.width, data->map.height);
					data->n_monkeys++;
					data->monkeys[data->n_monkeys] = newMonkey(position);
				} else {
					printf("Vous n'avez que %d bananes...", data->bananas);
				}
				break;
			
			case 1 :
				if (data->bananas >= MONKEY_UPGRADE_PRICE) {
					data->bananas -= MONKEY_UPGRADE_PRICE;
					Monkey *monkey;
					do {
						monkey = monkeyAt(askPosition(data->map.width, data->map.height), data->monkeys, data->n_monkeys);
					} while (monkey == NULL);
					upMonkey(monkey);
				} else {
					printf("Vous n'avez que %d bananes...", data->bananas);
				}
				break;
			
			case 2 :
				quit = 1;
				break;
			
			case 3 :
				save(*data);
				return 1;
		}
	}
	return 0;
}


int game (GameData data) {
	/* Returns 0 if the player quit */
	int alive = 1;
	int quit = 0;
	while (data.round_number < data.rounds && alive && !quit) {
		
		data.round_number++;
		printf("Manche %d/%d !", data.round_number, data.rounds);
		
		quit = manage(&data);
		if (!quit) {
			alive = gameRound(&data);
		}
	}
	
	if (quit) {
		return score(data, alive);
	} else {
		save(data);
		return 0;
	}
}


int score (GameData data, int alive) {
	/* Gives a score based on the final state of the game */
	int s = 0;
	for (int i = 0; i < data.n_monkeys; i++) {
		s += data.monkeys[i].damage - data.monkeys[i].range;
	}
	s += data.bananas;
	s += data.health * 5;
	s += s * alive;
	return s;
}




#endif
