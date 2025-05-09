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
        position = vector(randint(0, map.width - 1), randint(0, map.height - 1));
    } while (getTile(map, position) != 'T');
    return position;
}

int main () {
    Map map = mapInit(WIDTH, HEIGHT, DIR_RIGHT, time(NULL));
    Crab *crabs = randomCrabs(CRABS, 1);
    Monkey monkeys[MONKEYS];
    for (int i = 0; i < MONKEYS; i++) {
        monkeys[i] = newMonkey(randomPosition(map));
    }
    display(map, crabs, CRABS, monkeys, MONKEYS);
    return 0;
}