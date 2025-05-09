#include "header.h"
#include "map.h"
#include "monkey.h"
#include "crabs.h"

#define CRABS 5
#define MONKEYS 2
#define HEIGHT 20
#define WIDTH 20


Vector randomPosition (Map map) {
    Vector position;
    do {
        position = vector(randint((MAP_SIZE_X_MAX-map.width)/2, WIDTH-((MAP_SIZE_X_MAX-map.width)/2)), randint((MAP_SIZE_Y_MAX-map.height)/2, MAP_SIZE_Y_MAX-((MAP_SIZE_Y_MAX-map.height)/2)));
    } while (getTile(map, position) == 'w');
    return position;
}



int main () {
    Map map = mapInit(1000, 1000, DIR_RIGHT, time(NULL));
    
    
    Crab *crabs = randomCrabs(CRABS, 1);
    Monkey monkeys[MONKEYS];
    for (int i = 0; i < MONKEYS; i++) {
    	
        monkeys[i] = newMonkey(randomPosition(map));
    }
    display(map, NULL, 0, NULL, 0);
    
    return 0;
}
