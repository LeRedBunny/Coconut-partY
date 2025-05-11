
#ifndef HEADER_H
#define HEADER_H


#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


typedef struct {
	int x, y;
} Vector;

typedef struct {
	int seed;
	int width, height;
	char **map;
	Vector *path;
	int path_length;
} Map;


typedef struct {
	int path_index;
	int health;
	int speed;
} Crab;


typedef struct {
	Vector position;
	int range;
	int damage; 	
} Monkey;


typedef struct {
	int round_number, rounds;
	Map map;
	Monkey *monkeys;
	int n_monkeys, max_monkeys;
	int health;
	int bananas;
} GameData;


typedef struct {
	GameData data;
	char name[20];
} Save;

	// Vector

Vector vector (int x, int y);

Vector add (Vector u, Vector v);

Vector scale (Vector v, int scalar);

Vector subtract (Vector u, Vector v);

float length (Vector v);

float distance (Vector u, Vector v);




	// Map


Map mapInit(int width, int height, Vector direction, int seed);

void mapMakeIsland (Map* map);

Vector mapPositionAway(Map map, Vector direction);

void mapMakePath(Map* map);

void display (Map map, Crab *crabs, int n_crabs, Monkey *monkeys, int n_monkeys);

int roundNumber (Map map); // Calculates the number of rounds to play to win on the given map

char getTile (Map map, Vector position);

int maxMonkeys (Map map);

	// Crabs

int move (Crab *crab, Map map);

void kill (Crab *crab);

Crab randomCrab (int round_number); // Creates a random crab

Crab *randomCrabs (int n, int round_number); // Creates an array of random crabs

int isDead (Crab crab);

int crabTimer ();

int spawnCrab(Crab *tab_crabs, int length_tab_crab);

int allDead (Crab *crabs, int nb_crab);

int checkKing (Crab *crabs, int n_crabs, int path_length);

	// Monkeys

int shoot (Monkey monkey, Crab *crabs, int n_crab, Map map);  	//à changer pour que ça renvoie un bool indiquant si le crabe est tué

Monkey newMonkey (Vector position);

void upMonkey (Monkey *monkey);

Monkey *monkeyAt (Vector position, Monkey *monkeys, int n_monkeys); 


	// Game

void displayGame (GameData data, Crab *crabs, int n_crabs, int crabs_spawned); // Displays the map, health and bananas of the player

int gameRound (GameData *data); // Returns 1 if player won the round, 0 if the player lost

int manage (GameData *data); // Phase of placing new monkeys and upgrading them

int game (GameData data); 

void placeMonkey (GameData *data);

int score (GameData data, int alive); // Gives the player a score based on the final state of the game


        // Save

int saveGame (GameData data);

Save* getSaves ();

Save load (int n);


	// Other

int randint (int a, int b);

int askInt (int a, int b); // Asks the player to input an integer in [a; b]

Vector askPosition (int width, int height);

int choice (char *options[], int n); // Prints the options and asks the player to choose, returns the chosen index

int binaryChoice ();

#endif
