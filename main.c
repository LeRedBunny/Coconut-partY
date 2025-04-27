#include "header.h"
#include <math.h>
#include "random.h"
#include "crab.h"
#include "monkey.h"
#include "map.h"
#include "player_interaction.h"

#define START_CRABS 3
#define CRAB_MULTIPLIER 1.2
#define MAX_HEIGHT 100
#define MAX_WIDTH 100

void round (GameData data) {
	/* Runs a single round/wave of crabs */
	
	// Create crabs
	int n_crabs = START_CRABS * pow(CRAB_MULTIPLIER, data.round_number);
	Crab *crabs = malloc(n_crabs * sizeof(Crab));
	if (crabs == NULL) {exit(1); }
	
	
	// Main round
	int crab_timer = crabTimer();
	int playing = 1;
	int crabs_to_spawn = 1;
	while (playing) {
		
		display(data.map, crabs, n_crabs, data.monkeys, data.n_monkeys);
		
		// Move crabs
		for (Crab *crab = crabs; crab < crabs + n_crabs; crab++) {
			if (crab->path_index >= 0) {
				move(crab, map);
			}
		}
		
		// Shoot crabs
		for (int i = 0; i < data.n_monkeys; i++) {
			shoot(data.monkeys[i], crabs, n_crabs, map); 
		}
		
		// Spawn in a new crab
		crab_timer -= crabs_to_spawn;
		if (!crab_timer) {
			crab_timer = crabTimer();
			crabs_to_spawn = spawnCrab(crabs, n_crabs);
		}
		
		playing = !allCrabsDead(crabs);	
	}
	
	// End of round
	free(crabs);
}


int startGame (char *save) {
	/* if save is NULL creates a new game, else loads the data, and start the game */
	
	GameData data;
	
	if (save == NULL) {
		
		int width = askInt(10, MAX_WIDTH);
		int height = askInt(10, MAX_HEIGHT);
		data.map = generate()
		// Generate, set health, place the first monkey
		
		
		
	} else {
		load(save, &data);
	}
	
	return game(data);
}

int game (GameData data) {
	/**/
	while (data.round_number < data.rounds && data.health > 0) {
		data.round_number++;
		round(data);
		manage(data);
	}
	return score(data);
}


int score (GameData data) {
	/* Gives a score based on the final state of the game */
	int s = 0;
	for (int i = 0; i < data.n_monkeys; i++) {
		s += data.monkeys[i].damage - data.monkeys[i].range;
	}
	s += data.bananas;
	s += data.health * 5;
	return s;
}







