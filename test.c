#include "map.h"
#include "monkey.h"
#include "game.h"
#include "crabs.h"
#include "player_interaction.h"

#define WIDTH 20
#define HEIGHT 20

int main () {
    
    GameData data;
    data.map = mapInit(WIDTH, HEIGHT, DIR_RIGHT, time(NULL));
    data.monkeys = malloc(sizeof(Monkey) * maxMonkeys(data.map));
    data.n_monkeys = 0;
    data.bananas = 10;
    data.health = 10;
    data.rounds = roundNumber(data.map);
    data.round_number = 0;
    game(data);
    printf("\nDone! 😁");
    return 0;
}
