#ifndef MONKEY_H
#define MONKEY_H


#include <stdio.h>


#include "crabs.h"
#include "header.h"
#include "map.h"
#include "vector.h"





#define RANGE_UPGRADE 1;
#define DAMAGE_UPGRADE 2;









Monkey newMonkey(Vector position){
	/*add a monkey based on a position*/
    Monkey monkey;
    monkey.position = position;
    monkey.range = 1;
    monkey.damage = 2;
    return monkey;
}

void upMonkey(Monkey *monkey){
	/*level up a monkey in parameter*/
    monkey->range += RANGE_UPGRADE;
    monkey->damage += DAMAGE_UPGRADE;
}

int shoot (Monkey monkey, Crab *crabs, int n_crab, Map map){
	/*attacks the oldest crab created, near the monkey*/
	Vector distance;
	int n = n_crab-1;
	int killed = 0;
	while(0<=n){
		if(0 < crabs[n].health){
			distance = subtract(monkey.position, map.path[crabs[n].path_index]);
			if(distance.x * distance.x + distance.y * distance.y <= monkey.range*monkey.range){
				crabs[n].health -= monkey.damage;
				printf("attaque crabe n°%d par singe en position (%d,%d)!\n", n, monkey.position.x, monkey.position.y);// a enlever durant l'intégration dans le code principale
				if( crabs[n].health <= 0){
					kill(crabs + n);
					killed = 1;
				}
				n = -1;
			}
		}
		n--;
	}
	return killed;
}


Monkey *monkeyAt (Vector position, Monkey *monkeys, int n_monkeys) {
	/* Returns a pointer to the monkey at the given position, NULL if there is no monkey */
	for (Monkey *monkey = monkeys; monkey < monkeys +n_monkeys; monkey++) {
		if (monkey->position.x == position.x && monkey->position.y == position.y) {
			return monkey;
		}
	}
	return NULL;
}

#endif
