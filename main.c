#include "header.h"
#include <math.h>
#include "random.h"
#include "crab.h"
#include "monkey.h"


#define START_CRABS 3
#define CRAB_MULTIPLIER 1.2


void round (Map map, Monkey *monkeys, int n_monkeys, int round_number) {
	/*  */
	
	// Create crabs
	int n_crabs = START_CRABS * pow(CRAB_MULTIPLIER, round_number);
	Crab *crabs = malloc(n_crabs * sizeof(Crab));
	if (crabs == NULL) {exit(1); }
	
	
	// Main round
	int crab_timer = crabTimer();
	int playing = 1;
	int crabs_to_spawn = 1;
	while (playing) {
		
		display(map, crabs, n_crabs, monkeys, n_monkeys);
		
		// Move crabs
		for (Crab *crab = crabs; crab < crabs + n_crabs; crab++) {
			if (crab->path_index >= 0) {
				move(crab, map);
			}
		}
		
		// Shoot crabs
		Monkey monkey;
		for (int i = 0; i < n_monkeys; i++) {
			shoot(monkeys[i], crabs, n_crabs, map); 
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


int game (char *save) {
	
	Map map;	
	Monkey *monkeys;
	int round_number, rounds, n_monkeys, health, bananas;
	
	
	if (save == NULL) {
		
		// Generate, set health, place the first monkey
		
	} else {
		load(save, &round_number, &map, monkeys, &n_monkeys, &health, &bananas); // Maybe don't make a load function and just write everything here ? idk
	}
	
	while (round_number < rounds && health > 0) {
		round_number++;
		round(map, monkeys, n_monkeys, round_number, health);
		// Buy and upgrade monkeys
	}
}




