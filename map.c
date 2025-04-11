#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include "vector.h"


#DEFINE ISLAND_SIZE_RATIO 4.0/5


void display (Map map, Crab *crabs, int n_crabs, Monkey *monkeys, int n_monkeys) {
	/* Displays the current state of the game */
	
	char **screen = malloc(width * height);
	if (screen == NULL) {exit(1); }
	
	for (int y = 0; y < map.height; y++) {
		for (int x = 0; x < map.width; x++) {
			screen[y][x] = map[y][x];
		}
	}
	
	Vector p;
	for (int i = 0; i < map.path_length; i++) {
		p = map.path[i];
		screen[p.y][p.x] = 'p';
	}
	
	for (Crab *crab = crabs; crab < crabs + n_crabs; crab++) {
	
		if (crab->path_index < 0) {
			continue;
		}
		
		p = map.path[crab->path_index];
		screen[p.y][p.x] = 'c';
	}
	
	for (Monkey *monkey = monkeys; monkey < monkeys + n_monkeys; monkey++) {
		p = monkey->position;
		screen[p.y][p.x] = 'm';
	}
	
	
	
	for (int y = 0; y < map.height; y++) {
		for (int x = 0; x < map.width; x++) {
			printf("%c", screen[y][x]);
		}
		printf("\n");
	}
}


Map generate (int width, int height, int seed) {
	/* Creates a new random map with the given width and height, generated with the given seed */
	
	srand(seed);
	
	Map map;
	map.width = width;
	map.height = height;
	map.map = malloc(width * height);
	
	// FAIRE
	
}






