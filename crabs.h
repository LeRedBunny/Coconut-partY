
#ifndef CRABS_H
#define CRABS_H


#include <stdio.h>
#include <stdlib.h>


#include "header.h"
#include "random.h"
#include "vector.h"

#define SIZE 4

#define AVG_CRAB_TIMER 4
#define TIMER_VARIANCE 2

#define DEATH_INDEX -1
#define BEFORE_SPAWN_INDEX -2

#define COEF_EVOLUTION 0.125

int crabTimer () {
	/* Returns a new value for the crab spawn timer */
	return AVG_CRAB_TIMER + randint(-TIMER_VARIANCE, TIMER_VARIANCE);
}

void kill (Crab *crab){
	crab->path_index = DEATH_INDEX;
}  // if the crab dies, it goes to address -1 on the path to remove it from the map

int move (Crab *crab, Map map){
	if(crab->health > 0){
		crab->path_index += crab->speed;
			if(crab->path_index >= map.path_length){
				kill(crab);
				return 1;
			}
	}
	return 0;
} //If the crab is alive and has not reached the end of the path, it moves forward n squares according to its speed. If it reaches the end of the map, it dies, causing the player to lose 1 life point

int spawnCrab(Crab *tab_crabs, int length_tab_crab){
	for(int i = 0; i < length_tab_crab; i++){
		if(tab_crabs[i].path_index == BEFORE_SPAWN_INDEX){
			tab_crabs[i].path_index = 0;
            return i < length_tab_crab;
		}
	}
	return 0;
} //The first crab in the table of crabs that has a path index equal to -2 is placed in the field. If there are more, the function returns 0

Crab randomCrab (int round_number){
    if (round_number <= 0){
        round_number = 1;
    }else if (round_number > 20){
        round_number = 20;
    }
    
    Crab crab;
    crab.path_index = BEFORE_SPAWN_INDEX;
    crab.health = (round_number * COEF_EVOLUTION) * randint(8,16);
    if ((round_number * COEF_EVOLUTION) * randint(1,11) >10){
        crab.speed =2;
    }else{
        crab.speed =1;
    }
    
    return crab;
}//Depending on the number of rounds played, creates a crab with variable characteristics

Crab *randomCrabs (int n, int round_number){
    Crab* crabs = NULL;
    crabs = malloc(sizeof(Crab) * n);
    if (crabs == NULL){
        printf("Allocation error: Crab *randomCrabs(int n, int round_number)");
        exit(4110);//4110 for AllO-cation
    }
    for(int i = 0; i<n; i++){
        crabs[i] = randomCrab(round_number);
    }
    return crabs;
}//Creates n crabs randomly, depending on the current round, in a list returned

int isDead (Crab crab){
    return crab.path_index == DEATH_INDEX;
}

int allDead (Crab *crabs, int nb_crab){
    for (int i =0; i<nb_crab; i++){
        if (!isDead(crabs[i])){
            return 0;
        }
    }
    return 1;
}//return 1 if all the crabs are dead, 0 if at least 1 remains


int checkKing (Crab *crabs, int n_crabs, int path_length) {
	/* Checks if a crab got to the end, returns 1 if one did and kills it */
	
	for (Crab *crab = crabs; crab < crabs + n_crabs; crab++) {
		if (crab->path_index + 1 == path_length) {
			crab->path_index = DEATH_INDEX;
			return 1;
		}
	}
	return 0;
}


int bananaDrop (Crab crab) {
    return 3 + 2 * crab.speed;
}

#endif
