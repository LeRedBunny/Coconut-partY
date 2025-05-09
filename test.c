#include "map.h"
#include "monkey.h"
#include "crabs.h"

#define CRABS 5
#define MONKEYS 2
#define HEIGHT 30
#define WIDTH 30


Vector randomPosition (Map map) {
    Vector position;
    Vector *trees = malloc(sizeof(Vector) * map.width * map.height);
    int i = 0;
    for (int x = 0; x < map.width; x++) {
        for (int y = 0; y < map.height; y++) {
            position = vector(x, y);
            if (getTile(map, position)) {
                trees[i] = position;
                i++;
            }
        }
    }
    return trees[randint(0, i - 1)];
}

int main () {
    Map map = mapInit(WIDTH, HEIGHT, DIR_RIGHT, time(NULL));
    printf("map faite\n");
    Crab *crabs = randomCrabs(CRABS, 1);
    printf("crabes faits\n");
    Monkey monkeys[MONKEYS];
    for (int i = 0; i < MONKEYS; i++) {
        monkeys[i] = newMonkey(randomPosition(map));
    }
    printf("singes faits\n");
    display(map, crabs, CRABS, monkeys, MONKEYS);
    return 0;
}
