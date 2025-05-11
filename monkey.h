
#ifndef MONKEY_H
#define MONKEY_H

#include "crabs.h"
#include "header.h"
#include "map.h"
#include "vector.h"
#include "screen.h"




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
	/*attacks the oldest crab created, near the monkey, and returns the bananas gained */
	float distance;
	int n = n_crab-1;
	int killed = 0;
	while(0<=n){
		if(0 < crabs[n].health){
			distance = length(subtract(monkey.position, map.path[crabs[n].path_index]));
			if(distance <= monkey.range){
				crabs[n].health -= monkey.damage;
				if( crabs[n].health <= 0){
					printf("\nUn singe a tué le crabe n°%d!", 1 + n);
					kill(crabs + n);
					return bananaDrop(*(crabs + n));
				}
				n = -1;
			}
		}
		n--;
	}
	return 0;
}


Monkey *monkeyAt (Vector position, Monkey *monkeys, int n_monkeys) {
	/* Returns a pointer to the monkey at the given position, NULL if there is no monkey */
	for (Monkey *monkey = monkeys; monkey < monkeys + n_monkeys; monkey++) {
		if (monkey->position.x == position.x && monkey->position.y == position.y) {
			return monkey;
		}
	}
	return NULL;
}


void frameAddMonkeys(Screen *screen, Vector shift, Monkey* monkeys, int n_monkeys){
    Vector p;
    if(monkeys != NULL){
		p = monkeys[n_monkeys-1].position;
		screen->frame[p.y + shift.y][p.x + shift.x] = 'm';
    }
    
}

#endif
