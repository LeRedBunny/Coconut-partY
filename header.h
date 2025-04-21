


typedef struct {
	int x, y;
} Vector;

typedef struct {
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


	// Map


Map generate (int width, int height, int seed);

void display (Map map, Crab *crabs, int n_crabs, Monkey *monkeys, int n_monkeys);



	// Crabs

int move (Crab *crab, Map map);

void kill (Crab *crab);

Crab randomCrab (int round_number);

Crab *randomCrabs (int n, int round_number);

int isDead (Crab crab);

int allDead (Crab *crabs);


	// Monkeys

void shoot (Monkey monkey, Crab *crabs, int n_crabs);

void placeMonkey (Map map, Monkey *monkeys);


	// Game

void round (Map map, Monkey *monkeys, int n_monkeys, int round_number);

int game (char *save); // save is a string containing the save file path, or NULL if new game

void load (char *save, int *round_number, Map *map, Monkey *monkeys, int &n_monkeys, int &health); // Loads the save file

int roundNumber (Map map); // Calculates the number of rounds to play to win on the given map


	// Other

int askInt (int a, int b); // Asks the player to input an integer in [a; b]

int choice (char **options, int n); // Prints the options and asks the player to choose, returns the chosen index



