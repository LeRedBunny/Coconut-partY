
#ifndef GAME_H
#define GAME_H

#include "header.h"
#include "map.h"

#include "screen.h"

#define START_CRABS 2
#define CRAB_MULTIPLIER 1.2
#define MAX_HEIGHT 100
#define MAX_WIDTH 100
#define MONKEY_PRICE 25
#define MONKEY_UPGRADE_PRICE 15

int gameRound (GameData *data, Screen screen) {
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
		
		displayGame(*data, crabs, n_crabs, crabs_spawned, screen);
		sleep(1);

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
	displayGame(*data, crabs, n_crabs, crabs_spawned, screen);
	// End of round
	free(crabs);
	
	return alive;
}



void displayGame (GameData data, Crab *crabs, int n_crabs, int crabs_spawned, Screen screen) {
    system("clear");
    frameAddNumber(crabs_spawned, screen, MAP_SIZE_X_MAX-11,1);
    frameAddNumber(n_crabs, screen, MAP_SIZE_X_MAX-8,1);
    
    frameAddNumber(data.health, screen, MAP_SIZE_X_MAX+2,2);
    frameAddNumber(data.bananas, screen, MAP_SIZE_X_MAX+2,5);
    
	frameAddCrabs(screen, vector(1,3), data.map, crabs, n_crabs);
	display2(screen);
    frameAddPath(screen, vector(1,3), data.map);
}


void placeMonkey (GameData *data, Screen *screen) {
	/*  */
	Vector position;
	char tile;
	do {
		position = subtract(askPosition(MAP_SIZE_X_MAX, MAP_SIZE_Y_MAX), vector(1, 1));
		tile = getTile(data->map, position);
	} while (tile == 'w' || tile == 'p');
	data->monkeys[data->n_monkeys] = newMonkey(position);
	data->n_monkeys++;
	frameAddMonkeys(screen, vector(1,3), data->monkeys, data->n_monkeys);
}

int manage (GameData *data, Screen *screen) {
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
					placeMonkey(data, screen);
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
    
    Screen screen = initScreen(MAP_SIZE_X_MAX+10, MAP_SIZE_Y_MAX+2, 2);
    
    
    frameAddTextZone(&screen, MAP_SIZE_X_MAX+2,1 , MAP_SIZE_X_MAX+10,MAP_SIZE_Y_MAX+2);
    frameAddColumnChar('|', screen, MAP_SIZE_X_MAX+1);
    frameAddTabChar("Vie :", 5, screen, MAP_SIZE_X_MAX+2,1);
    frameAddNumber(data.health, screen, MAP_SIZE_X_MAX+2,2);
    frameAddTabChar("Bananes :", 9, screen, MAP_SIZE_X_MAX+2,4);
    frameAddNumber(data.bananas, screen, MAP_SIZE_X_MAX+2,5);
    
    frameAddTextZone(&screen, 1,1 , MAP_SIZE_X_MAX,1);
    frameAddLigneChar('-', screen, 2);
    frameAddPath(screen, vector(1,3), data.map);
    frameAddTabChar("Manche n°  /  &", 15, screen, 1,1);
    frameAddNumber(data.round_number, screen, 11,1);
    frameAddNumber(data.rounds, screen, 14,1);
    frameAddTabChar("&00/00 crabes", 13, screen, MAP_SIZE_X_MAX-12,1);
    
    frameAddTabTabChar(data.map.map, MAP_SIZE_X_MAX, MAP_SIZE_Y_MAX, screen, 1, 3);
    
    display2(screen);

    
	//display(data.map, NULL, 0, NULL, 0);
	printf("\nPlacez votre premier singe : ");
	placeMonkey(&data, &screen);

	while (data.round_number < data.rounds && alive && !quit) {
		
		data.round_number++;
		frameAddNumber(data.round_number, screen, 11,1);
        frameAddNumber(data.rounds, screen, 14,1);
    
		quit = manage(&data, &screen);
		if (!quit) {
			alive = gameRound(&data, screen);
		}
	}
	
	freeScreen(&screen);
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
