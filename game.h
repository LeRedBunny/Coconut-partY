
#ifndef GAME_H
#define GAME_H

#include "header.h"
#include "map.h"


#define START_CRABS 2
#define CRAB_MULTIPLIER 1.2
#define MAX_HEIGHT 100
#define MAX_WIDTH 100
#define MONKEY_PRICE 25
#define MONKEY_UPGRADE_PRICE 15

int gameRound (GameData *data) {
	/* Runs a single round/wave of crabs, returns 1 if player won and 0 if they lost */
	
	// Create crabs
	int n_crabs = START_CRABS * pow(CRAB_MULTIPLIER, data->round_number);
	Crab *crabs = randomCrabs(n_crabs, data->round_number);
	
	// Main round
	int alive = 1;
	int crab_timer = 1;
	int crabs_to_spawn = 1;
	int bananas_gained;
	int crabs_spawned = 0;
	while (alive && !allDead(crabs, n_crabs)) {
		
		sleep(1);
		displayGame(*data, crabs, n_crabs, crabs_spawned);

		// Shoot crabs
		for (Monkey *monkey = data->monkeys; monkey < data->monkeys + data->n_monkeys; monkey++) {
			bananas_gained = shoot(*monkey, crabs, n_crabs, data->map);
			if (bananas_gained) {
				printf("\nVous avez obtenu %d Bananes !", bananas_gained);
				data->bananas += bananas_gained;
			} 
		}

		// Move crabs
		for (Crab *crab = crabs; crab < crabs + n_crabs; crab++) {
			if (crab->path_index >= 0) {
				move(crab, data->map);
			}
		}
		
		// Spawn in a new crab
		crab_timer -= crabs_to_spawn;
		if (!crab_timer) {
			crabs_spawned++;
			crab_timer = crabTimer();
			crabs_to_spawn = spawnCrab(crabs, n_crabs);
		}
		
		// Check death
		data->health -= checkKing(crabs, n_crabs, data->map.path_length);
		if (!data->health) {
			alive = 0;
		}
	}
	
	// End of round
	free(crabs);
	
	return alive;
}



void displayGame (GameData data, Crab *crabs, int n_crabs, int crabs_spawned) {
	printf("\nManche %d/%d : %d/%d Crabes\nVie : %d    Bananes : %d\n", data.round_number, data.rounds, crabs_spawned, n_crabs, data.health, data.bananas);
	display(data.map, crabs, n_crabs, data.monkeys, data.n_monkeys);
}


void placeMonkey (GameData *data) {
	/*  */
	Vector position;
	char tile;
	do {
		position = subtract(askPosition(MAP_SIZE_X_MAX, MAP_SIZE_Y_MAX), vector(1, 1));
		tile = getTile(data->map, position);
	} while (tile == 'w' || tile == 'p');
	data->monkeys[data->n_monkeys] = newMonkey(position);
	data->n_monkeys++;
}

int manage (GameData *data) {
	/* Returns 1 if player quits */
	int quit = 0;
	int option;
	
	char *options[4] =  {"Acheter",
			     "Améliorer",
			     "Passer",
			     "Quitter"
			     };
	
	while (!quit) {
		printf("\nVous avez %d Bananes et %d PV !", data->bananas, data->health);
		printf("\nVoulez-vous acheter des singes (%d bananes), améliorer (%d bananes) ou passer à la manche suivante ?", MONKEY_PRICE, MONKEY_UPGRADE_PRICE);
		option = choice(options, 4); 
		switch (option) {
			
			case 0 :
				if (data->bananas < MONKEY_PRICE) {
					printf("\nVous n'avez que %d bananes...", data->bananas);
				} else if (data->n_monkeys >= data->max_monkeys) {
					printf("\nVous avez atteint le maximum de singes.");
				} else {
					data->bananas -= MONKEY_PRICE;
					placeMonkey(data);
				}
				break;
			
			case 1 :
				if (data->bananas >= MONKEY_UPGRADE_PRICE) {
					data->bananas -= MONKEY_UPGRADE_PRICE;
					Monkey *monkey;
					do {
						monkey = monkeyAt(subtract(askPosition(MAP_SIZE_X_MAX, MAP_SIZE_Y_MAX), vector(1, 1)), data->monkeys, data->n_monkeys);
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
				return 1;
		}
	}
	return 0;
}

int game (GameData data) {
	/* Returns 0 if the player quit */
	int alive = 1;
	int quit = 0;

	display(data.map, NULL, 0, NULL, 0);
	printf("\nPlacez votre premier singe : ");
	placeMonkey(&data);

	while (data.round_number < data.rounds && alive && !quit) {
		
		data.round_number++;
		printf("\nManche %d/%d !", data.round_number, data.rounds);
		
		quit = manage(&data);
		if (!quit) {
			alive = gameRound(&data);
		}
	}
	
	if (alive) {
		return score(data, alive);
	} else {
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
