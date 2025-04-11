#include "header.h"
#include <math.h>
#include "random.h"



#define START_CRABS 3
#define CRAB_MULTIPLIER 1.2
#define AVG_CRAB_TIMER = 4
#define TIMER_VARIANCE = 3



int crabTimer () {
	/* Returns a new value for the crab timer */
	return AVG_CRAB_TIMER + randint(-TIMER_VARIANCE, TIMER_VARIANCE);
}


void round (Map map, Monkey *monkeys, int n_monkeys, int round_number) {
	/*  */
	
	// Create crabs
	int n_crabs = START_CRABS * pow(CRAB_MULTIPLIER, round_number);
	Crab *crabs = malloc(n_crabs * sizeof(Crab));
	if (crabs == NULL) {exit(1); }
	
	
	// Main round
	int crab_timer = crabTimer();
	while (1) {
		
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
		crab_timer--;
		if (!crab_timer) {
			crab_timer = crabTimer();
			spawnCrab(crabs, n_crabs);
		}
		
		
		
	}
	
	// End of round
	free(crabs);
}






